#include "iohelper.h"
#include "TFile.h"
#include <iostream>

using namespace std;

IOString::IOString(const String& str) : String(str)
{
}	
void IOString::Set(string cppstr)
{
	for(size_t b = 0 ; b < cppstr.size() ; ++b)
	{
		str(cppstr[b], b);
	}
}
string IOString::Get()
{
	string cppstr(Num_str(), ' ');	
	for(size_t b = 0 ; b < cppstr.size() ; ++b)
	{
		cppstr[b] = str(b);
	}
	return cppstr;
}

