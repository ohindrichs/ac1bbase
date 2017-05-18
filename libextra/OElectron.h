#ifndef OELECTRONH
#define OELECTRONH
#include <Electron.h> 
#include <LV.h> 

class GenBasicParticle;

using namespace std;

class OElectron : public Electron
{
	private:
		GenBasicParticle* genp_;
		L1Object* l1matchp_;
	public:
		enum IDS {ID_NONE, TIGHT_16, LOOSE_16};
		OElectron(IOElectron el);
		~OElectron(){if(l1matchp_ != nullptr) delete l1matchp_;}
		//OElectron(){}
		//double CorPFIsolation2011() const;
		//double CorPFIsolation2012() const;
		double CorPFIsolation2015() const;
		bool ID(IDS idtyp = TIGHT_16, bool iso = true) const;
		bool Clean() const;
		GenBasicParticle* GenParticle() const {return(genp_);}
		void SetGen(GenBasicParticle* genp);
		L1Object* L1Match();
		
};
#endif
