#ifndef CJETH
#define CJETH
#include "LV.h" 
#include "TriggerObject.h"

using namespace BASEIO;

class Jet : public LV<IOPFJet>, public TriggerObject
{
	public:
		Jet(IOPFJet jet);

};
#endif
