/*-------------------------------------------------------------------------*/

#ifndef __LEPTON_ANALYSIS_H
#define __LEPTON_ANALYSIS_H

/*-------------------------------------------------------------------------*/

#include "../../core/include/core.h"

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

} TLeptonType;

/*-------------------------------------------------------------------------*/

class TLeptonAnalysis: public TNTuple
{
  protected:
	void initTriggers(void);

	void fixeEnergy(void);

  public:
	Int_t nPV2;
	Int_t nPV3;

	/*-----------------------------------------------------------------*/
	/* TOOLS							   */
	/*-----------------------------------------------------------------*/

	AnalysisMuonEfficiencyScaleFactors *m_stacoSF;
	AnalysisMuonEfficiencyScaleFactors *m_muidSF;
	SmearingClass *m_stacoSM;
	SmearingClass *m_muidSM;
	EnergyRescaler *m_energyRescaler;
	egammaSFclass *m_egammaSF;

	/*-----------------------------------------------------------------*/

	TLeptonAnalysis(TChain *chain): TNTuple(chain)
	{
		Vector_t<Double_t> int_lum(9);
		int_lum[0] =  11.991; // luminosity for period B
		int_lum[1] = 166.467; // luminosity for period D
		int_lum[2] =  50.418; // luminosity for period E
		int_lum[3] = 136.759; // luminosity for period F
		int_lum[4] = 517.988; // luminosity for period G
		int_lum[5] = 264.752; // luminosity for period H
		int_lum[6] = 333.797; // luminosity for period I
		int_lum[7] = 233.152; // luminosity for period J
		int_lum[8] = 551.354; // luminosity for period K

		m_stacoSF = new AnalysisMuonEfficiencyScaleFactors("STACO_CB", int_lum, "MeV", "./tools/MuonEfficiencyCorrections/share/");
		m_muidSF = new AnalysisMuonEfficiencyScaleFactors("Muid_CB", int_lum, "MeV", "./tools/MuonEfficiencyCorrections/share/");
		m_stacoSM = new SmearingClass("Data11", "staco", "q_pT", "Rel17", "./tools/MuonMomentumCorrections/share/");
		m_muidSM = new SmearingClass("Data11", "muid", "q_pT", "Rel17", "./tools/MuonMomentumCorrections/share/");
		m_energyRescaler = new EnergyRescaler();
		m_egammaSF = new egammaSFclass();

		/**/

		m_stacoSM->UseScale(1);
		m_muidSM->UseScale(1);

		m_energyRescaler->useDefaultCalibConstants("2011");

		/**/

		initTriggers();
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
	}

	/*-----------------------------------------------------------------*/
	/* DEFINITIONS */
	/*-----------------------------------------------------------------*/

	Float_t eventGetWeight(void);

	Float_t electronGetEtaDirection(Int_t index);
	Float_t electronGetPhiDirection(Int_t index);
	Float_t electronGetEt(Int_t index);

//	Bool_t el_loosePlusPlus_at(Int_t index, Bool_t isTrigger = false);
//	Bool_t el_mediumPlusPlus_at(Int_t index, Bool_t isTrigger = false);

//	Bool_t trig_EF_el_loosePlusPlus_at(Int_t index);
//	Bool_t trig_EF_el_mediumPlusPlus_at(Int_t index);

	/*-----------------------------------------------------------------*/
	/* SELECTION							   */
	/*-----------------------------------------------------------------*/

	Bool_t checkObjectQuality(
		Int_t index,
		TLeptonType type
	);

	Bool_t checkObject(
		Int_t index,
		TLeptonType type,
		Float_t __el_et,
		Float_t __mu_pt,
		Bool_t useLoose,
		Bool_t useForward
	);

	Bool_t checkStacoOverlapping(
		Int_t index,
		TLeptonType type,
		Float_t __el_et,
		Float_t __mu_pt,
		Bool_t useLoose,
		Bool_t useForward
	);

	Bool_t checkMuidOverlapping(
		Int_t index,
		TLeptonType type,
		Float_t __el_et,
		Float_t __mu_pt,
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

