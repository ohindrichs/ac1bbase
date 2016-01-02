#include "Photon.h"
#include "Analyse.h"

Photon::Photon(IOPhoton ph) : LVp<IOPhoton>(ph), TriggerObject(TriggerMatching(), GLAN->runlist.find(GLAN->Run())->second.HLTPhotonAllNames()) {}

//SuperCluster Photon::SC() {return SuperCluster(SC());}
