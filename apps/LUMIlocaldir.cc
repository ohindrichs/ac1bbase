#include "Analyse.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <boost/algorithm/string.hpp>

#include <TH1D.h>

#include <sys/types.h>
#include <dirent.h>

using namespace std;

class MyAnalysis : public Analyse
{
	private:
		TH1D* truepileupdist;
		TH1D* vertexdist;
	public:
		MyAnalysis() 
		{
		}
		virtual ~MyAnalysis() {}
		virtual Int_t AnalyseEvent() 
		{
			return(1);
		}
};

int main(int argc, char** argv)
{
	if(argc == 1)
	{
		cerr << "You have to pass a local directory as argument." << endl;
		exit(-1);
	}
	string localdir(argv[1]);

	DIR* dirhandle = opendir(localdir.c_str());

	if(!dirhandle)
	{
		cerr << "Directory " << localdir << " cannot be opened." << endl;
		exit(-1);
	}

	list<string> filenames;
	struct dirent* dirinfo;
	while((dirinfo = readdir(dirhandle)) != 0)
	{
		string filename(dirinfo->d_name);
		if(filename.find(".root") != string::npos && filename.find("LUMI_INFO") == string::npos)
		{
			filenames.push_back(filename);
			cout << filename << endl;
		}
	}

	MyAnalysis ana;
	for(list<string>::iterator it = filenames.begin() ; it != filenames.end() ; ++it)
	{
		ana.AddLumiFile(localdir + "/" + *it, true);
	}

	ana.ResetLumiValues();

	TH1D* muhist = new TH1D("DAmudist", "DAmudist", 200, 0., 100.);
	//if(ana.IsData())
	if(false)
	{
		fstream file("lumi.cvs");
		char line[1000];
		Float_t lumirecorded;
		Float_t avgpu;
		UInt_t run;
		UInt_t block;
		if(file.is_open())
		{
			file.getline(line, 1000);
			while(!file.eof())
			{
				file.getline(line,1000);
				vector<std::string> strs;
				boost::split(strs, line, boost::is_any_of(","));
				if(strs.size() != 8) continue;
				run = atoi(strs[0].c_str());
				vector<std::string> blocks;
				boost::split(blocks, strs[1], boost::is_any_of(":"));
				block = atoi(blocks[0].c_str());
				lumirecorded = atof(strs[6].c_str());
				avgpu = atof(strs[7].c_str());
				if(lumirecorded == 0.)
				{
					cout << "WARNING Lumi value is 0. Run: " << run << ", Block: " << block << endl;
					continue;
				}
				if(ana.SetLumi(run, block, lumirecorded/1000000., avgpu) == 1)
				{
					//muhist->Fill(atof(strs[7].c_str())*766./693.);
					muhist->Fill(avgpu);
				}
			}
			file.close();
		}
		else
		{
			cout << "WARNING: lumi.cvs could not be opened! No lumi information stored." << endl;
		}
	}
	//ana.PrintLumiOfRuns();
	ana.WriteLumiFile(localdir + "/LUMI_INFO.root");
	TFile* lumfile = new TFile((localdir + "/LUMI_INFO.root").c_str(), "update");
	muhist->Write();
 	lumfile->Write();
	lumfile->Close();
}

