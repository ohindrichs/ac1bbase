#ifndef OPHOTONH
#define OPHOTONH
#include <Analyse.h> 

using namespace std;

class OPhoton : public Photon
{
		GenBasicParticle* mygen;
	public:
		OPhoton(Photon ph);
		OPhoton(){}
		double EAcharged() const;
		double EAneutral() const;
		double EAphoton() const;
		Float_t CorIsoPFR3Photon() const;
		Float_t CorIsoPFR3Neutral() const;
		Float_t CorIsoPFR3Charged() const;
		bool ID(Int_t idtyp = 1) const;
		bool Clean() const;
		bool IDEHCalOverECal() const;
		bool IDSigmaIEtaIEta() const;
		bool IDPhoton() const;
		bool IDNeutral() const;
		bool IDCharged() const;
		TLorentzVector* MyGen() const {return(mygen);}
		void SetGen(GenBasicParticle* Mygen) {mygen = Mygen;}
		
};
#endif
