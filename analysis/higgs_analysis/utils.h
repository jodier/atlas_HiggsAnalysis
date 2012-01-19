/*-------------------------------------------------------------------------*/

#ifndef __LEPTON_ANALYSIS_H
#define __LEPTON_ANALYSIS_H

/*-------------------------------------------------------------------------*/

#include "../../core/include/core.h"

#include <PileupReweighting/TPileupReweighting.h>

#include <MuonEfficiencyCorrections/AnalysisMuonEfficiencyScaleFactors.h>
#include <MuonMomentumCorrections/SmearingClass.h>

#include <egammaAnalysisUtils/egammaTriggerMatching.h>
#include <egammaAnalysisUtils/EnergyRescaler.h>
#include <egammaAnalysisUtils/egammaSFclass.h>

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

class TLeptonAnalysis: public TNTuple
{
  protected:
	void fixeEnergy(void);

  public:
	Int_t nPV2;
	Int_t nPV3;

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

	/*-----------------------------------------------------------------*/

	TLeptonAnalysis(TChain *chain): TNTuple(chain)
	{
		Vector_t<Double_t> int_lum(11);

		int_lum[0] = 11.7377f; // luminosity for period B
		int_lum[0] = 00.0000f; // luminosity for period B
		int_lum[1] = 166.737f; // luminosity for period D
		int_lum[2] = 48.8244f; // luminosity for period E
		int_lum[3] = 142.575f; // luminosity for period F
		int_lum[4] = 537.542f; // luminosity for period G
		int_lum[5] = 259.459f; // luminosity for period H
		int_lum[6] = 226.460f; // luminosity for period I
		int_lum[7] = 600.069f; // luminosity for period J
		int_lum[8] = 1401.87f; // luminosity for period K
		int_lum[9] = 1025.62f; // luminosity for period L

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

		m_energyRescaler->useDefaultCalibConstants("2011");
	}

	/*-----------------------------------------------------------------*/

	~TLeptonAnalysis(void)
	{
		delete m_stacoSF;
		delete m_muidSF;
		delete m_stacoSM;
		delete m_muidSM;
		delete m_energyRescaler;
		delete m_egammaSF;

		delete m_pileupReweightingBD;
		delete m_pileupReweightingEH;
		delete m_pileupReweightingIK;
		delete m_pileupReweightingLM;
	}

	/*-----------------------------------------------------------------*/
	/* DEFINITIONS */
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
	/* MATCHING							   */
	/*-----------------------------------------------------------------*/

	Bool_t truthMatch(
		Int_t index,
		TLeptonType type
	);

	Bool_t triggerMatch(
		Int_t index,
		TLeptonType type
	);

	/*-----------------------------------------------------------------*/
	/* TRIGGER							   */
	/*-----------------------------------------------------------------*/

	Bool_t getElTrigger(void);
	Bool_t getMuTrigger(void);

	Vector_t<Int_t> *getElTriggerDec(void);
	Vector_t<Int_t> *getMuTriggerDec(void);

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

