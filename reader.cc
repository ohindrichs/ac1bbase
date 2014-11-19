#include "BaseIO.h"
#include "TFile.h"
#include <iostream>

using namespace std;


int main()
{

TFile* infile = TFile::Open("out.root", "read");

BaseIO myio("AnalysisTree", false);

myio.SetFile(infile);

for(UInt_t i = 0 ; i < myio.GetEntries() ; ++i)
{
	myio.GetEntry(i);
	UInt_t nmu = myio.NumMuons();
	cout << nmu << endl;
		
	Muon mu = myio.GetMuon(0);
	cout << mu.px() << " " << mu.py()  << " " << mu.pz() <<  " " << mu.Num_v() << endl;
	Track tr = mu.InnerTrack();
	cout << tr.px() << " " << tr.py()  << " " << tr.pz() <<  " " << tr.Num_HP() << " " << tr.Num_HitPos() << endl;
	mu = myio.GetMuon(1);
	cout << mu.px() << " " << mu.py()  << " " << mu.pz() <<  " " << mu.Num_v() << endl;
	tr = mu.InnerTrack();
	cout << tr.px() << " " << tr.py()  << " " << tr.pz() <<  " " << tr.Num_HP() << " " << tr.Num_HitPos() << endl;
//	Muon mu = myio.GetMuon(0);
//	mu.px(15.);
//	mu.py(13.);
//	mu.pz(14.);
//	mu.v(100., 0);
//	mu.v(100., 1);
//	mu.v(100., 2);
//	Track mt = mu.InnerTrack();
//	mt.px(-8);
//	mt.py(-6);
//	mt.pz(-4);
//	mt.HP(0.5, 0);
//	mt.HP(0.6, 1);
//	mt.HP(0.7, 2);
//	mu = myio.GetMuon(1);
//	mu.px(15.);
//	mu.py(13.);
//	mu.pz(14.);
//	mt = mu.InnerTrack();
//	mt.px(-7);
//	mt.py(-5);
//	mt.pz(-3);
//	mt.HP(-0.5, 0);
//	mt.HP(-0.6, 1);
//	mt.HP(-0.7, 2);
//	mt.HP(-0.8, 3);
//	Pos mpt = mt.HitPos(0);
//	mpt.x(1);
//	mpt.y(2);
//	mpt.z(3);
//	mpt = mt.HitPos(1);
//	mpt.x(1);
//	mpt.y(2);
//	mpt.z(3);
//	mu.v(100., 0);
//	mu.v(100., 1);
//	mu.v(100., 2);
//	Track tr = myio.GetTrack(0);
//	tr.px(14);
//	tr.py(12);
//	tr.pz(13);
//	tr.HP(1.5, 0);
//	tr.HP(1.5, 1);
//	tr.HP(1.5, 2);
//	tr.HP(1.5, 3);
//	tr.HP(1.5, 4);
//
//	myio.Fill();
}
infile->Close();

}
