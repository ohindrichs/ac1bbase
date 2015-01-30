#include "GenBasicParticle.h"
#include "TMath.h" 
#include "Analyse.h"

GenBasicParticle::GenBasicParticle(AllGenParticle p) : AllGenParticle(p), TLorentzVector(p.px(), p.py(), p.pz(), TMath::Sqrt(p.px()*p.px() + p.py()*p.py() + p.pz()*p.pz())) {}


GenBasicParticle GenBasicParticle::GetMother(Int_t n)
{
	return GenBasicParticle(GLAN->GetAllGenParticle(Mother(n)));
}

GenBasicParticle GenBasicParticle::GetDaughter(Int_t n)
{
	return GenBasicParticle(GLAN->GetAllGenParticle(Daughter(n)));
}

bool GenBasicParticle::HasMother(Int_t pdgid)
{
	for(UInt_t m = 0 ; m < Num_Mother() ; ++m)
	{
		if(GetMother(m).PDGID() == pdgid){return true;}
	}
	return false;
}
