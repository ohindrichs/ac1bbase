#ifndef HELPER_H
#define HELPER_H
#include <string>
#include <map>
#include <vector>
//#include <Analyse.h> 
#include "GenBasicParticle.h" 
#include "OMuon.h" 
#include "OElectron.h" 

#include "TH1D.h"
#include "TH2D.h"
#include "TLorentzVector.h"
#include "TMath.h"

using namespace std;

//Path and Filenames
string FNbody(string filename);
string FNfilename(string filename);
string FNpath(string filename);
string FNnoext(string filename);

double ProbToSigma(double prob);
double SigmaToProb(double sigma);

//Histgramm Collections

class TH1DCollection
{
	private:
		string prefix;
		map<string, TH1D*> hmap;
	public:
		TH1DCollection(string _prefix);
		TH1D* AddHist(string name, Int_t bins, Double_t min, Double_t max, string xlabel, string ylabel);
		TH1D* AddHist(string name, vector<Double_t>& bins, string xlabel, string ylabel);

		TH1D* Get(string name);
		TH1D* operator[](string name);
};

class TH2DCollection
{
	private:
		string prefix;
		map<string, TH2D*> hmap;
	public:
		TH2DCollection(string _prefix);
		TH2D* AddHist(string name, Int_t xbins, Double_t xmin, Double_t xmax, Int_t ybins, Double_t ymin, Double_t ymax, string xlabel, string ylabel);
		TH2D* AddHist(string name, Int_t xbins, Double_t xmin, Double_t xmax, const vector<Double_t>& ybins, string xlabel, string ylabel);
		TH2D* AddHist(string name, const vector<Double_t>& xbins, Int_t ybins, Double_t ymin, Double_t ymax, string xlabel, string ylabel);
		TH2D* AddHist(string name, const vector<Double_t>& xbins, const vector<Double_t>& ybins, string xlabel, string ylabel);

		TH2D* Get(string name);
		TH2D* operator[](string name);
};

//Sort
double getThetaStar(TLorentzVector Z1, TLorentzVector Z2);

bool tlvsortpt(const TLorentzVector& JA, const TLorentzVector& JB);
bool tlvsortetaabs(const TLorentzVector& JA, const TLorentzVector& JB);
bool sortpdgid(const GenBasicParticle& JA, const GenBasicParticle& JB);

bool ptlvsortpt(const TLorentzVector* JA, const TLorentzVector* JB);
bool ptlvsortetaabs(const TLorentzVector* JA, const TLorentzVector* JB);
bool ptlvsorteta(const TLorentzVector* JA, const TLorentzVector* JB);
bool psortpdgid(const GenBasicParticle* JA, const GenBasicParticle* JB);

//Statistics

template<typename T> T ME(const T& m){return m;}

template<class InputIt, class UnaryFunction>
pair<double, double> mean_var(InputIt first, InputIt last, UnaryFunction f = ME)
{
	int n = 0;
	double mean = 0.;
	for(InputIt it = first ; it != last ; ++it)
	{
		mean += f(*it);
	}
	mean /= n;
	double var = 0.;
	for(InputIt it = first ; it != last ; ++it)
	{
		double tmp = (f(*it) - mean);
		var += tmp*tmp;                        
	}
	var /= n-1;
	return pair<double, double>(mean, var);
}

class Mean_Var
{
private:
	int n_ = 0;
	double sum_ = 0.;
	double sumq_ = 0.;

public:
	void Reset() {n_ = 0; sum_ = 0.; sumq_ = 0.;}
	void Add(double val) {n_++; sum_ += val; sumq_ += val*val;}
	double Mean() const {return sum_/n_;} 
	double Var() const {return (sumq_ + sum_*sum_*(-1./n_))/(n_ - 1.);} 
	double STD() const {return Sqrt(Var());} 
};

#endif
