#ifndef CGENBPH
#define CGENBPH
#include <BASEIO.h> 
#include "TLorentzVector.h" 

using namespace BASEIO;

class GenBasicParticle : public AllGenParticle, public TLorentzVector
{
	public:
		GenBasicParticle(AllGenParticle p);
		GenBasicParticle GetMother(Int_t n);
		GenBasicParticle GetDaughter(Int_t n);
		bool HasMother(Int_t pdgid);

};
#endif