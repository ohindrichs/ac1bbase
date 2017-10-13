#include "OElectron.h"
#include "Analyse.h"
#include "SuperCluster.h"
#include "GenBasicParticle.h"
#include "TMath.h"

using namespace TMath;


OElectron::OElectron(IOElectron el) : Electron(el), genp_(nullptr), l1matchp_(nullptr)
{}


double OElectron::CorPFIsolation2015() const
{
	//double eta = Abs(SuperCluster(SC()).Eta());
	double eta = Abs(Eta());
    double effarea = 0.2393;
    if(eta < 1.){ effarea = 0.1703;}
    else if(eta < 1.479){ effarea = 0.1715;}
    else if(eta < 2.){ effarea = 0.1213;}
    else if(eta < 2.2){ effarea = 0.1230;}
    else if(eta < 2.3){ effarea = 0.1635;}
    else if(eta < 2.4){ effarea = 0.1937;}
	return((PFR3().Charged() + Max(PFR3().Neutral() + PFR3().Photon() - GLAN->Rho()*effarea, 0.))/Pt());
	//return((PFR3().Charged()-PFR3NoB().Charged() + Max(PFR3().Neutral()-PFR3NoB().Neutral() + PFR3().Photon()-PFR3NoB().Photon() - GLAN->Rho()*effarea, 0.))/Pt());
}

bool OElectron::Clean() const
{
    TVector3 spike;
    TVector3 test(SuperCluster(SC()).Vect());
    //spike.SetPtEtaPhi(1., -1.76, 1.37);
    //if(spike.DeltaR(test) < 0.05){return(false);}
    //spike.SetPtEtaPhi(1., 2.37, 2.69);
    //if(spike.DeltaR(test) < 0.05){return(false);}

	if(Abs(test.Eta()) > 2.5) return(false);
	if(Abs(test.Eta()) < 1.566 && Abs(test.Eta()) > 1.4442) return(false);

	return(true);
}

bool OElectron::ID(IDS idtyp, bool iso) const
{
	if(!Clean()) return(false);
	if(idtyp == ID_NONE) return(true);
	else if(idtyp == TIGHT_16)
	{
		if(IsEB())
		{
			if(SigmaIEtaIEta() > 0.00998){return(false);}
			if(Abs(DeltaEtaSCTrack()) > 0.00308){return(false);}
			if(Abs(DeltaPhiSCTrack()) > 0.0816){return(false);}
			if(EHCalTowerOverECal() > 0.0414){return(false);}
			if(iso && CorPFIsolation2015() > 0.0588){return(false);}
			if(Abs((1. - ESCOverETrack())/ECalEnergy()) > 0.0129){return(false);}
			if(GSFTrack().NMissingInnerHits() > 1){return(false);}
			if(HasMatchedConversion()){return(false);}
			if(Abs(GSFTrack().Dxy()) > 0.05){return(false);}
			if(Abs(GSFTrack().Dz()) > 0.1){return(false);}
			return(true);
		}
		if(IsEE())
		{   
			if(SigmaIEtaIEta() > 0.0292){return(false);}
			if(Abs(DeltaEtaSCTrack()) > 0.00605){return(false);}
			if(Abs(DeltaPhiSCTrack()) > 0.0394){return(false);}
			if(EHCalTowerOverECal() > 0.0641){return(false);}
			if(iso && CorPFIsolation2015() > 0.0571){return(false);}
			if(Abs((1. - ESCOverETrack())/ECalEnergy()) > 0.0129){return(false);}
			if(GSFTrack().NMissingInnerHits() > 1){return(false);}
			if(HasMatchedConversion()){return(false);}
			if(Abs(GSFTrack().Dxy()) > 0.1){return(false);}
			if(Abs(GSFTrack().Dz()) > 0.2){return(false);}
			return(true);
		}
	}
	else if(idtyp == LOOSE_16)
	{
		if(IsEB())
		{
			if(SigmaIEtaIEta() > 0.011){return(false);}
			if(Abs(DeltaEtaSCTrack()) > 0.00477){return(false);}
			if(Abs(DeltaPhiSCTrack()) > 0.222){return(false);}
			if(EHCalTowerOverECal() > 0.298){return(false);}
			if(iso && CorPFIsolation2015() > 0.0994){return(false);}
			if(Abs((1. - ESCOverETrack())/ECalEnergy()) > 0.241){return(false);}
			if(GSFTrack().NMissingInnerHits() > 1){return(false);}
			if(HasMatchedConversion()){return(false);}
			if(Abs(GSFTrack().Dxy()) > 0.05){return(false);}
			if(Abs(GSFTrack().Dz()) > 0.1){return(false);}
			return(true);
		}
		if(IsEE())
		{   
			if(SigmaIEtaIEta() > 0.0314){return(false);}
			if(Abs(DeltaEtaSCTrack()) > 0.00868){return(false);}
			if(Abs(DeltaPhiSCTrack()) > 0.213){return(false);}
			if(EHCalTowerOverECal() > 0.101){return(false);}
			if(iso && CorPFIsolation2015() > 0.107){return(false);}
			if(Abs((1. - ESCOverETrack())/ECalEnergy()) > 0.14){return(false);}
			if(GSFTrack().NMissingInnerHits() > 1){return(false);}
			if(HasMatchedConversion()){return(false);}
			if(Abs(GSFTrack().Dxy()) > 0.1){return(false);}
			if(Abs(GSFTrack().Dz()) > 0.2){return(false);}
			return(true);
		}
	}
	return(false);
}

void OElectron::SetGen(GenBasicParticle* genp)
{
genp_ = genp;
}


L1Object* OElectron::L1Match()
{
	if(l1matchp_ != nullptr) return l1matchp_;
	double dr = 0.15;
	for(size_t n = 0 ; n < GLAN->NumL1EGammas() ; ++n)
	{
		L1Object l1match(GLAN->GetL1EGamma(n));
		if(DeltaR(l1match) < dr)
		{
			dr = DeltaR(l1match);	
			l1matchp_ = new L1Object(l1match);
		}

	}
	return l1matchp_;
}














