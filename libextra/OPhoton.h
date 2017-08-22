#ifndef OPHOTONH
#define OPHOTONH
#include <Photon.h> 
#include "SuperCluster.h"

using namespace std;

class GenBasicParticle;

class OPhoton : public Photon
{
	private:
		GenBasicParticle* genp_;
		double EAcharged() const;
		double EAneutral() const;
		double EAphoton() const;
	public:
		OPhoton(Photon ph);
		bool ID(Int_t idtyp = 1) const;
		bool Clean() const;
		GenBasicParticle* GenParticle() const {return(genp_);}
		void SetGen(GenBasicParticle* genp);
		int MapX(size_t n) const {int val = HitMap(n); return val >> 26 ;}
		int MapY(size_t n) const {int val = HitMap(n); return (val << 6) >> 26 ;}
		float MapE(size_t n) const {int val = HitMap(n); return float(val & 0xFFFFF)/(1<<20);}
		double PFIsolationDB() const;
		double CorPFIsolation() const;

		
};
#endif
