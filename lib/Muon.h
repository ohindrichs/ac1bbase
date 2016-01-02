#ifndef CMUONH
#define CMUONH
#include "LV.h"
#include "TriggerObject.h"

#include <TLorentzVector.h>


using namespace BASEIO;

class Muon : public LVp<IOMuon>, public TriggerObject
{
	public:
		Muon(IOMuon mu);
		bool IsGlobal() const {return IOMuon::Info() & 1 << 0;}
		bool IsTracker() const {return IOMuon::Info() & 1 << 1;}
		bool IsStandAlone() const {return IOMuon::Info() & 1 << 2;}
		bool IsCalo() const {return IOMuon::Info() & 1 << 3;}
		bool IsPF() const {return IOMuon::Info() & 1 << 4;}
		int Charge() const {return (IOMuon::Info() & 1 << 5) ? 1 : -1;}

};
#endif
