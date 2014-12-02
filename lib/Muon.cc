#include "Muon.h"
#include "TMath.h" 

Muon::Muon(IOMuon& mu) : IOMuon(mu), TLorentzVector(mu.px(), mu.py(), mu.pz(), TMath::Sqrt(mu.px()*mu.px() + mu.py()*mu.py() + mu.pz()*mu.pz())) {}
