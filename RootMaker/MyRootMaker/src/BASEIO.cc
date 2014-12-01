#include "RootMaker/MyRootMaker/interface/BASEIO.h"

//Data_IOString Data_IOString Data_IOString Data_IOString Data_IOString Data_IOString Data_IOString Data_IOString Data_IOString Data_IOString 
BaseIO* Data_IOString::baseio = 0;
Data_IOString::Data_IOString(UInt_t size, std::string prefix = "") : 
size_(size),
prefix_(prefix)
{
	str_num_ = new UInt_t[size_];
	str_ = new Char_t[size_*100];
}

Data_IOString::~Data_IOString()
{
	delete[] str_;
	delete[] str_num_;
}

void Data_IOString::Fill()
{
	count_ = 0;
	str_count_ = 0;
}

void Data_IOString::SetUpWrite(TTree* tree)
{
	tree->Branch((prefix_ + "_count").c_str(), &count_, (prefix_ + "_count/i").c_str());
	tree->Branch((prefix_ + "_str_count").c_str(), &str_count_, (prefix_ + "_str_count/i").c_str());
	tree->Branch((prefix_ + "_str_num").c_str(), str_num_, (prefix_ + "_str_num[" + prefix_ + "_count]/i").c_str());
	tree->Branch((prefix_ + "_str").c_str(), str_, (prefix_ + "_str[" + prefix_ + "_str_count]/B").c_str());
}

void Data_IOString::SetUpRead(TTree* tree)
{
	tree->SetBranchAddress((prefix_ + "_count").c_str(), &count_);
	tree->SetBranchAddress((prefix_ + "_str_count").c_str(), &str_count_);
	tree->SetBranchAddress((prefix_ + "_str_num").c_str(), str_num_);
	tree->SetBranchAddress((prefix_ + "_str").c_str(), str_);
}

void Data_IOString::Load(TTree* tree, bool load)
{
	tree->SetBranchStatus((prefix_ + "_count").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_str_count").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_str_num").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_str").c_str(), load);
}



//IOString == IOString == IOString == IOString == IOString == IOString == IOString == IOString == IOString == IOString == IOString == IOString == IOString == IOString == IOString == 
BaseIO* IOString::baseio = 0;
IOString::IOString(Data_IOString* data, UInt_t number) : 
number_(number),
data_(data)
{
	Init();
}

IOString::IOString(const IOString& _iostring) : 
number_( _iostring.number_),
data_( _iostring.data_)
{
}

void IOString::Init()
{
	if(baseio->IsWritable())
	{
		if(number_ == 0) {data_->str_num_[number_] = 0;}
		else {data_->str_num_[number_] = data_->str_num_[number_-1];}
		data_->count_ = number_+1;
	}
}

UInt_t IOString::Num_str() const
{
	return number_ == 0 ? data_->str_num_[number_] : data_->str_num_[number_] - data_->str_num_[number_-1];
}

Char_t IOString::str(UInt_t n) const
{
	return number_ == 0 ? data_->str_[n] : data_->str_[data_->str_num_[number_-1]  + n];
}

void IOString::str(Char_t _str, UInt_t n)
{
	if(number_ == 0) {data_->str_[n] = _str;}
	else {data_->str_[data_->str_num_[number_-1] +n] = _str;}
	data_->str_num_[number_]++;
	data_->str_count_++;
}



//Data_PrimaryVertex Data_PrimaryVertex Data_PrimaryVertex Data_PrimaryVertex Data_PrimaryVertex Data_PrimaryVertex Data_PrimaryVertex Data_PrimaryVertex Data_PrimaryVertex Data_PrimaryVertex 
BaseIO* Data_PrimaryVertex::baseio = 0;
Data_PrimaryVertex::Data_PrimaryVertex(UInt_t size, std::string prefix = "") : 
size_(size),
prefix_(prefix)
{
	NumTracks_ = new UChar_t[size_];
	Vx_ = new Float_t[size_];
	Vy_ = new Float_t[size_];
	Vz_ = new Float_t[size_];
	ChiQ_ = new Float_t[size_];
	NDOF_ = new Float_t[size_];
	SumPtQ_ = new Float_t[size_];
}

Data_PrimaryVertex::~Data_PrimaryVertex()
{
	delete[] NumTracks_;
	delete[] Vx_;
	delete[] Vy_;
	delete[] Vz_;
	delete[] ChiQ_;
	delete[] NDOF_;
	delete[] SumPtQ_;
}

void Data_PrimaryVertex::Fill()
{
	count_ = 0;
}

void Data_PrimaryVertex::SetUpWrite(TTree* tree)
{
	tree->Branch((prefix_ + "_count").c_str(), &count_, (prefix_ + "_count/i").c_str());
	tree->Branch((prefix_ + "_NumTracks").c_str(), NumTracks_, (prefix_ + "_NumTracks[" + prefix_ + "_count]/b").c_str());
	tree->Branch((prefix_ + "_Vx").c_str(), Vx_, (prefix_ + "_Vx[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_Vy").c_str(), Vy_, (prefix_ + "_Vy[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_Vz").c_str(), Vz_, (prefix_ + "_Vz[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_ChiQ").c_str(), ChiQ_, (prefix_ + "_ChiQ[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_NDOF").c_str(), NDOF_, (prefix_ + "_NDOF[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_SumPtQ").c_str(), SumPtQ_, (prefix_ + "_SumPtQ[" + prefix_ + "_count]/F").c_str());
}

void Data_PrimaryVertex::SetUpRead(TTree* tree)
{
	tree->SetBranchAddress((prefix_ + "_count").c_str(), &count_);
	tree->SetBranchAddress((prefix_ + "_NumTracks").c_str(), NumTracks_);
	tree->SetBranchAddress((prefix_ + "_Vx").c_str(), Vx_);
	tree->SetBranchAddress((prefix_ + "_Vy").c_str(), Vy_);
	tree->SetBranchAddress((prefix_ + "_Vz").c_str(), Vz_);
	tree->SetBranchAddress((prefix_ + "_ChiQ").c_str(), ChiQ_);
	tree->SetBranchAddress((prefix_ + "_NDOF").c_str(), NDOF_);
	tree->SetBranchAddress((prefix_ + "_SumPtQ").c_str(), SumPtQ_);
}

void Data_PrimaryVertex::Load(TTree* tree, bool load)
{
	tree->SetBranchStatus((prefix_ + "_count").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NumTracks").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Vx").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Vy").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Vz").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_ChiQ").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NDOF").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_SumPtQ").c_str(), load);
}



//PrimaryVertex == PrimaryVertex == PrimaryVertex == PrimaryVertex == PrimaryVertex == PrimaryVertex == PrimaryVertex == PrimaryVertex == PrimaryVertex == PrimaryVertex == PrimaryVertex == PrimaryVertex == PrimaryVertex == PrimaryVertex == PrimaryVertex == 
BaseIO* PrimaryVertex::baseio = 0;
PrimaryVertex::PrimaryVertex(Data_PrimaryVertex* data, UInt_t number) : 
number_(number),
data_(data)
{
	Init();
}

PrimaryVertex::PrimaryVertex(const PrimaryVertex& _primaryvertex) : 
number_( _primaryvertex.number_),
data_( _primaryvertex.data_)
{
}

void PrimaryVertex::Init()
{
	if(baseio->IsWritable())
	{
		data_->count_ = number_+1;
	}
}

UChar_t PrimaryVertex::NumTracks() const
{
	return data_->NumTracks_[number_];
}

Float_t PrimaryVertex::Vx() const
{
	return data_->Vx_[number_];
}

Float_t PrimaryVertex::Vy() const
{
	return data_->Vy_[number_];
}

Float_t PrimaryVertex::Vz() const
{
	return data_->Vz_[number_];
}

Float_t PrimaryVertex::ChiQ() const
{
	return data_->ChiQ_[number_];
}

Float_t PrimaryVertex::NDOF() const
{
	return data_->NDOF_[number_];
}

Float_t PrimaryVertex::SumPtQ() const
{
	return data_->SumPtQ_[number_];
}

void PrimaryVertex::NumTracks(UChar_t _NumTracks)
{
	data_->NumTracks_[number_] = _NumTracks;
}

void PrimaryVertex::Vx(Float_t _Vx)
{
	data_->Vx_[number_] = _Vx;
}

void PrimaryVertex::Vy(Float_t _Vy)
{
	data_->Vy_[number_] = _Vy;
}

void PrimaryVertex::Vz(Float_t _Vz)
{
	data_->Vz_[number_] = _Vz;
}

void PrimaryVertex::ChiQ(Float_t _ChiQ)
{
	data_->ChiQ_[number_] = _ChiQ;
}

void PrimaryVertex::NDOF(Float_t _NDOF)
{
	data_->NDOF_[number_] = _NDOF;
}

void PrimaryVertex::SumPtQ(Float_t _SumPtQ)
{
	data_->SumPtQ_[number_] = _SumPtQ;
}



//Data_IOEventInfo Data_IOEventInfo Data_IOEventInfo Data_IOEventInfo Data_IOEventInfo Data_IOEventInfo Data_IOEventInfo Data_IOEventInfo Data_IOEventInfo Data_IOEventInfo 
BaseIO* Data_IOEventInfo::baseio = 0;
Data_IOEventInfo::Data_IOEventInfo(UInt_t size, std::string prefix = "") : 
size_(size),
prefix_(prefix)
{
	ProcessingErrors_ = new UInt_t[size_];
	EventNumber_ = new UInt_t[size_];
	LumiSectionNumber_ = new UInt_t[size_];
	RunNumber_ = new UInt_t[size_];
	TimeUnix_ = new UInt_t[size_];
	TimeMuSec_ = new UInt_t[size_];
	AK5PFRho_ = new Float_t[size_];
	AK5PFSigma_ = new Float_t[size_];
	TriggerHLT_num_ = new UInt_t[size_];
	TriggerHLT_ = new UChar_t[size_*150];
}

Data_IOEventInfo::~Data_IOEventInfo()
{
	delete[] ProcessingErrors_;
	delete[] EventNumber_;
	delete[] LumiSectionNumber_;
	delete[] RunNumber_;
	delete[] TimeUnix_;
	delete[] TimeMuSec_;
	delete[] AK5PFRho_;
	delete[] AK5PFSigma_;
	delete[] TriggerHLT_;
	delete[] TriggerHLT_num_;
}

void Data_IOEventInfo::Fill()
{
	count_ = 0;
	TriggerHLT_count_ = 0;
}

void Data_IOEventInfo::SetUpWrite(TTree* tree)
{
	tree->Branch((prefix_ + "_count").c_str(), &count_, (prefix_ + "_count/i").c_str());
	tree->Branch((prefix_ + "_ProcessingErrors").c_str(), ProcessingErrors_, (prefix_ + "_ProcessingErrors[" + prefix_ + "_count]/i").c_str());
	tree->Branch((prefix_ + "_EventNumber").c_str(), EventNumber_, (prefix_ + "_EventNumber[" + prefix_ + "_count]/i").c_str());
	tree->Branch((prefix_ + "_LumiSectionNumber").c_str(), LumiSectionNumber_, (prefix_ + "_LumiSectionNumber[" + prefix_ + "_count]/i").c_str());
	tree->Branch((prefix_ + "_RunNumber").c_str(), RunNumber_, (prefix_ + "_RunNumber[" + prefix_ + "_count]/i").c_str());
	tree->Branch((prefix_ + "_TimeUnix").c_str(), TimeUnix_, (prefix_ + "_TimeUnix[" + prefix_ + "_count]/i").c_str());
	tree->Branch((prefix_ + "_TimeMuSec").c_str(), TimeMuSec_, (prefix_ + "_TimeMuSec[" + prefix_ + "_count]/i").c_str());
	tree->Branch((prefix_ + "_AK5PFRho").c_str(), AK5PFRho_, (prefix_ + "_AK5PFRho[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_AK5PFSigma").c_str(), AK5PFSigma_, (prefix_ + "_AK5PFSigma[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_TriggerHLT_count").c_str(), &TriggerHLT_count_, (prefix_ + "_TriggerHLT_count/i").c_str());
	tree->Branch((prefix_ + "_TriggerHLT_num").c_str(), TriggerHLT_num_, (prefix_ + "_TriggerHLT_num[" + prefix_ + "_count]/i").c_str());
	tree->Branch((prefix_ + "_TriggerHLT").c_str(), TriggerHLT_, (prefix_ + "_TriggerHLT[" + prefix_ + "_TriggerHLT_count]/b").c_str());
}

void Data_IOEventInfo::SetUpRead(TTree* tree)
{
	tree->SetBranchAddress((prefix_ + "_count").c_str(), &count_);
	tree->SetBranchAddress((prefix_ + "_ProcessingErrors").c_str(), ProcessingErrors_);
	tree->SetBranchAddress((prefix_ + "_EventNumber").c_str(), EventNumber_);
	tree->SetBranchAddress((prefix_ + "_LumiSectionNumber").c_str(), LumiSectionNumber_);
	tree->SetBranchAddress((prefix_ + "_RunNumber").c_str(), RunNumber_);
	tree->SetBranchAddress((prefix_ + "_TimeUnix").c_str(), TimeUnix_);
	tree->SetBranchAddress((prefix_ + "_TimeMuSec").c_str(), TimeMuSec_);
	tree->SetBranchAddress((prefix_ + "_AK5PFRho").c_str(), AK5PFRho_);
	tree->SetBranchAddress((prefix_ + "_AK5PFSigma").c_str(), AK5PFSigma_);
	tree->SetBranchAddress((prefix_ + "_TriggerHLT_count").c_str(), &TriggerHLT_count_);
	tree->SetBranchAddress((prefix_ + "_TriggerHLT_num").c_str(), TriggerHLT_num_);
	tree->SetBranchAddress((prefix_ + "_TriggerHLT").c_str(), TriggerHLT_);
}

void Data_IOEventInfo::Load(TTree* tree, bool load)
{
	tree->SetBranchStatus((prefix_ + "_count").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_ProcessingErrors").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_EventNumber").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_LumiSectionNumber").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_RunNumber").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_TimeUnix").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_TimeMuSec").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_AK5PFRho").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_AK5PFSigma").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_TriggerHLT_count").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_TriggerHLT_num").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_TriggerHLT").c_str(), load);
}



//IOEventInfo == IOEventInfo == IOEventInfo == IOEventInfo == IOEventInfo == IOEventInfo == IOEventInfo == IOEventInfo == IOEventInfo == IOEventInfo == IOEventInfo == IOEventInfo == IOEventInfo == IOEventInfo == IOEventInfo == 
BaseIO* IOEventInfo::baseio = 0;
IOEventInfo::IOEventInfo(Data_IOEventInfo* data, UInt_t number) : 
number_(number),
data_(data)
{
	Init();
}

IOEventInfo::IOEventInfo(const IOEventInfo& _ioeventinfo) : 
number_( _ioeventinfo.number_),
data_( _ioeventinfo.data_)
{
}

void IOEventInfo::Init()
{
	if(baseio->IsWritable())
	{
		if(number_ == 0) {data_->TriggerHLT_num_[number_] = 0;}
		else {data_->TriggerHLT_num_[number_] = data_->TriggerHLT_num_[number_-1];}
		data_->count_ = number_+1;
	}
}

UInt_t IOEventInfo::ProcessingErrors() const
{
	return data_->ProcessingErrors_[number_];
}

UInt_t IOEventInfo::EventNumber() const
{
	return data_->EventNumber_[number_];
}

UInt_t IOEventInfo::LumiSectionNumber() const
{
	return data_->LumiSectionNumber_[number_];
}

UInt_t IOEventInfo::RunNumber() const
{
	return data_->RunNumber_[number_];
}

UInt_t IOEventInfo::TimeUnix() const
{
	return data_->TimeUnix_[number_];
}

UInt_t IOEventInfo::TimeMuSec() const
{
	return data_->TimeMuSec_[number_];
}

Float_t IOEventInfo::AK5PFRho() const
{
	return data_->AK5PFRho_[number_];
}

Float_t IOEventInfo::AK5PFSigma() const
{
	return data_->AK5PFSigma_[number_];
}

UInt_t IOEventInfo::Num_TriggerHLT() const
{
	return number_ == 0 ? data_->TriggerHLT_num_[number_] : data_->TriggerHLT_num_[number_] - data_->TriggerHLT_num_[number_-1];
}

UChar_t IOEventInfo::TriggerHLT(UInt_t n) const
{
	return number_ == 0 ? data_->TriggerHLT_[n] : data_->TriggerHLT_[data_->TriggerHLT_num_[number_-1]  + n];
}

void IOEventInfo::ProcessingErrors(UInt_t _ProcessingErrors)
{
	data_->ProcessingErrors_[number_] = _ProcessingErrors;
}

void IOEventInfo::EventNumber(UInt_t _EventNumber)
{
	data_->EventNumber_[number_] = _EventNumber;
}

void IOEventInfo::LumiSectionNumber(UInt_t _LumiSectionNumber)
{
	data_->LumiSectionNumber_[number_] = _LumiSectionNumber;
}

void IOEventInfo::RunNumber(UInt_t _RunNumber)
{
	data_->RunNumber_[number_] = _RunNumber;
}

void IOEventInfo::TimeUnix(UInt_t _TimeUnix)
{
	data_->TimeUnix_[number_] = _TimeUnix;
}

void IOEventInfo::TimeMuSec(UInt_t _TimeMuSec)
{
	data_->TimeMuSec_[number_] = _TimeMuSec;
}

void IOEventInfo::AK5PFRho(Float_t _AK5PFRho)
{
	data_->AK5PFRho_[number_] = _AK5PFRho;
}

void IOEventInfo::AK5PFSigma(Float_t _AK5PFSigma)
{
	data_->AK5PFSigma_[number_] = _AK5PFSigma;
}

void IOEventInfo::TriggerHLT(UChar_t _TriggerHLT, UInt_t n)
{
	if(number_ == 0) {data_->TriggerHLT_[n] = _TriggerHLT;}
	else {data_->TriggerHLT_[data_->TriggerHLT_num_[number_-1] +n] = _TriggerHLT;}
	data_->TriggerHLT_num_[number_]++;
	data_->TriggerHLT_count_++;
}



//Data_GenInfo Data_GenInfo Data_GenInfo Data_GenInfo Data_GenInfo Data_GenInfo Data_GenInfo Data_GenInfo Data_GenInfo Data_GenInfo 
BaseIO* Data_GenInfo::baseio = 0;
Data_GenInfo::Data_GenInfo(UInt_t size, std::string prefix = "") : 
size_(size),
prefix_(prefix)
{
	PDGID1_ = new Int_t[size_];
	PDGID2_ = new Int_t[size_];
	NumPUInteractions_ = new Int_t[size_];
	NumPUInteractionsBefore_ = new Int_t[size_];
	NumPUInteractionsAfter_ = new Int_t[size_];
	Weight_ = new Float_t[size_];
	x1_ = new Float_t[size_];
	x2_ = new Float_t[size_];
	RenScale_ = new Float_t[size_];
	FacScale_ = new Float_t[size_];
	METx_ = new Float_t[size_];
	METy_ = new Float_t[size_];
	NumTrueInteractions_ = new Float_t[size_];
}

Data_GenInfo::~Data_GenInfo()
{
	delete[] PDGID1_;
	delete[] PDGID2_;
	delete[] NumPUInteractions_;
	delete[] NumPUInteractionsBefore_;
	delete[] NumPUInteractionsAfter_;
	delete[] Weight_;
	delete[] x1_;
	delete[] x2_;
	delete[] RenScale_;
	delete[] FacScale_;
	delete[] METx_;
	delete[] METy_;
	delete[] NumTrueInteractions_;
}

void Data_GenInfo::Fill()
{
	count_ = 0;
}

void Data_GenInfo::SetUpWrite(TTree* tree)
{
	tree->Branch((prefix_ + "_count").c_str(), &count_, (prefix_ + "_count/i").c_str());
	tree->Branch((prefix_ + "_PDGID1").c_str(), PDGID1_, (prefix_ + "_PDGID1[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_PDGID2").c_str(), PDGID2_, (prefix_ + "_PDGID2[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_NumPUInteractions").c_str(), NumPUInteractions_, (prefix_ + "_NumPUInteractions[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_NumPUInteractionsBefore").c_str(), NumPUInteractionsBefore_, (prefix_ + "_NumPUInteractionsBefore[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_NumPUInteractionsAfter").c_str(), NumPUInteractionsAfter_, (prefix_ + "_NumPUInteractionsAfter[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_Weight").c_str(), Weight_, (prefix_ + "_Weight[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_x1").c_str(), x1_, (prefix_ + "_x1[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_x2").c_str(), x2_, (prefix_ + "_x2[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_RenScale").c_str(), RenScale_, (prefix_ + "_RenScale[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_FacScale").c_str(), FacScale_, (prefix_ + "_FacScale[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_METx").c_str(), METx_, (prefix_ + "_METx[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_METy").c_str(), METy_, (prefix_ + "_METy[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_NumTrueInteractions").c_str(), NumTrueInteractions_, (prefix_ + "_NumTrueInteractions[" + prefix_ + "_count]/F").c_str());
}

void Data_GenInfo::SetUpRead(TTree* tree)
{
	tree->SetBranchAddress((prefix_ + "_count").c_str(), &count_);
	tree->SetBranchAddress((prefix_ + "_PDGID1").c_str(), PDGID1_);
	tree->SetBranchAddress((prefix_ + "_PDGID2").c_str(), PDGID2_);
	tree->SetBranchAddress((prefix_ + "_NumPUInteractions").c_str(), NumPUInteractions_);
	tree->SetBranchAddress((prefix_ + "_NumPUInteractionsBefore").c_str(), NumPUInteractionsBefore_);
	tree->SetBranchAddress((prefix_ + "_NumPUInteractionsAfter").c_str(), NumPUInteractionsAfter_);
	tree->SetBranchAddress((prefix_ + "_Weight").c_str(), Weight_);
	tree->SetBranchAddress((prefix_ + "_x1").c_str(), x1_);
	tree->SetBranchAddress((prefix_ + "_x2").c_str(), x2_);
	tree->SetBranchAddress((prefix_ + "_RenScale").c_str(), RenScale_);
	tree->SetBranchAddress((prefix_ + "_FacScale").c_str(), FacScale_);
	tree->SetBranchAddress((prefix_ + "_METx").c_str(), METx_);
	tree->SetBranchAddress((prefix_ + "_METy").c_str(), METy_);
	tree->SetBranchAddress((prefix_ + "_NumTrueInteractions").c_str(), NumTrueInteractions_);
}

void Data_GenInfo::Load(TTree* tree, bool load)
{
	tree->SetBranchStatus((prefix_ + "_count").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_PDGID1").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_PDGID2").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NumPUInteractions").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NumPUInteractionsBefore").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NumPUInteractionsAfter").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Weight").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_x1").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_x2").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_RenScale").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_FacScale").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_METx").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_METy").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NumTrueInteractions").c_str(), load);
}



//GenInfo == GenInfo == GenInfo == GenInfo == GenInfo == GenInfo == GenInfo == GenInfo == GenInfo == GenInfo == GenInfo == GenInfo == GenInfo == GenInfo == GenInfo == 
BaseIO* GenInfo::baseio = 0;
GenInfo::GenInfo(Data_GenInfo* data, UInt_t number) : 
number_(number),
data_(data)
{
	Init();
}

GenInfo::GenInfo(const GenInfo& _geninfo) : 
number_( _geninfo.number_),
data_( _geninfo.data_)
{
}

void GenInfo::Init()
{
	if(baseio->IsWritable())
	{
		data_->count_ = number_+1;
	}
}

Int_t GenInfo::PDGID1() const
{
	return data_->PDGID1_[number_];
}

Int_t GenInfo::PDGID2() const
{
	return data_->PDGID2_[number_];
}

Int_t GenInfo::NumPUInteractions() const
{
	return data_->NumPUInteractions_[number_];
}

Int_t GenInfo::NumPUInteractionsBefore() const
{
	return data_->NumPUInteractionsBefore_[number_];
}

Int_t GenInfo::NumPUInteractionsAfter() const
{
	return data_->NumPUInteractionsAfter_[number_];
}

Float_t GenInfo::Weight() const
{
	return data_->Weight_[number_];
}

Float_t GenInfo::x1() const
{
	return data_->x1_[number_];
}

Float_t GenInfo::x2() const
{
	return data_->x2_[number_];
}

Float_t GenInfo::RenScale() const
{
	return data_->RenScale_[number_];
}

Float_t GenInfo::FacScale() const
{
	return data_->FacScale_[number_];
}

Float_t GenInfo::METx() const
{
	return data_->METx_[number_];
}

Float_t GenInfo::METy() const
{
	return data_->METy_[number_];
}

Float_t GenInfo::NumTrueInteractions() const
{
	return data_->NumTrueInteractions_[number_];
}

void GenInfo::PDGID1(Int_t _PDGID1)
{
	data_->PDGID1_[number_] = _PDGID1;
}

void GenInfo::PDGID2(Int_t _PDGID2)
{
	data_->PDGID2_[number_] = _PDGID2;
}

void GenInfo::NumPUInteractions(Int_t _NumPUInteractions)
{
	data_->NumPUInteractions_[number_] = _NumPUInteractions;
}

void GenInfo::NumPUInteractionsBefore(Int_t _NumPUInteractionsBefore)
{
	data_->NumPUInteractionsBefore_[number_] = _NumPUInteractionsBefore;
}

void GenInfo::NumPUInteractionsAfter(Int_t _NumPUInteractionsAfter)
{
	data_->NumPUInteractionsAfter_[number_] = _NumPUInteractionsAfter;
}

void GenInfo::Weight(Float_t _Weight)
{
	data_->Weight_[number_] = _Weight;
}

void GenInfo::x1(Float_t _x1)
{
	data_->x1_[number_] = _x1;
}

void GenInfo::x2(Float_t _x2)
{
	data_->x2_[number_] = _x2;
}

void GenInfo::RenScale(Float_t _RenScale)
{
	data_->RenScale_[number_] = _RenScale;
}

void GenInfo::FacScale(Float_t _FacScale)
{
	data_->FacScale_[number_] = _FacScale;
}

void GenInfo::METx(Float_t _METx)
{
	data_->METx_[number_] = _METx;
}

void GenInfo::METy(Float_t _METy)
{
	data_->METy_[number_] = _METy;
}

void GenInfo::NumTrueInteractions(Float_t _NumTrueInteractions)
{
	data_->NumTrueInteractions_[number_] = _NumTrueInteractions;
}



//Data_IOMuon Data_IOMuon Data_IOMuon Data_IOMuon Data_IOMuon Data_IOMuon Data_IOMuon Data_IOMuon Data_IOMuon Data_IOMuon 
BaseIO* Data_IOMuon::baseio = 0;
Data_IOMuon::Data_IOMuon(UInt_t size, std::string prefix = "") : 
size_(size),
prefix_(prefix)
, PFR3_(new Data_PFIsolation(size_, prefix_ + "_PFR3"))
, PFR4_(new Data_PFIsolation(size_, prefix_ + "_PFR4"))
, InnerTrack_(new Data_IOTrack(size_, prefix_ + "_InnerTrack"))
, DetR3_(new Data_DetIsolation(size_, prefix_ + "_DetR3"))
, DetR4_(new Data_DetIsolation(size_, prefix_ + "_DetR4"))
{
	VertexNumber_ = new Int_t[size_];
	Charge_ = new Int_t[size_];
	NumChamber_ = new Int_t[size_];
	NumChambersWithSegments_ = new Int_t[size_];
	NumValidMuonHits_ = new Int_t[size_];
	NumMatchedStations_ = new Int_t[size_];
	px_ = new Float_t[size_];
	py_ = new Float_t[size_];
	pz_ = new Float_t[size_];
	PtUnc_ = new Float_t[size_];
	ChiQ_ = new Float_t[size_];
	NDOF_ = new Float_t[size_];
	ECalEnergy_ = new Float_t[size_];
	HCalEnergy_ = new Float_t[size_];
	TriggerMatching_ = new UInt_t[size_];
}

Data_IOMuon::~Data_IOMuon()
{
	delete PFR3_;
	delete PFR4_;
	delete[] VertexNumber_;
	delete[] Charge_;
	delete[] NumChamber_;
	delete[] NumChambersWithSegments_;
	delete[] NumValidMuonHits_;
	delete[] NumMatchedStations_;
	delete[] px_;
	delete[] py_;
	delete[] pz_;
	delete[] PtUnc_;
	delete[] ChiQ_;
	delete[] NDOF_;
	delete[] ECalEnergy_;
	delete[] HCalEnergy_;
	delete[] TriggerMatching_;
	delete InnerTrack_;
	delete DetR3_;
	delete DetR4_;
}

void Data_IOMuon::Fill()
{
	count_ = 0;
	PFR3_->Fill();
	PFR4_->Fill();
	InnerTrack_->Fill();
	DetR3_->Fill();
	DetR4_->Fill();
}

void Data_IOMuon::SetUpWrite(TTree* tree)
{
	tree->Branch((prefix_ + "_count").c_str(), &count_, (prefix_ + "_count/i").c_str());
	tree->Branch((prefix_ + "_VertexNumber").c_str(), VertexNumber_, (prefix_ + "_VertexNumber[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_Charge").c_str(), Charge_, (prefix_ + "_Charge[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_NumChamber").c_str(), NumChamber_, (prefix_ + "_NumChamber[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_NumChambersWithSegments").c_str(), NumChambersWithSegments_, (prefix_ + "_NumChambersWithSegments[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_NumValidMuonHits").c_str(), NumValidMuonHits_, (prefix_ + "_NumValidMuonHits[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_NumMatchedStations").c_str(), NumMatchedStations_, (prefix_ + "_NumMatchedStations[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_px").c_str(), px_, (prefix_ + "_px[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_py").c_str(), py_, (prefix_ + "_py[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_pz").c_str(), pz_, (prefix_ + "_pz[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_PtUnc").c_str(), PtUnc_, (prefix_ + "_PtUnc[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_ChiQ").c_str(), ChiQ_, (prefix_ + "_ChiQ[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_NDOF").c_str(), NDOF_, (prefix_ + "_NDOF[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_ECalEnergy").c_str(), ECalEnergy_, (prefix_ + "_ECalEnergy[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_HCalEnergy").c_str(), HCalEnergy_, (prefix_ + "_HCalEnergy[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_TriggerMatching").c_str(), TriggerMatching_, (prefix_ + "_TriggerMatching[" + prefix_ + "_count]/i").c_str());
	PFR3_->SetUpWrite(tree);
	PFR4_->SetUpWrite(tree);
	InnerTrack_->SetUpWrite(tree);
	DetR3_->SetUpWrite(tree);
	DetR4_->SetUpWrite(tree);
}

void Data_IOMuon::SetUpRead(TTree* tree)
{
	tree->SetBranchAddress((prefix_ + "_count").c_str(), &count_);
	tree->SetBranchAddress((prefix_ + "_VertexNumber").c_str(), VertexNumber_);
	tree->SetBranchAddress((prefix_ + "_Charge").c_str(), Charge_);
	tree->SetBranchAddress((prefix_ + "_NumChamber").c_str(), NumChamber_);
	tree->SetBranchAddress((prefix_ + "_NumChambersWithSegments").c_str(), NumChambersWithSegments_);
	tree->SetBranchAddress((prefix_ + "_NumValidMuonHits").c_str(), NumValidMuonHits_);
	tree->SetBranchAddress((prefix_ + "_NumMatchedStations").c_str(), NumMatchedStations_);
	tree->SetBranchAddress((prefix_ + "_px").c_str(), px_);
	tree->SetBranchAddress((prefix_ + "_py").c_str(), py_);
	tree->SetBranchAddress((prefix_ + "_pz").c_str(), pz_);
	tree->SetBranchAddress((prefix_ + "_PtUnc").c_str(), PtUnc_);
	tree->SetBranchAddress((prefix_ + "_ChiQ").c_str(), ChiQ_);
	tree->SetBranchAddress((prefix_ + "_NDOF").c_str(), NDOF_);
	tree->SetBranchAddress((prefix_ + "_ECalEnergy").c_str(), ECalEnergy_);
	tree->SetBranchAddress((prefix_ + "_HCalEnergy").c_str(), HCalEnergy_);
	tree->SetBranchAddress((prefix_ + "_TriggerMatching").c_str(), TriggerMatching_);
	PFR3_->SetUpRead(tree);
	PFR4_->SetUpRead(tree);
	InnerTrack_->SetUpRead(tree);
	DetR3_->SetUpRead(tree);
	DetR4_->SetUpRead(tree);
}

void Data_IOMuon::Load(TTree* tree, bool load)
{
	tree->SetBranchStatus((prefix_ + "_count").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_VertexNumber").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Charge").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NumChamber").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NumChambersWithSegments").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NumValidMuonHits").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NumMatchedStations").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_px").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_py").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_pz").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_PtUnc").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_ChiQ").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NDOF").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_ECalEnergy").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_HCalEnergy").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_TriggerMatching").c_str(), load);
	PFR3_->Load(tree, load);
	PFR4_->Load(tree, load);
	InnerTrack_->Load(tree, load);
	DetR3_->Load(tree, load);
	DetR4_->Load(tree, load);
}



//IOMuon == IOMuon == IOMuon == IOMuon == IOMuon == IOMuon == IOMuon == IOMuon == IOMuon == IOMuon == IOMuon == IOMuon == IOMuon == IOMuon == IOMuon == 
BaseIO* IOMuon::baseio = 0;
IOMuon::IOMuon(Data_IOMuon* data, UInt_t number) : 
number_(number),
data_(data)
{
	Init();
}

IOMuon::IOMuon(const IOMuon& _iomuon) : 
number_( _iomuon.number_),
data_( _iomuon.data_)
{
}

void IOMuon::Init()
{
	if(baseio->IsWritable())
	{
		data_->count_ = number_+1;
	}
}

PFIsolation IOMuon::PFR3() const
{
	return PFIsolation(data_->PFR3_, number_);
}

PFIsolation IOMuon::PFR4() const
{
	return PFIsolation(data_->PFR4_, number_);
}

Int_t IOMuon::VertexNumber() const
{
	return data_->VertexNumber_[number_];
}

Int_t IOMuon::Charge() const
{
	return data_->Charge_[number_];
}

Int_t IOMuon::NumChamber() const
{
	return data_->NumChamber_[number_];
}

Int_t IOMuon::NumChambersWithSegments() const
{
	return data_->NumChambersWithSegments_[number_];
}

Int_t IOMuon::NumValidMuonHits() const
{
	return data_->NumValidMuonHits_[number_];
}

Int_t IOMuon::NumMatchedStations() const
{
	return data_->NumMatchedStations_[number_];
}

Float_t IOMuon::px() const
{
	return data_->px_[number_];
}

Float_t IOMuon::py() const
{
	return data_->py_[number_];
}

Float_t IOMuon::pz() const
{
	return data_->pz_[number_];
}

Float_t IOMuon::PtUnc() const
{
	return data_->PtUnc_[number_];
}

Float_t IOMuon::ChiQ() const
{
	return data_->ChiQ_[number_];
}

Float_t IOMuon::NDOF() const
{
	return data_->NDOF_[number_];
}

Float_t IOMuon::ECalEnergy() const
{
	return data_->ECalEnergy_[number_];
}

Float_t IOMuon::HCalEnergy() const
{
	return data_->HCalEnergy_[number_];
}

UInt_t IOMuon::TriggerMatching() const
{
	return data_->TriggerMatching_[number_];
}

IOTrack IOMuon::InnerTrack() const
{
	return IOTrack(data_->InnerTrack_, number_);
}

DetIsolation IOMuon::DetR3() const
{
	return DetIsolation(data_->DetR3_, number_);
}

DetIsolation IOMuon::DetR4() const
{
	return DetIsolation(data_->DetR4_, number_);
}

void IOMuon::VertexNumber(Int_t _VertexNumber)
{
	data_->VertexNumber_[number_] = _VertexNumber;
}

void IOMuon::Charge(Int_t _Charge)
{
	data_->Charge_[number_] = _Charge;
}

void IOMuon::NumChamber(Int_t _NumChamber)
{
	data_->NumChamber_[number_] = _NumChamber;
}

void IOMuon::NumChambersWithSegments(Int_t _NumChambersWithSegments)
{
	data_->NumChambersWithSegments_[number_] = _NumChambersWithSegments;
}

void IOMuon::NumValidMuonHits(Int_t _NumValidMuonHits)
{
	data_->NumValidMuonHits_[number_] = _NumValidMuonHits;
}

void IOMuon::NumMatchedStations(Int_t _NumMatchedStations)
{
	data_->NumMatchedStations_[number_] = _NumMatchedStations;
}

void IOMuon::px(Float_t _px)
{
	data_->px_[number_] = _px;
}

void IOMuon::py(Float_t _py)
{
	data_->py_[number_] = _py;
}

void IOMuon::pz(Float_t _pz)
{
	data_->pz_[number_] = _pz;
}

void IOMuon::PtUnc(Float_t _PtUnc)
{
	data_->PtUnc_[number_] = _PtUnc;
}

void IOMuon::ChiQ(Float_t _ChiQ)
{
	data_->ChiQ_[number_] = _ChiQ;
}

void IOMuon::NDOF(Float_t _NDOF)
{
	data_->NDOF_[number_] = _NDOF;
}

void IOMuon::ECalEnergy(Float_t _ECalEnergy)
{
	data_->ECalEnergy_[number_] = _ECalEnergy;
}

void IOMuon::HCalEnergy(Float_t _HCalEnergy)
{
	data_->HCalEnergy_[number_] = _HCalEnergy;
}

void IOMuon::TriggerMatching(UInt_t _TriggerMatching)
{
	data_->TriggerMatching_[number_] = _TriggerMatching;
}



//Data_IOMET Data_IOMET Data_IOMET Data_IOMET Data_IOMET Data_IOMET Data_IOMET Data_IOMET Data_IOMET Data_IOMET 
BaseIO* Data_IOMET::baseio = 0;
Data_IOMET::Data_IOMET(UInt_t size, std::string prefix = "") : 
size_(size),
prefix_(prefix)
{
	pfmetpx_ = new Float_t[size_];
	pfmetpy_ = new Float_t[size_];
	pfmetpxcorr_ = new Float_t[size_];
	pfmetpycorr_ = new Float_t[size_];
}

Data_IOMET::~Data_IOMET()
{
	delete[] pfmetpx_;
	delete[] pfmetpy_;
	delete[] pfmetpxcorr_;
	delete[] pfmetpycorr_;
}

void Data_IOMET::Fill()
{
	count_ = 0;
}

void Data_IOMET::SetUpWrite(TTree* tree)
{
	tree->Branch((prefix_ + "_count").c_str(), &count_, (prefix_ + "_count/i").c_str());
	tree->Branch((prefix_ + "_pfmetpx").c_str(), pfmetpx_, (prefix_ + "_pfmetpx[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_pfmetpy").c_str(), pfmetpy_, (prefix_ + "_pfmetpy[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_pfmetpxcorr").c_str(), pfmetpxcorr_, (prefix_ + "_pfmetpxcorr[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_pfmetpycorr").c_str(), pfmetpycorr_, (prefix_ + "_pfmetpycorr[" + prefix_ + "_count]/F").c_str());
}

void Data_IOMET::SetUpRead(TTree* tree)
{
	tree->SetBranchAddress((prefix_ + "_count").c_str(), &count_);
	tree->SetBranchAddress((prefix_ + "_pfmetpx").c_str(), pfmetpx_);
	tree->SetBranchAddress((prefix_ + "_pfmetpy").c_str(), pfmetpy_);
	tree->SetBranchAddress((prefix_ + "_pfmetpxcorr").c_str(), pfmetpxcorr_);
	tree->SetBranchAddress((prefix_ + "_pfmetpycorr").c_str(), pfmetpycorr_);
}

void Data_IOMET::Load(TTree* tree, bool load)
{
	tree->SetBranchStatus((prefix_ + "_count").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_pfmetpx").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_pfmetpy").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_pfmetpxcorr").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_pfmetpycorr").c_str(), load);
}



//IOMET == IOMET == IOMET == IOMET == IOMET == IOMET == IOMET == IOMET == IOMET == IOMET == IOMET == IOMET == IOMET == IOMET == IOMET == 
BaseIO* IOMET::baseio = 0;
IOMET::IOMET(Data_IOMET* data, UInt_t number) : 
number_(number),
data_(data)
{
	Init();
}

IOMET::IOMET(const IOMET& _iomet) : 
number_( _iomet.number_),
data_( _iomet.data_)
{
}

void IOMET::Init()
{
	if(baseio->IsWritable())
	{
		data_->count_ = number_+1;
	}
}

Float_t IOMET::pfmetpx() const
{
	return data_->pfmetpx_[number_];
}

Float_t IOMET::pfmetpy() const
{
	return data_->pfmetpy_[number_];
}

Float_t IOMET::pfmetpxcorr() const
{
	return data_->pfmetpxcorr_[number_];
}

Float_t IOMET::pfmetpycorr() const
{
	return data_->pfmetpycorr_[number_];
}

void IOMET::pfmetpx(Float_t _pfmetpx)
{
	data_->pfmetpx_[number_] = _pfmetpx;
}

void IOMET::pfmetpy(Float_t _pfmetpy)
{
	data_->pfmetpy_[number_] = _pfmetpy;
}

void IOMET::pfmetpxcorr(Float_t _pfmetpxcorr)
{
	data_->pfmetpxcorr_[number_] = _pfmetpxcorr;
}

void IOMET::pfmetpycorr(Float_t _pfmetpycorr)
{
	data_->pfmetpycorr_[number_] = _pfmetpycorr;
}



//Data_IOTrack Data_IOTrack Data_IOTrack Data_IOTrack Data_IOTrack Data_IOTrack Data_IOTrack Data_IOTrack Data_IOTrack Data_IOTrack 
BaseIO* Data_IOTrack::baseio = 0;
Data_IOTrack::Data_IOTrack(UInt_t size, std::string prefix = "") : 
size_(size),
prefix_(prefix)
{
	VertexNumber_ = new Int_t[size_];
	Charge_ = new Char_t[size_];
	NHits_ = new UChar_t[size_];
	NPixelHits_ = new UChar_t[size_];
	NMissingHits_ = new UChar_t[size_];
	NPixelLayers_ = new UChar_t[size_];
	NStripLayers_ = new UChar_t[size_];
	px_ = new Float_t[size_];
	py_ = new Float_t[size_];
	pz_ = new Float_t[size_];
	ChiQ_ = new Float_t[size_];
	NDOF_ = new Float_t[size_];
	Dxy_ = new Float_t[size_];
	DxyUnc_ = new Float_t[size_];
	Dz_ = new Float_t[size_];
	DzUnc_ = new Float_t[size_];
	DeDx_ = new Float_t[size_];
}

Data_IOTrack::~Data_IOTrack()
{
	delete[] VertexNumber_;
	delete[] Charge_;
	delete[] NHits_;
	delete[] NPixelHits_;
	delete[] NMissingHits_;
	delete[] NPixelLayers_;
	delete[] NStripLayers_;
	delete[] px_;
	delete[] py_;
	delete[] pz_;
	delete[] ChiQ_;
	delete[] NDOF_;
	delete[] Dxy_;
	delete[] DxyUnc_;
	delete[] Dz_;
	delete[] DzUnc_;
	delete[] DeDx_;
}

void Data_IOTrack::Fill()
{
	count_ = 0;
}

void Data_IOTrack::SetUpWrite(TTree* tree)
{
	tree->Branch((prefix_ + "_count").c_str(), &count_, (prefix_ + "_count/i").c_str());
	tree->Branch((prefix_ + "_VertexNumber").c_str(), VertexNumber_, (prefix_ + "_VertexNumber[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_Charge").c_str(), Charge_, (prefix_ + "_Charge[" + prefix_ + "_count]/B").c_str());
	tree->Branch((prefix_ + "_NHits").c_str(), NHits_, (prefix_ + "_NHits[" + prefix_ + "_count]/b").c_str());
	tree->Branch((prefix_ + "_NPixelHits").c_str(), NPixelHits_, (prefix_ + "_NPixelHits[" + prefix_ + "_count]/b").c_str());
	tree->Branch((prefix_ + "_NMissingHits").c_str(), NMissingHits_, (prefix_ + "_NMissingHits[" + prefix_ + "_count]/b").c_str());
	tree->Branch((prefix_ + "_NPixelLayers").c_str(), NPixelLayers_, (prefix_ + "_NPixelLayers[" + prefix_ + "_count]/b").c_str());
	tree->Branch((prefix_ + "_NStripLayers").c_str(), NStripLayers_, (prefix_ + "_NStripLayers[" + prefix_ + "_count]/b").c_str());
	tree->Branch((prefix_ + "_px").c_str(), px_, (prefix_ + "_px[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_py").c_str(), py_, (prefix_ + "_py[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_pz").c_str(), pz_, (prefix_ + "_pz[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_ChiQ").c_str(), ChiQ_, (prefix_ + "_ChiQ[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_NDOF").c_str(), NDOF_, (prefix_ + "_NDOF[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_Dxy").c_str(), Dxy_, (prefix_ + "_Dxy[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_DxyUnc").c_str(), DxyUnc_, (prefix_ + "_DxyUnc[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_Dz").c_str(), Dz_, (prefix_ + "_Dz[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_DzUnc").c_str(), DzUnc_, (prefix_ + "_DzUnc[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_DeDx").c_str(), DeDx_, (prefix_ + "_DeDx[" + prefix_ + "_count]/F").c_str());
}

void Data_IOTrack::SetUpRead(TTree* tree)
{
	tree->SetBranchAddress((prefix_ + "_count").c_str(), &count_);
	tree->SetBranchAddress((prefix_ + "_VertexNumber").c_str(), VertexNumber_);
	tree->SetBranchAddress((prefix_ + "_Charge").c_str(), Charge_);
	tree->SetBranchAddress((prefix_ + "_NHits").c_str(), NHits_);
	tree->SetBranchAddress((prefix_ + "_NPixelHits").c_str(), NPixelHits_);
	tree->SetBranchAddress((prefix_ + "_NMissingHits").c_str(), NMissingHits_);
	tree->SetBranchAddress((prefix_ + "_NPixelLayers").c_str(), NPixelLayers_);
	tree->SetBranchAddress((prefix_ + "_NStripLayers").c_str(), NStripLayers_);
	tree->SetBranchAddress((prefix_ + "_px").c_str(), px_);
	tree->SetBranchAddress((prefix_ + "_py").c_str(), py_);
	tree->SetBranchAddress((prefix_ + "_pz").c_str(), pz_);
	tree->SetBranchAddress((prefix_ + "_ChiQ").c_str(), ChiQ_);
	tree->SetBranchAddress((prefix_ + "_NDOF").c_str(), NDOF_);
	tree->SetBranchAddress((prefix_ + "_Dxy").c_str(), Dxy_);
	tree->SetBranchAddress((prefix_ + "_DxyUnc").c_str(), DxyUnc_);
	tree->SetBranchAddress((prefix_ + "_Dz").c_str(), Dz_);
	tree->SetBranchAddress((prefix_ + "_DzUnc").c_str(), DzUnc_);
	tree->SetBranchAddress((prefix_ + "_DeDx").c_str(), DeDx_);
}

void Data_IOTrack::Load(TTree* tree, bool load)
{
	tree->SetBranchStatus((prefix_ + "_count").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_VertexNumber").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Charge").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NHits").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NPixelHits").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NMissingHits").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NPixelLayers").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NStripLayers").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_px").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_py").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_pz").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_ChiQ").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NDOF").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Dxy").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_DxyUnc").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Dz").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_DzUnc").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_DeDx").c_str(), load);
}



//IOTrack == IOTrack == IOTrack == IOTrack == IOTrack == IOTrack == IOTrack == IOTrack == IOTrack == IOTrack == IOTrack == IOTrack == IOTrack == IOTrack == IOTrack == 
BaseIO* IOTrack::baseio = 0;
IOTrack::IOTrack(Data_IOTrack* data, UInt_t number) : 
number_(number),
data_(data)
{
	Init();
}

IOTrack::IOTrack(const IOTrack& _iotrack) : 
number_( _iotrack.number_),
data_( _iotrack.data_)
{
}

void IOTrack::Init()
{
	if(baseio->IsWritable())
	{
		data_->count_ = number_+1;
	}
}

Int_t IOTrack::VertexNumber() const
{
	return data_->VertexNumber_[number_];
}

Char_t IOTrack::Charge() const
{
	return data_->Charge_[number_];
}

UChar_t IOTrack::NHits() const
{
	return data_->NHits_[number_];
}

UChar_t IOTrack::NPixelHits() const
{
	return data_->NPixelHits_[number_];
}

UChar_t IOTrack::NMissingHits() const
{
	return data_->NMissingHits_[number_];
}

UChar_t IOTrack::NPixelLayers() const
{
	return data_->NPixelLayers_[number_];
}

UChar_t IOTrack::NStripLayers() const
{
	return data_->NStripLayers_[number_];
}

Float_t IOTrack::px() const
{
	return data_->px_[number_];
}

Float_t IOTrack::py() const
{
	return data_->py_[number_];
}

Float_t IOTrack::pz() const
{
	return data_->pz_[number_];
}

Float_t IOTrack::ChiQ() const
{
	return data_->ChiQ_[number_];
}

Float_t IOTrack::NDOF() const
{
	return data_->NDOF_[number_];
}

Float_t IOTrack::Dxy() const
{
	return data_->Dxy_[number_];
}

Float_t IOTrack::DxyUnc() const
{
	return data_->DxyUnc_[number_];
}

Float_t IOTrack::Dz() const
{
	return data_->Dz_[number_];
}

Float_t IOTrack::DzUnc() const
{
	return data_->DzUnc_[number_];
}

Float_t IOTrack::DeDx() const
{
	return data_->DeDx_[number_];
}

void IOTrack::VertexNumber(Int_t _VertexNumber)
{
	data_->VertexNumber_[number_] = _VertexNumber;
}

void IOTrack::Charge(Char_t _Charge)
{
	data_->Charge_[number_] = _Charge;
}

void IOTrack::NHits(UChar_t _NHits)
{
	data_->NHits_[number_] = _NHits;
}

void IOTrack::NPixelHits(UChar_t _NPixelHits)
{
	data_->NPixelHits_[number_] = _NPixelHits;
}

void IOTrack::NMissingHits(UChar_t _NMissingHits)
{
	data_->NMissingHits_[number_] = _NMissingHits;
}

void IOTrack::NPixelLayers(UChar_t _NPixelLayers)
{
	data_->NPixelLayers_[number_] = _NPixelLayers;
}

void IOTrack::NStripLayers(UChar_t _NStripLayers)
{
	data_->NStripLayers_[number_] = _NStripLayers;
}

void IOTrack::px(Float_t _px)
{
	data_->px_[number_] = _px;
}

void IOTrack::py(Float_t _py)
{
	data_->py_[number_] = _py;
}

void IOTrack::pz(Float_t _pz)
{
	data_->pz_[number_] = _pz;
}

void IOTrack::ChiQ(Float_t _ChiQ)
{
	data_->ChiQ_[number_] = _ChiQ;
}

void IOTrack::NDOF(Float_t _NDOF)
{
	data_->NDOF_[number_] = _NDOF;
}

void IOTrack::Dxy(Float_t _Dxy)
{
	data_->Dxy_[number_] = _Dxy;
}

void IOTrack::DxyUnc(Float_t _DxyUnc)
{
	data_->DxyUnc_[number_] = _DxyUnc;
}

void IOTrack::Dz(Float_t _Dz)
{
	data_->Dz_[number_] = _Dz;
}

void IOTrack::DzUnc(Float_t _DzUnc)
{
	data_->DzUnc_[number_] = _DzUnc;
}

void IOTrack::DeDx(Float_t _DeDx)
{
	data_->DeDx_[number_] = _DeDx;
}



//Data_IOPosition Data_IOPosition Data_IOPosition Data_IOPosition Data_IOPosition Data_IOPosition Data_IOPosition Data_IOPosition Data_IOPosition Data_IOPosition 
BaseIO* Data_IOPosition::baseio = 0;
Data_IOPosition::Data_IOPosition(UInt_t size, std::string prefix = "") : 
size_(size),
prefix_(prefix)
{
	x_ = new Double_t[size_];
	y_ = new Double_t[size_];
	z_ = new Double_t[size_];
}

Data_IOPosition::~Data_IOPosition()
{
	delete[] x_;
	delete[] y_;
	delete[] z_;
}

void Data_IOPosition::Fill()
{
	count_ = 0;
}

void Data_IOPosition::SetUpWrite(TTree* tree)
{
	tree->Branch((prefix_ + "_count").c_str(), &count_, (prefix_ + "_count/i").c_str());
	tree->Branch((prefix_ + "_x").c_str(), x_, (prefix_ + "_x[" + prefix_ + "_count]/D").c_str());
	tree->Branch((prefix_ + "_y").c_str(), y_, (prefix_ + "_y[" + prefix_ + "_count]/D").c_str());
	tree->Branch((prefix_ + "_z").c_str(), z_, (prefix_ + "_z[" + prefix_ + "_count]/D").c_str());
}

void Data_IOPosition::SetUpRead(TTree* tree)
{
	tree->SetBranchAddress((prefix_ + "_count").c_str(), &count_);
	tree->SetBranchAddress((prefix_ + "_x").c_str(), x_);
	tree->SetBranchAddress((prefix_ + "_y").c_str(), y_);
	tree->SetBranchAddress((prefix_ + "_z").c_str(), z_);
}

void Data_IOPosition::Load(TTree* tree, bool load)
{
	tree->SetBranchStatus((prefix_ + "_count").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_x").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_y").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_z").c_str(), load);
}



//IOPosition == IOPosition == IOPosition == IOPosition == IOPosition == IOPosition == IOPosition == IOPosition == IOPosition == IOPosition == IOPosition == IOPosition == IOPosition == IOPosition == IOPosition == 
BaseIO* IOPosition::baseio = 0;
IOPosition::IOPosition(Data_IOPosition* data, UInt_t number) : 
number_(number),
data_(data)
{
	Init();
}

IOPosition::IOPosition(const IOPosition& _ioposition) : 
number_( _ioposition.number_),
data_( _ioposition.data_)
{
}

void IOPosition::Init()
{
	if(baseio->IsWritable())
	{
		data_->count_ = number_+1;
	}
}

Double_t IOPosition::x() const
{
	return data_->x_[number_];
}

Double_t IOPosition::y() const
{
	return data_->y_[number_];
}

Double_t IOPosition::z() const
{
	return data_->z_[number_];
}

void IOPosition::x(Double_t _x)
{
	data_->x_[number_] = _x;
}

void IOPosition::y(Double_t _y)
{
	data_->y_[number_] = _y;
}

void IOPosition::z(Double_t _z)
{
	data_->z_[number_] = _z;
}



//Data_PFIsolation Data_PFIsolation Data_PFIsolation Data_PFIsolation Data_PFIsolation Data_PFIsolation Data_PFIsolation Data_PFIsolation Data_PFIsolation Data_PFIsolation 
BaseIO* Data_PFIsolation::baseio = 0;
Data_PFIsolation::Data_PFIsolation(UInt_t size, std::string prefix = "") : 
size_(size),
prefix_(prefix)
{
	NumCharged_ = new Int_t[size_];
	NumNeutral_ = new Int_t[size_];
	NumHadron_ = new Int_t[size_];
	NumPhoton_ = new Int_t[size_];
	Charged_ = new Float_t[size_];
	Neutral_ = new Float_t[size_];
	Hadron_ = new Float_t[size_];
	Photon_ = new Float_t[size_];
}

Data_PFIsolation::~Data_PFIsolation()
{
	delete[] NumCharged_;
	delete[] NumNeutral_;
	delete[] NumHadron_;
	delete[] NumPhoton_;
	delete[] Charged_;
	delete[] Neutral_;
	delete[] Hadron_;
	delete[] Photon_;
}

void Data_PFIsolation::Fill()
{
	count_ = 0;
}

void Data_PFIsolation::SetUpWrite(TTree* tree)
{
	tree->Branch((prefix_ + "_count").c_str(), &count_, (prefix_ + "_count/i").c_str());
	tree->Branch((prefix_ + "_NumCharged").c_str(), NumCharged_, (prefix_ + "_NumCharged[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_NumNeutral").c_str(), NumNeutral_, (prefix_ + "_NumNeutral[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_NumHadron").c_str(), NumHadron_, (prefix_ + "_NumHadron[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_NumPhoton").c_str(), NumPhoton_, (prefix_ + "_NumPhoton[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_Charged").c_str(), Charged_, (prefix_ + "_Charged[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_Neutral").c_str(), Neutral_, (prefix_ + "_Neutral[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_Hadron").c_str(), Hadron_, (prefix_ + "_Hadron[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_Photon").c_str(), Photon_, (prefix_ + "_Photon[" + prefix_ + "_count]/F").c_str());
}

void Data_PFIsolation::SetUpRead(TTree* tree)
{
	tree->SetBranchAddress((prefix_ + "_count").c_str(), &count_);
	tree->SetBranchAddress((prefix_ + "_NumCharged").c_str(), NumCharged_);
	tree->SetBranchAddress((prefix_ + "_NumNeutral").c_str(), NumNeutral_);
	tree->SetBranchAddress((prefix_ + "_NumHadron").c_str(), NumHadron_);
	tree->SetBranchAddress((prefix_ + "_NumPhoton").c_str(), NumPhoton_);
	tree->SetBranchAddress((prefix_ + "_Charged").c_str(), Charged_);
	tree->SetBranchAddress((prefix_ + "_Neutral").c_str(), Neutral_);
	tree->SetBranchAddress((prefix_ + "_Hadron").c_str(), Hadron_);
	tree->SetBranchAddress((prefix_ + "_Photon").c_str(), Photon_);
}

void Data_PFIsolation::Load(TTree* tree, bool load)
{
	tree->SetBranchStatus((prefix_ + "_count").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NumCharged").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NumNeutral").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NumHadron").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NumPhoton").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Charged").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Neutral").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Hadron").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Photon").c_str(), load);
}



//PFIsolation == PFIsolation == PFIsolation == PFIsolation == PFIsolation == PFIsolation == PFIsolation == PFIsolation == PFIsolation == PFIsolation == PFIsolation == PFIsolation == PFIsolation == PFIsolation == PFIsolation == 
BaseIO* PFIsolation::baseio = 0;
PFIsolation::PFIsolation(Data_PFIsolation* data, UInt_t number) : 
number_(number),
data_(data)
{
	Init();
}

PFIsolation::PFIsolation(const PFIsolation& _pfisolation) : 
number_( _pfisolation.number_),
data_( _pfisolation.data_)
{
}

void PFIsolation::Init()
{
	if(baseio->IsWritable())
	{
		data_->count_ = number_+1;
	}
}

Int_t PFIsolation::NumCharged() const
{
	return data_->NumCharged_[number_];
}

Int_t PFIsolation::NumNeutral() const
{
	return data_->NumNeutral_[number_];
}

Int_t PFIsolation::NumHadron() const
{
	return data_->NumHadron_[number_];
}

Int_t PFIsolation::NumPhoton() const
{
	return data_->NumPhoton_[number_];
}

Float_t PFIsolation::Charged() const
{
	return data_->Charged_[number_];
}

Float_t PFIsolation::Neutral() const
{
	return data_->Neutral_[number_];
}

Float_t PFIsolation::Hadron() const
{
	return data_->Hadron_[number_];
}

Float_t PFIsolation::Photon() const
{
	return data_->Photon_[number_];
}

void PFIsolation::NumCharged(Int_t _NumCharged)
{
	data_->NumCharged_[number_] = _NumCharged;
}

void PFIsolation::NumNeutral(Int_t _NumNeutral)
{
	data_->NumNeutral_[number_] = _NumNeutral;
}

void PFIsolation::NumHadron(Int_t _NumHadron)
{
	data_->NumHadron_[number_] = _NumHadron;
}

void PFIsolation::NumPhoton(Int_t _NumPhoton)
{
	data_->NumPhoton_[number_] = _NumPhoton;
}

void PFIsolation::Charged(Float_t _Charged)
{
	data_->Charged_[number_] = _Charged;
}

void PFIsolation::Neutral(Float_t _Neutral)
{
	data_->Neutral_[number_] = _Neutral;
}

void PFIsolation::Hadron(Float_t _Hadron)
{
	data_->Hadron_[number_] = _Hadron;
}

void PFIsolation::Photon(Float_t _Photon)
{
	data_->Photon_[number_] = _Photon;
}



//Data_IOElectron Data_IOElectron Data_IOElectron Data_IOElectron Data_IOElectron Data_IOElectron Data_IOElectron Data_IOElectron Data_IOElectron Data_IOElectron 
BaseIO* Data_IOElectron::baseio = 0;
Data_IOElectron::Data_IOElectron(UInt_t size, std::string prefix = "") : 
size_(size),
prefix_(prefix)
, ECalPos_(new Data_IOPosition(size_, prefix_ + "_ECalPos"))
, PFR3_(new Data_PFIsolation(size_, prefix_ + "_PFR3"))
, PFR4_(new Data_PFIsolation(size_, prefix_ + "_PFR4"))
, GSFTrack_(new Data_IOTrack(size_, prefix_ + "_GSFTrack"))
, DetR3_(new Data_DetIsolation(size_, prefix_ + "_DetR3"))
, DetR4_(new Data_DetIsolation(size_, prefix_ + "_DetR4"))
, SC_(new Data_IOSuperCluster(size_, prefix_ + "_SC"))
{
	px_ = new Float_t[size_];
	py_ = new Float_t[size_];
	pz_ = new Float_t[size_];
	DeltaEtaSCTrack_ = new Float_t[size_];
	DeltaPhiSCTrack_ = new Float_t[size_];
	ESCOverETrack_ = new Float_t[size_];
	E1x5_ = new Float_t[size_];
	E2x5_ = new Float_t[size_];
	E5x5_ = new Float_t[size_];
	R9_ = new Float_t[size_];
	SigmaIEtaIEta_ = new Float_t[size_];
	SigmaIPhiIPhi_ = new Float_t[size_];
	SigmaIEtaIPhi_ = new Float_t[size_];
	EHCalTowerOverECal_ = new Float_t[size_];
	VertexNumber_ = new Int_t[size_];
	Trigger_ = new Int_t[size_];
}

Data_IOElectron::~Data_IOElectron()
{
	delete[] px_;
	delete[] py_;
	delete[] pz_;
	delete[] DeltaEtaSCTrack_;
	delete[] DeltaPhiSCTrack_;
	delete[] ESCOverETrack_;
	delete[] E1x5_;
	delete[] E2x5_;
	delete[] E5x5_;
	delete[] R9_;
	delete[] SigmaIEtaIEta_;
	delete[] SigmaIPhiIPhi_;
	delete[] SigmaIEtaIPhi_;
	delete[] EHCalTowerOverECal_;
	delete[] VertexNumber_;
	delete[] Trigger_;
	delete ECalPos_;
	delete PFR3_;
	delete PFR4_;
	delete GSFTrack_;
	delete DetR3_;
	delete DetR4_;
	delete SC_;
}

void Data_IOElectron::Fill()
{
	count_ = 0;
	ECalPos_->Fill();
	PFR3_->Fill();
	PFR4_->Fill();
	GSFTrack_->Fill();
	DetR3_->Fill();
	DetR4_->Fill();
	SC_->Fill();
}

void Data_IOElectron::SetUpWrite(TTree* tree)
{
	tree->Branch((prefix_ + "_count").c_str(), &count_, (prefix_ + "_count/i").c_str());
	tree->Branch((prefix_ + "_px").c_str(), px_, (prefix_ + "_px[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_py").c_str(), py_, (prefix_ + "_py[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_pz").c_str(), pz_, (prefix_ + "_pz[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_DeltaEtaSCTrack").c_str(), DeltaEtaSCTrack_, (prefix_ + "_DeltaEtaSCTrack[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_DeltaPhiSCTrack").c_str(), DeltaPhiSCTrack_, (prefix_ + "_DeltaPhiSCTrack[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_ESCOverETrack").c_str(), ESCOverETrack_, (prefix_ + "_ESCOverETrack[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_E1x5").c_str(), E1x5_, (prefix_ + "_E1x5[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_E2x5").c_str(), E2x5_, (prefix_ + "_E2x5[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_E5x5").c_str(), E5x5_, (prefix_ + "_E5x5[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_R9").c_str(), R9_, (prefix_ + "_R9[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_SigmaIEtaIEta").c_str(), SigmaIEtaIEta_, (prefix_ + "_SigmaIEtaIEta[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_SigmaIPhiIPhi").c_str(), SigmaIPhiIPhi_, (prefix_ + "_SigmaIPhiIPhi[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_SigmaIEtaIPhi").c_str(), SigmaIEtaIPhi_, (prefix_ + "_SigmaIEtaIPhi[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_EHCalTowerOverECal").c_str(), EHCalTowerOverECal_, (prefix_ + "_EHCalTowerOverECal[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_VertexNumber").c_str(), VertexNumber_, (prefix_ + "_VertexNumber[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_Trigger").c_str(), Trigger_, (prefix_ + "_Trigger[" + prefix_ + "_count]/I").c_str());
	ECalPos_->SetUpWrite(tree);
	PFR3_->SetUpWrite(tree);
	PFR4_->SetUpWrite(tree);
	GSFTrack_->SetUpWrite(tree);
	DetR3_->SetUpWrite(tree);
	DetR4_->SetUpWrite(tree);
	SC_->SetUpWrite(tree);
}

void Data_IOElectron::SetUpRead(TTree* tree)
{
	tree->SetBranchAddress((prefix_ + "_count").c_str(), &count_);
	tree->SetBranchAddress((prefix_ + "_px").c_str(), px_);
	tree->SetBranchAddress((prefix_ + "_py").c_str(), py_);
	tree->SetBranchAddress((prefix_ + "_pz").c_str(), pz_);
	tree->SetBranchAddress((prefix_ + "_DeltaEtaSCTrack").c_str(), DeltaEtaSCTrack_);
	tree->SetBranchAddress((prefix_ + "_DeltaPhiSCTrack").c_str(), DeltaPhiSCTrack_);
	tree->SetBranchAddress((prefix_ + "_ESCOverETrack").c_str(), ESCOverETrack_);
	tree->SetBranchAddress((prefix_ + "_E1x5").c_str(), E1x5_);
	tree->SetBranchAddress((prefix_ + "_E2x5").c_str(), E2x5_);
	tree->SetBranchAddress((prefix_ + "_E5x5").c_str(), E5x5_);
	tree->SetBranchAddress((prefix_ + "_R9").c_str(), R9_);
	tree->SetBranchAddress((prefix_ + "_SigmaIEtaIEta").c_str(), SigmaIEtaIEta_);
	tree->SetBranchAddress((prefix_ + "_SigmaIPhiIPhi").c_str(), SigmaIPhiIPhi_);
	tree->SetBranchAddress((prefix_ + "_SigmaIEtaIPhi").c_str(), SigmaIEtaIPhi_);
	tree->SetBranchAddress((prefix_ + "_EHCalTowerOverECal").c_str(), EHCalTowerOverECal_);
	tree->SetBranchAddress((prefix_ + "_VertexNumber").c_str(), VertexNumber_);
	tree->SetBranchAddress((prefix_ + "_Trigger").c_str(), Trigger_);
	ECalPos_->SetUpRead(tree);
	PFR3_->SetUpRead(tree);
	PFR4_->SetUpRead(tree);
	GSFTrack_->SetUpRead(tree);
	DetR3_->SetUpRead(tree);
	DetR4_->SetUpRead(tree);
	SC_->SetUpRead(tree);
}

void Data_IOElectron::Load(TTree* tree, bool load)
{
	tree->SetBranchStatus((prefix_ + "_count").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_px").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_py").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_pz").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_DeltaEtaSCTrack").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_DeltaPhiSCTrack").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_ESCOverETrack").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_E1x5").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_E2x5").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_E5x5").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_R9").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_SigmaIEtaIEta").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_SigmaIPhiIPhi").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_SigmaIEtaIPhi").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_EHCalTowerOverECal").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_VertexNumber").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Trigger").c_str(), load);
	ECalPos_->Load(tree, load);
	PFR3_->Load(tree, load);
	PFR4_->Load(tree, load);
	GSFTrack_->Load(tree, load);
	DetR3_->Load(tree, load);
	DetR4_->Load(tree, load);
	SC_->Load(tree, load);
}



//IOElectron == IOElectron == IOElectron == IOElectron == IOElectron == IOElectron == IOElectron == IOElectron == IOElectron == IOElectron == IOElectron == IOElectron == IOElectron == IOElectron == IOElectron == 
BaseIO* IOElectron::baseio = 0;
IOElectron::IOElectron(Data_IOElectron* data, UInt_t number) : 
number_(number),
data_(data)
{
	Init();
}

IOElectron::IOElectron(const IOElectron& _ioelectron) : 
number_( _ioelectron.number_),
data_( _ioelectron.data_)
{
}

void IOElectron::Init()
{
	if(baseio->IsWritable())
	{
		data_->count_ = number_+1;
	}
}

Float_t IOElectron::px() const
{
	return data_->px_[number_];
}

Float_t IOElectron::py() const
{
	return data_->py_[number_];
}

Float_t IOElectron::pz() const
{
	return data_->pz_[number_];
}

Float_t IOElectron::DeltaEtaSCTrack() const
{
	return data_->DeltaEtaSCTrack_[number_];
}

Float_t IOElectron::DeltaPhiSCTrack() const
{
	return data_->DeltaPhiSCTrack_[number_];
}

Float_t IOElectron::ESCOverETrack() const
{
	return data_->ESCOverETrack_[number_];
}

Float_t IOElectron::E1x5() const
{
	return data_->E1x5_[number_];
}

Float_t IOElectron::E2x5() const
{
	return data_->E2x5_[number_];
}

Float_t IOElectron::E5x5() const
{
	return data_->E5x5_[number_];
}

Float_t IOElectron::R9() const
{
	return data_->R9_[number_];
}

Float_t IOElectron::SigmaIEtaIEta() const
{
	return data_->SigmaIEtaIEta_[number_];
}

Float_t IOElectron::SigmaIPhiIPhi() const
{
	return data_->SigmaIPhiIPhi_[number_];
}

Float_t IOElectron::SigmaIEtaIPhi() const
{
	return data_->SigmaIEtaIPhi_[number_];
}

Float_t IOElectron::EHCalTowerOverECal() const
{
	return data_->EHCalTowerOverECal_[number_];
}

Int_t IOElectron::VertexNumber() const
{
	return data_->VertexNumber_[number_];
}

Int_t IOElectron::Trigger() const
{
	return data_->Trigger_[number_];
}

IOPosition IOElectron::ECalPos() const
{
	return IOPosition(data_->ECalPos_, number_);
}

PFIsolation IOElectron::PFR3() const
{
	return PFIsolation(data_->PFR3_, number_);
}

PFIsolation IOElectron::PFR4() const
{
	return PFIsolation(data_->PFR4_, number_);
}

IOTrack IOElectron::GSFTrack() const
{
	return IOTrack(data_->GSFTrack_, number_);
}

DetIsolation IOElectron::DetR3() const
{
	return DetIsolation(data_->DetR3_, number_);
}

DetIsolation IOElectron::DetR4() const
{
	return DetIsolation(data_->DetR4_, number_);
}

IOSuperCluster IOElectron::SC() const
{
	return IOSuperCluster(data_->SC_, number_);
}

void IOElectron::px(Float_t _px)
{
	data_->px_[number_] = _px;
}

void IOElectron::py(Float_t _py)
{
	data_->py_[number_] = _py;
}

void IOElectron::pz(Float_t _pz)
{
	data_->pz_[number_] = _pz;
}

void IOElectron::DeltaEtaSCTrack(Float_t _DeltaEtaSCTrack)
{
	data_->DeltaEtaSCTrack_[number_] = _DeltaEtaSCTrack;
}

void IOElectron::DeltaPhiSCTrack(Float_t _DeltaPhiSCTrack)
{
	data_->DeltaPhiSCTrack_[number_] = _DeltaPhiSCTrack;
}

void IOElectron::ESCOverETrack(Float_t _ESCOverETrack)
{
	data_->ESCOverETrack_[number_] = _ESCOverETrack;
}

void IOElectron::E1x5(Float_t _E1x5)
{
	data_->E1x5_[number_] = _E1x5;
}

void IOElectron::E2x5(Float_t _E2x5)
{
	data_->E2x5_[number_] = _E2x5;
}

void IOElectron::E5x5(Float_t _E5x5)
{
	data_->E5x5_[number_] = _E5x5;
}

void IOElectron::R9(Float_t _R9)
{
	data_->R9_[number_] = _R9;
}

void IOElectron::SigmaIEtaIEta(Float_t _SigmaIEtaIEta)
{
	data_->SigmaIEtaIEta_[number_] = _SigmaIEtaIEta;
}

void IOElectron::SigmaIPhiIPhi(Float_t _SigmaIPhiIPhi)
{
	data_->SigmaIPhiIPhi_[number_] = _SigmaIPhiIPhi;
}

void IOElectron::SigmaIEtaIPhi(Float_t _SigmaIEtaIPhi)
{
	data_->SigmaIEtaIPhi_[number_] = _SigmaIEtaIPhi;
}

void IOElectron::EHCalTowerOverECal(Float_t _EHCalTowerOverECal)
{
	data_->EHCalTowerOverECal_[number_] = _EHCalTowerOverECal;
}

void IOElectron::VertexNumber(Int_t _VertexNumber)
{
	data_->VertexNumber_[number_] = _VertexNumber;
}

void IOElectron::Trigger(Int_t _Trigger)
{
	data_->Trigger_[number_] = _Trigger;
}



//Data_AllGenParticle Data_AllGenParticle Data_AllGenParticle Data_AllGenParticle Data_AllGenParticle Data_AllGenParticle Data_AllGenParticle Data_AllGenParticle Data_AllGenParticle Data_AllGenParticle 
BaseIO* Data_AllGenParticle::baseio = 0;
Data_AllGenParticle::Data_AllGenParticle(UInt_t size, std::string prefix = "") : 
size_(size),
prefix_(prefix)
{
	PDGID_ = new Int_t[size_];
	Status_ = new Int_t[size_];
	px_ = new Float_t[size_];
	py_ = new Float_t[size_];
	pz_ = new Float_t[size_];
	e_ = new Float_t[size_];
	vx_ = new Float_t[size_];
	vy_ = new Float_t[size_];
	vz_ = new Float_t[size_];
	Mother_num_ = new UInt_t[size_];
	Mother_ = new Int_t[size_*100];
	Daughter_num_ = new UInt_t[size_];
	Daughter_ = new Int_t[size_*100];
}

Data_AllGenParticle::~Data_AllGenParticle()
{
	delete[] PDGID_;
	delete[] Status_;
	delete[] px_;
	delete[] py_;
	delete[] pz_;
	delete[] e_;
	delete[] vx_;
	delete[] vy_;
	delete[] vz_;
	delete[] Mother_;
	delete[] Mother_num_;
	delete[] Daughter_;
	delete[] Daughter_num_;
}

void Data_AllGenParticle::Fill()
{
	count_ = 0;
	Mother_count_ = 0;
	Daughter_count_ = 0;
}

void Data_AllGenParticle::SetUpWrite(TTree* tree)
{
	tree->Branch((prefix_ + "_count").c_str(), &count_, (prefix_ + "_count/i").c_str());
	tree->Branch((prefix_ + "_PDGID").c_str(), PDGID_, (prefix_ + "_PDGID[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_Status").c_str(), Status_, (prefix_ + "_Status[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_px").c_str(), px_, (prefix_ + "_px[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_py").c_str(), py_, (prefix_ + "_py[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_pz").c_str(), pz_, (prefix_ + "_pz[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_e").c_str(), e_, (prefix_ + "_e[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_vx").c_str(), vx_, (prefix_ + "_vx[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_vy").c_str(), vy_, (prefix_ + "_vy[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_vz").c_str(), vz_, (prefix_ + "_vz[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_Mother_count").c_str(), &Mother_count_, (prefix_ + "_Mother_count/i").c_str());
	tree->Branch((prefix_ + "_Mother_num").c_str(), Mother_num_, (prefix_ + "_Mother_num[" + prefix_ + "_count]/i").c_str());
	tree->Branch((prefix_ + "_Mother").c_str(), Mother_, (prefix_ + "_Mother[" + prefix_ + "_Mother_count]/I").c_str());
	tree->Branch((prefix_ + "_Daughter_count").c_str(), &Daughter_count_, (prefix_ + "_Daughter_count/i").c_str());
	tree->Branch((prefix_ + "_Daughter_num").c_str(), Daughter_num_, (prefix_ + "_Daughter_num[" + prefix_ + "_count]/i").c_str());
	tree->Branch((prefix_ + "_Daughter").c_str(), Daughter_, (prefix_ + "_Daughter[" + prefix_ + "_Daughter_count]/I").c_str());
}

void Data_AllGenParticle::SetUpRead(TTree* tree)
{
	tree->SetBranchAddress((prefix_ + "_count").c_str(), &count_);
	tree->SetBranchAddress((prefix_ + "_PDGID").c_str(), PDGID_);
	tree->SetBranchAddress((prefix_ + "_Status").c_str(), Status_);
	tree->SetBranchAddress((prefix_ + "_px").c_str(), px_);
	tree->SetBranchAddress((prefix_ + "_py").c_str(), py_);
	tree->SetBranchAddress((prefix_ + "_pz").c_str(), pz_);
	tree->SetBranchAddress((prefix_ + "_e").c_str(), e_);
	tree->SetBranchAddress((prefix_ + "_vx").c_str(), vx_);
	tree->SetBranchAddress((prefix_ + "_vy").c_str(), vy_);
	tree->SetBranchAddress((prefix_ + "_vz").c_str(), vz_);
	tree->SetBranchAddress((prefix_ + "_Mother_count").c_str(), &Mother_count_);
	tree->SetBranchAddress((prefix_ + "_Mother_num").c_str(), Mother_num_);
	tree->SetBranchAddress((prefix_ + "_Mother").c_str(), Mother_);
	tree->SetBranchAddress((prefix_ + "_Daughter_count").c_str(), &Daughter_count_);
	tree->SetBranchAddress((prefix_ + "_Daughter_num").c_str(), Daughter_num_);
	tree->SetBranchAddress((prefix_ + "_Daughter").c_str(), Daughter_);
}

void Data_AllGenParticle::Load(TTree* tree, bool load)
{
	tree->SetBranchStatus((prefix_ + "_count").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_PDGID").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Status").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_px").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_py").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_pz").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_e").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_vx").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_vy").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_vz").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Mother_count").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Mother_num").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Mother").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Daughter_count").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Daughter_num").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Daughter").c_str(), load);
}



//AllGenParticle == AllGenParticle == AllGenParticle == AllGenParticle == AllGenParticle == AllGenParticle == AllGenParticle == AllGenParticle == AllGenParticle == AllGenParticle == AllGenParticle == AllGenParticle == AllGenParticle == AllGenParticle == AllGenParticle == 
BaseIO* AllGenParticle::baseio = 0;
AllGenParticle::AllGenParticle(Data_AllGenParticle* data, UInt_t number) : 
number_(number),
data_(data)
{
	Init();
}

AllGenParticle::AllGenParticle(const AllGenParticle& _allgenparticle) : 
number_( _allgenparticle.number_),
data_( _allgenparticle.data_)
{
}

void AllGenParticle::Init()
{
	if(baseio->IsWritable())
	{
		if(number_ == 0) {data_->Mother_num_[number_] = 0;}
		else {data_->Mother_num_[number_] = data_->Mother_num_[number_-1];}
		if(number_ == 0) {data_->Daughter_num_[number_] = 0;}
		else {data_->Daughter_num_[number_] = data_->Daughter_num_[number_-1];}
		data_->count_ = number_+1;
	}
}

Int_t AllGenParticle::PDGID() const
{
	return data_->PDGID_[number_];
}

Int_t AllGenParticle::Status() const
{
	return data_->Status_[number_];
}

Float_t AllGenParticle::px() const
{
	return data_->px_[number_];
}

Float_t AllGenParticle::py() const
{
	return data_->py_[number_];
}

Float_t AllGenParticle::pz() const
{
	return data_->pz_[number_];
}

Float_t AllGenParticle::e() const
{
	return data_->e_[number_];
}

Float_t AllGenParticle::vx() const
{
	return data_->vx_[number_];
}

Float_t AllGenParticle::vy() const
{
	return data_->vy_[number_];
}

Float_t AllGenParticle::vz() const
{
	return data_->vz_[number_];
}

UInt_t AllGenParticle::Num_Mother() const
{
	return number_ == 0 ? data_->Mother_num_[number_] : data_->Mother_num_[number_] - data_->Mother_num_[number_-1];
}

Int_t AllGenParticle::Mother(UInt_t n) const
{
	return number_ == 0 ? data_->Mother_[n] : data_->Mother_[data_->Mother_num_[number_-1]  + n];
}

UInt_t AllGenParticle::Num_Daughter() const
{
	return number_ == 0 ? data_->Daughter_num_[number_] : data_->Daughter_num_[number_] - data_->Daughter_num_[number_-1];
}

Int_t AllGenParticle::Daughter(UInt_t n) const
{
	return number_ == 0 ? data_->Daughter_[n] : data_->Daughter_[data_->Daughter_num_[number_-1]  + n];
}

void AllGenParticle::PDGID(Int_t _PDGID)
{
	data_->PDGID_[number_] = _PDGID;
}

void AllGenParticle::Status(Int_t _Status)
{
	data_->Status_[number_] = _Status;
}

void AllGenParticle::px(Float_t _px)
{
	data_->px_[number_] = _px;
}

void AllGenParticle::py(Float_t _py)
{
	data_->py_[number_] = _py;
}

void AllGenParticle::pz(Float_t _pz)
{
	data_->pz_[number_] = _pz;
}

void AllGenParticle::e(Float_t _e)
{
	data_->e_[number_] = _e;
}

void AllGenParticle::vx(Float_t _vx)
{
	data_->vx_[number_] = _vx;
}

void AllGenParticle::vy(Float_t _vy)
{
	data_->vy_[number_] = _vy;
}

void AllGenParticle::vz(Float_t _vz)
{
	data_->vz_[number_] = _vz;
}

void AllGenParticle::Mother(Int_t _Mother, UInt_t n)
{
	if(number_ == 0) {data_->Mother_[n] = _Mother;}
	else {data_->Mother_[data_->Mother_num_[number_-1] +n] = _Mother;}
	data_->Mother_num_[number_]++;
	data_->Mother_count_++;
}

void AllGenParticle::Daughter(Int_t _Daughter, UInt_t n)
{
	if(number_ == 0) {data_->Daughter_[n] = _Daughter;}
	else {data_->Daughter_[data_->Daughter_num_[number_-1] +n] = _Daughter;}
	data_->Daughter_num_[number_]++;
	data_->Daughter_count_++;
}



//Data_DetIsolation Data_DetIsolation Data_DetIsolation Data_DetIsolation Data_DetIsolation Data_DetIsolation Data_DetIsolation Data_DetIsolation Data_DetIsolation Data_DetIsolation 
BaseIO* Data_DetIsolation::baseio = 0;
Data_DetIsolation::Data_DetIsolation(UInt_t size, std::string prefix = "") : 
size_(size),
prefix_(prefix)
{
	NumTrack_ = new Int_t[size_];
	NumECal_ = new Int_t[size_];
	NumHCal_ = new Int_t[size_];
	Track_ = new Float_t[size_];
	ECal_ = new Float_t[size_];
	HCal_ = new Float_t[size_];
}

Data_DetIsolation::~Data_DetIsolation()
{
	delete[] NumTrack_;
	delete[] NumECal_;
	delete[] NumHCal_;
	delete[] Track_;
	delete[] ECal_;
	delete[] HCal_;
}

void Data_DetIsolation::Fill()
{
	count_ = 0;
}

void Data_DetIsolation::SetUpWrite(TTree* tree)
{
	tree->Branch((prefix_ + "_count").c_str(), &count_, (prefix_ + "_count/i").c_str());
	tree->Branch((prefix_ + "_NumTrack").c_str(), NumTrack_, (prefix_ + "_NumTrack[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_NumECal").c_str(), NumECal_, (prefix_ + "_NumECal[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_NumHCal").c_str(), NumHCal_, (prefix_ + "_NumHCal[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_Track").c_str(), Track_, (prefix_ + "_Track[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_ECal").c_str(), ECal_, (prefix_ + "_ECal[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_HCal").c_str(), HCal_, (prefix_ + "_HCal[" + prefix_ + "_count]/F").c_str());
}

void Data_DetIsolation::SetUpRead(TTree* tree)
{
	tree->SetBranchAddress((prefix_ + "_count").c_str(), &count_);
	tree->SetBranchAddress((prefix_ + "_NumTrack").c_str(), NumTrack_);
	tree->SetBranchAddress((prefix_ + "_NumECal").c_str(), NumECal_);
	tree->SetBranchAddress((prefix_ + "_NumHCal").c_str(), NumHCal_);
	tree->SetBranchAddress((prefix_ + "_Track").c_str(), Track_);
	tree->SetBranchAddress((prefix_ + "_ECal").c_str(), ECal_);
	tree->SetBranchAddress((prefix_ + "_HCal").c_str(), HCal_);
}

void Data_DetIsolation::Load(TTree* tree, bool load)
{
	tree->SetBranchStatus((prefix_ + "_count").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NumTrack").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NumECal").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NumHCal").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Track").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_ECal").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_HCal").c_str(), load);
}



//DetIsolation == DetIsolation == DetIsolation == DetIsolation == DetIsolation == DetIsolation == DetIsolation == DetIsolation == DetIsolation == DetIsolation == DetIsolation == DetIsolation == DetIsolation == DetIsolation == DetIsolation == 
BaseIO* DetIsolation::baseio = 0;
DetIsolation::DetIsolation(Data_DetIsolation* data, UInt_t number) : 
number_(number),
data_(data)
{
	Init();
}

DetIsolation::DetIsolation(const DetIsolation& _detisolation) : 
number_( _detisolation.number_),
data_( _detisolation.data_)
{
}

void DetIsolation::Init()
{
	if(baseio->IsWritable())
	{
		data_->count_ = number_+1;
	}
}

Int_t DetIsolation::NumTrack() const
{
	return data_->NumTrack_[number_];
}

Int_t DetIsolation::NumECal() const
{
	return data_->NumECal_[number_];
}

Int_t DetIsolation::NumHCal() const
{
	return data_->NumHCal_[number_];
}

Float_t DetIsolation::Track() const
{
	return data_->Track_[number_];
}

Float_t DetIsolation::ECal() const
{
	return data_->ECal_[number_];
}

Float_t DetIsolation::HCal() const
{
	return data_->HCal_[number_];
}

void DetIsolation::NumTrack(Int_t _NumTrack)
{
	data_->NumTrack_[number_] = _NumTrack;
}

void DetIsolation::NumECal(Int_t _NumECal)
{
	data_->NumECal_[number_] = _NumECal;
}

void DetIsolation::NumHCal(Int_t _NumHCal)
{
	data_->NumHCal_[number_] = _NumHCal;
}

void DetIsolation::Track(Float_t _Track)
{
	data_->Track_[number_] = _Track;
}

void DetIsolation::ECal(Float_t _ECal)
{
	data_->ECal_[number_] = _ECal;
}

void DetIsolation::HCal(Float_t _HCal)
{
	data_->HCal_[number_] = _HCal;
}



//Data_IOPFJet Data_IOPFJet Data_IOPFJet Data_IOPFJet Data_IOPFJet Data_IOPFJet Data_IOPFJet Data_IOPFJet Data_IOPFJet Data_IOPFJet 
BaseIO* Data_IOPFJet::baseio = 0;
Data_IOPFJet::Data_IOPFJet(UInt_t size, std::string prefix = "") : 
size_(size),
prefix_(prefix)
{
	NumCharged_ = new Int_t[size_];
	NumNeutral_ = new Int_t[size_];
	NumHadron_ = new Int_t[size_];
	NumPhoton_ = new Int_t[size_];
	NumElectron_ = new Int_t[size_];
	NumMuon_ = new Int_t[size_];
	MCFlavor_ = new Int_t[size_];
	px_ = new Float_t[size_];
	py_ = new Float_t[size_];
	pz_ = new Float_t[size_];
	e_ = new Float_t[size_];
	HCalEnergy_ = new Float_t[size_];
	ECalEnergy_ = new Float_t[size_];
	TrackEnergy_ = new Float_t[size_];
	ChargedEnergy_ = new Float_t[size_];
	NeutralEnergy_ = new Float_t[size_];
	HadronEnergy_ = new Float_t[size_];
	PhotonEnergy_ = new Float_t[size_];
	ElectronEnergy_ = new Float_t[size_];
	MuonEnergy_ = new Float_t[size_];
	ChargedPtMomPA_ = new Float_t[size_];
	ChargedPtMomPB_ = new Float_t[size_];
	ConstPtMomPA_ = new Float_t[size_];
	ConstPtMomPB_ = new Float_t[size_];
	PtWrongPrimaryVertex_ = new Float_t[size_];
	EnergyCorrection_ = new Float_t[size_];
	EnergyCorrectionUnc_ = new Float_t[size_];
}

Data_IOPFJet::~Data_IOPFJet()
{
	delete[] NumCharged_;
	delete[] NumNeutral_;
	delete[] NumHadron_;
	delete[] NumPhoton_;
	delete[] NumElectron_;
	delete[] NumMuon_;
	delete[] MCFlavor_;
	delete[] px_;
	delete[] py_;
	delete[] pz_;
	delete[] e_;
	delete[] HCalEnergy_;
	delete[] ECalEnergy_;
	delete[] TrackEnergy_;
	delete[] ChargedEnergy_;
	delete[] NeutralEnergy_;
	delete[] HadronEnergy_;
	delete[] PhotonEnergy_;
	delete[] ElectronEnergy_;
	delete[] MuonEnergy_;
	delete[] ChargedPtMomPA_;
	delete[] ChargedPtMomPB_;
	delete[] ConstPtMomPA_;
	delete[] ConstPtMomPB_;
	delete[] PtWrongPrimaryVertex_;
	delete[] EnergyCorrection_;
	delete[] EnergyCorrectionUnc_;
}

void Data_IOPFJet::Fill()
{
	count_ = 0;
}

void Data_IOPFJet::SetUpWrite(TTree* tree)
{
	tree->Branch((prefix_ + "_count").c_str(), &count_, (prefix_ + "_count/i").c_str());
	tree->Branch((prefix_ + "_NumCharged").c_str(), NumCharged_, (prefix_ + "_NumCharged[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_NumNeutral").c_str(), NumNeutral_, (prefix_ + "_NumNeutral[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_NumHadron").c_str(), NumHadron_, (prefix_ + "_NumHadron[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_NumPhoton").c_str(), NumPhoton_, (prefix_ + "_NumPhoton[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_NumElectron").c_str(), NumElectron_, (prefix_ + "_NumElectron[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_NumMuon").c_str(), NumMuon_, (prefix_ + "_NumMuon[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_MCFlavor").c_str(), MCFlavor_, (prefix_ + "_MCFlavor[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_px").c_str(), px_, (prefix_ + "_px[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_py").c_str(), py_, (prefix_ + "_py[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_pz").c_str(), pz_, (prefix_ + "_pz[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_e").c_str(), e_, (prefix_ + "_e[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_HCalEnergy").c_str(), HCalEnergy_, (prefix_ + "_HCalEnergy[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_ECalEnergy").c_str(), ECalEnergy_, (prefix_ + "_ECalEnergy[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_TrackEnergy").c_str(), TrackEnergy_, (prefix_ + "_TrackEnergy[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_ChargedEnergy").c_str(), ChargedEnergy_, (prefix_ + "_ChargedEnergy[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_NeutralEnergy").c_str(), NeutralEnergy_, (prefix_ + "_NeutralEnergy[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_HadronEnergy").c_str(), HadronEnergy_, (prefix_ + "_HadronEnergy[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_PhotonEnergy").c_str(), PhotonEnergy_, (prefix_ + "_PhotonEnergy[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_ElectronEnergy").c_str(), ElectronEnergy_, (prefix_ + "_ElectronEnergy[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_MuonEnergy").c_str(), MuonEnergy_, (prefix_ + "_MuonEnergy[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_ChargedPtMomPA").c_str(), ChargedPtMomPA_, (prefix_ + "_ChargedPtMomPA[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_ChargedPtMomPB").c_str(), ChargedPtMomPB_, (prefix_ + "_ChargedPtMomPB[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_ConstPtMomPA").c_str(), ConstPtMomPA_, (prefix_ + "_ConstPtMomPA[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_ConstPtMomPB").c_str(), ConstPtMomPB_, (prefix_ + "_ConstPtMomPB[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_PtWrongPrimaryVertex").c_str(), PtWrongPrimaryVertex_, (prefix_ + "_PtWrongPrimaryVertex[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_EnergyCorrection").c_str(), EnergyCorrection_, (prefix_ + "_EnergyCorrection[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_EnergyCorrectionUnc").c_str(), EnergyCorrectionUnc_, (prefix_ + "_EnergyCorrectionUnc[" + prefix_ + "_count]/F").c_str());
}

void Data_IOPFJet::SetUpRead(TTree* tree)
{
	tree->SetBranchAddress((prefix_ + "_count").c_str(), &count_);
	tree->SetBranchAddress((prefix_ + "_NumCharged").c_str(), NumCharged_);
	tree->SetBranchAddress((prefix_ + "_NumNeutral").c_str(), NumNeutral_);
	tree->SetBranchAddress((prefix_ + "_NumHadron").c_str(), NumHadron_);
	tree->SetBranchAddress((prefix_ + "_NumPhoton").c_str(), NumPhoton_);
	tree->SetBranchAddress((prefix_ + "_NumElectron").c_str(), NumElectron_);
	tree->SetBranchAddress((prefix_ + "_NumMuon").c_str(), NumMuon_);
	tree->SetBranchAddress((prefix_ + "_MCFlavor").c_str(), MCFlavor_);
	tree->SetBranchAddress((prefix_ + "_px").c_str(), px_);
	tree->SetBranchAddress((prefix_ + "_py").c_str(), py_);
	tree->SetBranchAddress((prefix_ + "_pz").c_str(), pz_);
	tree->SetBranchAddress((prefix_ + "_e").c_str(), e_);
	tree->SetBranchAddress((prefix_ + "_HCalEnergy").c_str(), HCalEnergy_);
	tree->SetBranchAddress((prefix_ + "_ECalEnergy").c_str(), ECalEnergy_);
	tree->SetBranchAddress((prefix_ + "_TrackEnergy").c_str(), TrackEnergy_);
	tree->SetBranchAddress((prefix_ + "_ChargedEnergy").c_str(), ChargedEnergy_);
	tree->SetBranchAddress((prefix_ + "_NeutralEnergy").c_str(), NeutralEnergy_);
	tree->SetBranchAddress((prefix_ + "_HadronEnergy").c_str(), HadronEnergy_);
	tree->SetBranchAddress((prefix_ + "_PhotonEnergy").c_str(), PhotonEnergy_);
	tree->SetBranchAddress((prefix_ + "_ElectronEnergy").c_str(), ElectronEnergy_);
	tree->SetBranchAddress((prefix_ + "_MuonEnergy").c_str(), MuonEnergy_);
	tree->SetBranchAddress((prefix_ + "_ChargedPtMomPA").c_str(), ChargedPtMomPA_);
	tree->SetBranchAddress((prefix_ + "_ChargedPtMomPB").c_str(), ChargedPtMomPB_);
	tree->SetBranchAddress((prefix_ + "_ConstPtMomPA").c_str(), ConstPtMomPA_);
	tree->SetBranchAddress((prefix_ + "_ConstPtMomPB").c_str(), ConstPtMomPB_);
	tree->SetBranchAddress((prefix_ + "_PtWrongPrimaryVertex").c_str(), PtWrongPrimaryVertex_);
	tree->SetBranchAddress((prefix_ + "_EnergyCorrection").c_str(), EnergyCorrection_);
	tree->SetBranchAddress((prefix_ + "_EnergyCorrectionUnc").c_str(), EnergyCorrectionUnc_);
}

void Data_IOPFJet::Load(TTree* tree, bool load)
{
	tree->SetBranchStatus((prefix_ + "_count").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NumCharged").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NumNeutral").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NumHadron").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NumPhoton").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NumElectron").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NumMuon").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_MCFlavor").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_px").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_py").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_pz").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_e").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_HCalEnergy").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_ECalEnergy").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_TrackEnergy").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_ChargedEnergy").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_NeutralEnergy").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_HadronEnergy").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_PhotonEnergy").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_ElectronEnergy").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_MuonEnergy").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_ChargedPtMomPA").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_ChargedPtMomPB").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_ConstPtMomPA").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_ConstPtMomPB").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_PtWrongPrimaryVertex").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_EnergyCorrection").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_EnergyCorrectionUnc").c_str(), load);
}



//IOPFJet == IOPFJet == IOPFJet == IOPFJet == IOPFJet == IOPFJet == IOPFJet == IOPFJet == IOPFJet == IOPFJet == IOPFJet == IOPFJet == IOPFJet == IOPFJet == IOPFJet == 
BaseIO* IOPFJet::baseio = 0;
IOPFJet::IOPFJet(Data_IOPFJet* data, UInt_t number) : 
number_(number),
data_(data)
{
	Init();
}

IOPFJet::IOPFJet(const IOPFJet& _iopfjet) : 
number_( _iopfjet.number_),
data_( _iopfjet.data_)
{
}

void IOPFJet::Init()
{
	if(baseio->IsWritable())
	{
		data_->count_ = number_+1;
	}
}

Int_t IOPFJet::NumCharged() const
{
	return data_->NumCharged_[number_];
}

Int_t IOPFJet::NumNeutral() const
{
	return data_->NumNeutral_[number_];
}

Int_t IOPFJet::NumHadron() const
{
	return data_->NumHadron_[number_];
}

Int_t IOPFJet::NumPhoton() const
{
	return data_->NumPhoton_[number_];
}

Int_t IOPFJet::NumElectron() const
{
	return data_->NumElectron_[number_];
}

Int_t IOPFJet::NumMuon() const
{
	return data_->NumMuon_[number_];
}

Int_t IOPFJet::MCFlavor() const
{
	return data_->MCFlavor_[number_];
}

Float_t IOPFJet::px() const
{
	return data_->px_[number_];
}

Float_t IOPFJet::py() const
{
	return data_->py_[number_];
}

Float_t IOPFJet::pz() const
{
	return data_->pz_[number_];
}

Float_t IOPFJet::e() const
{
	return data_->e_[number_];
}

Float_t IOPFJet::HCalEnergy() const
{
	return data_->HCalEnergy_[number_];
}

Float_t IOPFJet::ECalEnergy() const
{
	return data_->ECalEnergy_[number_];
}

Float_t IOPFJet::TrackEnergy() const
{
	return data_->TrackEnergy_[number_];
}

Float_t IOPFJet::ChargedEnergy() const
{
	return data_->ChargedEnergy_[number_];
}

Float_t IOPFJet::NeutralEnergy() const
{
	return data_->NeutralEnergy_[number_];
}

Float_t IOPFJet::HadronEnergy() const
{
	return data_->HadronEnergy_[number_];
}

Float_t IOPFJet::PhotonEnergy() const
{
	return data_->PhotonEnergy_[number_];
}

Float_t IOPFJet::ElectronEnergy() const
{
	return data_->ElectronEnergy_[number_];
}

Float_t IOPFJet::MuonEnergy() const
{
	return data_->MuonEnergy_[number_];
}

Float_t IOPFJet::ChargedPtMomPA() const
{
	return data_->ChargedPtMomPA_[number_];
}

Float_t IOPFJet::ChargedPtMomPB() const
{
	return data_->ChargedPtMomPB_[number_];
}

Float_t IOPFJet::ConstPtMomPA() const
{
	return data_->ConstPtMomPA_[number_];
}

Float_t IOPFJet::ConstPtMomPB() const
{
	return data_->ConstPtMomPB_[number_];
}

Float_t IOPFJet::PtWrongPrimaryVertex() const
{
	return data_->PtWrongPrimaryVertex_[number_];
}

Float_t IOPFJet::EnergyCorrection() const
{
	return data_->EnergyCorrection_[number_];
}

Float_t IOPFJet::EnergyCorrectionUnc() const
{
	return data_->EnergyCorrectionUnc_[number_];
}

void IOPFJet::NumCharged(Int_t _NumCharged)
{
	data_->NumCharged_[number_] = _NumCharged;
}

void IOPFJet::NumNeutral(Int_t _NumNeutral)
{
	data_->NumNeutral_[number_] = _NumNeutral;
}

void IOPFJet::NumHadron(Int_t _NumHadron)
{
	data_->NumHadron_[number_] = _NumHadron;
}

void IOPFJet::NumPhoton(Int_t _NumPhoton)
{
	data_->NumPhoton_[number_] = _NumPhoton;
}

void IOPFJet::NumElectron(Int_t _NumElectron)
{
	data_->NumElectron_[number_] = _NumElectron;
}

void IOPFJet::NumMuon(Int_t _NumMuon)
{
	data_->NumMuon_[number_] = _NumMuon;
}

void IOPFJet::MCFlavor(Int_t _MCFlavor)
{
	data_->MCFlavor_[number_] = _MCFlavor;
}

void IOPFJet::px(Float_t _px)
{
	data_->px_[number_] = _px;
}

void IOPFJet::py(Float_t _py)
{
	data_->py_[number_] = _py;
}

void IOPFJet::pz(Float_t _pz)
{
	data_->pz_[number_] = _pz;
}

void IOPFJet::e(Float_t _e)
{
	data_->e_[number_] = _e;
}

void IOPFJet::HCalEnergy(Float_t _HCalEnergy)
{
	data_->HCalEnergy_[number_] = _HCalEnergy;
}

void IOPFJet::ECalEnergy(Float_t _ECalEnergy)
{
	data_->ECalEnergy_[number_] = _ECalEnergy;
}

void IOPFJet::TrackEnergy(Float_t _TrackEnergy)
{
	data_->TrackEnergy_[number_] = _TrackEnergy;
}

void IOPFJet::ChargedEnergy(Float_t _ChargedEnergy)
{
	data_->ChargedEnergy_[number_] = _ChargedEnergy;
}

void IOPFJet::NeutralEnergy(Float_t _NeutralEnergy)
{
	data_->NeutralEnergy_[number_] = _NeutralEnergy;
}

void IOPFJet::HadronEnergy(Float_t _HadronEnergy)
{
	data_->HadronEnergy_[number_] = _HadronEnergy;
}

void IOPFJet::PhotonEnergy(Float_t _PhotonEnergy)
{
	data_->PhotonEnergy_[number_] = _PhotonEnergy;
}

void IOPFJet::ElectronEnergy(Float_t _ElectronEnergy)
{
	data_->ElectronEnergy_[number_] = _ElectronEnergy;
}

void IOPFJet::MuonEnergy(Float_t _MuonEnergy)
{
	data_->MuonEnergy_[number_] = _MuonEnergy;
}

void IOPFJet::ChargedPtMomPA(Float_t _ChargedPtMomPA)
{
	data_->ChargedPtMomPA_[number_] = _ChargedPtMomPA;
}

void IOPFJet::ChargedPtMomPB(Float_t _ChargedPtMomPB)
{
	data_->ChargedPtMomPB_[number_] = _ChargedPtMomPB;
}

void IOPFJet::ConstPtMomPA(Float_t _ConstPtMomPA)
{
	data_->ConstPtMomPA_[number_] = _ConstPtMomPA;
}

void IOPFJet::ConstPtMomPB(Float_t _ConstPtMomPB)
{
	data_->ConstPtMomPB_[number_] = _ConstPtMomPB;
}

void IOPFJet::PtWrongPrimaryVertex(Float_t _PtWrongPrimaryVertex)
{
	data_->PtWrongPrimaryVertex_[number_] = _PtWrongPrimaryVertex;
}

void IOPFJet::EnergyCorrection(Float_t _EnergyCorrection)
{
	data_->EnergyCorrection_[number_] = _EnergyCorrection;
}

void IOPFJet::EnergyCorrectionUnc(Float_t _EnergyCorrectionUnc)
{
	data_->EnergyCorrectionUnc_[number_] = _EnergyCorrectionUnc;
}



//Data_SelectedGenParticle Data_SelectedGenParticle Data_SelectedGenParticle Data_SelectedGenParticle Data_SelectedGenParticle Data_SelectedGenParticle Data_SelectedGenParticle Data_SelectedGenParticle Data_SelectedGenParticle Data_SelectedGenParticle 
BaseIO* Data_SelectedGenParticle::baseio = 0;
Data_SelectedGenParticle::Data_SelectedGenParticle(UInt_t size, std::string prefix = "") : 
size_(size),
prefix_(prefix)
{
	PDGID_ = new Int_t[size_];
	Status_ = new Int_t[size_];
	Info_ = new Int_t[size_];
	Mother_ = new Int_t[size_];
	IndirectMother_ = new Int_t[size_];
	px_ = new Float_t[size_];
	py_ = new Float_t[size_];
	pz_ = new Float_t[size_];
	e_ = new Float_t[size_];
	vx_ = new Float_t[size_];
	vy_ = new Float_t[size_];
	vz_ = new Float_t[size_];
}

Data_SelectedGenParticle::~Data_SelectedGenParticle()
{
	delete[] PDGID_;
	delete[] Status_;
	delete[] Info_;
	delete[] Mother_;
	delete[] IndirectMother_;
	delete[] px_;
	delete[] py_;
	delete[] pz_;
	delete[] e_;
	delete[] vx_;
	delete[] vy_;
	delete[] vz_;
}

void Data_SelectedGenParticle::Fill()
{
	count_ = 0;
}

void Data_SelectedGenParticle::SetUpWrite(TTree* tree)
{
	tree->Branch((prefix_ + "_count").c_str(), &count_, (prefix_ + "_count/i").c_str());
	tree->Branch((prefix_ + "_PDGID").c_str(), PDGID_, (prefix_ + "_PDGID[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_Status").c_str(), Status_, (prefix_ + "_Status[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_Info").c_str(), Info_, (prefix_ + "_Info[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_Mother").c_str(), Mother_, (prefix_ + "_Mother[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_IndirectMother").c_str(), IndirectMother_, (prefix_ + "_IndirectMother[" + prefix_ + "_count]/I").c_str());
	tree->Branch((prefix_ + "_px").c_str(), px_, (prefix_ + "_px[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_py").c_str(), py_, (prefix_ + "_py[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_pz").c_str(), pz_, (prefix_ + "_pz[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_e").c_str(), e_, (prefix_ + "_e[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_vx").c_str(), vx_, (prefix_ + "_vx[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_vy").c_str(), vy_, (prefix_ + "_vy[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_vz").c_str(), vz_, (prefix_ + "_vz[" + prefix_ + "_count]/F").c_str());
}

void Data_SelectedGenParticle::SetUpRead(TTree* tree)
{
	tree->SetBranchAddress((prefix_ + "_count").c_str(), &count_);
	tree->SetBranchAddress((prefix_ + "_PDGID").c_str(), PDGID_);
	tree->SetBranchAddress((prefix_ + "_Status").c_str(), Status_);
	tree->SetBranchAddress((prefix_ + "_Info").c_str(), Info_);
	tree->SetBranchAddress((prefix_ + "_Mother").c_str(), Mother_);
	tree->SetBranchAddress((prefix_ + "_IndirectMother").c_str(), IndirectMother_);
	tree->SetBranchAddress((prefix_ + "_px").c_str(), px_);
	tree->SetBranchAddress((prefix_ + "_py").c_str(), py_);
	tree->SetBranchAddress((prefix_ + "_pz").c_str(), pz_);
	tree->SetBranchAddress((prefix_ + "_e").c_str(), e_);
	tree->SetBranchAddress((prefix_ + "_vx").c_str(), vx_);
	tree->SetBranchAddress((prefix_ + "_vy").c_str(), vy_);
	tree->SetBranchAddress((prefix_ + "_vz").c_str(), vz_);
}

void Data_SelectedGenParticle::Load(TTree* tree, bool load)
{
	tree->SetBranchStatus((prefix_ + "_count").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_PDGID").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Status").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Info").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Mother").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_IndirectMother").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_px").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_py").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_pz").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_e").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_vx").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_vy").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_vz").c_str(), load);
}



//SelectedGenParticle == SelectedGenParticle == SelectedGenParticle == SelectedGenParticle == SelectedGenParticle == SelectedGenParticle == SelectedGenParticle == SelectedGenParticle == SelectedGenParticle == SelectedGenParticle == SelectedGenParticle == SelectedGenParticle == SelectedGenParticle == SelectedGenParticle == SelectedGenParticle == 
BaseIO* SelectedGenParticle::baseio = 0;
SelectedGenParticle::SelectedGenParticle(Data_SelectedGenParticle* data, UInt_t number) : 
number_(number),
data_(data)
{
	Init();
}

SelectedGenParticle::SelectedGenParticle(const SelectedGenParticle& _selectedgenparticle) : 
number_( _selectedgenparticle.number_),
data_( _selectedgenparticle.data_)
{
}

void SelectedGenParticle::Init()
{
	if(baseio->IsWritable())
	{
		data_->count_ = number_+1;
	}
}

Int_t SelectedGenParticle::PDGID() const
{
	return data_->PDGID_[number_];
}

Int_t SelectedGenParticle::Status() const
{
	return data_->Status_[number_];
}

Int_t SelectedGenParticle::Info() const
{
	return data_->Info_[number_];
}

Int_t SelectedGenParticle::Mother() const
{
	return data_->Mother_[number_];
}

Int_t SelectedGenParticle::IndirectMother() const
{
	return data_->IndirectMother_[number_];
}

Float_t SelectedGenParticle::px() const
{
	return data_->px_[number_];
}

Float_t SelectedGenParticle::py() const
{
	return data_->py_[number_];
}

Float_t SelectedGenParticle::pz() const
{
	return data_->pz_[number_];
}

Float_t SelectedGenParticle::e() const
{
	return data_->e_[number_];
}

Float_t SelectedGenParticle::vx() const
{
	return data_->vx_[number_];
}

Float_t SelectedGenParticle::vy() const
{
	return data_->vy_[number_];
}

Float_t SelectedGenParticle::vz() const
{
	return data_->vz_[number_];
}

void SelectedGenParticle::PDGID(Int_t _PDGID)
{
	data_->PDGID_[number_] = _PDGID;
}

void SelectedGenParticle::Status(Int_t _Status)
{
	data_->Status_[number_] = _Status;
}

void SelectedGenParticle::Info(Int_t _Info)
{
	data_->Info_[number_] = _Info;
}

void SelectedGenParticle::Mother(Int_t _Mother)
{
	data_->Mother_[number_] = _Mother;
}

void SelectedGenParticle::IndirectMother(Int_t _IndirectMother)
{
	data_->IndirectMother_[number_] = _IndirectMother;
}

void SelectedGenParticle::px(Float_t _px)
{
	data_->px_[number_] = _px;
}

void SelectedGenParticle::py(Float_t _py)
{
	data_->py_[number_] = _py;
}

void SelectedGenParticle::pz(Float_t _pz)
{
	data_->pz_[number_] = _pz;
}

void SelectedGenParticle::e(Float_t _e)
{
	data_->e_[number_] = _e;
}

void SelectedGenParticle::vx(Float_t _vx)
{
	data_->vx_[number_] = _vx;
}

void SelectedGenParticle::vy(Float_t _vy)
{
	data_->vy_[number_] = _vy;
}

void SelectedGenParticle::vz(Float_t _vz)
{
	data_->vz_[number_] = _vz;
}



//Data_IOSuperCluster Data_IOSuperCluster Data_IOSuperCluster Data_IOSuperCluster Data_IOSuperCluster Data_IOSuperCluster Data_IOSuperCluster Data_IOSuperCluster Data_IOSuperCluster Data_IOSuperCluster 
BaseIO* Data_IOSuperCluster::baseio = 0;
Data_IOSuperCluster::Data_IOSuperCluster(UInt_t size, std::string prefix = "") : 
size_(size),
prefix_(prefix)
, Pos_(new Data_IOPosition(size_, prefix_ + "_Pos"))
{
	Energy_ = new Float_t[size_];
	RawEnergy_ = new Float_t[size_];
	PhiWidth_ = new Float_t[size_];
	EtaWidth_ = new Float_t[size_];
}

Data_IOSuperCluster::~Data_IOSuperCluster()
{
	delete[] Energy_;
	delete[] RawEnergy_;
	delete[] PhiWidth_;
	delete[] EtaWidth_;
	delete Pos_;
}

void Data_IOSuperCluster::Fill()
{
	count_ = 0;
	Pos_->Fill();
}

void Data_IOSuperCluster::SetUpWrite(TTree* tree)
{
	tree->Branch((prefix_ + "_count").c_str(), &count_, (prefix_ + "_count/i").c_str());
	tree->Branch((prefix_ + "_Energy").c_str(), Energy_, (prefix_ + "_Energy[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_RawEnergy").c_str(), RawEnergy_, (prefix_ + "_RawEnergy[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_PhiWidth").c_str(), PhiWidth_, (prefix_ + "_PhiWidth[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_EtaWidth").c_str(), EtaWidth_, (prefix_ + "_EtaWidth[" + prefix_ + "_count]/F").c_str());
	Pos_->SetUpWrite(tree);
}

void Data_IOSuperCluster::SetUpRead(TTree* tree)
{
	tree->SetBranchAddress((prefix_ + "_count").c_str(), &count_);
	tree->SetBranchAddress((prefix_ + "_Energy").c_str(), Energy_);
	tree->SetBranchAddress((prefix_ + "_RawEnergy").c_str(), RawEnergy_);
	tree->SetBranchAddress((prefix_ + "_PhiWidth").c_str(), PhiWidth_);
	tree->SetBranchAddress((prefix_ + "_EtaWidth").c_str(), EtaWidth_);
	Pos_->SetUpRead(tree);
}

void Data_IOSuperCluster::Load(TTree* tree, bool load)
{
	tree->SetBranchStatus((prefix_ + "_count").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Energy").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_RawEnergy").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_PhiWidth").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_EtaWidth").c_str(), load);
	Pos_->Load(tree, load);
}



//IOSuperCluster == IOSuperCluster == IOSuperCluster == IOSuperCluster == IOSuperCluster == IOSuperCluster == IOSuperCluster == IOSuperCluster == IOSuperCluster == IOSuperCluster == IOSuperCluster == IOSuperCluster == IOSuperCluster == IOSuperCluster == IOSuperCluster == 
BaseIO* IOSuperCluster::baseio = 0;
IOSuperCluster::IOSuperCluster(Data_IOSuperCluster* data, UInt_t number) : 
number_(number),
data_(data)
{
	Init();
}

IOSuperCluster::IOSuperCluster(const IOSuperCluster& _iosupercluster) : 
number_( _iosupercluster.number_),
data_( _iosupercluster.data_)
{
}

void IOSuperCluster::Init()
{
	if(baseio->IsWritable())
	{
		data_->count_ = number_+1;
	}
}

Float_t IOSuperCluster::Energy() const
{
	return data_->Energy_[number_];
}

Float_t IOSuperCluster::RawEnergy() const
{
	return data_->RawEnergy_[number_];
}

Float_t IOSuperCluster::PhiWidth() const
{
	return data_->PhiWidth_[number_];
}

Float_t IOSuperCluster::EtaWidth() const
{
	return data_->EtaWidth_[number_];
}

IOPosition IOSuperCluster::Pos() const
{
	return IOPosition(data_->Pos_, number_);
}

void IOSuperCluster::Energy(Float_t _Energy)
{
	data_->Energy_[number_] = _Energy;
}

void IOSuperCluster::RawEnergy(Float_t _RawEnergy)
{
	data_->RawEnergy_[number_] = _RawEnergy;
}

void IOSuperCluster::PhiWidth(Float_t _PhiWidth)
{
	data_->PhiWidth_[number_] = _PhiWidth;
}

void IOSuperCluster::EtaWidth(Float_t _EtaWidth)
{
	data_->EtaWidth_[number_] = _EtaWidth;
}



//Data_IOBeamSpot Data_IOBeamSpot Data_IOBeamSpot Data_IOBeamSpot Data_IOBeamSpot Data_IOBeamSpot Data_IOBeamSpot Data_IOBeamSpot Data_IOBeamSpot Data_IOBeamSpot 
BaseIO* Data_IOBeamSpot::baseio = 0;
Data_IOBeamSpot::Data_IOBeamSpot(UInt_t size, std::string prefix = "") : 
size_(size),
prefix_(prefix)
{
	Vx_ = new Float_t[size_];
	Vy_ = new Float_t[size_];
	Vz_ = new Float_t[size_];
	XWidth_ = new Float_t[size_];
	YWidth_ = new Float_t[size_];
	ZWidth_ = new Float_t[size_];
}

Data_IOBeamSpot::~Data_IOBeamSpot()
{
	delete[] Vx_;
	delete[] Vy_;
	delete[] Vz_;
	delete[] XWidth_;
	delete[] YWidth_;
	delete[] ZWidth_;
}

void Data_IOBeamSpot::Fill()
{
	count_ = 0;
}

void Data_IOBeamSpot::SetUpWrite(TTree* tree)
{
	tree->Branch((prefix_ + "_count").c_str(), &count_, (prefix_ + "_count/i").c_str());
	tree->Branch((prefix_ + "_Vx").c_str(), Vx_, (prefix_ + "_Vx[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_Vy").c_str(), Vy_, (prefix_ + "_Vy[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_Vz").c_str(), Vz_, (prefix_ + "_Vz[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_XWidth").c_str(), XWidth_, (prefix_ + "_XWidth[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_YWidth").c_str(), YWidth_, (prefix_ + "_YWidth[" + prefix_ + "_count]/F").c_str());
	tree->Branch((prefix_ + "_ZWidth").c_str(), ZWidth_, (prefix_ + "_ZWidth[" + prefix_ + "_count]/F").c_str());
}

void Data_IOBeamSpot::SetUpRead(TTree* tree)
{
	tree->SetBranchAddress((prefix_ + "_count").c_str(), &count_);
	tree->SetBranchAddress((prefix_ + "_Vx").c_str(), Vx_);
	tree->SetBranchAddress((prefix_ + "_Vy").c_str(), Vy_);
	tree->SetBranchAddress((prefix_ + "_Vz").c_str(), Vz_);
	tree->SetBranchAddress((prefix_ + "_XWidth").c_str(), XWidth_);
	tree->SetBranchAddress((prefix_ + "_YWidth").c_str(), YWidth_);
	tree->SetBranchAddress((prefix_ + "_ZWidth").c_str(), ZWidth_);
}

void Data_IOBeamSpot::Load(TTree* tree, bool load)
{
	tree->SetBranchStatus((prefix_ + "_count").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Vx").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Vy").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_Vz").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_XWidth").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_YWidth").c_str(), load);
	tree->SetBranchStatus((prefix_ + "_ZWidth").c_str(), load);
}



//IOBeamSpot == IOBeamSpot == IOBeamSpot == IOBeamSpot == IOBeamSpot == IOBeamSpot == IOBeamSpot == IOBeamSpot == IOBeamSpot == IOBeamSpot == IOBeamSpot == IOBeamSpot == IOBeamSpot == IOBeamSpot == IOBeamSpot == 
BaseIO* IOBeamSpot::baseio = 0;
IOBeamSpot::IOBeamSpot(Data_IOBeamSpot* data, UInt_t number) : 
number_(number),
data_(data)
{
	Init();
}

IOBeamSpot::IOBeamSpot(const IOBeamSpot& _iobeamspot) : 
number_( _iobeamspot.number_),
data_( _iobeamspot.data_)
{
}

void IOBeamSpot::Init()
{
	if(baseio->IsWritable())
	{
		data_->count_ = number_+1;
	}
}

Float_t IOBeamSpot::Vx() const
{
	return data_->Vx_[number_];
}

Float_t IOBeamSpot::Vy() const
{
	return data_->Vy_[number_];
}

Float_t IOBeamSpot::Vz() const
{
	return data_->Vz_[number_];
}

Float_t IOBeamSpot::XWidth() const
{
	return data_->XWidth_[number_];
}

Float_t IOBeamSpot::YWidth() const
{
	return data_->YWidth_[number_];
}

Float_t IOBeamSpot::ZWidth() const
{
	return data_->ZWidth_[number_];
}

void IOBeamSpot::Vx(Float_t _Vx)
{
	data_->Vx_[number_] = _Vx;
}

void IOBeamSpot::Vy(Float_t _Vy)
{
	data_->Vy_[number_] = _Vy;
}

void IOBeamSpot::Vz(Float_t _Vz)
{
	data_->Vz_[number_] = _Vz;
}

void IOBeamSpot::XWidth(Float_t _XWidth)
{
	data_->XWidth_[number_] = _XWidth;
}

void IOBeamSpot::YWidth(Float_t _YWidth)
{
	data_->YWidth_[number_] = _YWidth;
}

void IOBeamSpot::ZWidth(Float_t _ZWidth)
{
	data_->ZWidth_[number_] = _ZWidth;
}



BaseIO::BaseIO(std::string treename, bool writable) : 
PrimaryVertex_container_(200, "PrimaryVertex"),
IOEventInfo_container_(1, "IOEventInfo"),
GenInfo_container_(1, "GenInfo"),
IOMuon_container_(50, "IOMuon"),
IOMET_container_(1, "IOMET"),
IOTrack_container_(500, "IOTrack"),
IOElectron_container_(100, "IOElectron"),
AllGenParticle_container_(10000, "AllGenParticle"),
IOPFJet_container_(100, "IOPFJet"),
SelectedGenParticle_container_(10000, "SelectedGenParticle"),
IOBeamSpot_container_(1, "IOBeamSpot"),
writable_(writable),
tree_(0),
copytree_(0),
treename_(treename)
{
IOString::baseio = this;
	Data_IOString::baseio = this;
PrimaryVertex::baseio = this;
	Data_PrimaryVertex::baseio = this;
IOEventInfo::baseio = this;
	Data_IOEventInfo::baseio = this;
GenInfo::baseio = this;
	Data_GenInfo::baseio = this;
IOMuon::baseio = this;
	Data_IOMuon::baseio = this;
IOMET::baseio = this;
	Data_IOMET::baseio = this;
IOTrack::baseio = this;
	Data_IOTrack::baseio = this;
IOPosition::baseio = this;
	Data_IOPosition::baseio = this;
PFIsolation::baseio = this;
	Data_PFIsolation::baseio = this;
IOElectron::baseio = this;
	Data_IOElectron::baseio = this;
AllGenParticle::baseio = this;
	Data_AllGenParticle::baseio = this;
DetIsolation::baseio = this;
	Data_DetIsolation::baseio = this;
IOPFJet::baseio = this;
	Data_IOPFJet::baseio = this;
SelectedGenParticle::baseio = this;
	Data_SelectedGenParticle::baseio = this;
IOSuperCluster::baseio = this;
	Data_IOSuperCluster::baseio = this;
IOBeamSpot::baseio = this;
	Data_IOBeamSpot::baseio = this;
}

BaseIO::~BaseIO()
{
}

void BaseIO::SetFile(TFile* file)
{
	if(writable_)
	{
	file->cd();
	tree_ = new TTree(treename_.c_str(), treename_.c_str(), 1);
		PrimaryVertex_container_.SetUpWrite(tree_);
		IOEventInfo_container_.SetUpWrite(tree_);
		GenInfo_container_.SetUpWrite(tree_);
		IOMuon_container_.SetUpWrite(tree_);
		IOMET_container_.SetUpWrite(tree_);
		IOTrack_container_.SetUpWrite(tree_);
		IOElectron_container_.SetUpWrite(tree_);
		AllGenParticle_container_.SetUpWrite(tree_);
		IOPFJet_container_.SetUpWrite(tree_);
		SelectedGenParticle_container_.SetUpWrite(tree_);
		IOBeamSpot_container_.SetUpWrite(tree_);
		PrimaryVertex_container_.Fill();
		IOEventInfo_container_.Fill();
		GenInfo_container_.Fill();
		IOMuon_container_.Fill();
		IOMET_container_.Fill();
		IOTrack_container_.Fill();
		IOElectron_container_.Fill();
		AllGenParticle_container_.Fill();
		IOPFJet_container_.Fill();
		SelectedGenParticle_container_.Fill();
		IOBeamSpot_container_.Fill();
	}
	else
	{
		file->GetObject(treename_.c_str(), tree_);
		PrimaryVertex_container_.SetUpRead(tree_);
		IOEventInfo_container_.SetUpRead(tree_);
		GenInfo_container_.SetUpRead(tree_);
		IOMuon_container_.SetUpRead(tree_);
		IOMET_container_.SetUpRead(tree_);
		IOTrack_container_.SetUpRead(tree_);
		IOElectron_container_.SetUpRead(tree_);
		AllGenParticle_container_.SetUpRead(tree_);
		IOPFJet_container_.SetUpRead(tree_);
		SelectedGenParticle_container_.SetUpRead(tree_);
		IOBeamSpot_container_.SetUpRead(tree_);
	}
}

bool BaseIO::IsWritable() const {return writable_;}
void BaseIO::Fill(){
	tree_->Fill();
	PrimaryVertex_container_.Fill();
	IOEventInfo_container_.Fill();
	GenInfo_container_.Fill();
	IOMuon_container_.Fill();
	IOMET_container_.Fill();
	IOTrack_container_.Fill();
	IOElectron_container_.Fill();
	AllGenParticle_container_.Fill();
	IOPFJet_container_.Fill();
	SelectedGenParticle_container_.Fill();
	IOBeamSpot_container_.Fill();
}
UInt_t BaseIO::GetEntries() {return tree_->GetEntries();}
void BaseIO::GetEntry(UInt_t n) {tree_->GetEntry(n);}
UInt_t BaseIO::NumPrimaryVertexs()
{
	return PrimaryVertex_container_.count_;
}
PrimaryVertex BaseIO::GetPrimaryVertex(UInt_t n)
{
	return PrimaryVertex(&PrimaryVertex_container_, n);
}
void BaseIO::LoadPrimaryVertex(bool load)
{
	PrimaryVertex_container_.Load(tree_, load);
}

UInt_t BaseIO::NumIOEventInfos()
{
	return IOEventInfo_container_.count_;
}
IOEventInfo BaseIO::GetIOEventInfo(UInt_t n)
{
	return IOEventInfo(&IOEventInfo_container_, n);
}
void BaseIO::LoadIOEventInfo(bool load)
{
	IOEventInfo_container_.Load(tree_, load);
}

UInt_t BaseIO::NumGenInfos()
{
	return GenInfo_container_.count_;
}
GenInfo BaseIO::GetGenInfo(UInt_t n)
{
	return GenInfo(&GenInfo_container_, n);
}
void BaseIO::LoadGenInfo(bool load)
{
	GenInfo_container_.Load(tree_, load);
}

UInt_t BaseIO::NumIOMuons()
{
	return IOMuon_container_.count_;
}
IOMuon BaseIO::GetIOMuon(UInt_t n)
{
	return IOMuon(&IOMuon_container_, n);
}
void BaseIO::LoadIOMuon(bool load)
{
	IOMuon_container_.Load(tree_, load);
}

UInt_t BaseIO::NumIOMETs()
{
	return IOMET_container_.count_;
}
IOMET BaseIO::GetIOMET(UInt_t n)
{
	return IOMET(&IOMET_container_, n);
}
void BaseIO::LoadIOMET(bool load)
{
	IOMET_container_.Load(tree_, load);
}

UInt_t BaseIO::NumIOTracks()
{
	return IOTrack_container_.count_;
}
IOTrack BaseIO::GetIOTrack(UInt_t n)
{
	return IOTrack(&IOTrack_container_, n);
}
void BaseIO::LoadIOTrack(bool load)
{
	IOTrack_container_.Load(tree_, load);
}

UInt_t BaseIO::NumIOElectrons()
{
	return IOElectron_container_.count_;
}
IOElectron BaseIO::GetIOElectron(UInt_t n)
{
	return IOElectron(&IOElectron_container_, n);
}
void BaseIO::LoadIOElectron(bool load)
{
	IOElectron_container_.Load(tree_, load);
}

UInt_t BaseIO::NumAllGenParticles()
{
	return AllGenParticle_container_.count_;
}
AllGenParticle BaseIO::GetAllGenParticle(UInt_t n)
{
	return AllGenParticle(&AllGenParticle_container_, n);
}
void BaseIO::LoadAllGenParticle(bool load)
{
	AllGenParticle_container_.Load(tree_, load);
}

UInt_t BaseIO::NumIOPFJets()
{
	return IOPFJet_container_.count_;
}
IOPFJet BaseIO::GetIOPFJet(UInt_t n)
{
	return IOPFJet(&IOPFJet_container_, n);
}
void BaseIO::LoadIOPFJet(bool load)
{
	IOPFJet_container_.Load(tree_, load);
}

UInt_t BaseIO::NumSelectedGenParticles()
{
	return SelectedGenParticle_container_.count_;
}
SelectedGenParticle BaseIO::GetSelectedGenParticle(UInt_t n)
{
	return SelectedGenParticle(&SelectedGenParticle_container_, n);
}
void BaseIO::LoadSelectedGenParticle(bool load)
{
	SelectedGenParticle_container_.Load(tree_, load);
}

UInt_t BaseIO::NumIOBeamSpots()
{
	return IOBeamSpot_container_.count_;
}
IOBeamSpot BaseIO::GetIOBeamSpot(UInt_t n)
{
	return IOBeamSpot(&IOBeamSpot_container_, n);
}
void BaseIO::LoadIOBeamSpot(bool load)
{
	IOBeamSpot_container_.Load(tree_, load);
}
