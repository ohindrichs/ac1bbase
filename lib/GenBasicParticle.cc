#include "GenBasicParticle.h"
#include "TMath.h" 
#include "Analyse.h"

GenBasicParticle::GenBasicParticle(AllGenParticle p) : AllGenParticle(p), TLorentzVector(p.px(), p.py(), p.pz(), TMath::Sqrt(p.px()*p.px() + p.py()*p.py() + p.pz()*p.pz())) {}


GenBasicParticle GenBasicParticle::GetMother(Int_t n)
{
	return GenBasicParticle(GLAN->GetAllGenParticle(Mother(n)));
}
