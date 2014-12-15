#ifndef OJETH
#define OJETH
#include <Jet.h> 
#include <OMuon.h> 
#include <OElectron.h> 
#include <OPhoton.h> 

using namespace std;

class OJet : public Jet
{
		GenBasicParticle* genp_;
		int mcflavour;
	public:
		OJet(IOPFJet jet);
		bool Clean(const vector<OMuon*>& muons, const vector<OElectron*>& electrons, const vector<OPhoton*>& photons) const;
		TLorentzVector* GenParticle() const {return(genp_);}
		void SetGen(GenBasicParticle* genp) {genp_ = genp;}
		bool CalculateMCFlavour();
		int GetMCFlavour() const {return(mcflavour);}
		
};
#endif
