#include "Analyse.h"
#include "helper.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <regex>
#include <fstream>
//#include <boost/algorithm/string.hpp>

#include <TH1D.h>
#include <TROOT.h>


using namespace std;

class MyAnalysis : public Analyse
{
	private:
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

	vector<string> filenames = dir_content(localdir);

	MyAnalysis ana;
	TH1D* mc_mu = nullptr;
	TH1D* mc_pu = nullptr;
	TH1D* mc_pup = nullptr;
	TH1D* mc_pum = nullptr;
	for(vector<string>::iterator it = filenames.begin() ; it != filenames.end() ; ++it)
	{
		if(it->find(".root") == string::npos || it->find("LUMI_INFO") != string::npos) {continue;}
		string fullfilename(localdir + "/" + *it);
		ana.AddLumiFile(fullfilename, true);
		TFile* eventsfile = TFile::Open(fullfilename.c_str(), "read");
		TH1D* mu = dynamic_cast<TH1D*>(eventsfile->Get("makeroottree/mu"));
		TH1D* pu = dynamic_cast<TH1D*>(eventsfile->Get("makeroottree/pu"));
		TH1D* pum = dynamic_cast<TH1D*>(eventsfile->Get("makeroottree/pum"));
		TH1D* pup = dynamic_cast<TH1D*>(eventsfile->Get("makeroottree/pup"));
		if(mc_mu == nullptr)
		{
			gROOT->cd();
			mc_mu = new TH1D(*mu);
			mc_pu = new TH1D(*pu);
			mc_pup = new TH1D(*pup);
			mc_pum = new TH1D(*pum);
		}
		else
		{
			mc_mu->Add(mu);
			mc_pu->Add(pu);
			mc_pup->Add(pup);
			mc_pum->Add(pum);
		}
		eventsfile->Close();
	}

	ana.ResetLumiValues();

	TH1D* da_mu = new TH1D(*mc_mu);
	da_mu->Reset();
	if(mc_mu->GetEntries() == 0)
	{
		fstream file("lumi.cvs");
		string line;
		Float_t lumirecorded;
		Float_t avgpu;
		UInt_t run;
		UInt_t block;
		Float_t lumirecordedsum = 0.;
		if(file.is_open())
		{
			while(!file.eof())
			{
				getline(file, line);
				vector<string> data = string_split(line, {"#"});
				if(data.size() == 0) continue;
				vector<std::string> strs = string_split(data[0], {","});
				if(strs.size() != 9) continue;
				string srun = string_split(strs[0], {":"}).front();
				run = stringtotype<UInt_t>(srun);
				string sblock = string_split(strs[1], {":"}).front();
				block = stringtotype<UInt_t>(sblock);
				lumirecorded = stringtotype<Float_t>(strs[6]);
				avgpu = stringtotype<Float_t>(strs[7]);
				if(lumirecorded == 0.)
				{
					cout << "WARNING Lumi value is 0. Run: " << run << ", Block: " << block << endl;
					continue;
				}
				if(ana.SetLumi(run, block, lumirecorded, avgpu) == 1)
				{
					da_mu->Fill(avgpu, lumirecorded);
					lumirecordedsum += lumirecorded;
				}
			}
			file.close();
			cout << "INFO: luminosity is " << lumirecordedsum << "/pb." << endl;
		}
		else
		{
			cout << "WARNING: lumi.cvs could not be opened! No lumi information stored." << endl;
		}
	}
	//ana.PrintLumiOfRuns();
	ana.WriteLumiFile(localdir + "/LUMI_INFO.root", "recreate");
	TFile* lumfile = new TFile((localdir + "/LUMI_INFO.root").c_str(), "update");
	regex myreg("/store/.*");
    smatch base_match;
	regex_search(localdir, base_match, myreg);
	if(base_match.size() == 1)
	{

		string xrdprefix = base_match[0].str();
		xrdprefix = "root://cmseos.fnal.gov/" + xrdprefix + "/";
		cout << "Using: " << xrdprefix << "LUMI_INFO.root"<< endl;
		TNamed* prefixname = new TNamed("fileprefix", xrdprefix.c_str());
		prefixname->Write("fileprefix");
	}
	else
	{
		cout << "WARNING: no xrootd with local file." << endl;
	}
	mc_mu->Write("mc_mu");
	mc_pu->Write("mc_pu");
	mc_pup->Write("mc_pup");
	mc_pum->Write("mc_pum");
	da_mu->Write("da_mu");
 	lumfile->Write();
	lumfile->Close();
}

