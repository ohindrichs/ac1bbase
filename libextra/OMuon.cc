#include "OMuon.h"
#include "GenBasicParticle.h"
#include "TMath.h"

OMuon::OMuon(IOMuon mu) : Muon(mu), genp_(0)
{}


bool OMuon::ID(Int_t idtyp) const
{
	if(idtyp == 0) return(true);
	if(idtyp == 1)
	{
		if(TMath::Abs(Eta()) > 2.4) return(false);
		if(!IsGlobal()) return(false);
		if(InnerTrack(0).NPixelHits() <= 0) return(false);
		if(InnerTrack(0).NPixelLayers() + InnerTrack(0).NStripLayers() <= 5) return(false);
		if(NumValidMuonHits() <= 0) return(false);
		if(NumMatchedStations() <= 1) return(false);
		if(TMath::Abs(InnerTrack(0).Dxy()) > 0.2) return(false);
		if(TMath::Abs(InnerTrack(0).Dz()) > 0.5) return(false);
		//if(Pt() > 200.) return(true);	
		if(ChiQ()/NDOF() > 10.) return(false);
		//if((PFR4().Charged())/Pt() > 0.1) return(false);
		if((PFR4().Charged() + PFR4().Neutral() + PFR4().Photon())/Pt() > 0.2) return(false);
		return(true);
	}
	return(false);
}

void OMuon::SetGen(GenBasicParticle* genp) {genp_ = genp;}
