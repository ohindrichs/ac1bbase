#include "Run.h"
#include "iohelper.h"
#include <algorithm>
#include <regex>

RunInfo::RunInfo(const BASEIORUN::IORunInfo& runinfo) : 
runnumber(runinfo.RunNumber()),
hltnum(runinfo.NumHLTs()),
hlttablesnum(runinfo.HLTPrescaleColumns())
{
	splitstring(BASEIORUN::String(runinfo.HLTNames()).Get(), hltnames);
	splitstring(BASEIORUN::String(runinfo.HLTNamesMuMatched()).Get(), hltmunames);
	splitstring(BASEIORUN::String(runinfo.HLTNamesElMatched()).Get(), hltelnames);
	splitstring(BASEIORUN::String(runinfo.HLTNamesTauMatched()).Get(), hlttaunames);
	splitstring(BASEIORUN::String(runinfo.HLTNamesPhMatched()).Get(), hltphotonnames);
	splitstring(BASEIORUN::String(runinfo.HLTNamesJetMatched()).Get(), hltjetnames);
	hltprescales.resize(NumHLT());
	for(UInt_t i = 0 ; i < NumHLT() ; i++)
	{
		for(UInt_t j = 0 ; j < NumHLTColumns() ; j++)
		{
			hltprescales[i].push_back(runinfo.HLTPrescaleTable(i+NumHLT()*j));
		}
	}
}

vector<string> RunInfo::MatchTriggerNames(string name)
{
	vector<string> result;

	for(UInt_t i = 0 ; i < NumHLT() ; i++)
	{
		if(regex_match(HLTName(i).c_str(), regex(name)))
		{
			result.push_back(HLTName(i));
		}
	}
	return(result);
}

Int_t RunInfo::HLTIndex(string name) const
{
	for(Int_t i = 0 ; i < Int_t(hltnames.size()) ; i++)
	{
		if(hltnames[i] == name) return(i);
	}
	return(-1);
}

void RunInfo::FillOutPut(BASEIORUN::IORunInfo& runinfo) const
{
	runinfo.RunNumber(RunNumber());
	runinfo.NumHLTs(NumHLT());
	runinfo.HLTPrescaleColumns(NumHLTColumns());
	BASEIORUN::String(runinfo.HLTNames()).Set(combinestring(hltnames));
	BASEIORUN::String(runinfo.HLTNamesMuMatched()).Set(combinestring(hltmunames));
	BASEIORUN::String(runinfo.HLTNamesElMatched()).Set(combinestring(hltelnames));
	BASEIORUN::String(runinfo.HLTNamesTauMatched()).Set(combinestring(hlttaunames));
	BASEIORUN::String(runinfo.HLTNamesPhMatched()).Set(combinestring(hltphotonnames));
	BASEIORUN::String(runinfo.HLTNamesJetMatched()).Set(combinestring(hltjetnames));
}
