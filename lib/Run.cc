#include "Run.h"
#include "iohelper.h"
#include <algorithm>
#include <regex>

RunInfo::RunInfo(const BASEIORUN::IORunInfo& runinfo) : 
runnumber(runinfo.RunNumber()),
hltnum(runinfo.Num_TriggerPS()),
hlttablesnum(runinfo.TriggerPS(0).Num_PS())
{
	splitstring(BASEIORUN::String(runinfo.HLTNames()).Get(), hltnames);
	splitstring(BASEIORUN::String(runinfo.L1Names()).Get(), l1names);
	splitstring(BASEIORUN::String(runinfo.HLTNamesMuMatched()).Get(), hltmunames);
	splitstring(BASEIORUN::String(runinfo.HLTNamesElMatched()).Get(), hltelnames);
	splitstring(BASEIORUN::String(runinfo.HLTNamesTauMatched()).Get(), hlttaunames);
	splitstring(BASEIORUN::String(runinfo.HLTNamesPhMatched()).Get(), hltphotonnames);
	splitstring(BASEIORUN::String(runinfo.HLTNamesJetMatched()).Get(), hltjetnames);
	hltprescales.resize(hltnum);
	l1seeds.resize(hltnum);
	for(UInt_t i = 0 ; i < NumHLT() ; i++)
	{
		BASEIORUN::PrescaleRow psrow(runinfo.TriggerPS(i));
		for(UInt_t j = 0 ; j < NumHLTColumns() ; j++)
		{
			hltprescales[i].push_back(psrow.PS(j));
		}
		BASEIORUN::L1SeedInfo l1s(runinfo.L1Seed(i));
		for(UInt_t j = 0 ; j < l1s.Num_Seed() ; j++)
		{
			l1seeds[i].push_back(l1s.Seed(j));
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

Int_t RunInfo::L1Index(string name) const
{
	for(Int_t i = 0 ; i < Int_t(l1names.size()) ; i++)
	{
		if(l1names[i] == name) return(i);
	}
	return(-1);
}

Int_t RunInfo::HLTPrescale(UInt_t trigger, UInt_t table) const 
{
	if(trigger < NumHLT() && table < NumHLTColumns())
	{
		return(hltprescales[trigger][table]);
	}
	else
	{
		return(1);
	}
}



void RunInfo::FillOutPut(BASEIORUN::IORunInfo& runinfo) const
{
	runinfo.RunNumber(RunNumber());
	BASEIORUN::String(runinfo.HLTNames()).Set(combinestring(hltnames));
	BASEIORUN::String(runinfo.L1Names()).Set(combinestring(l1names));
	BASEIORUN::String(runinfo.HLTNamesMuMatched()).Set(combinestring(hltmunames));
	BASEIORUN::String(runinfo.HLTNamesElMatched()).Set(combinestring(hltelnames));
	BASEIORUN::String(runinfo.HLTNamesTauMatched()).Set(combinestring(hlttaunames));
	BASEIORUN::String(runinfo.HLTNamesPhMatched()).Set(combinestring(hltphotonnames));
	BASEIORUN::String(runinfo.HLTNamesJetMatched()).Set(combinestring(hltjetnames));
	for(UInt_t i = 0 ; i < NumHLT() ; i++)
	{
		BASEIORUN::PrescaleRow psrow(runinfo.TriggerPS(i));
		for(UInt_t j = 0 ; j < NumHLTColumns() ; j++)
		{
			psrow.PS(hltprescales[i][j], j);
		}
		BASEIORUN::L1SeedInfo l1s(runinfo.L1Seed(i));
		for(UInt_t j = 0 ; j < l1seeds[i].size() ; j++)
		{
			l1s.Seed(l1seeds[i][j], j);
		}
	}
}
