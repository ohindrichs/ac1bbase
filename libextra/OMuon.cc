#include "OMuon.h"
#include "GenBasicParticle.h"
#include "TMath.h"

bool TestMuonInnerTrack(const IOTrack& trk)
{
		if(trk.NPixelHits() <= 0) return(false);
		if(trk.NPixelLayers() + trk.NStripLayers() <= 5) return(false);
		if(TMath::Abs(trk.Dxy()) > 0.2) return(false);
		if(TMath::Abs(trk.Dz()) > 0.5) return(false);
		return(true);
}

OMuon::OMuon(IOMuon mu) : Muon(mu), genp_(0)
{}


bool OMuon::IsGoodSA() const
{
		if(NumValidMuonHits() == 0) return(false);
		return(true);
}

bool OMuon::IsGoodTRK() const
{
	return(TestMuonInnerTrack(InnerTrack(0)));	
	//	if(InnerTrack(0).NPixelHits() <= 0) return(false);
	//	if(InnerTrack(0).NPixelLayers() + InnerTrack(0).NStripLayers() <= 5) return(false);
	//	if(TMath::Abs(InnerTrack(0).Dxy()) > 0.2) return(false);
	//	if(TMath::Abs(InnerTrack(0).Dz()) > 0.5) return(false);
	//	return(true);
}

bool OMuon::IsMatched() const
{
	if(NumValidMuonHits() <= 0) return(false);
	if(ChiQ()/NDOF() > 10.) return(false);
	if(NumMatchedStations() <= 1) return(false);
	if(!IsPF()) return(false);
	return(true);
}

double OMuon::PFIsolationDB() const
{
	return (PFR4().Charged() + Max(PFR4().Neutral() + PFR4().Photon() - 0.5*PFR4().ChargedPU(), 0.))/Pt();
	//return (PFR4().Charged()-PFR4NoB().Charged() + Max(PFR4().Neutral()-PFR4NoB().Neutral() + PFR4().Photon()-PFR4NoB().Photon() - 0.5*(PFR4().ChargedPU()-PFR4NoB().ChargedPU()), 0.))/Pt();
}

bool OMuon::IsISO(IDS idtyp) const
{
	if(idtyp == TIGHT_15)
	{
		//if((DetR3().Track())/Pt() > 0.05) return(false);
		if(PFIsolationDB() > 0.15) return(false);
	}
	else if(idtyp == LOOSE_15)
	{
		//if((DetR3().Track())/Pt() > 0.1) return(false);
		if(PFIsolationDB() > 0.25) return(false);
	}
	return(true);
}

bool OMuon::ID(IDS idtyp, bool iso) const
{
	if(idtyp == ID_NONE) return(true);
	if(idtyp == TIGHT_15)
	{
		if(TMath::Abs(Eta()) > 2.4) return(false);
		if(!IsGlobal()) return(false);
		if(!IsGoodSA()) return(false);
		if(!IsGoodTRK()) return(false);
		if(!IsMatched()) return(false);
		if(iso && !IsISO(TIGHT_15)) return(false);
		return(true);
	}
	return(false);
}

//bool OMuon::ID(Int_t idtyp) const
//{
//	if(idtyp == 0) return(true);
//	if(idtyp == 1)
//	{
//		if(TMath::Abs(Eta()) > 2.4) return(false);
//		if(!IsGlobal()) return(false);
//		if(InnerTrack(0).NPixelHits() <= 0) return(false);
//		if(InnerTrack(0).NPixelLayers() + InnerTrack(0).NStripLayers() <= 5) return(false);
//		if(NumValidMuonHits() <= 0) return(false);
//		if(NumMatchedStations() <= 1) return(false);
//		if(TMath::Abs(InnerTrack(0).Dxy()) > 0.2) return(false);
//		if(TMath::Abs(InnerTrack(0).Dz()) > 0.5) return(false);
//		//if(Pt() > 200.) return(true);	
//		if(ChiQ()/NDOF() > 10.) return(false);
//		//if((PFR4().Charged())/Pt() > 0.1) return(false);
//		if((PFR4().Charged() + PFR4().Neutral() + PFR4().Photon())/Pt() > 0.2) return(false);
//		return(true);
//	}
//	return(false);
//}
//
void OMuon::SetGen(GenBasicParticle* genp) {genp_ = genp;}
