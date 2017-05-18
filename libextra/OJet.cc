#include "BASEIO.h"
#include "OJet.h"
#include "GenBasicParticle.h"
#include "GenSelectedParticle.h"
#include "GenJet.h"
#include "Analyse.h"

OJet::OJet(IOPFJet jet) : Jet(jet), genp_(0), mcflavour(0), genjet(-2)
{}

bool OJet::IDLeptonVeto() const
{
if(ID() && ElectronEnergy()/e() < 0.9 && MuonEnergy()/e() < 0.8){return true;}

return false;

}

bool OJet::ID() const
{
	if(NumChargedHadrons() + NumNeutralHadrons() + NumPhotons() + NumElectrons() + NumMuons() + NumForwardEMs() + NumForwardHads() <= 1) {return false;}
	if(NeutralHadronEnergy()/e() >= 0.90){return false;}
	if(PhotonEnergy()/e() >= 0.90){return false;}
	if(TMath::Abs(Eta()) < 2.4)
	{
		if(ElectronEnergy()/e() >= 0.99){return false;}
		if(ChargedHadronEnergy()/e() == 0.){return false;}
		if(NumChargedHadrons() + NumElectrons() + NumMuons() <= 0.){return false;}
	}
	return(true);
}

bool OJet::Clean(const vector<OMuon*>& muons, const vector<OElectron*>& electrons, const vector<OPhoton*>& photons, double dr) const
{
	for(OMuon* mu : muons)
	{
		if(DeltaR(*mu) < dr) return(false);
	}
	for(OElectron* el : electrons)
	{
		if(DeltaR(*el) < dr) return(false);
	}
	for(OPhoton* ph : photons)
	{
		if(DeltaR(*ph) < dr) return(false);
	}
	return(true);
}

void OJet::MatchGenJet()
{
	if(genjet != -2) {return;}
	genjet = -1;
	for(UInt_t i = 0 ; i < GLAN->NumIOGenAK4Jets() ; i++)
	{
		GenJet mp(GLAN->GetIOGenAK4Jet(i));
		if(DeltaR(mp) > 0.4) continue;
		if(genjet != -1 && Abs(Pt() - GenJet(GLAN->GetIOGenAK4Jet(genjet)).Pt()) < Abs(Pt() - mp.Pt())) continue;
		genjet = i;
	}
}

void OJet::CalculateMCFlavour()
{
	if(mcflavour != 0) {return;}
	mcflavour = 10000000;
	mcpt = 0.;
	double ptmax = 0.;
	if(GLAN->NumAllGenParticles() != 0)
	{
		for(UInt_t i = 0 ; i < GLAN->NumAllGenParticles() ; i++)
		{
			GenBasicParticle mp(GLAN->GetAllGenParticle(i));
			if(Abs(mp.PDGID()) > 6 && mp.PDGID() != 21)	continue;
			if(mp.Pt() < 0.01) continue;
			if(DeltaR(mp) > 0.4) continue;
			if(mp.Pt() < ptmax)	continue;
			ptmax = mp.Pt();
			mcflavour = mp.PDGID();
			mcpt = mp.Pt();
		}
	}
	else if(GLAN->NumSelectedGenParticles() != 0)
	{
		for(UInt_t i = 0 ; i < GLAN->NumSelectedGenParticles() ; i++)
		{
			GenSelectedParticle mp(GLAN->GetSelectedGenParticle(i));
			if(Abs(mp.PDGID()) > 6 && mp.PDGID() != 21)	continue;
			if(mp.Pt() < 0.01) continue;
			if(DeltaR(mp) > 0.4) continue;
			if(mp.Pt() < ptmax)	continue;
			ptmax = mp.Pt();
			mcflavour = mp.PDGID();
			mcpt = mp.Pt();
		}
	}
}


pair<double, double> OJet::GetMainAxis()
{
	double p = (MPhiPhi()+MEtaEta())/2.;
	double q = MPhiPhi()*MEtaEta()-MPhiEta()*MPhiEta();
	double la = p + Sqrt(p*p - q);
	double lb = p - Sqrt(p*p - q);
	return pair<double, double>(la, lb);
}


void OJet::SetGen(GenBasicParticle* genp) {genp_ = genp;}
