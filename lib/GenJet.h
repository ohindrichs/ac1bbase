#ifndef CGENJETH
#define CGENJETH
#include <BASEIO.h> 
#include "TLorentzVector.h" 

using namespace BASEIO;

class GenJet : public IOGenJet, public TLorentzVector
{
	public:
		GenJet(IOGenJet p);
};
#endif
