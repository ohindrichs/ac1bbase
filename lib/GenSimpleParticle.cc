#include "GenSimpleParticle.h"
#include "TMath.h" 
#include "Analyse.h"

GenSimpleParticle::GenSimpleParticle(GenSelectedParticle p) : TLorentzVector(p), status(p.Status()), pdgid(p.PDGID()), isor3(p.IsoR3()) {}
GenSimpleParticle::GenSimpleParticle(GenBasicParticle p) : TLorentzVector(p), status(p.Status()), pdgid(p.PDGID()) {}
