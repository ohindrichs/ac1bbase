#include "BASEIO.h"
#include "TFile.h"
#include <iostream>
#include <string>

using namespace std;

class IOString : public String
{
	private:

	public:
		IOString(const String& str);
		void Set(string cppstr);
		string Get();
};
