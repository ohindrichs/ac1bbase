#ifndef CMUONH
#define CMUONH
#include <BASEIO.h> 
#include "TLorentzVector.h" 

using namespace BASEIO;

class Muon : public IOMuon, public TLorentzVector
{
	public:
		Muon(IOMuon& mu);

};
#endif
