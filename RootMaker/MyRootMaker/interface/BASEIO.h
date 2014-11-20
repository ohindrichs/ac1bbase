#ifndef CLASS_BASEIO
#define CLASS_BASEIO
#include "TTree.h"
#include "TFile.h"
#include <string>
class BaseIO;
class Data_IOString;
class IOString;
class Data_PrimaryVertex;
class PrimaryVertex;
class Data_IOEventInfo;
class IOEventInfo;
class Data_GenInfo;
class GenInfo;
class Data_IOMuon;
class IOMuon;
class Data_IOMET;
class IOMET;
class Data_IOTrack;
class IOTrack;
class Data_IOPosition;
class IOPosition;
class Data_PFIsolation;
class PFIsolation;
class Data_IOElectron;
class IOElectron;
class Data_AllGenParticle;
class AllGenParticle;
class Data_DetIsolation;
class DetIsolation;
class Data_IOPFJet;
class IOPFJet;
class Data_SelectedGenParticle;
class SelectedGenParticle;
class Data_IOSuperCluster;
class IOSuperCluster;
class Data_IOBeamSpot;
class IOBeamSpot;

class Data_IOString
 {
	friend class IOString;
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t size_;
		std::string prefix_;
		UInt_t count_;
		UInt_t str_count_;
		UInt_t* str_num_;
		Char_t* str_;
	public:
		void Fill();
		Data_IOString(UInt_t size, std::string prefix);
		~Data_IOString();
		void SetUpWrite(TTree* tree);
		void SetUpRead(TTree* tree);
		void Load(TTree* tree, bool load);
 };


class IOString
 {
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t number_;
		Data_IOString* data_;
	public:
		IOString(Data_IOString* data, UInt_t number);
		IOString(const IOString& _iostring);
		void Init();
		Char_t str(UInt_t n) const;
		UInt_t Num_str() const;
		void str(Char_t _str, UInt_t n);
 };



class Data_PrimaryVertex
 {
	friend class PrimaryVertex;
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t size_;
		std::string prefix_;
		UInt_t count_;
		UChar_t* NumTracks_;
		Float_t* Vx_;
		Float_t* Vy_;
		Float_t* Vz_;
		Float_t* ChiQ_;
		Float_t* NDOF_;
		Float_t* SumPtQ_;
	public:
		void Fill();
		Data_PrimaryVertex(UInt_t size, std::string prefix);
		~Data_PrimaryVertex();
		void SetUpWrite(TTree* tree);
		void SetUpRead(TTree* tree);
		void Load(TTree* tree, bool load);
 };


class PrimaryVertex
 {
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t number_;
		Data_PrimaryVertex* data_;
	public:
		PrimaryVertex(Data_PrimaryVertex* data, UInt_t number);
		PrimaryVertex(const PrimaryVertex& _primaryvertex);
		void Init();
		UChar_t NumTracks() const;
		Float_t Vx() const;
		Float_t Vy() const;
		Float_t Vz() const;
		Float_t ChiQ() const;
		Float_t NDOF() const;
		Float_t SumPtQ() const;
		void NumTracks(UChar_t _NumTracks);
		void Vx(Float_t _Vx);
		void Vy(Float_t _Vy);
		void Vz(Float_t _Vz);
		void ChiQ(Float_t _ChiQ);
		void NDOF(Float_t _NDOF);
		void SumPtQ(Float_t _SumPtQ);
 };



class Data_IOEventInfo
 {
	friend class IOEventInfo;
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t size_;
		std::string prefix_;
		UInt_t count_;
		UInt_t* ProcessingErrors_;
		UInt_t* EventNumber_;
		UInt_t* LumiSectionNumber_;
		UInt_t* RunNumber_;
		UInt_t* TimeUnix_;
		UInt_t* TimeMuSec_;
		Float_t* AK5PFRho_;
		Float_t* AK5PFSigma_;
		UInt_t TriggerHLT_count_;
		UInt_t* TriggerHLT_num_;
		UChar_t* TriggerHLT_;
	public:
		void Fill();
		Data_IOEventInfo(UInt_t size, std::string prefix);
		~Data_IOEventInfo();
		void SetUpWrite(TTree* tree);
		void SetUpRead(TTree* tree);
		void Load(TTree* tree, bool load);
 };


class IOEventInfo
 {
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t number_;
		Data_IOEventInfo* data_;
	public:
		IOEventInfo(Data_IOEventInfo* data, UInt_t number);
		IOEventInfo(const IOEventInfo& _ioeventinfo);
		void Init();
		UInt_t ProcessingErrors() const;
		UInt_t EventNumber() const;
		UInt_t LumiSectionNumber() const;
		UInt_t RunNumber() const;
		UInt_t TimeUnix() const;
		UInt_t TimeMuSec() const;
		Float_t AK5PFRho() const;
		Float_t AK5PFSigma() const;
		UChar_t TriggerHLT(UInt_t n) const;
		UInt_t Num_TriggerHLT() const;
		void ProcessingErrors(UInt_t _ProcessingErrors);
		void EventNumber(UInt_t _EventNumber);
		void LumiSectionNumber(UInt_t _LumiSectionNumber);
		void RunNumber(UInt_t _RunNumber);
		void TimeUnix(UInt_t _TimeUnix);
		void TimeMuSec(UInt_t _TimeMuSec);
		void AK5PFRho(Float_t _AK5PFRho);
		void AK5PFSigma(Float_t _AK5PFSigma);
		void TriggerHLT(UChar_t _TriggerHLT, UInt_t n);
 };



class Data_GenInfo
 {
	friend class GenInfo;
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t size_;
		std::string prefix_;
		UInt_t count_;
		Int_t* PDGID1_;
		Int_t* PDGID2_;
		Int_t* NumPUInteractions_;
		Int_t* NumPUInteractionsBefore_;
		Int_t* NumPUInteractionsAfter_;
		Float_t* Weight_;
		Float_t* x1_;
		Float_t* x2_;
		Float_t* RenScale_;
		Float_t* FacScale_;
		Float_t* METx_;
		Float_t* METy_;
		Float_t* NumTrueInteractions_;
	public:
		void Fill();
		Data_GenInfo(UInt_t size, std::string prefix);
		~Data_GenInfo();
		void SetUpWrite(TTree* tree);
		void SetUpRead(TTree* tree);
		void Load(TTree* tree, bool load);
 };


class GenInfo
 {
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t number_;
		Data_GenInfo* data_;
	public:
		GenInfo(Data_GenInfo* data, UInt_t number);
		GenInfo(const GenInfo& _geninfo);
		void Init();
		Int_t PDGID1() const;
		Int_t PDGID2() const;
		Int_t NumPUInteractions() const;
		Int_t NumPUInteractionsBefore() const;
		Int_t NumPUInteractionsAfter() const;
		Float_t Weight() const;
		Float_t x1() const;
		Float_t x2() const;
		Float_t RenScale() const;
		Float_t FacScale() const;
		Float_t METx() const;
		Float_t METy() const;
		Float_t NumTrueInteractions() const;
		void PDGID1(Int_t _PDGID1);
		void PDGID2(Int_t _PDGID2);
		void NumPUInteractions(Int_t _NumPUInteractions);
		void NumPUInteractionsBefore(Int_t _NumPUInteractionsBefore);
		void NumPUInteractionsAfter(Int_t _NumPUInteractionsAfter);
		void Weight(Float_t _Weight);
		void x1(Float_t _x1);
		void x2(Float_t _x2);
		void RenScale(Float_t _RenScale);
		void FacScale(Float_t _FacScale);
		void METx(Float_t _METx);
		void METy(Float_t _METy);
		void NumTrueInteractions(Float_t _NumTrueInteractions);
 };



class Data_IOMuon
 {
	friend class IOMuon;
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t size_;
		std::string prefix_;
		UInt_t count_;
		Data_PFIsolation* PFR3_;
		Data_PFIsolation* PFR4_;
		Int_t* VertexNumber_;
		Int_t* Charge_;
		Int_t* NumChamber_;
		Int_t* NumChambersWithSegments_;
		Int_t* NumValidMuonHits_;
		Int_t* NumMatchedStations_;
		Float_t* px_;
		Float_t* py_;
		Float_t* pz_;
		Float_t* PtUnc_;
		Float_t* ChiQ_;
		Float_t* NDOF_;
		Float_t* ECalEnergy_;
		Float_t* HCalEnergy_;
		UInt_t* TriggerMatching_;
		Data_IOTrack* InnerTrack_;
		Data_DetIsolation* DetR3_;
		Data_DetIsolation* DetR4_;
	public:
		void Fill();
		Data_IOMuon(UInt_t size, std::string prefix);
		~Data_IOMuon();
		void SetUpWrite(TTree* tree);
		void SetUpRead(TTree* tree);
		void Load(TTree* tree, bool load);
 };


class IOMuon
 {
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t number_;
		Data_IOMuon* data_;
	public:
		IOMuon(Data_IOMuon* data, UInt_t number);
		IOMuon(const IOMuon& _iomuon);
		void Init();
		PFIsolation PFR3() const;
		PFIsolation PFR4() const;
		Int_t VertexNumber() const;
		Int_t Charge() const;
		Int_t NumChamber() const;
		Int_t NumChambersWithSegments() const;
		Int_t NumValidMuonHits() const;
		Int_t NumMatchedStations() const;
		Float_t px() const;
		Float_t py() const;
		Float_t pz() const;
		Float_t PtUnc() const;
		Float_t ChiQ() const;
		Float_t NDOF() const;
		Float_t ECalEnergy() const;
		Float_t HCalEnergy() const;
		UInt_t TriggerMatching() const;
		IOTrack InnerTrack() const;
		DetIsolation DetR3() const;
		DetIsolation DetR4() const;
		void VertexNumber(Int_t _VertexNumber);
		void Charge(Int_t _Charge);
		void NumChamber(Int_t _NumChamber);
		void NumChambersWithSegments(Int_t _NumChambersWithSegments);
		void NumValidMuonHits(Int_t _NumValidMuonHits);
		void NumMatchedStations(Int_t _NumMatchedStations);
		void px(Float_t _px);
		void py(Float_t _py);
		void pz(Float_t _pz);
		void PtUnc(Float_t _PtUnc);
		void ChiQ(Float_t _ChiQ);
		void NDOF(Float_t _NDOF);
		void ECalEnergy(Float_t _ECalEnergy);
		void HCalEnergy(Float_t _HCalEnergy);
		void TriggerMatching(UInt_t _TriggerMatching);
 };



class Data_IOMET
 {
	friend class IOMET;
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t size_;
		std::string prefix_;
		UInt_t count_;
		Float_t* pfmetpx_;
		Float_t* pfmetpy_;
		Float_t* pfmetpxcorr_;
		Float_t* pfmetpycorr_;
	public:
		void Fill();
		Data_IOMET(UInt_t size, std::string prefix);
		~Data_IOMET();
		void SetUpWrite(TTree* tree);
		void SetUpRead(TTree* tree);
		void Load(TTree* tree, bool load);
 };


class IOMET
 {
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t number_;
		Data_IOMET* data_;
	public:
		IOMET(Data_IOMET* data, UInt_t number);
		IOMET(const IOMET& _iomet);
		void Init();
		Float_t pfmetpx() const;
		Float_t pfmetpy() const;
		Float_t pfmetpxcorr() const;
		Float_t pfmetpycorr() const;
		void pfmetpx(Float_t _pfmetpx);
		void pfmetpy(Float_t _pfmetpy);
		void pfmetpxcorr(Float_t _pfmetpxcorr);
		void pfmetpycorr(Float_t _pfmetpycorr);
 };



class Data_IOTrack
 {
	friend class IOTrack;
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t size_;
		std::string prefix_;
		UInt_t count_;
		Int_t* VertexNumber_;
		Char_t* Charge_;
		UChar_t* NHits_;
		UChar_t* NPixelHits_;
		UChar_t* NMissingHits_;
		UChar_t* NPixelLayers_;
		UChar_t* NStripLayers_;
		Float_t* px_;
		Float_t* py_;
		Float_t* pz_;
		Float_t* ChiQ_;
		Float_t* NDOF_;
		Float_t* Dxy_;
		Float_t* DxyUnc_;
		Float_t* Dz_;
		Float_t* DzUnc_;
		Float_t* DeDx_;
	public:
		void Fill();
		Data_IOTrack(UInt_t size, std::string prefix);
		~Data_IOTrack();
		void SetUpWrite(TTree* tree);
		void SetUpRead(TTree* tree);
		void Load(TTree* tree, bool load);
 };


class IOTrack
 {
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t number_;
		Data_IOTrack* data_;
	public:
		IOTrack(Data_IOTrack* data, UInt_t number);
		IOTrack(const IOTrack& _iotrack);
		void Init();
		Int_t VertexNumber() const;
		Char_t Charge() const;
		UChar_t NHits() const;
		UChar_t NPixelHits() const;
		UChar_t NMissingHits() const;
		UChar_t NPixelLayers() const;
		UChar_t NStripLayers() const;
		Float_t px() const;
		Float_t py() const;
		Float_t pz() const;
		Float_t ChiQ() const;
		Float_t NDOF() const;
		Float_t Dxy() const;
		Float_t DxyUnc() const;
		Float_t Dz() const;
		Float_t DzUnc() const;
		Float_t DeDx() const;
		void VertexNumber(Int_t _VertexNumber);
		void Charge(Char_t _Charge);
		void NHits(UChar_t _NHits);
		void NPixelHits(UChar_t _NPixelHits);
		void NMissingHits(UChar_t _NMissingHits);
		void NPixelLayers(UChar_t _NPixelLayers);
		void NStripLayers(UChar_t _NStripLayers);
		void px(Float_t _px);
		void py(Float_t _py);
		void pz(Float_t _pz);
		void ChiQ(Float_t _ChiQ);
		void NDOF(Float_t _NDOF);
		void Dxy(Float_t _Dxy);
		void DxyUnc(Float_t _DxyUnc);
		void Dz(Float_t _Dz);
		void DzUnc(Float_t _DzUnc);
		void DeDx(Float_t _DeDx);
 };



class Data_IOPosition
 {
	friend class IOPosition;
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t size_;
		std::string prefix_;
		UInt_t count_;
		Double_t* x_;
		Double_t* y_;
		Double_t* z_;
	public:
		void Fill();
		Data_IOPosition(UInt_t size, std::string prefix);
		~Data_IOPosition();
		void SetUpWrite(TTree* tree);
		void SetUpRead(TTree* tree);
		void Load(TTree* tree, bool load);
 };


class IOPosition
 {
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t number_;
		Data_IOPosition* data_;
	public:
		IOPosition(Data_IOPosition* data, UInt_t number);
		IOPosition(const IOPosition& _ioposition);
		void Init();
		Double_t x() const;
		Double_t y() const;
		Double_t z() const;
		void x(Double_t _x);
		void y(Double_t _y);
		void z(Double_t _z);
 };



class Data_PFIsolation
 {
	friend class PFIsolation;
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t size_;
		std::string prefix_;
		UInt_t count_;
		Int_t* NumCharged_;
		Int_t* NumNeutral_;
		Int_t* NumHadron_;
		Int_t* NumPhoton_;
		Float_t* Charged_;
		Float_t* Neutral_;
		Float_t* Hadron_;
		Float_t* Photon_;
	public:
		void Fill();
		Data_PFIsolation(UInt_t size, std::string prefix);
		~Data_PFIsolation();
		void SetUpWrite(TTree* tree);
		void SetUpRead(TTree* tree);
		void Load(TTree* tree, bool load);
 };


class PFIsolation
 {
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t number_;
		Data_PFIsolation* data_;
	public:
		PFIsolation(Data_PFIsolation* data, UInt_t number);
		PFIsolation(const PFIsolation& _pfisolation);
		void Init();
		Int_t NumCharged() const;
		Int_t NumNeutral() const;
		Int_t NumHadron() const;
		Int_t NumPhoton() const;
		Float_t Charged() const;
		Float_t Neutral() const;
		Float_t Hadron() const;
		Float_t Photon() const;
		void NumCharged(Int_t _NumCharged);
		void NumNeutral(Int_t _NumNeutral);
		void NumHadron(Int_t _NumHadron);
		void NumPhoton(Int_t _NumPhoton);
		void Charged(Float_t _Charged);
		void Neutral(Float_t _Neutral);
		void Hadron(Float_t _Hadron);
		void Photon(Float_t _Photon);
 };



class Data_IOElectron
 {
	friend class IOElectron;
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t size_;
		std::string prefix_;
		UInt_t count_;
		Float_t* px_;
		Float_t* py_;
		Float_t* pz_;
		Float_t* DeltaEtaSCTrack_;
		Float_t* DeltaPhiSCTrack_;
		Float_t* ESCOverETrack_;
		Float_t* E1x5_;
		Float_t* E2x5_;
		Float_t* E5x5_;
		Float_t* R9_;
		Float_t* SigmaIEtaIEta_;
		Float_t* SigmaIPhiIPhi_;
		Float_t* SigmaIEtaIPhi_;
		Float_t* EHCalTowerOverECal_;
		Int_t* VertexNumber_;
		Int_t* Trigger_;
		Data_IOPosition* ECalPos_;
		Data_PFIsolation* PFR3_;
		Data_PFIsolation* PFR4_;
		Data_IOTrack* GSFTrack_;
		Data_DetIsolation* DetR3_;
		Data_DetIsolation* DetR4_;
		Data_IOSuperCluster* SC_;
	public:
		void Fill();
		Data_IOElectron(UInt_t size, std::string prefix);
		~Data_IOElectron();
		void SetUpWrite(TTree* tree);
		void SetUpRead(TTree* tree);
		void Load(TTree* tree, bool load);
 };


class IOElectron
 {
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t number_;
		Data_IOElectron* data_;
	public:
		IOElectron(Data_IOElectron* data, UInt_t number);
		IOElectron(const IOElectron& _ioelectron);
		void Init();
		Float_t px() const;
		Float_t py() const;
		Float_t pz() const;
		Float_t DeltaEtaSCTrack() const;
		Float_t DeltaPhiSCTrack() const;
		Float_t ESCOverETrack() const;
		Float_t E1x5() const;
		Float_t E2x5() const;
		Float_t E5x5() const;
		Float_t R9() const;
		Float_t SigmaIEtaIEta() const;
		Float_t SigmaIPhiIPhi() const;
		Float_t SigmaIEtaIPhi() const;
		Float_t EHCalTowerOverECal() const;
		Int_t VertexNumber() const;
		Int_t Trigger() const;
		IOPosition ECalPos() const;
		PFIsolation PFR3() const;
		PFIsolation PFR4() const;
		IOTrack GSFTrack() const;
		DetIsolation DetR3() const;
		DetIsolation DetR4() const;
		IOSuperCluster SC() const;
		void px(Float_t _px);
		void py(Float_t _py);
		void pz(Float_t _pz);
		void DeltaEtaSCTrack(Float_t _DeltaEtaSCTrack);
		void DeltaPhiSCTrack(Float_t _DeltaPhiSCTrack);
		void ESCOverETrack(Float_t _ESCOverETrack);
		void E1x5(Float_t _E1x5);
		void E2x5(Float_t _E2x5);
		void E5x5(Float_t _E5x5);
		void R9(Float_t _R9);
		void SigmaIEtaIEta(Float_t _SigmaIEtaIEta);
		void SigmaIPhiIPhi(Float_t _SigmaIPhiIPhi);
		void SigmaIEtaIPhi(Float_t _SigmaIEtaIPhi);
		void EHCalTowerOverECal(Float_t _EHCalTowerOverECal);
		void VertexNumber(Int_t _VertexNumber);
		void Trigger(Int_t _Trigger);
 };



class Data_AllGenParticle
 {
	friend class AllGenParticle;
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t size_;
		std::string prefix_;
		UInt_t count_;
		Int_t* PDGID_;
		Int_t* Status_;
		Float_t* px_;
		Float_t* py_;
		Float_t* pz_;
		Float_t* e_;
		Float_t* vx_;
		Float_t* vy_;
		Float_t* vz_;
		UInt_t Mother_count_;
		UInt_t* Mother_num_;
		Int_t* Mother_;
		UInt_t Daughter_count_;
		UInt_t* Daughter_num_;
		Int_t* Daughter_;
	public:
		void Fill();
		Data_AllGenParticle(UInt_t size, std::string prefix);
		~Data_AllGenParticle();
		void SetUpWrite(TTree* tree);
		void SetUpRead(TTree* tree);
		void Load(TTree* tree, bool load);
 };


class AllGenParticle
 {
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t number_;
		Data_AllGenParticle* data_;
	public:
		AllGenParticle(Data_AllGenParticle* data, UInt_t number);
		AllGenParticle(const AllGenParticle& _allgenparticle);
		void Init();
		Int_t PDGID() const;
		Int_t Status() const;
		Float_t px() const;
		Float_t py() const;
		Float_t pz() const;
		Float_t e() const;
		Float_t vx() const;
		Float_t vy() const;
		Float_t vz() const;
		Int_t Mother(UInt_t n) const;
		UInt_t Num_Mother() const;
		Int_t Daughter(UInt_t n) const;
		UInt_t Num_Daughter() const;
		void PDGID(Int_t _PDGID);
		void Status(Int_t _Status);
		void px(Float_t _px);
		void py(Float_t _py);
		void pz(Float_t _pz);
		void e(Float_t _e);
		void vx(Float_t _vx);
		void vy(Float_t _vy);
		void vz(Float_t _vz);
		void Mother(Int_t _Mother, UInt_t n);
		void Daughter(Int_t _Daughter, UInt_t n);
 };



class Data_DetIsolation
 {
	friend class DetIsolation;
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t size_;
		std::string prefix_;
		UInt_t count_;
		Int_t* NumTrack_;
		Int_t* NumECal_;
		Int_t* NumHCal_;
		Float_t* Track_;
		Float_t* ECal_;
		Float_t* HCal_;
	public:
		void Fill();
		Data_DetIsolation(UInt_t size, std::string prefix);
		~Data_DetIsolation();
		void SetUpWrite(TTree* tree);
		void SetUpRead(TTree* tree);
		void Load(TTree* tree, bool load);
 };


class DetIsolation
 {
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t number_;
		Data_DetIsolation* data_;
	public:
		DetIsolation(Data_DetIsolation* data, UInt_t number);
		DetIsolation(const DetIsolation& _detisolation);
		void Init();
		Int_t NumTrack() const;
		Int_t NumECal() const;
		Int_t NumHCal() const;
		Float_t Track() const;
		Float_t ECal() const;
		Float_t HCal() const;
		void NumTrack(Int_t _NumTrack);
		void NumECal(Int_t _NumECal);
		void NumHCal(Int_t _NumHCal);
		void Track(Float_t _Track);
		void ECal(Float_t _ECal);
		void HCal(Float_t _HCal);
 };



class Data_IOPFJet
 {
	friend class IOPFJet;
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t size_;
		std::string prefix_;
		UInt_t count_;
		Int_t* NumCharged_;
		Int_t* NumNeutral_;
		Int_t* NumHadron_;
		Int_t* NumPhoton_;
		Int_t* NumElectron_;
		Int_t* NumMuon_;
		Int_t* MCFlavor_;
		Float_t* px_;
		Float_t* py_;
		Float_t* pz_;
		Float_t* e_;
		Float_t* HCalEnergy_;
		Float_t* ECalEnergy_;
		Float_t* TrackEnergy_;
		Float_t* ChargedEnergy_;
		Float_t* NeutralEnergy_;
		Float_t* HadronEnergy_;
		Float_t* PhotonEnergy_;
		Float_t* ElectronEnergy_;
		Float_t* MuonEnergy_;
		Float_t* ChargedPtMomPA_;
		Float_t* ChargedPtMomPB_;
		Float_t* ConstPtMomPA_;
		Float_t* ConstPtMomPB_;
		Float_t* PtWrongPrimaryVertex_;
		Float_t* EnergyCorrection_;
		Float_t* EnergyCorrectionUnc_;
	public:
		void Fill();
		Data_IOPFJet(UInt_t size, std::string prefix);
		~Data_IOPFJet();
		void SetUpWrite(TTree* tree);
		void SetUpRead(TTree* tree);
		void Load(TTree* tree, bool load);
 };


class IOPFJet
 {
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t number_;
		Data_IOPFJet* data_;
	public:
		IOPFJet(Data_IOPFJet* data, UInt_t number);
		IOPFJet(const IOPFJet& _iopfjet);
		void Init();
		Int_t NumCharged() const;
		Int_t NumNeutral() const;
		Int_t NumHadron() const;
		Int_t NumPhoton() const;
		Int_t NumElectron() const;
		Int_t NumMuon() const;
		Int_t MCFlavor() const;
		Float_t px() const;
		Float_t py() const;
		Float_t pz() const;
		Float_t e() const;
		Float_t HCalEnergy() const;
		Float_t ECalEnergy() const;
		Float_t TrackEnergy() const;
		Float_t ChargedEnergy() const;
		Float_t NeutralEnergy() const;
		Float_t HadronEnergy() const;
		Float_t PhotonEnergy() const;
		Float_t ElectronEnergy() const;
		Float_t MuonEnergy() const;
		Float_t ChargedPtMomPA() const;
		Float_t ChargedPtMomPB() const;
		Float_t ConstPtMomPA() const;
		Float_t ConstPtMomPB() const;
		Float_t PtWrongPrimaryVertex() const;
		Float_t EnergyCorrection() const;
		Float_t EnergyCorrectionUnc() const;
		void NumCharged(Int_t _NumCharged);
		void NumNeutral(Int_t _NumNeutral);
		void NumHadron(Int_t _NumHadron);
		void NumPhoton(Int_t _NumPhoton);
		void NumElectron(Int_t _NumElectron);
		void NumMuon(Int_t _NumMuon);
		void MCFlavor(Int_t _MCFlavor);
		void px(Float_t _px);
		void py(Float_t _py);
		void pz(Float_t _pz);
		void e(Float_t _e);
		void HCalEnergy(Float_t _HCalEnergy);
		void ECalEnergy(Float_t _ECalEnergy);
		void TrackEnergy(Float_t _TrackEnergy);
		void ChargedEnergy(Float_t _ChargedEnergy);
		void NeutralEnergy(Float_t _NeutralEnergy);
		void HadronEnergy(Float_t _HadronEnergy);
		void PhotonEnergy(Float_t _PhotonEnergy);
		void ElectronEnergy(Float_t _ElectronEnergy);
		void MuonEnergy(Float_t _MuonEnergy);
		void ChargedPtMomPA(Float_t _ChargedPtMomPA);
		void ChargedPtMomPB(Float_t _ChargedPtMomPB);
		void ConstPtMomPA(Float_t _ConstPtMomPA);
		void ConstPtMomPB(Float_t _ConstPtMomPB);
		void PtWrongPrimaryVertex(Float_t _PtWrongPrimaryVertex);
		void EnergyCorrection(Float_t _EnergyCorrection);
		void EnergyCorrectionUnc(Float_t _EnergyCorrectionUnc);
 };



class Data_SelectedGenParticle
 {
	friend class SelectedGenParticle;
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t size_;
		std::string prefix_;
		UInt_t count_;
		Int_t* PDGID_;
		Int_t* Status_;
		Int_t* Info_;
		Int_t* Mother_;
		Int_t* IndirectMother_;
		Float_t* px_;
		Float_t* py_;
		Float_t* pz_;
		Float_t* e_;
		Float_t* vx_;
		Float_t* vy_;
		Float_t* vz_;
	public:
		void Fill();
		Data_SelectedGenParticle(UInt_t size, std::string prefix);
		~Data_SelectedGenParticle();
		void SetUpWrite(TTree* tree);
		void SetUpRead(TTree* tree);
		void Load(TTree* tree, bool load);
 };


class SelectedGenParticle
 {
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t number_;
		Data_SelectedGenParticle* data_;
	public:
		SelectedGenParticle(Data_SelectedGenParticle* data, UInt_t number);
		SelectedGenParticle(const SelectedGenParticle& _selectedgenparticle);
		void Init();
		Int_t PDGID() const;
		Int_t Status() const;
		Int_t Info() const;
		Int_t Mother() const;
		Int_t IndirectMother() const;
		Float_t px() const;
		Float_t py() const;
		Float_t pz() const;
		Float_t e() const;
		Float_t vx() const;
		Float_t vy() const;
		Float_t vz() const;
		void PDGID(Int_t _PDGID);
		void Status(Int_t _Status);
		void Info(Int_t _Info);
		void Mother(Int_t _Mother);
		void IndirectMother(Int_t _IndirectMother);
		void px(Float_t _px);
		void py(Float_t _py);
		void pz(Float_t _pz);
		void e(Float_t _e);
		void vx(Float_t _vx);
		void vy(Float_t _vy);
		void vz(Float_t _vz);
 };



class Data_IOSuperCluster
 {
	friend class IOSuperCluster;
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t size_;
		std::string prefix_;
		UInt_t count_;
		Float_t* Energy_;
		Float_t* RawEnergy_;
		Float_t* PhiWidth_;
		Float_t* EtaWidth_;
		Data_IOPosition* Pos_;
	public:
		void Fill();
		Data_IOSuperCluster(UInt_t size, std::string prefix);
		~Data_IOSuperCluster();
		void SetUpWrite(TTree* tree);
		void SetUpRead(TTree* tree);
		void Load(TTree* tree, bool load);
 };


class IOSuperCluster
 {
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t number_;
		Data_IOSuperCluster* data_;
	public:
		IOSuperCluster(Data_IOSuperCluster* data, UInt_t number);
		IOSuperCluster(const IOSuperCluster& _iosupercluster);
		void Init();
		Float_t Energy() const;
		Float_t RawEnergy() const;
		Float_t PhiWidth() const;
		Float_t EtaWidth() const;
		IOPosition Pos() const;
		void Energy(Float_t _Energy);
		void RawEnergy(Float_t _RawEnergy);
		void PhiWidth(Float_t _PhiWidth);
		void EtaWidth(Float_t _EtaWidth);
 };



class Data_IOBeamSpot
 {
	friend class IOBeamSpot;
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t size_;
		std::string prefix_;
		UInt_t count_;
		Float_t* Vx_;
		Float_t* Vy_;
		Float_t* Vz_;
		Float_t* XWidth_;
		Float_t* YWidth_;
		Float_t* ZWidth_;
	public:
		void Fill();
		Data_IOBeamSpot(UInt_t size, std::string prefix);
		~Data_IOBeamSpot();
		void SetUpWrite(TTree* tree);
		void SetUpRead(TTree* tree);
		void Load(TTree* tree, bool load);
 };


class IOBeamSpot
 {
	friend class BaseIO;
	private:
		static BaseIO* baseio;
		UInt_t number_;
		Data_IOBeamSpot* data_;
	public:
		IOBeamSpot(Data_IOBeamSpot* data, UInt_t number);
		IOBeamSpot(const IOBeamSpot& _iobeamspot);
		void Init();
		Float_t Vx() const;
		Float_t Vy() const;
		Float_t Vz() const;
		Float_t XWidth() const;
		Float_t YWidth() const;
		Float_t ZWidth() const;
		void Vx(Float_t _Vx);
		void Vy(Float_t _Vy);
		void Vz(Float_t _Vz);
		void XWidth(Float_t _XWidth);
		void YWidth(Float_t _YWidth);
		void ZWidth(Float_t _ZWidth);
 };


class BaseIO
{
	friend class PrimaryVertex;
	friend class IOEventInfo;
	friend class GenInfo;
	friend class IOMuon;
	friend class IOMET;
	friend class IOTrack;
	friend class IOElectron;
	friend class AllGenParticle;
	friend class IOPFJet;
	friend class SelectedGenParticle;
	friend class IOBeamSpot;
	private:
		Data_PrimaryVertex PrimaryVertex_container_;
		Data_IOEventInfo IOEventInfo_container_;
		Data_GenInfo GenInfo_container_;
		Data_IOMuon IOMuon_container_;
		Data_IOMET IOMET_container_;
		Data_IOTrack IOTrack_container_;
		Data_IOElectron IOElectron_container_;
		Data_AllGenParticle AllGenParticle_container_;
		Data_IOPFJet IOPFJet_container_;
		Data_SelectedGenParticle SelectedGenParticle_container_;
		Data_IOBeamSpot IOBeamSpot_container_;
		bool writable_;
		TTree* tree_;
		TTree* copytree_;
		std::string treename_;
	public:
		BaseIO(std::string treename, bool writable);
		~BaseIO();
		void SetFile(TFile* file);
		bool IsWritable() const;
		void Fill();
		UInt_t GetEntries();
		void GetEntry(UInt_t n);
		UInt_t NumPrimaryVertexs();
		PrimaryVertex GetPrimaryVertex(UInt_t n);
		void LoadPrimaryVertex(bool load);
		UInt_t NumIOEventInfos();
		IOEventInfo GetIOEventInfo(UInt_t n);
		void LoadIOEventInfo(bool load);
		UInt_t NumGenInfos();
		GenInfo GetGenInfo(UInt_t n);
		void LoadGenInfo(bool load);
		UInt_t NumIOMuons();
		IOMuon GetIOMuon(UInt_t n);
		void LoadIOMuon(bool load);
		UInt_t NumIOMETs();
		IOMET GetIOMET(UInt_t n);
		void LoadIOMET(bool load);
		UInt_t NumIOTracks();
		IOTrack GetIOTrack(UInt_t n);
		void LoadIOTrack(bool load);
		UInt_t NumIOElectrons();
		IOElectron GetIOElectron(UInt_t n);
		void LoadIOElectron(bool load);
		UInt_t NumAllGenParticles();
		AllGenParticle GetAllGenParticle(UInt_t n);
		void LoadAllGenParticle(bool load);
		UInt_t NumIOPFJets();
		IOPFJet GetIOPFJet(UInt_t n);
		void LoadIOPFJet(bool load);
		UInt_t NumSelectedGenParticles();
		SelectedGenParticle GetSelectedGenParticle(UInt_t n);
		void LoadSelectedGenParticle(bool load);
		UInt_t NumIOBeamSpots();
		IOBeamSpot GetIOBeamSpot(UInt_t n);
		void LoadIOBeamSpot(bool load);
};
#endif
