#include "RootMaker/MyRootMaker/interface/RootMaker.h"
#include "CommonTools/Statistics/interface/ChiSquaredProbability.h"

using namespace reco;
typedef ROOT::Math::SMatrix<double, 3, 3, ROOT::Math::MatRepSym<double, 3> > SMatrixSym3D;
typedef ROOT::Math::SVector<double, 3> SVector3;

RootMaker::RootMaker(const edm::ParameterSet& iConfig) :
	baseio("URTREE", true),
	cgen(iConfig.getUntrackedParameter<bool>("GenSomeParticles", false)),
	cgenallparticles(iConfig.getUntrackedParameter<bool>("GenAllParticles", false)),
	cgenak5jets(iConfig.getUntrackedParameter<bool>("GenAK5Jets", false)),
	ctrigger(iConfig.getUntrackedParameter<bool>("Trigger", false)),
	cbeamspot(iConfig.getUntrackedParameter<bool>("RecBeamSpot", false)),
	crectrack(iConfig.getUntrackedParameter<bool>("RecTrack", false)),
	crecprimvertex(iConfig.getUntrackedParameter<bool>("RecPrimVertex", false)),
	crecsupercluster(iConfig.getUntrackedParameter<bool>("RecSuperCluster", false)),
	crecsuperclusterFilterPtMin(iConfig.getUntrackedParameter<double>("RecSuperClusterFilterPtMin", 0.)),
	crecsuperclusterFilterEtaMax(iConfig.getUntrackedParameter<double>("RecSuperClusterFilterEtaMax", 100000.)),
	crecsuperclustermember(iConfig.getUntrackedParameter<bool>("RecSuperClusterBasicCluster", false)),
	crecsuperclusterhit(iConfig.getUntrackedParameter<bool>("RecSuperClusterHit", false)),
	crecmuon(iConfig.getUntrackedParameter<bool>("RecMuon", false)),
	crectau(iConfig.getUntrackedParameter<bool>("RecTau", false)),
	crecelectron(iConfig.getUntrackedParameter<bool>("RecElectron", false)),
	crecphoton(iConfig.getUntrackedParameter<bool>("RecPhoton", false)),
	crecallconversion(iConfig.getUntrackedParameter<bool>("RecAllConversion", false)),
	crecak5calojet(iConfig.getUntrackedParameter<bool>("RecAK5CaloJet", false)),
	crecak5jptjet(iConfig.getUntrackedParameter<bool>("RecAK5JPTJet", false)),
	crecak5pfjet(iConfig.getUntrackedParameter<bool>("RecAK5PFJet", false)),
	crecak5pfchsjet(iConfig.getUntrackedParameter<bool>("RecAK5PFCHSJet", false)),
	crecpfmet(iConfig.getUntrackedParameter<bool>("RecPFMet", false)),
	crecsecvertices(iConfig.getUntrackedParameter<bool>("RecSecVertices", false)),
	crecmusecvertices(iConfig.getUntrackedParameter<bool>("RecMuSecVertices", false)),
	cHLTriggerNamesSelection(iConfig.getUntrackedParameter<vector<string> >("HLTriggerSelection")),
	cTriggerProcess(iConfig.getUntrackedParameter<string>("TriggerProcess", "HLT")),
	cMuPtMin(iConfig.getUntrackedParameter<double>("RecMuonPtMin", 0.)),
	cMuTrackIso(iConfig.getUntrackedParameter<double>("RecMuonTrackIso", 100000.)),
	cMuEtaMax(iConfig.getUntrackedParameter<double>("RecMuonEtaMax", 1000000.)),
	cMuHLTriggerMatching(iConfig.getUntrackedParameter<vector<string> >("RecMuonHLTriggerMatching")),
	cMuNum(iConfig.getUntrackedParameter<int>("RecMuonNum", 0)),
	cElPtMin(iConfig.getUntrackedParameter<double>("RecElectronPtMin", 0.)),
	cElTrackIso(iConfig.getUntrackedParameter<double>("RecElectronTrackIso", 1000000.)),
	cElEtaMax(iConfig.getUntrackedParameter<double>("RecElectronEtaMax", 1000000.)),
	cElHLTriggerMatching(iConfig.getUntrackedParameter<vector<string> >("RecElectronHLTriggerMatching")),
	cElNum(iConfig.getUntrackedParameter<int>("RecElectronNum", 0)),
	cElFilterPtMin(iConfig.getUntrackedParameter<double>("RecElectronFilterPtMin", 0.)),
	cElFilterEtaMax(iConfig.getUntrackedParameter<double>("RecElectronFilterEtaMax", 1000000.)),
	cTauPtMin(iConfig.getUntrackedParameter<double>("RecTauPtMin", 0.)),
	cTauEtaMax(iConfig.getUntrackedParameter<double>("RecTauEtaMax", 1000000.)),
	cTauHLTriggerMatching(iConfig.getUntrackedParameter<vector<string> >("RecTauHLTriggerMatching")),
	cTauDiscriminators(iConfig.getUntrackedParameter<vector<string> >("RecTauDiscriminators")),
	cTauNum(iConfig.getUntrackedParameter<int>("RecTauNum", 0)),
	cTrackFilterPtMin(iConfig.getUntrackedParameter<double>("RecTrackFilterPtMin", 0.)),
	cTrackPtMin(iConfig.getUntrackedParameter<double>("RecTrackPtMin", 0.)),
	cTrackEtaMax(iConfig.getUntrackedParameter<double>("RecTrackEtaMax", 1000000.)),
	cTrackNum(iConfig.getUntrackedParameter<int>("RecTrackNum", 0)),
	cPhotonPtMin(iConfig.getUntrackedParameter<double>("RecPhotonPtMin", 0.)),
	cPhotonEtaMax(iConfig.getUntrackedParameter<double>("RecPhotonEtaMax", 1000000.)),
	cPhotonHLTriggerMatching(iConfig.getUntrackedParameter<vector<string> >("RecPhotonHLTriggerMatching")),
	cPhotonNum(iConfig.getUntrackedParameter<int>("RecPhotonNum", 0)),
	cPhotonFilterPtMin(iConfig.getUntrackedParameter<double>("RecPhotonFilterPtMin", 0.)),
	cPhotonFilterEtaMax(iConfig.getUntrackedParameter<double>("RecPhotonFilterEtaMax", 1000000.)),
	cAK5CaloFilterPtMin(iConfig.getUntrackedParameter<double>("RecAK5CaloFilterPtMin", 0.)),
	cAK5CaloPtMin(iConfig.getUntrackedParameter<double>("RecAK5CaloPtMin", 0.)),
	cAK5CaloEtaMax(iConfig.getUntrackedParameter<double>("RecAK5CaloEtaMax", 1000000.)),
	cAK5CaloNum(iConfig.getUntrackedParameter<int>("RecAK5CaloNum", 0)),
	cAK5JPTFilterPtMin(iConfig.getUntrackedParameter<double>("RecAK5JPTFilterPtMin", 0.)),
	cAK5JPTPtMin(iConfig.getUntrackedParameter<double>("RecAK5JPTPtMin", 0.)),
	cAK5JPTEtaMax(iConfig.getUntrackedParameter<double>("RecAK5JPTEtaMax", 1000000.)),
	cAK5JPTNum(iConfig.getUntrackedParameter<int>("RecAK5JPTNum", 0)),
	cAK5PFCHSFilterPtMin(iConfig.getUntrackedParameter<double>("RecAK5PFCHSFilterPtMin", 0.)),
	cAK5PFCHSPtMin(iConfig.getUntrackedParameter<double>("RecAK5PFCHSPtMin", 0.)),
	cAK5PFCHSEtaMax(iConfig.getUntrackedParameter<double>("RecAK5PFCHSEtaMax", 1000000.)),
	cAK5PFCHSNum(iConfig.getUntrackedParameter<int>("RecAK5PFCHSNum", 0)),
	cAK5PFFilterPtMin(iConfig.getUntrackedParameter<double>("RecAK5PFFilterPtMin", 0.)),
	cAK5PFPtMin(iConfig.getUntrackedParameter<double>("RecAK5PFPtMin", 0.)),
	cAK5PFEtaMax(iConfig.getUntrackedParameter<double>("RecAK5PFEtaMax", 1000000.)),
	cAK5PFNum(iConfig.getUntrackedParameter<int>("RecAK5PFNum", 0)),
	cJetCorrection(iConfig.getUntrackedParameter<string>("JetCorrection", "L1FastL2L3Residual")),
	cJetHLTriggerMatching(iConfig.getUntrackedParameter<vector<string> >("RecJetHLTriggerMatching")),
	cMassMuMuMin(iConfig.getUntrackedParameter<double>("RecMassMuMuMin", 0.)),
	cMassMuMuMax(iConfig.getUntrackedParameter<double>("RecMassMuMuMax", 0.)),
	cVertexTRKChi2(iConfig.getUntrackedParameter<double>("RecVertexTRKChi2", 10.)),
	cVertexTRKHitsMin(iConfig.getUntrackedParameter<int>("RecVertexTRKHitsMin", 6)),
	cVertexChi2(iConfig.getUntrackedParameter<double>("RecVertexChi2", 5.)),
	cVertexSig2D(iConfig.getUntrackedParameter<double>("RecVertexSig2D", 15.)),
	cKaonMassWindow(iConfig.getUntrackedParameter<double>("RecVertexKaonMassWin", 0.05)),
	cLambdaMassWindow(iConfig.getUntrackedParameter<double>("RecVertexLambdaMassWin", 0.02)),
	propagatorWithMaterial(0)
{
	double barrelRadius = 129.; //p81, p50, ECAL TDR
	double endcapZ = 320.5; // fig 3.26, p81, ECAL TDR
	Surface::RotationType rot;

	ecalBarrel = Cylinder::build(Surface::PositionType(0, 0, 0), rot, barrelRadius);
	ecalNegativeEtaEndcap = Plane::build(Surface::PositionType(0, 0, -endcapZ), rot);
	ecalPositiveEtaEndcap = Plane::build(Surface::PositionType(0, 0, endcapZ), rot);
}

RootMaker::~RootMaker()
{
	if(propagatorWithMaterial != 0){ delete propagatorWithMaterial;}
}

void RootMaker::beginJob()
{
	edm::Service<TFileService> FS;
	baseio.SetFile(&(FS->file()));
}

void RootMaker::beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup)
{
	if(propagatorWithMaterial != 0){ delete propagatorWithMaterial;}
	iSetup.get<IdealMagneticFieldRecord>().get(magneticField);
	propagatorWithMaterial = new PropagatorWithMaterial(alongMomentum, 0.10566, &(*magneticField));
	iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder", TTrackBuilder);
}

void RootMaker::beginLuminosityBlock(const edm::LuminosityBlock& iLumiBlock, const edm::EventSetup& iSetup)
{
}

void RootMaker::endLuminosityBlock(const edm::LuminosityBlock& iLumiBlock, const edm::EventSetup& iSetup)
{
}


void RootMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	bool takeevent = false;

	pv_position = math::XYZPoint(0.,0.,0.);
	bs_position = math::XYZPoint(0.,0.,0.);


	EventInfo evinfo = baseio.GetIOEventInfo(0);
	evinfo.EventNumber(iEvent.id().event());
	evinfo.RunNumber(iEvent.id().run());
	evinfo.LumiSectionNumber(iEvent.getLuminosityBlock().luminosityBlock());
	evinfo.TimeUnix(iEvent.time().unixTime());
	evinfo.TimeMuSec(iEvent.time().microsecondOffset());
	edm::Handle<double> rho;
	iEvent.getByLabel(edm::InputTag("kt6PFJets", "rho", "ROOTMAKER"), rho);
	evinfo.AK5PFRho(*rho);
	edm::Handle<double> sigma;
	iEvent.getByLabel(edm::InputTag("kt6PFJets", "sigma", "ROOTMAKER"), sigma);
	evinfo.AK5PFSigma(*sigma);

	//HLTriggerResults
	iEvent.getByLabel(edm::InputTag("TriggerResults", "", cTriggerProcess), HLTrigger);
	for(int i = 0  ; i < 150 ; i++){evinfo.TriggerHLT(0, i);}

	for(unsigned i = 0 ; i < min(unsigned(HLTrigger->size()), unsigned(1200)) ; i++)
	{
		evinfo.SetHLT(i, HLTrigger->accept(i));
		if(HLTrigger->accept(i) && find(HLTriggerIndexSelection.begin(), HLTriggerIndexSelection.end(), i) != HLTriggerIndexSelection.end())
		{ takeevent = true;}
	}
	//TriggerEvent for matching
	iEvent.getByLabel(edm::InputTag("hltTriggerSummaryAOD", "", cTriggerProcess), HLTriggerEvent);
	//cout<<"PASSED!"<<endl;
	if(HLTriggerIndexSelection.size() == 0 || !ctrigger)
	{
		takeevent = true;
	}

	if(!takeevent) return;

	if(crecprimvertex)
	{
		iEvent.getByLabel(edm::InputTag("offlinePrimaryVertices"), Vertices);

		if(Vertices.isValid())
		{
			for(unsigned i = 0 ; i < Vertices->size(); i++)
			{
				PrimaryVertex vtx = baseio.GetPrimaryVertex(0);
				vtx.Vx((*Vertices)[i].x());
				vtx.Vy((*Vertices)[i].y());
				vtx.Vz((*Vertices)[i].z());
				vtx.ChiQ((*Vertices)[i].chi2());
				vtx.NDOF((*Vertices)[i].ndof());
				vtx.NumTracks((*Vertices)[i].tracksSize());
				Float_t ptq = 0.;
				for(Vertex::trackRef_iterator it = (*Vertices)[i].tracks_begin() ; it != (*Vertices)[i].tracks_end() ; ++it)
				{
					ptq += (*it)->pt() * (*it)->pt();
				}
				vtx.SumPtQ(ptq);
			}
			if(Vertices->size() > 0)
			{
				pv_position = (*Vertices)[0].position();
				primvertex = (*Vertices)[0];
			}
			else
			{
				return;
			}
		}
	}

	if(cbeamspot)
	{
		edm::Handle<BeamSpot> TheBeamSpot;
		iEvent.getByLabel(edm::InputTag("offlineBeamSpot"), TheBeamSpot);
		if(TheBeamSpot.isValid())
		{
			IOBeamSpot bs = baseio.GetIOBeamSpot(0);
			bs.Vx(TheBeamSpot->x0());
			bs.Vy(TheBeamSpot->y0());
			bs.Vz(TheBeamSpot->z0());
			bs.XWidth(TheBeamSpot->BeamWidthX());
			bs.YWidth(TheBeamSpot->BeamWidthY());
			bs.YWidth(TheBeamSpot->sigmaZ());
			bs_position = TheBeamSpot->position();
		}
	}

	takeevent = false;

	if(crectrack)
	{
		takeevent = AddTracks(iEvent) || takeevent;
	}
	if(crecmuon)
	{
		takeevent = AddMuons(iEvent) || takeevent;
	}
	if(crecelectron)
	{
		takeevent = AddElectrons(iEvent, iSetup) || takeevent;
	}
	if(crecphoton)
	{
		takeevent = AddPhotons(iEvent, iSetup) || takeevent;
	}
	if(crecak5pfjet)
	{
		takeevent = AddAK5PFJets(iEvent, iSetup) && takeevent;
	}
	if(!takeevent) return;

	if(crecpfmet)
	{
		IOMET met = baseio.GetIOMET(0);
		edm::Handle<reco::PFMETCollection> pfMet;
		iEvent.getByLabel(edm::InputTag("pfMet"), pfMet);
		if(pfMet.isValid() && pfMet->size() > 0)
		{
			met.pfmetpx((*pfMet)[0].px());
			met.pfmetpy((*pfMet)[0].py());
		}
		edm::Handle<reco::PFMETCollection> pfMetType0Type1;
		iEvent.getByLabel(edm::InputTag("pfType0Type1CorrectedMet"), pfMetType0Type1);
		if(pfMetType0Type1.isValid() && pfMetType0Type1->size() > 0)
		{
			met.pfmetpx((*pfMetType0Type1)[0].px());
			met.pfmetpy((*pfMetType0Type1)[0].py());
		}
	}

	if(cgen || cgenallparticles || cgenak5jets)
	{
		GenInfo gi = baseio.GetGenInfo(0);
		edm::Handle<GenEventInfoProduct> HEPMC;
		iEvent.getByLabel(edm::InputTag("generator"), HEPMC);
		if(HEPMC.isValid())
		{
			gi.Weight(HEPMC->weight());
			gi.PDGID1(HEPMC->pdf()->id.first);
			gi.x1(HEPMC->pdf()->x.first);
			gi.PDGID2(HEPMC->pdf()->id.second);
			gi.x2(HEPMC->pdf()->x.second);
			gi.RenScale(HEPMC->qScale());
			gi.FacScale(HEPMC->qScale());
		}

		edm::Handle<vector<PileupSummaryInfo> > PUInfo;
		iEvent.getByLabel(edm::InputTag("addPileupInfo"), PUInfo);

		if(PUInfo.isValid())
		{
			for(vector<PileupSummaryInfo>::const_iterator PVI = PUInfo->begin(); PVI != PUInfo->end(); ++PVI)
			{
				int BX = PVI->getBunchCrossing();
				if(BX == -1)
				{ 
					gi.NumPUInteractionsBefore(PVI->getPU_NumInteractions());
				}
				else if(BX == 0)
				{ 
					gi.NumPUInteractions(PVI->getPU_NumInteractions());
					gi.NumTrueInteractions(PVI->getTrueNumInteractions());
				}
				else if(BX == 1)
				{ 
					gi.NumPUInteractionsAfter(PVI->getPU_NumInteractions());
				}
			}
		}

		edm::Handle<GenMETCollection> GenMetTrue;
		iEvent.getByLabel(edm::InputTag("genMetTrue"), GenMetTrue);
		if(GenMetTrue.isValid() && GenMetTrue->size() > 0)
		{
			
			gi.METx((*GenMetTrue)[0].px());
			gi.METy((*GenMetTrue)[0].py());
		}
		else
		{
			gi.METx(0.);
			gi.METy(0.);
		}

	}  

	if(cgenallparticles)
	{
		edm::Handle<GenParticleCollection> GenParticles;
		iEvent.getByLabel(edm::InputTag("genPlusSimParticles"), GenParticles);
		if(!GenParticles.isValid())
		{
			iEvent.getByLabel(edm::InputTag("genParticles"), GenParticles);
		}

		if(GenParticles.isValid())
		{
			for(unsigned i = 0 ; i < GenParticles->size() ; i++)
			{
				AllGenParticle gp = baseio.GetAllGenParticle(i);
				gp.e((*GenParticles)[i].energy());
				gp.px((*GenParticles)[i].px());
				gp.py((*GenParticles)[i].py());
				gp.pz((*GenParticles)[i].pz());
				gp.vx((*GenParticles)[i].vx());
				gp.vy((*GenParticles)[i].vy());
				gp.vz((*GenParticles)[i].vz());
				gp.PDGID((*GenParticles)[i].pdgId());
				gp.Status((*GenParticles)[i].status());
				int counter = 0;
				for(unsigned j = 0 ; j < (*GenParticles)[i].numberOfMothers() ; j++)
				{
					gp.Mother(FindGenParticle(*GenParticles, (*GenParticles)[i].mother(j)), counter);
					counter++;
				}
				counter = 0;
				for(unsigned j = 0 ; j < (*GenParticles)[i].numberOfDaughters() ; j++)
				{
					gp.Daughter(FindGenParticle(*GenParticles, (*GenParticles)[i].daughter(j)), counter);
					counter++;
				}
			}

		}
	}


	if(takeevent)
	{
		baseio.Fill();
	}
}

void RootMaker::endJob()
{
}

bool RootMaker::AddMuons(const edm::Event& iEvent)
{
	return(false);
}


bool RootMaker::AddPhotons(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	return(false);
}


bool RootMaker::AddTracks(const edm::Event& iEvent)
{
	return(false);
}

bool RootMaker::AddAK5PFJets(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	return(false);
}
bool RootMaker::AddElectrons(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	return(false);
}

UInt_t RootMaker::FindGenParticle(const GenParticleCollection& genparticles,  const Candidate* particle)
{
	for(size_t i = 0 ; i < genparticles.size() ; i++)
	{
		const GenParticle& gp(genparticles[i]);
		if(particle->pdgId() == gp.pdgId() && particle->status() == gp.status() && particle->energy() == gp.energy() && particle->px() == gp.px() && particle->py() == gp.py() && particle->pz() == gp.pz())
		{
			return(i);
		}
	}
	return(10000000);
}

pair<Int_t, Int_t> RootMaker::HasAnyMother(const GenParticle* particle, vector<int> ids)
{
	Int_t motherid = 0;
	vector<unsigned> bknummother;
	vector<const GenParticle*> bkparticle;
	bknummother.reserve(10);
	bkparticle.reserve(10);
	int level = 0;
	bkparticle.push_back(particle);
	bknummother.push_back(0);

	vector<int>::const_iterator it;
	UInt_t result = 0;
	unsigned j = 0;
	while(true)
	{
		if(j == bkparticle[level]->numberOfMothers())
		{
			level--;
			if(level == -1){break;}
			j = bknummother[level];
			bkparticle.resize(level+1);
			bknummother.resize(level+1);
			continue;
		}

		if(motherid == 0 && bkparticle[level]->mother(j)->pdgId() != particle->pdgId()){motherid = bkparticle[level]->mother(j)->pdgId();}
		it = find(ids.begin(), ids.end(), bkparticle[level]->mother(j)->pdgId());
		if(it != ids.end()){result |= 1<<(it-ids.begin());}

		if(bkparticle[level]->mother(j)->numberOfMothers() > 0)
		{
			bknummother[level] = j+1;
			bkparticle.push_back(dynamic_cast<const GenParticle*>(bkparticle[level]->mother(j)));
			bknummother.push_back(0);
			j = 0;
			level++;
			continue;
		}
		j++;
	}
	return(pair<Int_t, Int_t>(result, motherid));
}

Int_t RootMaker::HasAnyMother(const GenParticle* particle, int id)
{
	vector<unsigned> bknummother;
	vector<const GenParticle*> bkparticle;
	bknummother.reserve(10);
	bkparticle.reserve(10);
	int level = 0;
	bkparticle.push_back(particle);
	bknummother.push_back(0);

	unsigned j = 0;
	while(true)
	{
		if(j == bkparticle[level]->numberOfMothers())
		{
			level--;
			if(level == -1){return(0);}
			j = bknummother[level];
			bkparticle.resize(level+1);
			bknummother.resize(level+1);
			continue;
		}

		if(bkparticle[level]->mother(j)->pdgId() == id) return(2);
		if(abs(bkparticle[level]->mother(j)->pdgId()) == abs(id)) return(1);

		if(bkparticle[level]->mother(j)->numberOfMothers() > 0)
		{
			bknummother[level] = j+1;
			bkparticle.push_back(dynamic_cast<const GenParticle*>(bkparticle[level]->mother(j)));
			bknummother.push_back(0);
			j = 0;
			level++;
			continue;
		}
		j++;
	}
	return(0);
}

math::XYZPoint RootMaker::PositionOnECalSurface(TransientTrack& trTrack)
{
	math::XYZPoint ecalPosition(0.,0.,0.);
	const FreeTrajectoryState myTSOS = trTrack.initialFreeState();
	TrajectoryStateOnSurface stateAtECal = propagatorWithMaterial->propagate(myTSOS, *ecalBarrel);

	if(stateAtECal.isValid() && stateAtECal.globalPosition().eta() > 1.479) 
	{
		stateAtECal= propagatorWithMaterial->propagate(myTSOS, *ecalPositiveEtaEndcap);
	}    

	if(stateAtECal.isValid() && stateAtECal.globalPosition().eta() < -1.479) 
	{
		stateAtECal= propagatorWithMaterial->propagate(myTSOS, *ecalNegativeEtaEndcap);
	}    

	if(stateAtECal.isValid())
	{
		ecalPosition = stateAtECal.globalPosition();
	}
	return(ecalPosition);
}

RootMaker::JetShape RootMaker::getJetShape(const PFJet& jet)
{
	using namespace TMath;
	RootMaker::JetShape res;
	Float_t chargedetaeta1 = 0.;
	Float_t chargedphiphi1 = 0.;
	Float_t chargedetaeta2 = 0.;
	Float_t chargedphiphi2 = 0.;
	Float_t chargedetaphi = 0.;
	Float_t chargedmaxpt = 0.;
	UInt_t chargedmulti = 0;
	Float_t chargedptsum = 0.;
	Float_t chargedptsummv = 0.;
	Float_t neutraletaeta1 = 0.;
	Float_t neutralphiphi1 = 0.;
	Float_t neutraletaeta2 = 0.;
	Float_t neutralphiphi2 = 0.;
	Float_t neutraletaphi = 0.;
	Float_t neutralptsum = 0.;
	Float_t neutralmaxpt = 0.;
	Float_t alletaeta1 = 0.;
	Float_t alletaeta2 = 0.;
	Float_t alletaphi = 0.;
	Float_t allphiphi1 = 0.;
	Float_t allphiphi2 = 0.;
	Float_t allptsum = 0.;
	Float_t allmaxpt = 0.;
	vector<PFCandidatePtr> constituents(jet.getPFConstituents());
	for(size_t i = 0 ; i < constituents.size() ; ++i)
	{
		const PFCandidate& con = *(constituents[i]);
		TVector3 tvcon;
		tvcon.SetPtEtaPhi(con.pt(), con.eta(), con.phi());
		TVector3 tvjet;
		tvjet.SetPtEtaPhi(jet.pt(), jet.eta(), jet.phi());
		Float_t deta = jet.eta() - con.eta();
		Float_t dphi = tvjet.DeltaPhi(tvcon);
		
		//Float_t deta = jet.eta() - con.eta();
		//Float_t dphi = jet.phi() - con.phi();
		//if(dphi > 4.*atan(1.) ) dphi = dphi-8.*atan(1.);
		//if(dphi < -1.*4.*atan(1.) ) dphi = dphi+8.*atan(1.);

		if(con.trackRef().isNonnull())
		{
			chargedptsum += con.pt();      
			int vertex = getPrimVertex(*(con.trackRef()));
			if(vertex == 0 || vertex == -1)
			{
				if(con.pt() > chargedmaxpt) {chargedmaxpt = con.pt();}
				chargedmulti++;
				chargedetaeta1 += deta*con.pt();
				chargedetaeta2 += deta*deta*con.pt();
				chargedetaphi += deta*dphi*con.pt();
				chargedphiphi1 += dphi*con.pt();
				chargedphiphi2 += dphi*dphi*con.pt();
				chargedptsummv += con.pt();
			}
		}
		else
		{
			if(con.pt() > neutralmaxpt) {neutralmaxpt = con.pt();}
			neutralptsum += con.pt();
			neutraletaeta1 += deta*con.pt();
			neutraletaeta2 += deta*deta*con.pt();
			neutraletaphi += deta*dphi*con.pt();
			neutralphiphi1 += dphi*con.pt();
			neutralphiphi2 += dphi*dphi*con.pt();
		}
		if(con.pt() > allmaxpt) {allmaxpt = con.pt();}
		allptsum += con.pt();
		alletaeta1 += deta*con.pt();
		alletaeta2 += deta*deta*con.pt();
		alletaphi += deta*dphi*con.pt();
		allphiphi1 += dphi*con.pt();
		allphiphi2 += dphi*dphi*con.pt();
	}
	if(chargedptsum != 0)
	{
		chargedetaeta1/=chargedptsum;
		chargedetaeta2/=chargedptsum;
		chargedetaphi/=chargedptsum;
		chargedphiphi1/=chargedptsum;
		chargedphiphi2/=chargedptsum;
	}
	else
	{
		chargedetaeta1 = 0.;
		chargedetaeta2 = 0.;
		chargedetaphi = 0.;
		chargedphiphi1 = 0.;
		chargedphiphi2 = 0.;
	}
	if(neutralptsum != 0)
	{
		neutraletaeta1/=neutralptsum;
		neutraletaeta2/=neutralptsum;
		neutraletaphi/=neutralptsum;
		neutralphiphi1/=neutralptsum;
		neutralphiphi2/=neutralptsum;
	}
	else
	{
		neutraletaeta1 = 0.;
		neutraletaeta2 = 0.;
		neutraletaphi = 0.;
		neutralphiphi1 = 0.;
		neutralphiphi2 = 0.;
	}
	if(allptsum != 0)
	{
		alletaeta1/=allptsum;
		alletaeta2/=allptsum;
		alletaphi/=allptsum;
		allphiphi1/=allptsum;
		allphiphi2/=allptsum;
	}
	else
	{
		alletaeta1 = 0.;
		alletaeta2 = 0.;
		alletaphi = 0.;
		allphiphi1 = 0.;
		allphiphi2 = 0.;
	}

	Float_t chargedetavar = chargedetaeta2-chargedetaeta1*chargedetaeta1;
	Float_t chargedphivar = chargedphiphi2-chargedphiphi1*chargedphiphi1;
	Float_t chargedphidetacov = chargedetaphi - chargedetaeta1*chargedphiphi1;

	Float_t chargeddet = (chargedetavar-chargedphivar)*(chargedetavar-chargedphivar)+4*chargedphidetacov*chargedphidetacov;
	Float_t chargedx1 = (chargedetavar+chargedphivar+sqrt(chargeddet))/2.;
	Float_t chargedx2 = (chargedetavar+chargedphivar-sqrt(chargeddet))/2.;

	Float_t neutraletavar = neutraletaeta2-neutraletaeta1*neutraletaeta1;
	Float_t neutralphivar = neutralphiphi2-neutralphiphi1*neutralphiphi1;
	Float_t neutralphidetacov = neutraletaphi - neutraletaeta1*neutralphiphi1;

	Float_t neutraldet = (neutraletavar-neutralphivar)*(neutraletavar-neutralphivar)+4*neutralphidetacov*neutralphidetacov;
	Float_t neutralx1 = (neutraletavar+neutralphivar+sqrt(neutraldet))/2.;
	Float_t neutralx2 = (neutraletavar+neutralphivar-sqrt(neutraldet))/2.;

	Float_t alletavar = alletaeta2-alletaeta1*alletaeta1;
	Float_t allphivar = allphiphi2-allphiphi1*allphiphi1;
	Float_t allphidetacov = alletaphi - alletaeta1*allphiphi1;

	Float_t alldet = (alletavar-allphivar)*(alletavar-allphivar)+4*allphidetacov*allphidetacov;
	Float_t allx1 = (alletavar+allphivar+sqrt(alldet))/2.;
	Float_t allx2 = (alletavar+allphivar-sqrt(alldet))/2.;

	res.chargeda = chargedx1;
	res.chargedb = chargedx2;
	res.neutrala = neutralx1;
	res.neutralb = neutralx2;
	res.alla = allx1;
	res.allb = allx2;
	res.chargedfractionmv = chargedptsummv/chargedptsum;
	res.chargedmulti = chargedmulti;
	res.chargedmaxpt = chargedmaxpt;
	res.neutralmaxpt = neutralmaxpt;
	res.allmaxpt = allmaxpt;
	return(res);

}



Int_t RootMaker::getPrimVertex(const Track& trk)
{
	if(Vertices.isValid())
	{
		for(unsigned i = 0 ; i < Vertices->size(); i++)
		{
			if((*Vertices)[i].isValid() && !(*Vertices)[i].isFake())
			{
				for(Vertex::trackRef_iterator it = (*Vertices)[i].tracks_begin() ; it != (*Vertices)[i].tracks_end() ; ++it)
				{
					if(trk.px() - (*it)->px() < 0.01 && trk.py() - (*it)->py() < 0.01 && trk.pz() - (*it)->pz() < 0.01)  return(i);
				}
			}
		}
	}
	return(-1);
}

double RootMaker::DR(const Candidate& A, const Candidate& B)
{
	//using namespace TMath;
	TLorentzVector TA(A.px(), A.py(), A.pz(), A.energy());
	TLorentzVector TB(B.px(), B.py(), B.pz(), B.energy());
	return(TA.DeltaR(TB));
}

UInt_t RootMaker::GetTrigger(const LeafCandidate& particle, vector<pair<unsigned, int> >& triggers)
{
	UInt_t result = 0;

	if(HLTrigger.isValid() && HLTriggerEvent.isValid())
	{
		const trigger::TriggerObjectCollection& TOC(HLTriggerEvent->getObjects());
		for(unsigned n = 0 ; n < triggers.size() ; n++)
		{
			unsigned TriggerIndex = triggers[n].first;
			int Filter = abs(triggers[n].second);
			const vector<string>& ModuleLabels(HLTConfiguration.moduleLabels(TriggerIndex));
			const unsigned FilterIndex = HLTriggerEvent->filterIndex(edm::InputTag(ModuleLabels[Filter], "", cTriggerProcess));
			if(FilterIndex < HLTriggerEvent->sizeFilters())
			{
				const trigger::Keys& KEYS(HLTriggerEvent->filterKeys(FilterIndex));
				for(unsigned j = 0 ; j < KEYS.size() ; j++)
				{
					TLorentzVector TA(particle.px(), particle.py(), particle.pz(), particle.energy());
					TLorentzVector TB(TOC[KEYS[j]].px(), TOC[KEYS[j]].py(), TOC[KEYS[j]].pz(), TOC[KEYS[j]].energy());
					double dr = TA.DeltaR(TB);
					//double dpt = TMath::Abs(particle.pt() - TOC[KEYS[j]].pt())/particle.pt();  
					if(dr < 0.3)
					{
						if(triggers[n].second >= 0)
						{
							result |= 1<<n;
							break;
						}
						if(triggers[n].second < 0 && TOC[KEYS[j]].pt() > 10.)
						{
							result |= 1<<n;
							break;
						}

					}
				}
			}
		}
	}
	return(result);
}

void RootMaker::TriggerIndexSelection(vector<string> configstring, vector<pair<unsigned, int> >& triggers, string& allnames)
{
	triggers.clear();
	allnames.clear();
	boost::cmatch what;
	vector<pair<boost::regex, bool> > regexes;
	for(unsigned i = 0 ; i < configstring.size() ; i++)
	{
		vector<string> strs;
		boost::split(strs, configstring[i], boost::is_any_of(":"));
		bool dofilter = false;
		if(strs.size() == 2 && strs[1] == "FilterTrue") dofilter = true;
		regexes.push_back(pair<boost::regex, bool>(boost::regex(strs[0].c_str()), dofilter));
	}

	for(unsigned i = 0 ; i < HLTConfiguration.size() ; i++)
	{
		unsigned TriggerIndex = HLTConfiguration.triggerIndex(HLTConfiguration.triggerName(i));
		const vector<string>& ModuleLabels(HLTConfiguration.moduleLabels(TriggerIndex));
		for(unsigned j = 0 ; j < regexes.size() ; j++)
		{
			if(boost::regex_match(HLTConfiguration.triggerName(i).c_str(), what, regexes[j].first) && triggers.size() < 32)
			{
				for(int u = ModuleLabels.size()-1 ; u >= 0 ; u--)
				{
					if(HLTConfiguration.saveTags(ModuleLabels[u])) 
					{
						allnames += HLTConfiguration.triggerName(i) + string(":") + ModuleLabels[u] + string(" ");
						triggers.push_back(pair<unsigned, int>(TriggerIndex, u));
						cout << triggers.size() << ": " << HLTConfiguration.triggerName(i) << " " << TriggerIndex << " " << ModuleLabels[u] << " " << u << endl;
						if("hltL1sL1DoubleMu10MuOpen" == ModuleLabels[u])
						{
							allnames += HLTConfiguration.triggerName(i) + string(":") + ModuleLabels[u] + string("gt10 ");
							triggers.push_back(pair<unsigned, int>(TriggerIndex, -1*u));
						}
						if(regexes[j].second == false)
						{
							break;
						}
					}
				}
			}
		}
	}
	if(triggers.size() == 32) {cout << "ERROR: more than 32 triggers to match" << endl;}
}

