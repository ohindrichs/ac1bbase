#include "BASEIO.h"
#include "TLorentzVector.h"
#include <iostream>
#include <string>

using namespace std;

class String : public IOString
{
	private:

	public:
		String(const IOString& str);
		void Set(string cppstr);
		string Get();
};

class EventInfo : public IOEventInfo
{
private:

public:
	EventInfo(const IOEventInfo& evinfo);
	void SetHLT(UInt_t num, bool val);
	bool GetHLT(UInt_t num);
};

