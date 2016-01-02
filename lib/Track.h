#ifndef CTRACKH
#define CTRACKH
#include "LV.h" 

using namespace BASEIO;

class Track : public LVp<IOTrack>
{
	public:
		Track(IOTrack trk);

};
#endif
