#!/bin/python2
import sys, os

def linesplit(line):
	line = line.strip()
	vec = line.split(':', 1)
	vec[0] = vec[0].strip() 
	vec[1] = vec[1].strip() 
	return vec

def cleandatamembers(string):
	vec = string.split(',')
	vec = [v.strip() for v in vec if '[' not in v]
	return vec

def cleandatavecs(string):
	vec = string.split(',')
	vec = [v.strip() for v in vec if '[' in v]
	res = []
	for d in vec:
		temp = d.split('[')
		name = temp[0]
		length = -1
		if temp[1] != ']':
			length = int(temp[1][:-1])
		res.append([name, length])
	return res

class CLASS:
	TYPS = {'D' : 'Double_t', 'F' : 'Float_t' , 'I' : 'Int_t', 'i' : 'UInt_t', 'L' : 'Long64_t', 'l' : 'ULong64_t', 'B' : 'Char_t', 'b': 'UChar_t'}
	def __init__(self, name, config):
		print name
		print config
		self.sizehint = 1
		self.ExternInit = ''
		self.ClassDes = ''
		self.datamember = {}
		self.datavecs = {}
		self.vectorclass = False
		self.name = name
		if '[' in name:
			temp = name.split('[')
			print temp
			self.name = temp[0]
			self.sizehint = int(temp[1][:-1])
		for line in config:
			info = linesplit(line)
			if info[0] == 'BeginClass':
				vinfo = info[1].split(':')
			#	if len(vinfo) == 2:
			#		self.ClassDes = vinfo[1].strip()			
				continue
			#if info[0] == 'ExternInit':
			#	self.ExternInit += info[1]
			#	continue
			for TYP in CLASS.TYPS:
				if info[0] == TYP:
					if TYP in self.datamember:
						self.datamember[TYP] += cleandatamembers(info[1])
					else:
						self.datamember[TYP] = cleandatamembers(info[1])
					if TYP in self.datavecs:
						self.datavecs[TYP] += cleandatavecs(info[1])
					else:
						self.datavecs[TYP] = cleandatavecs(info[1])
					continue
			if info[0].startswith('MemberClass'):
				TYP = info[0].split('MemberClass')[1].strip()
				if TYP in self.datamember:
					self.datamember[TYP] += cleandatamembers(info[1])
				else:
					self.datamember[TYP] = cleandatamembers(info[1])
				if TYP in self.datavecs:
					self.datavecs[TYP] += cleandatavecs(info[1])
				else:
					self.datavecs[TYP] = cleandatavecs(info[1])
				continue
		print self.ExternInit
		print self.ClassDes
		print self.datamember
		print self.datavecs

	def writeclassdef(self):
		classdef = ''
		classdef += '#ifndef CLASS_' + self.name.upper() + '\n'		
		classdef += '#define CLASS_' + self.name.upper() + '\n'		
		classdef += '#include "Data_' + self.name + '.h"\n'		
		for typ, des in self.datamember.iteritems():
			if typ not in CLASS.TYPS:
				classdef += '#include "' + typ + '.h"\n'		
		classdef += 'class BaseIO;\n'		
		classdef +=  'class ' + self.name
		if len(self.ClassDes) != 0:
			classdef += ' : ' + self.ClassDes
		
		classdef += '\n {\n'
		classdef += '\tprivate:\n'
		classdef += '\t\tUInt_t number_;\n'
		classdef += '\t\tData_' + self.name + '* data_;\n'
		
		classdef += '\tpublic:\n'
		
		classdef += '\t\t'+ self.name + '() = delete;\n'
		classdef += '\t\t'+ self.name + '(Data_' + self.name + '* data, UInt_t number);\n'
		for typ, des in self.datamember.iteritems():
			if typ in CLASS.TYPS:
				typ = CLASS.TYPS[typ]
			for mem in des:
				classdef += '\t\t' + typ + ' ' + mem + '() const;\n'
		for typ, des in self.datavecs.iteritems():
			if typ in CLASS.TYPS:
				typ = CLASS.TYPS[typ]
			for mem in des:
				classdef += '\t\t' + typ + ' ' + mem[0] + '(UInt_t n) const;\n'
				classdef += '\t\t' + 'UInt_t' + ' Num_' + mem[0] + '() const;\n'

		classdef += ' };\n'
		classdef += '#endif\n'		
		print classdef
		return classdef

	def writeclasscode(self):
		classcode = ''
		classcode += '#include "BaseIO.h"\n'		
		classcode += '#include "' + self.name + '.h"\n'		
		classcode += self.name+'::'+self.name + '(Data_' + self.name + '* data, UInt_t number) : \nnumber_(number),\ndata_(data)\n'
		classcode += '{\n'
		
		classcode += '}\n\n'
		
		for typ, des in self.datamember.iteritems():
			if typ in CLASS.TYPS:
				typ = CLASS.TYPS[typ]
				for mem in des:
					classcode += typ + ' ' + self.name + '::' + mem + '() const\n'
					classcode += '{\n'
					classcode += 'return data_->' + mem +'_[number_];\n' 
					classcode += '}\n\n'
			else:
				for mem in des:
					classcode += typ + ' ' + self.name + '::' + mem + '() const\n'
					classcode += '{\n'
					classcode += 'return '+typ+'(&(data_->' + mem +'_), number_);\n' 
					classcode += '}\n\n'

		for typ, des in self.datavecs.iteritems():
			if typ in CLASS.TYPS:
				typ = CLASS.TYPS[typ]
				for mem in des:
					classcode += 'UInt_t ' + self.name + '::Num_' + mem[0] + '() const\n'
					classcode += '{\n'
					classcode += 'return number_ == 0 ? data_->' + mem[0] +'_num_[number_] : data_->' + mem[0] +'_num_[number_] - data_->' + mem[0] +'_num_[number_-1];\n' 
					classcode += '}\n\n'
					classcode += typ + ' ' + self.name + '::' +  mem[0] + '(UInt_t n) const\n'
					classcode += '{\n'
					classcode += 'return number_ == 0 ? data_->' + mem[0] +'_[n] : data_->' + mem[0] +'_[data_->' + mem[0] +'_num_[number_-1]  + n];\n' 
					classcode += '}\n\n'
			else:
				for mem in des:
					classcode += 'UInt_t ' +self.name +'::Num_' + mem[0] + '() const\n'
					classcode += '{\n'
					classcode += 'return number_ == 0 ? data_->' + mem[0] +'_num_[number_] : data_->' + mem[0] +'_num_[number_] - data_->' + mem[0] +'_num_[number_-1];\n' 
					classcode += '}\n\n'
					classcode += typ + ' ' + self.name + '::' + mem[0] + '(UInt_t n) const\n'
					classcode += '{\n'
					classcode += 'return number_ == 0 ? '+typ+'(&(data_->' + mem[0] +'_), n) : '+typ+'(&(data_->' + mem[0] +'_), data_->' + mem[0] + '_num_[number_-1]  + n);\n' 
					classcode += '}\n\n'
				
		print classcode
		return classcode

	def writedataclassdef(self):
		classdef = ''
		classdef += '#ifndef CLASS_DATA_' + self.name.upper() + '\n'		
		classdef += '#define CLASS_DATA_' + self.name.upper() + '\n'		
		classdef += '#include <string>\n'		
		classdef += '#include "TTree.h"\n'		
		for typ, des in self.datamember.iteritems():
			if typ not in CLASS.TYPS:
				classdef += '#include "Data_' + typ + '.h"\n'		

		classdef +=  'class ' + 'Data_' + self.name
		classdef += '\n {\n'
		classdef += '\tfriend class ' + self.name +';\n'
		classdef += '\tfriend class BaseIO;\n'
		classdef += '\tprivate:\n'
		classdef += '\t\tUInt_t size_;\n'
		classdef += '\t\tstd::string prefix_;\n'
		classdef += '\t\t' + 'UInt_t count_;\n'
		for typ, des in self.datamember.iteritems():
			if typ in CLASS.TYPS:
				typ = CLASS.TYPS[typ]
				for mem in des:
					classdef += '\t\t' + typ + '* ' + mem + '_;\n'
			else:
				typ = 'Data_' + typ
				for mem in des:
					classdef += '\t\t' + typ + ' ' + mem + '_;\n'
		for typ, des in self.datavecs.iteritems():
			if typ in CLASS.TYPS:
				typ = CLASS.TYPS[typ]
				for mem in des:
					classdef += '\t\t' + 'UInt_t '+mem[0]+'_count_;\n'
					classdef += '\t\t' + 'UInt_t*' + ' ' + mem[0] + '_num_;\n'
					classdef += '\t\t' + typ + '* ' + mem[0] + '_;\n'
			else:
				typ = 'Data_' + typ
				for mem in des:
					classdef += '\t\t' + 'UInt_t*' + ' ' + mem[0] + '_num_;\n'
					classdef += '\t\t' + typ + ' ' + mem[0] + '_' + ';\n'
		classdef += '\tpublic:\n'
		classdef += '\t\t' + 'Data_' + self.name + '(UInt_t size, std::string prefix);\n'
		classdef += '\t\t' + '~Data_' + self.name + '();\n'
		classdef += '\t\tvoid SetUpWrite(TTree* tree);\n'
		classdef += '\t\tvoid SetUpRead(TTree* tree);\n'
		
		classdef += ' };\n'
		classdef += '#endif\n'		
		print classdef
		return classdef

	def writedataclasscode(self):
		#constructor
		classcode = ''
		classcode += '#include "Data_' + self.name + '.h"\n'
		classcode += '#include "TTree.h"\n'

		classcode += 'Data_'+self.name+'::Data_'+self.name + '(UInt_t size, std::string prefix = "") : \nsize_(size),\nprefix_(prefix)\n'
		for typ, des in self.datamember.iteritems():
			if typ not in CLASS.TYPS:
				for mem in des:
					classcode += ', ' +  mem + '_(size_, prefix_ + "_'+mem+'")\n'
		for typ, des in self.datavecs.iteritems():
			if typ not in CLASS.TYPS:
				for mem in des:
					classcode += ', ' +  mem[0] + '_(size_*'+str(mem[1])+', prefix_ + "_'+mem[0]+'")\n'
		classcode += '{\n'
		for typ, des in self.datamember.iteritems():
			if typ in CLASS.TYPS:
				ntyp = CLASS.TYPS[typ]
				for mem in des:
					classcode += '\t' + mem + '_ = new ' + ntyp + '[size_];\n'
		for typ, des in self.datavecs.iteritems():
			if typ in CLASS.TYPS:
				ntyp = CLASS.TYPS[typ]
				for mem in des:
					classcode += '\t' + mem[0] + '_num_ = new UInt_t[size_];\n'
					classcode += '\t' + mem[0] + '_ = new ' + ntyp + '[size_*'+str(mem[1])+'];\n'
		for typ, des in self.datavecs.iteritems():
			if typ not in CLASS.TYPS:
				for mem in des:
					classcode += '\t' + mem[0] + '_num_ = new UInt_t[size_];\n'
		classcode += '}\n\n'
		#destructor
		classcode += 'Data_'+self.name+'::~Data_'+self.name + '()\n'
		classcode += '{\n'
		for typ, des in self.datamember.iteritems():
			if typ in CLASS.TYPS:
				ntyp = CLASS.TYPS[typ]
				for mem in des:
					classcode += '\tdelete[] ' + mem + '_;\n'
		classcode += '}\n\n'
		#SetUp Tree Writing
		classcode += 'void Data_'+self.name+'::SetUpWrite(TTree* tree)\n'
		classcode += '{\n'
		classcode += '\ttree->Branch((prefix_ + "_count").c_str(), &count_, (prefix_ + "_count/i").c_str());\n'
		for typ, des in self.datamember.iteritems():
			if typ in CLASS.TYPS:
				ntyp = CLASS.TYPS[typ]
				for mem in des:
					classcode += '\ttree->Branch((prefix_ + "_' +mem+'").c_str(), ' + mem + '_, (prefix_ + "_' + mem + '[" + prefix_ + "_count]/'+typ+ '").c_str());\n'
		for typ, des in self.datavecs.iteritems():
			if typ in CLASS.TYPS:
				ntyp = CLASS.TYPS[typ]
				for mem in des:
					classcode += '\ttree->Branch((prefix_ + "_' +mem[0]+'_count").c_str(), &' + mem[0] + '_count_, (prefix_ + "_' + mem[0] + '_count/i").c_str());\n'
					classcode += '\ttree->Branch((prefix_ + "_' +mem[0]+'_num").c_str(), ' + mem[0] + '_num_, (prefix_ + "_' + mem[0] + '_num[" + prefix_ + "_count]/i").c_str());\n'
					classcode += '\ttree->Branch((prefix_ + "_' +mem[0]+'").c_str(), ' + mem[0] + '_, (prefix_ + "_' + mem[0] + '[" + prefix_ + "_' +mem[0]+'_count]/'+typ+ '").c_str());\n'
		for typ, des in self.datavecs.iteritems():
			if typ not in CLASS.TYPS:
				for mem in des:
					classcode += '\ttree->Branch((prefix_ + "_' +mem[0]+'_num").c_str(), ' + mem[0] + '_num_, (prefix_ + "_' + mem[0] + '_num[" + prefix_ + "_count]/i").c_str());\n'
					classcode += '\t' + mem[0] +'_.SetUpWrite(tree);\n'
					
		classcode += '}\n\n'
		#SetUp Tree Reading
		classcode += 'void Data_'+self.name+'::SetUpRead(TTree* tree)\n'
		classcode += '{\n'
		classcode += '\ttree->SetBranchAddress((prefix_ + "_count").c_str(), &count_);\n'
		for typ, des in self.datamember.iteritems():
			if typ in CLASS.TYPS:
				ntyp = CLASS.TYPS[typ]
				for mem in des:
					classcode += '\ttree->SetBranchAddress((prefix_ + "_' +mem+'").c_str(), ' + mem + '_);\n'
		for typ, des in self.datavecs.iteritems():
			if typ in CLASS.TYPS:
				ntyp = CLASS.TYPS[typ]
				for mem in des:
					classcode += '\ttree->SetBranchAddress((prefix_ + "_' +mem[0]+'_count").c_str(), &' + mem[0] + '_count_);\n'
					classcode += '\ttree->SetBranchAddress((prefix_ + "_' +mem[0]+'_num").c_str(), ' + mem[0] + '_num_);\n'
					classcode += '\ttree->SetBranchAddress((prefix_ + "_' +mem[0]+'").c_str(), ' + mem[0] + '_);\n'
		for typ, des in self.datavecs.iteritems():
			if typ not in CLASS.TYPS:
				for mem in des:
					classcode += '\ttree->Branch((prefix_ + "_' +mem[0]+'_num").c_str(), ' + mem[0] + '_num_);\n'
					classcode += '\t' + mem[0] +'_.SetUpRead(tree);\n'
		classcode += '}\n\n'

		print classcode
		return classcode

configfile = sys.argv[1]

classes = {}

configf = open(configfile)

classname = ''
classconfig = []
for l in configf:
	l=l.strip()
	if l.startswith('BeginClass'):
		classconfig = [l]
		l = l.split(':', 1)[1]
		print l
		l=l.strip()
		print l
		classname = l.split(' ')[0]
		continue
	if l.startswith('EndClass'):
		classes[classname] = CLASS(classname, classconfig)
		continue
	classconfig.append(l)


directory = 'BaseIO'

for c in classes:
	fclass = open(directory + '/' + classes[c].name + '.h', 'w')
	fclass.write(classes[c].writeclassdef())
	fclass.close()
	fclass = open(directory + '/' + classes[c].name + '.cc', 'w')
	fclass.write(classes[c].writeclasscode())
	fclass.close()
	fclass = open(directory + '/Data_' + classes[c].name + '.h', 'w')
	fclass.write(classes[c].writedataclassdef())
	fclass.close()
	fclass = open(directory + '/Data_' + classes[c].name + '.cc', 'w')
	fclass.write(classes[c].writedataclasscode())
	fclass.close()

classdef = ''
classdef += '#ifndef CLASS_BASEIO\n'	
classdef += '#define CLASS_BASEIO\n'
classdef += '#include "TTree.h"\n'
classdef += '#include <string>\n'
for n,c in classes.iteritems():
	if c.sizehint != 0:
		classdef += '#include "' + c.name + '.h"\n'	
classdef += 'class BaseIO\n'	
classdef += '{\n'	
for n,c in classes.iteritems():
	if c.sizehint != 0:
		classdef += '\tfriend class ' + c.name + ';\n' 	
classdef += '\tprivate:\n'	
classdef += '\t\tenum Mode {WRITE, READ};\n'	
for n,c in classes.iteritems():
	if c.sizehint != 0:
		classdef += '\t\tData_' + c.name + ' ' + c.name + '_container_;\n' 	
classdef += '\t\tTTree* tree_;\n'	
classdef += '\tpublic:\n'
classdef += '\t\tBaseIO(std::string treename, Mode m);\n'
for n,c in classes.iteritems():
	if c.sizehint != 0:
		classdef += '\t\tUInt_t Num' + c.name + 's();\n' 	
		classdef += '\t\t'+c.name+' Get' + c.name + '(UInt_t n);\n' 	
classdef += '};\n'	
classdef += '#endif\n'

classcode = ''
classcode += '#include "BaseIO.h"\n'
classcode += 'BaseIO::BaseIO(std::string treename, Mode m) : \n'
for n,c in classes.iteritems():
	if c.sizehint != 0:
		classcode += c.name + '_container_(' + str(c.sizehint) + ', "' + c.name +'"),\n' 	
classcode += 'tree_(new TTree(treename.c_str(), treename.c_str(), 1))\n'
classcode += '{\n'
classcode += '\tif(m == WRITE)\n'
classcode += '\t{\n'
for n,c in classes.iteritems():
	if c.sizehint != 0:
		classcode += '\t\t' + c.name + '_container_.SetUpWrite(tree_);\n' 	
classcode += '\t}\n'
classcode += '\tif(m == READ)\n'
classcode += '\t{\n'
for n,c in classes.iteritems():
	if c.sizehint != 0:
		classcode += '\t\t' + c.name + '_container_.SetUpRead(tree_);\n' 	
classcode += '\t}\n'
classcode += '}\n\n'
for n,c in classes.iteritems():
	if c.sizehint != 0:
		classcode += 'UInt_t BaseIO::Num' + c.name + 's()\n' 	
		classcode += '{\n'
		classcode += '\treturn ' + c.name + '_container_.count_;\n'
		classcode += '}\n'
		classcode += c.name+' BaseIO::Get' + c.name + '(UInt_t n)\n' 	
		classcode += '{\n'
		classcode += '\treturn ' + c.name + '(&' + c.name + '_container_, n);\n'
		classcode += '}\n'
classcode += ''
classcode += ''
classcode += ''

print classdef
print classcode
		
fclass = open(directory + '/BaseIO.cc', 'w')
fclass.write(classcode)
fclass.close()

fclass = open(directory + '/BaseIO.h', 'w')
fclass.write(classdef)
fclass.close()


