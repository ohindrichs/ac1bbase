#include "BaseIO.h"
#include "TFile.h"

using namespace std;


int main()
{

TFile* outfile = TFile::Open("out.root", "recreate");

BaseIO myio("AnalysisTree", true);

myio.SetFile(outfile);

for(int i = 0 ; i < 100 ; ++i)
{
	Muon mu = myio.GetMuon(0);
	mu.px(15.);
	mu.py(13.);
	mu.pz(14.);
	mu.v(100., 0);
	mu.v(100., 1);
	mu.v(100., 2);
	Track mt = mu.InnerTrack();
	mt.px(15.5);
	mt.py(13.4);
	mt.pz(14.2);
	mt.HP(0.5, 0);
	mt.HP(0.6, 1);
	mt.HP(0.7, 2);
	mu = myio.GetMuon(1);
	mu.px(15.);
	mu.py(13.);
	mu.pz(14.);
	mt = mu.InnerTrack();
	mt.px(15.5);
	mt.py(13.4);
	mt.pz(14.2);
	mt.HP(-0.5, 0);
	mt.HP(-0.6, 1);
	mt.HP(-0.7, 2);
	mt.HP(-0.8, 3);
	Pos mpt = mt.HitPos(0);
	mpt.x(1);
	mpt.y(2);
	mpt.z(3);
	mpt = mt.HitPos(1);
	mpt.x(1);
	mpt.y(2);
	mpt.z(3);
	mu.v(100., 0);
	mu.v(100., 1);
	mu.v(100., 2);
	Track tr = myio.GetTrack(0);
	tr.px(14);
	tr.py(12);
	tr.pz(13);
	tr.HP(1.5, 0);
	tr.HP(1.5, 1);
	tr.HP(1.5, 2);
	tr.HP(1.5, 3);
	tr.HP(1.5, 4);

	myio.Fill();
}
outfile->Write();
outfile->Close();

}
