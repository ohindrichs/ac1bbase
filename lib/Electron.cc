#include "Electron.h"
#include "Analyse.h"

Electron::Electron(IOElectron el) : LVp<IOElectron>(el), TriggerObject(TriggerMatching(), GLAN->runlist.find(GLAN->Run())->second.HLTElectronAllNames()) {}
