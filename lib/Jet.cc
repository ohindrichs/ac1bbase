#include "Jet.h"
#include "Analyse.h"

Jet::Jet(IOPFJet jet) : LV<IOPFJet>(jet), TriggerObject(TriggerMatching(), GLAN->runlist.find(GLAN->Run())->second.HLTJetAllNames()) {}
