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
		double IsoFarAll() const {return IsoFar().Charged()+IsoFar().Photon()+IsoFar().Neutral();}
		double IsoNearAll() const {return IsoNear().Charged()+IsoNear().Photon()+IsoNear().Neutral();}
		double IsoCentralAll() const {return IsoCentral().Charged()+IsoCentral().Photon()+IsoCentral().Neutral();}
		bool IsGoodSA() const;
		bool IsGoodTRK() const;
		bool IsMatched() const;
		bool IsISO(IDS idtyp = TIGHT_15) const;
		bool ID(IDS idtyp = TIGHT_15, bool iso = true) const;
		GenBasicParticle* GenParticle() const {return(genp_);}
		void SetGen(GenBasicParticle* genp);
		
};
#endif
