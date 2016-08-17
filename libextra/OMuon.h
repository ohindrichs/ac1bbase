#ifndef OMUONH
#define OMUONH
#include "Muon.h"

class GenBasicParticle;

bool TestMuonInnerTrack(const IOTrack& trk);

using namespace std;

class OMuon : public Muon
{
		GenBasicParticle* genp_;
	public:
		enum IDS {ID_NONE, TIGHT_15, LOOSE_15};
		OMuon(IOMuon mu);
		double PFIsolationDB() const;
		bool IsGoodSA() const;
		bool IsGoodTRK() const;
		bool IsMatched() const;
		bool IsISO(IDS idtyp = TIGHT_15) const;
		bool ID(IDS idtyp = TIGHT_15, bool iso = true) const;
		GenBasicParticle* GenParticle() const {return(genp_);}
		void SetGen(GenBasicParticle* genp);
		
};
#endif
