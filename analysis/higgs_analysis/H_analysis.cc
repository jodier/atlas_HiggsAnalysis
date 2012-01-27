/*-------------------------------------------------------------------------*/

#include <cmath>
#include <iostream>

#include <TLorentzVector.h>

#include <egammaAnalysisUtils/CaloIsoCorrection.h>

#include "main.h"

/*-------------------------------------------------------------------------*/

typedef struct TZVector
{
	Bool_t l1_truthMatch;
	Bool_t l2_truthMatch;

	Bool_t l1_triggerMatch;
	Bool_t l2_triggerMatch;

	TLorentzVector l1_lorentz;
	TLorentzVector l2_lorentz;

	TLorentzVector Z_lorentz;

} TZVector;

/*-------------------------------------------------------------------------*/

static inline Float_t extrapolate(Float_t x, Float_t x1, Float_t x2, Float_t y1, Float_t y2)
{
	Float_t a = (y2 - y1) / (x2 - x1);

	Float_t b = y1 - a * x1;
  
	return a * x + b;
}

/*-------------------------------------------------------------------------*/

Float_t getMassCut(Float_t H_mass)
{
	Float_t result;

	/**/ if(H_mass > 000.0f && H_mass <= 120.0f) {
		result = 15.000000000000000000000000000000000000000000000f;
	}
	else if(H_mass > 120.0f && H_mass <= 130.0f) {
		result = extrapolate(H_mass, 120.0f, 130.0f, 15.0f, 20.0f);
	}
	else if(H_mass > 130.0f && H_mass <= 150.0f) {
		result = extrapolate(H_mass, 130.0f, 150.0f, 20.0f, 30.0f);
	}
	else if(H_mass > 150.0f && H_mass <= 160.0f) {
		result = 30.000000000000000000000000000000000000000000000f;
	}
	else if(H_mass > 160.0f && H_mass <= 165.0f) {
		result = extrapolate(H_mass, 160.0f, 165.0f, 30.0f, 35.0f);
	}
	else if(H_mass > 165.0f && H_mass <= 180.0f) {
		result = extrapolate(H_mass, 165.0f, 180.0f, 35.0f, 40.0f);
	}
	else if(H_mass > 180.0f && H_mass <= 190.0f) {
		result = extrapolate(H_mass, 180.0f, 190.0f, 40.0f, 50.0f);
	}
	else if(H_mass > 190.0f && H_mass <= 200.0f) {
		result = extrapolate(H_mass, 190.0f, 200.0f, 50.0f, 60.0f);
	}
	else {
		result = 60.0f;
	}

	return result;
}

/*-------------------------------------------------------------------------*/

static Bool_t subLeadingCut(Float_t Z_mass, Float_t H_mass)
{
	return (Z_mass > getMassCut(H_mass)) && (Z_mass < 115.0f);
}

/*-------------------------------------------------------------------------*/

static Int_t ptCompare(const void *a, const void *b)
{
	Float_t A = *(Float_t *) a;
	Float_t B = *(Float_t *) b;

	/**/ if(A < B) {
		return -1;
	}
	else if(A > B) {
		return +1;
	}
	else {
		return 0;
	}
}

/*-------------------------------------------------------------------------*/

#define _INC(isOk, dest, level) \
									\
		if(isOk != false)					\
		{							\
			m_H[dest].flag[					\
				    m_H[dest].n				\
					    ] |= (1 << level);		\
		}

/*-------------------------------------------------------------------------*/

Bool_t THiggsBuilder::H_analysis(
	Int_t index1,
	Int_t index2,
	Int_t index3,
	Int_t index4,
	TLeptonType type1,
	TLeptonType type2,
	Int_t dest
) {
	Float_t Z_MASS = core::configFltLookup("Z_MASS");
	Float_t Z_REGION = core::configFltLookup("Z_REGION");

	Float_t higgs_el_trigg_pt = core::configFltLookup("higgs_el_trigg_pt");
	Float_t higgs_mu_trigg_pt = core::configFltLookup("higgs_mu_trigg_pt");

	Float_t tkIso = core::configFltLookup("tkIso");
	Float_t clIso = core::configFltLookup("clIso");
	Float_t d0sigma_el = core::configFltLookup("d0sigma_el");
	Float_t d0sigma_mu = core::configFltLookup("d0sigma_mu");

	/*-----------------------------------------------------------------*/
	/* EVENT							   */
	/*-----------------------------------------------------------------*/

	m_H[dest].RunNumber   =  RunNumber ;
	m_H[dest].EventNumber = EventNumber;
	m_H[dest].LumiBlock   =     lbn    ;

	m_H[dest].actualIntPerXing = actualIntPerXing;
	m_H[dest].averageIntPerXing = averageIntPerXing;

	m_H[dest].elTrigger = getElTrigger();
	m_H[dest].muTrigger = getMuTrigger();

	m_H[dest].tn = triggerTrace(m_H[dest].ta);

	Float_t weight1 = eventGetWeight1();
	Float_t weight2 = eventGetWeight2();
	Float_t weight3 = \
		eventGetWeight3(index1, type1) * eventGetWeight3(index2, type1)
		*
		eventGetWeight3(index3, type2) * eventGetWeight3(index4, type2)
	;

	/*-----------------------------------------------------------------*/
	/* VARIABLES							   */
	/*-----------------------------------------------------------------*/

	Float_t E1, pt1, eta1, phi1, charge1, tkIso1, clIso1, d0sigma1;
	Float_t E2, pt2, eta2, phi2, charge2, tkIso2, clIso2, d0sigma2;
	Float_t E3, pt3, eta3, phi3, charge3, tkIso3, clIso3, d0sigma3;
	Float_t E4, pt4, eta4, phi4, charge4, tkIso4, clIso4, d0sigma4;

	Float_t ptCut1, d0sigmaCut1;
	Float_t ptCut2, d0sigmaCut2;
	Float_t ptCut3, d0sigmaCut3;
	Float_t ptCut4, d0sigmaCut4;

	Float_t ptTkOverlapping1, ptClOverlapping1;
	Float_t ptTkOverlapping2, ptClOverlapping2;
	Float_t ptTkOverlapping3, ptClOverlapping3;
	Float_t ptTkOverlapping4, ptClOverlapping4;

	Bool_t truthMatch1 = truthMatch(index1, type1);
	Bool_t truthMatch2 = truthMatch(index2, type1);
	Bool_t truthMatch3 = truthMatch(index3, type2);
	Bool_t truthMatch4 = truthMatch(index4, type2);
	Bool_t triggerMatch1 = triggerMatch(index1, type1);
	Bool_t triggerMatch2 = triggerMatch(index2, type1);
	Bool_t triggerMatch3 = triggerMatch(index3, type2);
	Bool_t triggerMatch4 = triggerMatch(index4, type2);

	switch(type1)
	{
		case TYPE_ELECTRON:
			E1 = el_cl_E->at(index1);
			E2 = el_cl_E->at(index2);
			pt1 = electronGetEt(index1);
			pt2 = electronGetEt(index2);
			eta1 = electronGetEtaDirection(index1);
			eta2 = electronGetEtaDirection(index2);
			phi1 = electronGetPhiDirection(index1);
			phi2 = electronGetPhiDirection(index2);
			charge1 = el_charge->at(index1);
			charge2 = el_charge->at(index2);
			tkIso1 = el_ptcone20->at(index1) / pt1;
			tkIso2 = el_ptcone20->at(index2) / pt2;
			clIso1 = CaloIsoCorrection::GetNPVCorrectedIsolation(nPV2, el_etas2->at(index1), 20, core::isMC(RunNumber), el_Etcone20->at(index1), CaloIsoCorrection::ELECTRON) / pt1;
			clIso2 = CaloIsoCorrection::GetNPVCorrectedIsolation(nPV2, el_etas2->at(index2), 20, core::isMC(RunNumber), el_Etcone20->at(index2), CaloIsoCorrection::ELECTRON) / pt2;
			d0sigma1 = fabs(el_trackd0pvunbiased->at(index1) / el_tracksigd0pvunbiased->at(index1));
			d0sigma2 = fabs(el_trackd0pvunbiased->at(index2) / el_tracksigd0pvunbiased->at(index2));
			ptCut1 = ptCut2 = higgs_el_trigg_pt;
			d0sigmaCut1 = d0sigmaCut2 = d0sigma_el;
			ptTkOverlapping1 = el_trackpt->at(index1);
			ptTkOverlapping2 = el_trackpt->at(index2);
			ptClOverlapping1 = pt1;
			ptClOverlapping2 = pt2;
			break;

		case TYPE_MUON_STACO:
			E1 = mu_staco_E->at(index1);
			E2 = mu_staco_E->at(index2);
			pt1 = mu_staco_pt->at(index1);
			pt2 = mu_staco_pt->at(index2);
			eta1 = mu_staco_eta->at(index1);
			eta2 = mu_staco_eta->at(index2);
			phi1 = mu_staco_phi->at(index1);
			phi2 = mu_staco_phi->at(index2);
			charge1 = mu_staco_charge->at(index1);
			charge2 = mu_staco_charge->at(index2);
			tkIso1 = mu_staco_ptcone20->at(index1) / pt1;
			tkIso2 = mu_staco_ptcone20->at(index2) / pt2;
			clIso1 = (mu_staco_etcone20->at(index1) - Float_t(nPV2 - 1) * 33.5f) / pt1;
			clIso2 = (mu_staco_etcone20->at(index2) - Float_t(nPV2 - 1) * 33.5f) / pt2;
			d0sigma1 = fabs(mu_staco_trackIPEstimate_d0_unbiasedpvunbiased->at(index1) / mu_staco_trackIPEstimate_sigd0_unbiasedpvunbiased->at(index1));
			d0sigma2 = fabs(mu_staco_trackIPEstimate_d0_unbiasedpvunbiased->at(index2) / mu_staco_trackIPEstimate_sigd0_unbiasedpvunbiased->at(index2));
			ptCut1 = ptCut2 = higgs_mu_trigg_pt;
			d0sigmaCut1 = d0sigmaCut2 = d0sigma_mu;
			ptTkOverlapping1 = (mu_staco_id_qoverp_exPV->at(index1) != 0.0f) ? sinf(mu_staco_id_theta_exPV->at(index1)) / fabs(mu_staco_id_qoverp_exPV->at(index1)) : 0.0f;
			ptTkOverlapping2 = (mu_staco_id_qoverp_exPV->at(index2) != 0.0f) ? sinf(mu_staco_id_theta_exPV->at(index2)) / fabs(mu_staco_id_qoverp_exPV->at(index2)) : 0.0f;
			ptClOverlapping1 = 0.0f;
			ptClOverlapping2 = 0.0f;
			break;

		case TYPE_MUON_MUID:
			E1 = mu_muid_E->at(index1);
			E2 = mu_muid_E->at(index2);
			pt1 = mu_muid_pt->at(index1);
			pt2 = mu_muid_pt->at(index2);
			eta1 = mu_muid_eta->at(index1);
			eta2 = mu_muid_eta->at(index2);
			phi1 = mu_muid_phi->at(index1);
			phi2 = mu_muid_phi->at(index2);
			charge1 = mu_muid_charge->at(index1);
			charge2 = mu_muid_charge->at(index2);
			tkIso1 = mu_muid_ptcone20->at(index1) / pt1;
			tkIso2 = mu_muid_ptcone20->at(index2) / pt2;
			clIso1 = (mu_muid_etcone20->at(index1) - Float_t(nPV2 - 1) * 33.5f) / pt1;
			clIso2 = (mu_muid_etcone20->at(index2) - Float_t(nPV2 - 1) * 33.5f) / pt2;
			d0sigma1 = fabs(mu_muid_trackIPEstimate_d0_unbiasedpvunbiased->at(index1) / mu_muid_trackIPEstimate_sigd0_unbiasedpvunbiased->at(index1));
			d0sigma2 = fabs(mu_muid_trackIPEstimate_d0_unbiasedpvunbiased->at(index2) / mu_muid_trackIPEstimate_sigd0_unbiasedpvunbiased->at(index2));
			ptCut1 = ptCut2 = higgs_mu_trigg_pt;
			d0sigmaCut1 = d0sigmaCut2 = d0sigma_mu;
			ptTkOverlapping1 = (mu_muid_id_qoverp_exPV->at(index1) != 0.0f) ? sinf(mu_muid_id_theta_exPV->at(index1)) / fabs(mu_muid_id_qoverp_exPV->at(index1)) : 0.0f;
			ptTkOverlapping2 = (mu_muid_id_qoverp_exPV->at(index2) != 0.0f) ? sinf(mu_muid_id_theta_exPV->at(index2)) / fabs(mu_muid_id_qoverp_exPV->at(index2)) : 0.0f;
			ptClOverlapping1 = 0.0f;
			ptClOverlapping2 = 0.0f;
			break;

		default:
			return false;
	}

	switch(type2)
	{
		case TYPE_ELECTRON:
			E3 = el_cl_E->at(index3);
			E4 = el_cl_E->at(index4);
			pt3 = electronGetEt(index3);
			pt4 = electronGetEt(index4);
			eta3 = electronGetEtaDirection(index3);
			eta4 = electronGetEtaDirection(index4);
			phi3 = electronGetPhiDirection(index3);
			phi4 = electronGetPhiDirection(index4);
			charge3 = el_charge->at(index3);
			charge4 = el_charge->at(index4);
			tkIso3 = el_ptcone20->at(index3) / pt3;
			tkIso4 = el_ptcone20->at(index4) / pt4;
			clIso3 = CaloIsoCorrection::GetNPVCorrectedIsolation(nPV2, el_etas2->at(index3), 20, core::isMC(RunNumber), el_Etcone20->at(index3), CaloIsoCorrection::ELECTRON) / pt3;
			clIso4 = CaloIsoCorrection::GetNPVCorrectedIsolation(nPV2, el_etas2->at(index4), 20, core::isMC(RunNumber), el_Etcone20->at(index4), CaloIsoCorrection::ELECTRON) / pt4;
			d0sigma3 = fabs(el_trackd0pvunbiased->at(index3) / el_tracksigd0pvunbiased->at(index3));
			d0sigma4 = fabs(el_trackd0pvunbiased->at(index4) / el_tracksigd0pvunbiased->at(index4));
			ptCut3 = ptCut4 = higgs_el_trigg_pt;
			d0sigmaCut3 = d0sigmaCut4 = d0sigma_el;
			ptTkOverlapping3 = el_trackpt->at(index3);
			ptTkOverlapping4 = el_trackpt->at(index4);
			ptClOverlapping3 = pt3;
			ptClOverlapping4 = pt4;
			break;

		case TYPE_MUON_STACO:
			E3 = mu_staco_E->at(index3);
			E4 = mu_staco_E->at(index4);
			pt3 = mu_staco_pt->at(index3);
			pt4 = mu_staco_pt->at(index4);
			eta3 = mu_staco_eta->at(index3);
			eta4 = mu_staco_eta->at(index4);
			phi3 = mu_staco_phi->at(index3);
			phi4 = mu_staco_phi->at(index4);
			charge3 = mu_staco_charge->at(index3);
			charge4 = mu_staco_charge->at(index4);
			tkIso3 = mu_staco_ptcone20->at(index3) / pt3;
			tkIso4 = mu_staco_ptcone20->at(index4) / pt4;
			clIso3 = (mu_staco_etcone20->at(index3) - Float_t(nPV2 - 1) * 33.5f) / pt3;
			clIso4 = (mu_staco_etcone20->at(index4) - Float_t(nPV2 - 1) * 33.5f) / pt4;
			d0sigma3 = fabs(mu_staco_trackIPEstimate_d0_unbiasedpvunbiased->at(index3) / mu_staco_trackIPEstimate_sigd0_unbiasedpvunbiased->at(index3));
			d0sigma4 = fabs(mu_staco_trackIPEstimate_d0_unbiasedpvunbiased->at(index4) / mu_staco_trackIPEstimate_sigd0_unbiasedpvunbiased->at(index4));
			ptCut3 = ptCut4 = higgs_mu_trigg_pt;
			d0sigmaCut3 = d0sigmaCut4 = d0sigma_mu;
			ptTkOverlapping3 = (mu_staco_id_qoverp_exPV->at(index3) != 0.0f) ? sinf(mu_staco_id_theta_exPV->at(index3)) / fabs(mu_staco_id_qoverp_exPV->at(index3)) : 0.0f;
			ptTkOverlapping4 = (mu_staco_id_qoverp_exPV->at(index4) != 0.0f) ? sinf(mu_staco_id_theta_exPV->at(index4)) / fabs(mu_staco_id_qoverp_exPV->at(index4)) : 0.0f;
			ptClOverlapping3 = 0.0f;
			ptClOverlapping4 = 0.0f;
			break;

		case TYPE_MUON_MUID:
			E3 = mu_muid_E->at(index3);
			E4 = mu_muid_E->at(index4);
			pt3 = mu_muid_pt->at(index3);
			pt4 = mu_muid_pt->at(index4);
			eta3 = mu_muid_eta->at(index3);
			eta4 = mu_muid_eta->at(index4);
			phi3 = mu_muid_phi->at(index3);
			phi4 = mu_muid_phi->at(index4);
			charge3 = mu_muid_charge->at(index3);
			charge4 = mu_muid_charge->at(index4);
			tkIso3 = mu_muid_ptcone20->at(index3) / pt3;
			tkIso4 = mu_muid_ptcone20->at(index4) / pt4;
			clIso3 = (mu_muid_etcone20->at(index3) - Float_t(nPV2 - 1) * 33.5f) / pt3;
			clIso4 = (mu_muid_etcone20->at(index4) - Float_t(nPV2 - 1) * 33.5f) / pt4;
			d0sigma3 = fabs(mu_muid_trackIPEstimate_d0_unbiasedpvunbiased->at(index3) / mu_muid_trackIPEstimate_sigd0_unbiasedpvunbiased->at(index3));
			d0sigma4 = fabs(mu_muid_trackIPEstimate_d0_unbiasedpvunbiased->at(index4) / mu_muid_trackIPEstimate_sigd0_unbiasedpvunbiased->at(index4));
			ptCut3 = ptCut4 = higgs_mu_trigg_pt;
			d0sigmaCut3 = d0sigmaCut4 = d0sigma_mu;
			ptTkOverlapping3 = (mu_muid_id_qoverp_exPV->at(index3) != 0.0f) ? sinf(mu_muid_id_theta_exPV->at(index3)) / fabs(mu_muid_id_qoverp_exPV->at(index3)) : 0.0f;
			ptTkOverlapping4 = (mu_muid_id_qoverp_exPV->at(index4) != 0.0f) ? sinf(mu_muid_id_theta_exPV->at(index4)) / fabs(mu_muid_id_qoverp_exPV->at(index4)) : 0.0f;
			ptClOverlapping3 = 0.0f;
			ptClOverlapping4 = 0.0f;
			break;

		default:
			return false;
	}

	Bool_t isOk = true;

	Float_t eArray[4] = {E1, E2, E3, E4};
	Float_t ptArray[4] = {pt1, pt2, pt3, pt4};
	Float_t etaArray[4] = {eta1, eta2, eta3, eta4};
	Float_t phiArray[4] = {phi1, phi2, phi3, phi4};
	Float_t tkIsoArray[4] = {tkIso1, tkIso2, tkIso3, tkIso4};
	Float_t clIsoArray[4] = {clIso1, clIso2, clIso3, clIso4};
	Float_t d0sigmaArray[4] = {d0sigma1, d0sigma2, d0sigma3, d0sigma4};
	Float_t d0sigmaCutArray[4] = {d0sigmaCut1, d0sigmaCut2, d0sigmaCut3, d0sigmaCut4};

	Float_t ptTkOverlappingArray[4] = {ptTkOverlapping1, ptTkOverlapping2, ptTkOverlapping3, ptTkOverlapping4};
	Float_t ptClOverlappingArray[4] = {ptClOverlapping1, ptClOverlapping2, ptClOverlapping3, ptClOverlapping4};

	Int_t truthMatchArray[4] = {truthMatch1, truthMatch2, truthMatch3, truthMatch4};
	Int_t triggerMatchArray[4] = {triggerMatch1, triggerMatch2, triggerMatch3, triggerMatch4};

	_INC(isOk, dest, 0);

	/*-----------------------------------------------------------------*/
	/* SFOS + mass_2e2µ						   */
	/*-----------------------------------------------------------------*/

	Int_t pair1[2] = {-1, -1};
	Int_t pair2[2] = {-1, -1};
	Int_t pair3[2] = {-1, -1};
	Int_t pair4[2] = {-1, -1};

	if(buildPairs(pair1, pair2, pair3, pair4,
					type1, type2,
						charge1, charge2, charge3, charge4) == false)
	{
		return false;
	}

	/*-----------------------------------------------------------------*/

	Bool_t eeuu = true;

	TZVector Z1;
	TZVector Z2;
	TZVector Z3;
	TZVector Z4;

	TLorentzVector H_lorentz;

	if(type1 == type2)
	{
		/*---------------------------------------------------------*/
		/* eeee or µµµµ						   */
		/*---------------------------------------------------------*/

		Z1.l1_truthMatch = truthMatchArray[pair1[0]];
		Z1.l1_triggerMatch = triggerMatchArray[pair1[0]];
		Z1.l1_lorentz.SetPtEtaPhiE(1.0e-3f * ptArray[pair1[0]], etaArray[pair1[0]], phiArray[pair1[0]], 1.0e-3f * eArray[pair1[0]]);

		Z1.l2_truthMatch = truthMatchArray[pair1[1]];
		Z1.l2_triggerMatch = triggerMatchArray[pair1[1]];
		Z1.l2_lorentz.SetPtEtaPhiE(1.0e-3f * ptArray[pair1[1]], etaArray[pair1[1]], phiArray[pair1[1]], 1.0e-3f * eArray[pair1[1]]);

		Z2.l1_truthMatch = truthMatchArray[pair2[0]];
		Z2.l1_triggerMatch = triggerMatchArray[pair2[0]];
		Z2.l1_lorentz.SetPtEtaPhiE(1.0e-3f * ptArray[pair2[0]], etaArray[pair2[0]], phiArray[pair2[0]], 1.0e-3f * eArray[pair2[0]]);

		Z2.l2_truthMatch = truthMatchArray[pair2[1]];
		Z2.l2_triggerMatch = triggerMatchArray[pair2[1]];
		Z2.l2_lorentz.SetPtEtaPhiE(1.0e-3f * ptArray[pair2[1]], etaArray[pair2[1]], phiArray[pair2[1]], 1.0e-3f * eArray[pair2[1]]);

		Z1.Z_lorentz = Z1.l1_lorentz + Z1.l2_lorentz;
		Z2.Z_lorentz = Z2.l1_lorentz + Z2.l2_lorentz;
		TLorentzVector H1_lorentz = Z1.Z_lorentz + Z2.Z_lorentz;

		if(fabs(Z_MASS - Z1.Z_lorentz.M()) > fabs(Z_MASS - Z2.Z_lorentz.M()))
		{
			SWAP(Z1, Z2);
		}

		/**/

		Z3.l1_truthMatch = truthMatchArray[pair3[0]];
		Z3.l1_triggerMatch = triggerMatchArray[pair3[0]];
		Z3.l1_lorentz.SetPtEtaPhiE(1.0e-3f * ptArray[pair3[0]], etaArray[pair3[0]], phiArray[pair3[0]], 1.0e-3f * eArray[pair3[0]]);

		Z3.l2_truthMatch = truthMatchArray[pair3[1]];
		Z3.l2_triggerMatch = triggerMatchArray[pair3[1]];
		Z3.l2_lorentz.SetPtEtaPhiE(1.0e-3f * ptArray[pair3[1]], etaArray[pair3[1]], phiArray[pair3[1]], 1.0e-3f * eArray[pair3[1]]);

		Z4.l1_truthMatch = truthMatchArray[pair4[0]];
		Z4.l1_triggerMatch = triggerMatchArray[pair4[0]];
		Z4.l1_lorentz.SetPtEtaPhiE(1.0e-3f * ptArray[pair4[0]], etaArray[pair4[0]], phiArray[pair4[0]], 1.0e-3f * eArray[pair4[0]]);

		Z4.l2_truthMatch = truthMatchArray[pair4[1]];
		Z4.l2_triggerMatch = triggerMatchArray[pair4[1]];
		Z4.l2_lorentz.SetPtEtaPhiE(1.0e-3f * ptArray[pair4[1]], etaArray[pair4[1]], phiArray[pair4[1]], 1.0e-3f * eArray[pair4[1]]);

		Z3.Z_lorentz = Z3.l1_lorentz + Z3.l2_lorentz;
		Z4.Z_lorentz = Z4.l1_lorentz + Z4.l2_lorentz;
		TLorentzVector H2_lorentz = Z3.Z_lorentz + Z4.Z_lorentz;

		if(fabs(Z_MASS - Z3.Z_lorentz.M()) > fabs(Z_MASS - Z4.Z_lorentz.M()))
		{
			SWAP(Z3, Z4);
		}

		/**/

		if(fabs(H1_lorentz.M() - H2_lorentz.M()) > 1.0e-5f)
		{
			std::cerr << "Oula !!!" << std::endl;

			isOk = false;
		}

		H_lorentz = 0.5f * (H1_lorentz + H2_lorentz);

		/*---------------------------------------------------------*/
	}
	else
	{
		/*---------------------------------------------------------*/
		/* eeµµ or µµee						   */
		/*---------------------------------------------------------*/

		Z1.l1_truthMatch = truthMatchArray[pair1[0]];
		Z1.l1_triggerMatch = triggerMatchArray[pair1[0]];
		Z1.l1_lorentz.SetPtEtaPhiE(1.0e-3f * ptArray[pair1[0]], etaArray[pair1[0]], phiArray[pair1[0]], 1.0e-3f * eArray[pair1[0]]);

		Z1.l2_truthMatch = truthMatchArray[pair1[1]];
		Z1.l2_triggerMatch = triggerMatchArray[pair1[1]];
		Z1.l2_lorentz.SetPtEtaPhiE(1.0e-3f * ptArray[pair1[1]], etaArray[pair1[1]], phiArray[pair1[1]], 1.0e-3f * eArray[pair1[1]]);

		Z2.l1_truthMatch = truthMatchArray[pair2[0]];
		Z2.l1_triggerMatch = triggerMatchArray[pair2[0]];
		Z2.l1_lorentz.SetPtEtaPhiE(1.0e-3f * ptArray[pair2[0]], etaArray[pair2[0]], phiArray[pair2[0]], 1.0e-3f * eArray[pair2[0]]);

		Z2.l2_truthMatch = truthMatchArray[pair2[1]];
		Z2.l2_triggerMatch = triggerMatchArray[pair2[1]];
		Z2.l2_lorentz.SetPtEtaPhiE(1.0e-3f * ptArray[pair2[1]], etaArray[pair2[1]], phiArray[pair2[1]], 1.0e-3f * eArray[pair2[1]]);

		Z1.Z_lorentz = Z1.l1_lorentz + Z1.l2_lorentz;
		Z2.Z_lorentz = Z2.l1_lorentz + Z2.l2_lorentz;
		H_lorentz = Z1.Z_lorentz + Z2.Z_lorentz;

		if(fabs(Z_MASS - Z1.Z_lorentz.M()) > fabs(Z_MASS - Z2.Z_lorentz.M()))
		{
			SWAP(Z1, Z2);

			eeuu = false;
		}

		Z3 = Z1;
		Z4 = Z2;

		/**/

		if(Z1.Z_lorentz.M() < 15.0f
		   ||
		   Z2.Z_lorentz.M() < 15.0f
		 ) {
			isOk = false;
		}

		/*---------------------------------------------------------*/
	}

	_INC(isOk, dest, 1);

	/*-----------------------------------------------------------------*/
	/* KINEMATICS							   */
	/*-----------------------------------------------------------------*/

	Int_t nrKinematics = 0;

	if(pt1 > ptCut1) {
		nrKinematics++;
	}

	if(pt2 > ptCut2) {
		nrKinematics++;
	}

	if(pt3 > ptCut3) {
		nrKinematics++;
	}

	if(pt4 > ptCut4) {
		nrKinematics++;
	}

	if(nrKinematics < 2)
	{
		isOk = false;
	}

	_INC(isOk, dest, 2);

	/*-----------------------------------------------------------------*/
	/* TRIGGER							   */
	/*-----------------------------------------------------------------*/

	Int_t nrTrigger = 0;

	if(triggerMatch1 != false) {
		nrTrigger++;
	}

	if(triggerMatch2 != false) {
		nrTrigger++;
	}

	if(triggerMatch3 != false) {
		nrTrigger++;
	}

	if(triggerMatch4 != false) {
		nrTrigger++;
	}

	if(nrTrigger < 1)
	{
		isOk = false;
	}

	_INC(isOk, dest, 3);

	/*-----------------------------------------------------------------*/
	/* LEADING Z CUTS						   */
	/*-----------------------------------------------------------------*/

	Bool_t q1 = fabs(Z_MASS - Z1.Z_lorentz.M()) < Z_REGION;
	Bool_t q2 = fabs(Z_MASS - Z3.Z_lorentz.M()) < Z_REGION;

	if(q1 == false
	   &&
	   q2 == false
	 ) {
		isOk = false;
	}

	_INC(isOk, dest, 4);

	/*-----------------------------------------------------------------*/
	/* SUB-LEADING Z CUTS						   */
	/*-----------------------------------------------------------------*/

	Bool_t q3 = q1 && subLeadingCut(Z2.Z_lorentz.M(), H_lorentz.M());
	Bool_t q4 = q2 && subLeadingCut(Z4.Z_lorentz.M(), H_lorentz.M());

	/**/ if(q3 == false && q4 == false)
	{
		isOk = false;
	}
	else if(q3 != false && q4 != false)
	{
		if(fabs(Z_MASS - Z1.Z_lorentz.M()) > fabs(Z_MASS - Z3.Z_lorentz.M()))
		{
			SWAP(Z1, Z3);
			SWAP(Z2, Z4);
		}
	}
	else if(q3 == false && q4 != false)
	{
		SWAP(Z1, Z3);
		SWAP(Z2, Z4);
	}

	_INC(isOk, dest, 5);

	/*-----------------------------------------------------------------*/
	/* min[ΔR]>0.10							   */
	/*-----------------------------------------------------------------*/

	for(Int_t i = 0 + 0; i < 4; i++)
	{
		for(Int_t j = i + 1; j < 4; j++)
		{
			if(sqrtf(__dR2(etaArray[i], etaArray[j], phiArray[i], phiArray[j])) < 0.10f)
			{
				isOk = false;
			}
		}
	}

	_INC(isOk, dest, 6);

	/*-----------------------------------------------------------------*/
	/* TRACK ISOLATION						   */
	/*-----------------------------------------------------------------*/

	for(Int_t i = 0 + 0; i < 4; i++)
	{
		for(Int_t j = i + 1; j < 4; j++)
		{
			if(sqrtf(__dR2(etaArray[i], etaArray[j], phiArray[i], phiArray[j])) < 0.20f)
			{
				tkIsoArray[i] -= ptTkOverlappingArray[j] / ptArray[i];
				tkIsoArray[j] -= ptTkOverlappingArray[i] / ptArray[j];
			}
		}
	}

	if(tkIsoArray[0] > tkIso
	   ||
	   tkIsoArray[1] > tkIso
	   ||
	   tkIsoArray[2] > tkIso
	   ||
	   tkIsoArray[3] > tkIso
	 ) {
		isOk = false; 
	}

	_INC(isOk, dest, 7);

	/*-----------------------------------------------------------------*/
	/* CALO ISOLATION						   */
	/*-----------------------------------------------------------------*/

	for(Int_t i = 0 + 0; i < 4; i++)
	{
		for(Int_t j = i + 1; j < 4; j++)
		{
			if(sqrtf(__dR2(etaArray[i], etaArray[j], phiArray[i], phiArray[j])) < 0.18f)
			{
				clIsoArray[i] -= ptClOverlappingArray[j] / ptArray[i];
				clIsoArray[j] -= ptClOverlappingArray[i] / ptArray[j];
			}
		}
	}

	if(clIsoArray[0] > clIso
	   ||
	   clIsoArray[1] > clIso
	   ||
	   clIsoArray[2] > clIso
	   ||
	   clIsoArray[3] > clIso
	 ) {
		isOk = false; 
	}

	_INC(isOk, dest, 8);

	/*-----------------------------------------------------------------*/
	/* D0 SIGNIFICANCE						   */
	/*-----------------------------------------------------------------*/

	Int_t reArray[4];

	if(H_lorentz.M() < 190.0f)
	{
		reIndex(reArray, ptArray, ptCompare);

		if(d0sigmaArray[reArray[0]] > d0sigmaCutArray[reArray[0]]
	   	   ||
	   	   d0sigmaArray[reArray[1]] > d0sigmaCutArray[reArray[1]]
	 	 ) {
			isOk = false;
		}
	}

	_INC(isOk, dest, 9);

	/*-----------------------------------------------------------------*/

	Int_t n = m_H[dest].n++;

	m_H[dest].weight1[n] = weight1;
	m_H[dest].weight2[n] = weight2;
	m_H[dest].weight3[n] = weight3;

	m_H[dest].l1_truthMatch[n] = Z1.l1_truthMatch;
	m_H[dest].l2_truthMatch[n] = Z1.l2_truthMatch;
	m_H[dest].l3_truthMatch[n] = Z2.l1_truthMatch;
	m_H[dest].l4_truthMatch[n] = Z2.l2_truthMatch;
	m_H[dest].l1_triggerMatch[n] = Z1.l1_triggerMatch;
	m_H[dest].l2_triggerMatch[n] = Z1.l2_triggerMatch;
	m_H[dest].l3_triggerMatch[n] = Z2.l1_triggerMatch;
	m_H[dest].l4_triggerMatch[n] = Z2.l2_triggerMatch;

	m_H[dest].l1_pt[n] = Z1.l1_lorentz.Pt();
	m_H[dest].l2_pt[n] = Z1.l2_lorentz.Pt();
	m_H[dest].l3_pt[n] = Z2.l1_lorentz.Pt();
	m_H[dest].l4_pt[n] = Z2.l2_lorentz.Pt();
	m_H[dest].l1_eta[n] = Z1.l1_lorentz.Eta();
	m_H[dest].l2_eta[n] = Z1.l2_lorentz.Eta();
	m_H[dest].l3_eta[n] = Z2.l1_lorentz.Eta();
	m_H[dest].l4_eta[n] = Z2.l2_lorentz.Eta();
	m_H[dest].l1_phi[n] = Z1.l1_lorentz.Phi();
	m_H[dest].l2_phi[n] = Z1.l2_lorentz.Phi();
	m_H[dest].l3_phi[n] = Z2.l1_lorentz.Phi();
	m_H[dest].l4_phi[n] = Z2.l2_lorentz.Phi();

	m_H[dest].Z12_m[n] = Z1.Z_lorentz.M();
	m_H[dest].Z34_m[n] = Z2.Z_lorentz.M();
	m_H[dest].Z12_et[n] = Z1.Z_lorentz.Et();
	m_H[dest].Z34_et[n] = Z2.Z_lorentz.Et();
	m_H[dest].Z12_pt[n] = Z1.Z_lorentz.Pt();
	m_H[dest].Z34_pt[n] = Z2.Z_lorentz.Pt();
	m_H[dest].Z12_eta[n] = Z1.Z_lorentz.Eta();
	m_H[dest].Z34_eta[n] = Z2.Z_lorentz.Eta();
	m_H[dest].Z12_phi[n] = Z1.Z_lorentz.Phi();
	m_H[dest].Z34_phi[n] = Z2.Z_lorentz.Phi();

	m_H[dest].H_m[n] = H_lorentz.M();
	m_H[dest].H_et[n] = H_lorentz.Et();
	m_H[dest].H_pt[n] = H_lorentz.Pt();
	m_H[dest].H_eta[n] = H_lorentz.Eta();
	m_H[dest].H_phi[n] = H_lorentz.Phi();

	m_H[dest].eeuu[n] = eeuu;

	/*-----------------------------------------------------------------*/

	return true;
}

/*-------------------------------------------------------------------------*/

