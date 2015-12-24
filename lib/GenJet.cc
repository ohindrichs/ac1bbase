#include "GenJet.h"
#include "TMath.h" 
#include "Analyse.h"

GenJet::GenJet(IOGenJet p) : IOGenJet(p), TLorentzVector(p.px(), p.py(), p.pz(), p.e()) {}

