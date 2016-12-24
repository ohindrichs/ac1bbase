#ifndef OELECTRONH
#define OELECTRONH
#include <Electron.h> 

class GenBasicParticle;

using namespace std;

class OElectron : public Electron
{
	private:
		GenBasicParticle* genp_;
	public:
		enum IDS {ID_NONE, TIGHT_16, LOOSE_16};
		OElectron(IOElectron el);
		//OElectron(){}
		//double CorPFIsolation2011() const;
		//double CorPFIsolation2012() const;
		double CorPFIsolation2015() const;
		bool ID(IDS idtyp = TIGHT_16, bool iso = true) const;
		bool Clean() const;
		GenBasicParticle* GenParticle() const {return(genp_);}
		void SetGen(GenBasicParticle* genp);
		
};
#endif
