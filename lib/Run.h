#ifndef CRUN
#define CRUN

#include "BASEIORUN.h"
#include <string>
#include <vector>

using namespace std;

class RunInfo
{
	private:
		UInt_t runnumber;
		vector<string> hltnames;
		Int_t hltnum;
		Int_t hlttablesnum;
		vector<vector<UInt_t> > hltprescales;
		vector<string> hltmunames;
		vector<string> hltelnames;
		vector<string> hltphotonnames;
		vector<string> hlttaunames;
		vector<string> hltjetnames;
	public:
		RunInfo() : runnumber(0) {}
		RunInfo(const BASEIORUN::IORunInfo& runinfo);
		UInt_t RunNumber() const {return(runnumber);}
		UInt_t NumHLTColumns() const {return(hlttablesnum);} 
		UInt_t NumHLT() const {return(hltnum);}
		const vector<string>& HLTAllNames() const {return(hltnames);}
		const vector<string>& HLTMuonAllNames() const {return(hltmunames);}
		const vector<string>& HLTElectronAllNames() const {return(hltelnames);}
		const vector<string>& HLTTauAllNames() const {return(hltphotonnames);}
		const vector<string>& HLTPhotonAllNames() const {return(hlttaunames);}
		const vector<string>& HLTJetAllNames() const {return(hltjetnames);}
		UInt_t HLTPrescale(UInt_t trigger, UInt_t table) const {if(trigger < NumHLT() && table < NumHLTColumns()){return(hltprescales[trigger][table]);}else{return(1);}}
		string HLTName(UInt_t trigger) const {return(hltnames[trigger]);}
		vector<string> MatchTriggerNames(string name);
		Int_t HLTIndex(string name) const;
		void FillOutPut(BASEIORUN::IORunInfo& runinfo) const;
};

#endif
