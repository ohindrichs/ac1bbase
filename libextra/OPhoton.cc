#include "OPhoton.h"

OPhoton::OPhoton(Photon ph) : Photon(ph), mygen(0)
{}

double OPhoton::EAcharged() const
{
if(Abs(SCs(0).Eta()) < 1.) return(0.012);
if(Abs(SCs(0).Eta()) < 1.479) return(0.010);
if(Abs(SCs(0).Eta()) < 2.0) return(0.014);
if(Abs(SCs(0).Eta()) < 2.2) return(0.012);
if(Abs(SCs(0).Eta()) < 2.3) return(0.016);
if(Abs(SCs(0).Eta()) < 2.4) return(0.020);
return(0.012);
}

double OPhoton::EAneutral() const
{
if(Abs(SCs(0).Eta()) < 1.) return(0.030);
if(Abs(SCs(0).Eta()) < 1.479) return(0.057);
if(Abs(SCs(0).Eta()) < 2.0) return(0.039);
if(Abs(SCs(0).Eta()) < 2.2) return(0.015);
if(Abs(SCs(0).Eta()) < 2.3) return(0.024);
if(Abs(SCs(0).Eta()) < 2.4) return(0.039);
return(0.072);
}

double OPhoton::EAphoton() const
{
if(Abs(SCs(0).Eta()) < 1.) return(0.148);
if(Abs(SCs(0).Eta()) < 1.479) return(0.130);
if(Abs(SCs(0).Eta()) < 2.0) return(0.112);
if(Abs(SCs(0).Eta()) < 2.2) return(0.216);
if(Abs(SCs(0).Eta()) < 2.3) return(0.262);
if(Abs(SCs(0).Eta()) < 2.4) return(0.260);
return(0.266);
}

Float_t OPhoton::CorIsoPFR3Photon() const
{
	if(IsEB())
	{
		return(Max(IsoPFR3Photon() - GLAN->AK5PFRho()*EAphoton(), 0.) - 0.7 - 0.005*Pt());
	}
	if(IsEE())
	{
		return(Max(IsoPFR3Photon() - GLAN->AK5PFRho()*EAphoton(), 0.) - 1.0 - 0.005*Pt());
	}
	return(10000);
}

Float_t OPhoton::CorIsoPFR3Neutral() const
{
	if(IsEB())
	{
		return(Max(IsoPFR3Neutral() - GLAN->AK5PFRho()*EAneutral(), 0.) - 1.0 - 0.04*Pt());
	}
	if(IsEE())
	{
		return(Max(IsoPFR3Neutral() - GLAN->AK5PFRho()*EAneutral(), 0.) - 1.5 - 0.04*Pt());
	}
	return(10000);
}

Float_t OPhoton::CorIsoPFR3Charged() const
{
	if(IsEB())
	{
		return(Max(IsoPFR3Charged() - GLAN->AK5PFRho()*EAcharged(), 0.) - 1.5);
	}
	if(IsEE())
	{
		return(Max(IsoPFR3Charged() - GLAN->AK5PFRho()*EAcharged(), 0.) - 1.2);
	}
	return(10000.);
}

bool OPhoton::IDEHCalOverECal() const
{
	return(EHCalTowerOverECal() < 0.05);
	//return(EHCalOverECal() < 0.05);
}

bool OPhoton::IDSigmaIEtaIEta() const
{
	if(IsEB())
	{
		return(SigmaIEtaIEta() < 0.011);
	}
	if(IsEE())
	{
		return(SigmaIEtaIEta() < 0.033);
	}
	return(-100000000.);
}

bool OPhoton::IDPhoton() const
{
	return(CorIsoPFR3Photon() < 0.);
}

bool OPhoton::IDNeutral() const
{
	return(CorIsoPFR3Neutral() < 0.);
}

bool OPhoton::IDCharged() const
{
	return(CorIsoPFR3Charged() < 0.);
}

bool OPhoton::Clean() const
{
	if(Abs(SCs(0).Eta()) > 2.5) return(false);
	if(Abs(SCs(0).Eta()) > 1.4442 && Abs(SCs(0).Eta()) < 1.566) return(false);
	//if(R9() > 1.) return(false);
	if(R9() < 0.003) return(false);
	//if(SigmaIEtaIEta() < 0.001) return(false);
	TVector3 spike;
	spike.SetPtEtaPhi(1., -1.76, 1.37);
	if(spike.DeltaR(SCs(0).Vect()) < 0.05){return(false);}
	spike.SetPtEtaPhi(1., 2.37, 2.69);
	if(spike.DeltaR(SCs(0).Vect()) < 0.05){return(false);}
	
	return(true);
}

bool OPhoton::ID(Int_t idtyp) const
{
	if(idtyp == 0) return(true);
	if(idtyp == 1)
	{
		if(!IDEHCalOverECal()) return(false);
		if(HasPromptElectron()) return(false);
		if(!IDSigmaIEtaIEta()) return(false);
		if(!IDNeutral()) return(false);
		if(!IDPhoton()) return(false);
		if(!IDCharged()) return(false);
		return(true);
	}
	if(idtyp == 2)
	{
		if(!IDEHCalOverECal()) return(false);
		if(HasPromptElectron()) return(false);
		if(!IDNeutral()) return(false);
		if(!IDPhoton()) return(false);
		return(true);
	}
	if(idtyp == 3)
	{
		if(!IDEHCalOverECal()) return(false);
		if(HasPromptElectron()) return(false);
		if(!IDSigmaIEtaIEta()) return(false);
		if(!IDNeutral()) return(false);
		if(!IDCharged()) return(false);
		return(true);
	}
	if(idtyp == 4)
	{
		if(!IDEHCalOverECal()) return(false);
		if(HasPromptElectron()) return(false);
		if(!IDNeutral()) return(false);
		if(!IDCharged()) return(false);
		return(true);
	}
	return(false);
}

