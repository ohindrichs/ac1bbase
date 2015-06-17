#include <fstream>
#include <iostream>
#include <sstream>
#include "ConfigParser.h"

string cleanspaces(const string& str)
{
	string nstr;
	for(char l : str)
	{
		if(l != ' ' && l != '\t') nstr.push_back(l);
	}
	return(nstr);
}

ConfigParser::ConfigParser(string filename)
{
	fstream infile(filename, ios_base::in);
	string line;
	while(getline(infile, line))
	{
		size_t commentpos = line.find("#");
		if(commentpos != string::npos)
		{
			line = line.substr(0, commentpos);
		}
		cout << line << endl;
		size_t eqpos = line.find("=");
		if(eqpos == string::npos) {continue;}

		string parameter = line.substr(0, eqpos);
		string val = line.substr(eqpos+1);

		parameter = cleanspaces(parameter);
		val = cleanspaces(val);
		cout << parameter << ":" << val << endl;

		info[parameter] = val;
	}
}

//int ConfigParser::GetInt(string name)
//{
//	int i;
//	istringstream(info[name]) >> i;
//	return(i);
//}
//
//vector<int> ConfigParser::GetVInt(string name)
//{
//	vector<int> res;
//	string buff;
//	for(char l : info[name])
//	{
//		if(l == ',')
//		{
//			res.push_back(0);
//			istringstream(info[name]) >> res.back();
//			buff = "";
//			continue;
//		}
//		buff.push_back(l);
//	}
//	return(res);
//}
//
