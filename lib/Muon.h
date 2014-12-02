#ifndef CMUONH
#define CMUONH
#include <BASEIO.h> 
#include "TLorentzVector.h" 
#include "TriggerObject.h"

using namespace BASEIO;

class Muon : public IOMuon, public TLorentzVector, public TriggerObject
{
	public:
		Muon(IOMuon mu);

};
#endif
