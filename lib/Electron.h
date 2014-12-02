#ifndef CELECTRONH
#define CELECTRONH
#include <BASEIO.h> 
#include "TLorentzVector.h" 
#include "TriggerObject.h"

using namespace BASEIO;

class Electron : public IOElectron, public TLorentzVector, public TriggerObject
{
	public:
		Electron(IOElectron& el);

};
#endif
