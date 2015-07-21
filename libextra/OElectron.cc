#include "OElectron.h"
#include "Analyse.h"
#include "SuperCluster.h"
#include "GenBasicParticle.h"
#include "TMath.h"

using namespace TMath;


OElectron::OElectron(IOElectron el) : Electron(el), genp_(0)
{}

//double OElectron::CorPFIsolation2011() const
//{
//	double eta = Abs(SuperCluster(SC()).Eta());
//	double effarea = 0.;
//	effarea = 0.13;
//	if(eta < 1.){ effarea = 0.10;}
//	else if(eta < 1.479){ effarea = 0.12;}
//	else if(eta < 2.){ effarea = 0.085;}
//	else if(eta < 2.2){ effarea = 0.11;}
//	else if(eta < 2.3){ effarea = 0.12;}
//	else if(eta < 2.4){ effarea = 0.12;}
//
//	return((PFR3().Charged() + Max(PFR3().Neutral() + PFR3().Photon() - Max(GLAN->AK5PFRho(), 0.f)*effarea, 0.))/Pt());
//}
//
//double OElectron::CorPFIsolation2012() const
//{
//	double eta = Abs(SuperCluster(SC()).Eta());
//	double effarea = 0.;
//	effarea = 0.14;
//	if(eta < 1.){ effarea = 0.13;}
//	else if(eta < 1.479){ effarea = 0.14;}
//	else if(eta < 2.){ effarea = 0.07;}
//	else if(eta < 2.2){ effarea = 0.09;}
//	else if(eta < 2.3){ effarea = 0.11;}
//	else if(eta < 2.4){ effarea = 0.11;}
//
//	return((PFR3().Charged() + Max(PFR3().Neutral() + PFR3().Photon() - Max(GLAN->AK5PFRho(), 0.f)*effarea, 0.))/Pt());
//}

double OElectron::CorPFIsolation2015() const
{
	double eta = Abs(SuperCluster(SC()).Eta());
	double effarea = 0.;
	effarea = 0.;
	if(eta < 1.3){ effarea = 0.0988;}
	else if(eta < 2.0){ effarea = 0.0572;}
	else if(eta < 2.2){ effarea = 0.0842;}
	else if(eta < 2.5){ effarea = 0.1530;}

	return((PFR3().Charged() + Max(PFR3().Neutral() + PFR3().Photon() - Max(GLAN->AK5PFRho(), 0.f)*effarea, 0.))/Pt());
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
	else if(idtyp == MEDIUM_15)
	{
		if(IsEB())
		{
			if(Abs(DeltaEtaSCTrack()) > 0.008925){return(false);}
			if(Abs(DeltaPhiSCTrack()) > 0.035973){return(false);}
			if(Full5x5SigmaIEtaIEta() > 0.009996){return(false);}
			if(EHCalTowerOverECalD1() + EHCalTowerOverECalD2() > 0.050537){return(false);}
			if(Abs(GSFTrack().Dxy()) > 0.012235){return(false);}
			if(Abs(GSFTrack().Dz()) > 0.042020){return(false);}
			if(Abs((1. - ESCOverETrack())/ECalEnergy()) > 0.091942){return(false);}
			if(HasMatchedConversion()){return(false);}
			if(GSFTrack().NMissingInnerHits() > 1){return(false);}
			if(iso && CorPFIsolation2015() > 0.107587){return(false);}
			return(true);
		}
		if(IsEE())
		{   
			if(Abs(DeltaEtaSCTrack()) > 0.007429){return(false);}
			if(Abs(DeltaPhiSCTrack()) > 0.067879){return(false);}
			if(Full5x5SigmaIEtaIEta() > 0.030135){return(false);}
			if(EHCalTowerOverECalD1() + EHCalTowerOverECalD2() > 0.086782){return(false);}
			if(Abs(GSFTrack().Dxy()) > 0.036719){return(false);}
			if(Abs(GSFTrack().Dz()) > 0.138142){return(false);}
			if(Abs((1. - ESCOverETrack())/ECalEnergy()) > 0.100683){return(false);}
			if(HasMatchedConversion()){return(false);}
			if(GSFTrack().NMissingInnerHits() > 1){return(false);}
			if(iso && CorPFIsolation2015() > 0.113254){return(false);}
			return(true);
		}
	}
	else if(idtyp == LOOSE_15)
	{
		if(IsEB())
		{
			if(Abs(DeltaEtaSCTrack()) > 0.009277){return(false);}
			if(Abs(DeltaPhiSCTrack()) > 0.094739){return(false);}
			if(Full5x5SigmaIEtaIEta() > 0.010331){return(false);}
			if(EHCalTowerOverECalD1() + EHCalTowerOverECalD2() > 0.093068){return(false);}
			if(Abs(GSFTrack().Dxy()) > 0.035904){return(false);}
			if(Abs(GSFTrack().Dz()) > 0.075496){return(false);}
			if(Abs((1. - ESCOverETrack())/ECalEnergy()) > 0.189968){return(false);}
			if(HasMatchedConversion()){return(false);}
			if(GSFTrack().NMissingInnerHits() > 1){return(false);}
			if(iso && CorPFIsolation2015() > 0.130136){return(false);}
			return(true);
		}
		if(IsEE())
		{   
			if(Abs(DeltaEtaSCTrack()) > 0.009833){return(false);}
			if(Abs(DeltaPhiSCTrack()) > 0.149934){return(false);}
			if(Full5x5SigmaIEtaIEta() > 0.031838){return(false);}
			if(EHCalTowerOverECalD1() + EHCalTowerOverECalD2() > 0.115754){return(false);}
			if(Abs(GSFTrack().Dxy()) > 0.099266){return(false);}
			if(Abs(GSFTrack().Dz()) > 0.197897){return(false);}
			if(Abs((1. - ESCOverETrack())/ECalEnergy()) > 0.140662){return(false);}
			if(HasMatchedConversion()){return(false);}
			if(GSFTrack().NMissingInnerHits() > 1){return(false);}
			if(iso && CorPFIsolation2015() > 0.163368){return(false);}
			return(true);
		}
	}
	return(false);
}

void OElectron::SetGen(GenBasicParticle* genp)
{
genp_ = genp;
}

