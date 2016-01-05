#ifndef LVH
#define LVH
#include <BASEIO.h> 
#include "Analyse.h"
#include "TriggerObject.h"

#include <TLorentzVector.h>
#include <TMath.h>

using namespace BASEIO;

template < typename TA > class LVp : public TA, public TLorentzVector
{
	public:
		LVp(TA obj) : TA(obj), TLorentzVector(TA::px(), TA::py(), TA::pz(), TMath::Sqrt(TA::px()*TA::px() + TA::py()*TA::py() + TA::pz()*TA::pz())) {}
};

template < typename TA > class LV : public TA, public TLorentzVector
{
	public:
		LV(TA obj) : TA(obj), TLorentzVector(TA::px(), TA::py(), TA::pz(), TA::e()) {}
};

typedef LV< SubJet > SJet;

#endif
