#include "Muon.h"
#include "Analyse.h"

Muon::Muon(IOMuon mu) : LVp<IOMuon>(mu), TriggerObject(TriggerMatching(), GLAN->runlist.find(GLAN->Run())->second.HLTMuonAllNames()) {}
