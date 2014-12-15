#ifndef OMUONH
#define OMUONH
#include <Muon.h> 

class GenBasicParticle;

using namespace std;

class OMuon : public Muon
{
		GenBasicParticle* genp_;
	public:
		OMuon(IOMuon mu);
		bool ID(Int_t idtyp = 1) const;
		GenBasicParticle* GenParticle() const {return(genp_);}
		void SetGen(GenBasicParticle* genp);
		
};
#endif
