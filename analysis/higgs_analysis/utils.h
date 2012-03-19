/*-------------------------------------------------------------------------*/

#ifndef __LEPTON_ANALYSIS_H
#define __LEPTON_ANALYSIS_H

/*-------------------------------------------------------------------------*/

#include "../../core/include/core.h"

#include <PileupReweighting/TPileupReweighting.h>

#include <MuonEfficiencyCorrections/AnalysisMuonEfficiencyScaleFactors.h>
#include <MuonMomentumCorrections/SmearingClass.h>

#include <egammaAnalysisUtils/EnergyRescaler.h>
#include <egammaAnalysisUtils/egammaSFclass.h>

#include <TrigMuonEfficiency/TriggerNavigationVariables.h>
#include <TrigMuonEfficiency/ElectronTriggerMatching.h>
#include <TrigMuonEfficiency/MuonTriggerMatching.h>

/*-------------------------------------------------------------------------*/

using namespace eg2011;
using namespace Analysis;
using namespace MuonSmear;

/*-------------------------------------------------------------------------*/

typedef enum TLeptonType
{
	TYPE_ELECTRON
	,
	TYPE_MUON_MUID
	,
	TYPE_MUON_STACO
	,
	TYPE_MUON_CALO

} TLeptonType;

/*-------------------------------------------------------------------------*/

#define lumiPeriodB		11.7377f
#define lumiPeriodD		166.737f
#define lumiPeriodE		48.8244f
#define lumiPeriodF		142.575f
#define lumiPeriodG		537.542f
#define lumiPeriodH		259.459f
#define lumiPeriodI		386.226f
#define lumiPeriodJ		226.460f
#define lumiPeriodK		600.069f
#define lumiPeriodL		1401.87f
#define lumiPeriodM		1025.62f

/*-------------------------------------------------------------------------*/

class TLeptonAnalysis: public TNTuple
{
  protected:
	void fixeEnergy(void);

  public:
	Int_t nPV2;
	Int_t nPV3;

	UInt_t elTrigger;
	UInt_t muTrigger;

	/*-----------------------------------------------------------------*/
	/* TOOLS							   */
	/*-----------------------------------------------------------------*/

	Root::TPileupReweighting *m_pileupReweightingBD;
	Root::TPileupReweighting *m_pileupReweightingEH;
	Root::TPileupReweighting *m_pileupReweightingIK;
	Root::TPileupReweighting *m_pileupReweightingLM;

	AnalysisMuonEfficiencyScaleFactors *m_stacoSF;
	AnalysisMuonEfficiencyScaleFactors *m_muidSF;

	SmearingClass *m_stacoSM;
	SmearingClass *m_muidSM;

	EnergyRescaler *m_energyRescaler;
	egammaSFclass *m_egammaSF;

	TriggerNavigationVariables *m_triggerNavigationVariables;
	ElectronTriggerMatching *m_elTriggerMatching;
	MuonTriggerMatching *m_muTriggerMatching;

	/*-----------------------------------------------------------------*/

	TLeptonAnalysis(TChain *chain): TNTuple(chain)
	{
		Vector_t<Double_t> int_lum(11);

		int_lum[ 0] = lumiPeriodB; // luminosity for period B
		int_lum[ 1] = lumiPeriodD; // luminosity for period D
		int_lum[ 2] = lumiPeriodE; // luminosity for period E
		int_lum[ 3] = lumiPeriodF; // luminosity for period F
		int_lum[ 4] = lumiPeriodG; // luminosity for period G
		int_lum[ 5] = lumiPeriodH; // luminosity for period H
		int_lum[ 6] = lumiPeriodI; // luminosity for period I
		int_lum[ 7] = lumiPeriodJ; // luminosity for period J
		int_lum[ 8] = lumiPeriodK; // luminosity for period K
		int_lum[ 9] = lumiPeriodL; // luminosity for period L
		int_lum[10] = lumiPeriodM; // luminosity for period M

		m_pileupReweightingBD = new Root::TPileupReweighting("TPileupReweightingBD");
		m_pileupReweightingEH = new Root::TPileupReweighting("TPileupReweightingEH");
		m_pileupReweightingIK = new Root::TPileupReweighting("TPileupReweightingIK");
		m_pileupReweightingLM = new Root::TPileupReweighting("TPileupReweightingLM");

		if(m_pileupReweightingBD->initialize("analysis/ilumicalc_period_BD_Atlas_Ready.root", "avgintperbx", "analysis/Mu_MC11bprime_analysis.root", "mc11b_BD") != 0
		   ||
		   m_pileupReweightingEH->initialize("analysis/ilumicalc_period_EH_Atlas_Ready.root", "avgintperbx", "analysis/Mu_MC11bprime_analysis.root", "mc11b_EH") != 0
		   ||
		   m_pileupReweightingIK->initialize("analysis/ilumicalc_period_IK_Atlas_Ready.root", "avgintperbx", "analysis/Mu_MC11bprime_analysis.root", "mc11b_IK") != 0
		   ||
		   m_pileupReweightingLM->initialize("analysis/ilumicalc_period_LM_Atlas_Ready.root", "avgintperbx", "analysis/Mu_MC11bprime_analysis.root", "mc11b_LM") != 0
		 ) {
			std::cout << "Could not setup pileup reweighting !" << std::endl;

			exit(1);
		}

		m_stacoSF = new AnalysisMuonEfficiencyScaleFactors(    "STACO_CB"    , int_lum, "MeV", "./tools/MuonEfficiencyCorrections/share/");
		m_muidSF = new AnalysisMuonEfficiencyScaleFactors("Muid_CB_plus_ST", int_lum, "MeV", "./tools/MuonEfficiencyCorrections/share/");
		m_stacoSM = new SmearingClass("Data11", "staco", "pT", "Rel17", "./tools/MuonMomentumCorrections/share/");
		m_muidSM = new SmearingClass("Data11", "muid", "pT", "Rel17", "./tools/MuonMomentumCorrections/share/");
		m_energyRescaler = new EnergyRescaler();
		m_egammaSF = new egammaSFclass();

		/**/

		m_triggerNavigationVariables = new TriggerNavigationVariables();

		m_elTriggerMatching = new ElectronTriggerMatching(m_triggerNavigationVariables);
		m_muTriggerMatching = new MuonTriggerMatching(m_triggerNavigationVariables);

		/**/

		m_stacoSM->UseScale(1);
		m_muidSM->UseScale(1);

		m_energyRescaler->useDefaultCalibConstants("2011");
	}

	/*-----------------------------------------------------------------*/

	~TLeptonAnalysis(void)
	{
		delete m_pileupReweightingBD;
		delete m_pileupReweightingEH;
		delete m_pileupReweightingIK;
		delete m_pileupReweightingLM;

		delete m_stacoSF;
		delete m_muidSF;

		delete m_stacoSM;
		delete m_muidSM;

		delete m_energyRescaler;
		delete m_egammaSF;

		delete m_triggerNavigationVariables;
		delete m_elTriggerMatching;
		delete m_muTriggerMatching;
	}

	/*-----------------------------------------------------------------*/
	/* TRIGGER							   */
	/*-----------------------------------------------------------------*/

	void triggerInit(void)
	{
		m_triggerNavigationVariables->set_trig_DB_SMK(trig_DB_SMK);
		m_triggerNavigationVariables->set_trig_Nav_n(trig_Nav_n);
		m_triggerNavigationVariables->set_trig_Nav_chain_ChainId(trig_Nav_chain_ChainId);
		m_triggerNavigationVariables->set_trig_Nav_chain_RoIType(trig_Nav_chain_RoIType);
		m_triggerNavigationVariables->set_trig_Nav_chain_RoIIndex(trig_Nav_chain_RoIIndex);

		/* electron */
		m_triggerNavigationVariables->set_trig_RoI_EF_e_egammaContainer_egamma_Electrons(trig_RoI_EF_e_egammaContainer_egamma_Electrons);
		m_triggerNavigationVariables->set_trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus(trig_RoI_EF_e_egammaContainer_egamma_ElectronsStatus);
		m_triggerNavigationVariables->set_trig_EF_el_n(trig_EF_el_n);
		m_triggerNavigationVariables->set_trig_EF_el_eta(trig_EF_el_eta);
		m_triggerNavigationVariables->set_trig_EF_el_phi(trig_EF_el_phi);

		/* muon */
		m_triggerNavigationVariables->set_trig_RoI_EF_mu_Muon_ROI(trig_RoI_EF_mu_Muon_ROI);
		m_triggerNavigationVariables->set_trig_RoI_EF_mu_TrigMuonEFInfoContainer(trig_RoI_EF_mu_TrigMuonEFInfoContainer);
		m_triggerNavigationVariables->set_trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus(trig_RoI_EF_mu_TrigMuonEFInfoContainerStatus);
		m_triggerNavigationVariables->set_trig_RoI_L2_mu_CombinedMuonFeature(trig_RoI_L2_mu_CombinedMuonFeature);
		m_triggerNavigationVariables->set_trig_RoI_L2_mu_CombinedMuonFeatureStatus(trig_RoI_L2_mu_CombinedMuonFeatureStatus);
		m_triggerNavigationVariables->set_trig_RoI_L2_mu_MuonFeature(trig_RoI_L2_mu_MuonFeature);
		m_triggerNavigationVariables->set_trig_RoI_L2_mu_Muon_ROI(trig_RoI_L2_mu_Muon_ROI);
		m_triggerNavigationVariables->set_trig_EF_trigmuonef_track_CB_pt(trig_EF_trigmuonef_track_CB_pt);
		m_triggerNavigationVariables->set_trig_EF_trigmuonef_track_CB_eta(trig_EF_trigmuonef_track_CB_eta);
		m_triggerNavigationVariables->set_trig_EF_trigmuonef_track_CB_phi(trig_EF_trigmuonef_track_CB_phi);
		m_triggerNavigationVariables->set_trig_EF_trigmuonef_track_SA_pt(trig_EF_trigmuonef_track_SA_pt);
		m_triggerNavigationVariables->set_trig_EF_trigmuonef_track_SA_eta(trig_EF_trigmuonef_track_SA_eta);
		m_triggerNavigationVariables->set_trig_EF_trigmuonef_track_SA_phi(trig_EF_trigmuonef_track_SA_phi);
		m_triggerNavigationVariables->set_trig_EF_trigmugirl_track_CB_pt(trig_EF_trigmugirl_track_CB_pt);
		m_triggerNavigationVariables->set_trig_EF_trigmugirl_track_CB_eta(trig_EF_trigmugirl_track_CB_eta);
		m_triggerNavigationVariables->set_trig_EF_trigmugirl_track_CB_phi(trig_EF_trigmugirl_track_CB_phi);
		m_triggerNavigationVariables->set_trig_L2_combmuonfeature_eta(trig_L2_combmuonfeature_eta);
		m_triggerNavigationVariables->set_trig_L2_combmuonfeature_phi(trig_L2_combmuonfeature_phi);
		m_triggerNavigationVariables->set_trig_L2_muonfeature_eta(trig_L2_muonfeature_eta);
		m_triggerNavigationVariables->set_trig_L2_muonfeature_phi(trig_L2_muonfeature_phi);
		m_triggerNavigationVariables->set_trig_L1_mu_eta(trig_L1_mu_eta);
		m_triggerNavigationVariables->set_trig_L1_mu_phi(trig_L1_mu_phi);
		m_triggerNavigationVariables->set_trig_L1_mu_thrName(trig_L1_mu_thrName);

		if(m_triggerNavigationVariables->isValid() == false)
		{
			std::cerr << "VARIABLES NOT CORRECTLY SET\n";

			exit(1);
		}
	}

	/*-----------------------------------------------------------------*/
	/* DEFINITIONS							   */
	/*-----------------------------------------------------------------*/

	Float_t eventGetWeight1(void);
	Float_t eventGetWeight2(void);
	Float_t eventGetWeight3(
		Int_t index,
		TLeptonType type
	);

	Float_t electronGetEtaDirection(Int_t index);
	Float_t electronGetPhiDirection(Int_t index);
	Float_t electronGetEt(Int_t index);

	Bool_t el_loosePP_at(Int_t index);

	/*-----------------------------------------------------------------*/
	/* SELECTION							   */
	/*-----------------------------------------------------------------*/

	Bool_t checkObject(
		Int_t index,
		TLeptonType type,
		Float_t __el_et,
		Float_t __mu_pt,
		Float_t __mu_calo_pt,
		Bool_t useLoose,
		Bool_t useForward
	);

	Bool_t checkStacoOverlapping(
		Int_t index,
		TLeptonType type,
		Float_t __el_et,
		Float_t __mu_pt,
		Float_t __mu_calo_pt,
		Bool_t useLoose,
		Bool_t useForward
	);

	Bool_t checkMuidOverlapping(
		Int_t index,
		TLeptonType type,
		Float_t __el_et,
		Float_t __mu_pt,
		Float_t __mu_calo_pt,
		Bool_t useLoose,
		Bool_t useForward
	);

	Bool_t checkCaloOverlapping(
		Int_t index,
		TLeptonType type,
		Float_t __el_et,
		Float_t __mu_pt,
		Float_t __mu_calo_pt,
		Bool_t useLoose,
		Bool_t useForward
	);

	/*-----------------------------------------------------------------*/
	/* TRUTH							   */
	/*-----------------------------------------------------------------*/

	Bool_t truthMatch(
		Int_t index,
		TLeptonType type
	);

	/*-----------------------------------------------------------------*/
	/* TRIGGER							   */
	/*-----------------------------------------------------------------*/

	Bool_t isElectronMatched(Float_t eta, Float_t phi, Vector_t<int> *hypo);
	Bool_t isMuonMatched(Float_t eta, Float_t phi, Vector_t<int> *hypo);

	/**/

	UInt_t getElTrigger(void);
	UInt_t getMuTrigger(void);

	UInt_t triggerMatch(
		Int_t index,
		TLeptonType type
	);

	Int_t triggerTrace(UInt_t result[]);

	/*-----------------------------------------------------------------*/
};

/*-------------------------------------------------------------------------*/
/* UTILS								   */
/*-------------------------------------------------------------------------*/

Float_t __dR2(
	Float_t eta1, Float_t eta2,
	Float_t phi1, Float_t phi2
);

Bool_t buildPair(
	Int_t pair[2],
	Float_t charge1,
	Float_t charge2
);

Bool_t buildPairs(
	Int_t pair1[2],
	Int_t pair2[2],
	Int_t pair3[2],
	Int_t pair4[2],
	TLeptonType type1,
	TLeptonType type2,
	Float_t charge1,
	Float_t charge2,
	Float_t charge3,
	Float_t charge4
);

void reIndex(
	Int_t L[4],
	Float_t M[4],
	Int_t (* func)(const void *, const void *)
);

/*-------------------------------------------------------------------------*/

#endif /* __LEPTON_ANALYSIS_H */

/*-------------------------------------------------------------------------*/

