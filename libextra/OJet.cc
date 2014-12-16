#include "BASEIO.h"
#include "OJet.h"
#include "GenBasicParticle.h"
#include "Analyse.h"

OJet::OJet(IOPFJet jet) : Jet(jet), genp_(0), mcflavour(10000001)
{}

bool OJet::Clean(const vector<OMuon*>& muons, const vector<OElectron*>& electrons, const vector<OPhoton*>& photons) const
{
	for(OMuon* mu : muons)
	{
		if(DeltaR(*mu) < 0.5) return(false);
	}
	for(OElectron* el : electrons)
	{
		if(DeltaR(*el) < 0.5) return(false);
	}
	for(OPhoton* ph : photons)
	{
		if(DeltaR(*ph) < 0.5) return(false);
	}
	return(true);
}

bool OJet::CalculateMCFlavour()
{
	double ptmax = 0.;
	for(UInt_t i = 0 ; i < GLAN->NumAllGenParticles() ; i++)
	{
		GenBasicParticle mp(GLAN->GetAllGenParticle(i));
		if(Abs(mp.PDGID()) > 6 && mp.PDGID() != 21)	continue;
		if(mp.Pt() < 0.01) continue;
		if(DeltaR(mp) > 0.4) continue;
		if(mp.Pt() < ptmax)	continue;
		ptmax = mp.Pt();
		mcflavour = mp.PDGID();
	}
	return true;
}

void OJet::SetGen(GenBasicParticle* genp) {genp_ = genp;}
