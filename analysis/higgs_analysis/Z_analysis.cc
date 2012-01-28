/*-------------------------------------------------------------------------*/

#include <cmath>
#include <iostream>

#include <TLorentzVector.h>

#include <egammaAnalysisUtils/CaloIsoCorrection.h>

#include "main.h"

/*-------------------------------------------------------------------------*/

bool THiggsBuilder::Z_analysis(
	Int_t index1,
	Int_t index2,
	TLeptonType type,
	Int_t dest
) {
	Float_t higgs_el_trigg_pt = core::configFltLookup("higgs_el_trigg_pt");
	Float_t higgs_mu_trigg_pt = core::configFltLookup("higgs_mu_trigg_pt");

	/*-----------------------------------------------------------------*/
	/* EVENT							   */
	/*-----------------------------------------------------------------*/

	m_Z[dest].RunNumber   =  RunNumber ;
	m_Z[dest].EventNumber = EventNumber;
	m_Z[dest].LumiBlock   =     lbn    ;

	m_Z[dest].nPV2 = nPV2;
	m_Z[dest].nIntPerXing = averageIntPerXing;

	m_Z[dest].elTrigger = getElTrigger();
	m_Z[dest].muTrigger = getMuTrigger();

	m_Z[dest].tn = triggerTrace(m_Z[dest].ta);

	Float_t weight1 = eventGetWeight1();
	Float_t weight2 = eventGetWeight2();
	Float_t weight3 = \
		eventGetWeight3(index1, type)
		*
		eventGetWeight3(index2, type)
	;

	/*-----------------------------------------------------------------*/
	/* VARIABLES							   */
	/*-----------------------------------------------------------------*/

	Float_t E1, pt1, eta1, phi1, charge1, tkIso201, clIso201, d0sigma1;
	Float_t E2, pt2, eta2, phi2, charge2, tkIso202, clIso202, d0sigma2;

	Float_t ptCut1;
	Float_t ptCut2;

	Float_t ptTkOverlapping1, ptClOverlapping1;
	Float_t ptTkOverlapping2, ptClOverlapping2;

	Bool_t tight1;
	Bool_t tight2;

	Bool_t truthMatch1 = truthMatch(index1, type);
	Bool_t truthMatch2 = truthMatch(index2, type);
	Bool_t triggerMatch1 = triggerMatch(index1, type);
	Bool_t triggerMatch2 = triggerMatch(index2, type);

	switch(type)
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
			tight1 = el_tight->at(index1) != 0;
			tight2 = el_tight->at(index2) != 0;
			tkIso201 = el_ptcone20->at(index1) / pt1;
			tkIso202 = el_ptcone20->at(index2) / pt2;
			clIso201 = CaloIsoCorrection::GetNPVCorrectedIsolation(nPV2, el_etas2->at(index1), 20, __isMC, el_Etcone20->at(index1), CaloIsoCorrection::ELECTRON) / pt1;
			clIso202 = CaloIsoCorrection::GetNPVCorrectedIsolation(nPV2, el_etas2->at(index2), 20, __isMC, el_Etcone20->at(index2), CaloIsoCorrection::ELECTRON) / pt2;
			d0sigma1 = fabs(el_trackd0pvunbiased->at(index1) / el_tracksigd0pvunbiased->at(index1));
			d0sigma2 = fabs(el_trackd0pvunbiased->at(index2) / el_tracksigd0pvunbiased->at(index2));
			ptCut1 = ptCut2 = higgs_el_trigg_pt;
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
			tight1 = mu_staco_tight->at(index1) != 0;
			tight2 = mu_staco_tight->at(index2) != 0;
			tkIso201 = mu_staco_ptcone20->at(index1) / mu_staco_pt->at(index1);
			tkIso202 = mu_staco_ptcone20->at(index2) / mu_staco_pt->at(index2);
			clIso201 = (mu_staco_etcone20->at(index1) - Float_t(nPV2 - 1) * 33.5f) / mu_staco_pt->at(index1);
			clIso202 = (mu_staco_etcone20->at(index2) - Float_t(nPV2 - 1) * 33.5f) / mu_staco_pt->at(index2);
			d0sigma1 = fabs(mu_staco_trackIPEstimate_d0_unbiasedpvunbiased->at(index1) / mu_staco_trackIPEstimate_sigd0_unbiasedpvunbiased->at(index1));
			d0sigma2 = fabs(mu_staco_trackIPEstimate_d0_unbiasedpvunbiased->at(index2) / mu_staco_trackIPEstimate_sigd0_unbiasedpvunbiased->at(index2));
			ptCut1 = ptCut2 = higgs_mu_trigg_pt;
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
			tight1 = mu_muid_tight->at(index1) != 0;
			tight2 = mu_muid_tight->at(index2) != 0;
			tkIso201 = mu_muid_ptcone20->at(index1) / mu_muid_pt->at(index1);
			tkIso202 = mu_muid_ptcone20->at(index2) / mu_muid_pt->at(index2);
			clIso201 = (mu_muid_etcone20->at(index1) - Float_t(nPV2 - 1) * 33.5f) / mu_muid_pt->at(index1);
			clIso202 = (mu_muid_etcone20->at(index2) - Float_t(nPV2 - 1) * 33.5f) / mu_muid_pt->at(index2);
			d0sigma1 = fabs(mu_muid_trackIPEstimate_d0_unbiasedpvunbiased->at(index1) / mu_muid_trackIPEstimate_sigd0_unbiasedpvunbiased->at(index1));
			d0sigma2 = fabs(mu_muid_trackIPEstimate_d0_unbiasedpvunbiased->at(index2) / mu_muid_trackIPEstimate_sigd0_unbiasedpvunbiased->at(index2));
			ptCut1 = ptCut2 = higgs_mu_trigg_pt;
			ptTkOverlapping1 = (mu_muid_id_qoverp_exPV->at(index1) != 0.0f) ? sinf(mu_muid_id_theta_exPV->at(index1)) / fabs(mu_muid_id_qoverp_exPV->at(index1)) : 0.0f;
			ptTkOverlapping2 = (mu_muid_id_qoverp_exPV->at(index2) != 0.0f) ? sinf(mu_muid_id_theta_exPV->at(index2)) / fabs(mu_muid_id_qoverp_exPV->at(index2)) : 0.0f;
			ptClOverlapping1 = 0.0f;
			ptClOverlapping2 = 0.0f;
			break;

		default:
			return false;
	}

	Float_t eArray[2] = {E1, E2};
	Float_t ptArray[2] = {pt1, pt2};
	Float_t etaArray[2] = {eta1, eta2};
	Float_t phiArray[2] = {phi1, phi2};
	Bool_t tightArray[2] = {tight1, tight2};
	Float_t tkIso20Array[2] = {tkIso201, tkIso202};
	Float_t clIso20Array[2] = {clIso201, clIso202};
	Float_t d0sigmaArray[2] = {d0sigma1, d0sigma2};

	Float_t ptTkOverlappingArray[2] = {ptTkOverlapping1, ptTkOverlapping2};
	Float_t ptClOverlappingArray[2] = {ptClOverlapping1, ptClOverlapping2};

	Int_t truthMatchArray[2] = {truthMatch1, truthMatch2};
	Int_t triggerMatchArray[2] = {triggerMatch1, triggerMatch2};

	/*-----------------------------------------------------------------*/
	/* PAIR								   */
	/*-----------------------------------------------------------------*/

	Int_t pair[2] = {-1, -1};

	if(buildPair(pair, charge1, charge2) == false)
	{
		return false;
	}

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

	if(nrKinematics < 1)
	{
		return false;
	}

	/*-----------------------------------------------------------------*/
	/* TRIGGER							   */
	/*-----------------------------------------------------------------*/

	Int_t nrTrigger = 0;

	if(triggerMatch1) {
		nrTrigger++;
	}

	if(triggerMatch2) {
		nrTrigger++;
	}

	if(nrTrigger < 1)
	{
		return false;
	}

	/*-----------------------------------------------------------------*/
	/* RELATIVITY							   */
	/*-----------------------------------------------------------------*/

	TLorentzVector Pl1, Pl2, Pz;

	Pl1.SetPtEtaPhiE(1.0e-3f * ptArray[pair[0]], etaArray[pair[0]], phiArray[pair[0]], 1.0e-3f * eArray[pair[0]]);
	Pl2.SetPtEtaPhiE(1.0e-3f * ptArray[pair[1]], etaArray[pair[1]], phiArray[pair[1]], 1.0e-3f * eArray[pair[1]]);

	Pz = Pl1 + Pl2;

	/*-----------------------------------------------------------------*/
	/* TRACK ISOLATION						   */
	/*-----------------------------------------------------------------*/

	Float_t a = ptTkOverlappingArray[pair[1]] / ptArray[pair[0]];
	Float_t b = ptTkOverlappingArray[pair[0]] / ptArray[pair[1]];

	if(sqrtf(__dR2(etaArray[pair[0]], etaArray[pair[1]], phiArray[pair[0]], phiArray[pair[1]])) < 0.20f)
	{
		tkIso20Array[pair[0]] -= a;
		tkIso20Array[pair[1]] -= b;
	}

	/*-----------------------------------------------------------------*/
	/* CALO ISOLATION						   */
	/*-----------------------------------------------------------------*/

	Float_t c = ptClOverlappingArray[pair[1]] / ptArray[pair[0]];
	Float_t d = ptClOverlappingArray[pair[0]] / ptArray[pair[1]];

	if(sqrtf(__dR2(etaArray[pair[0]], etaArray[pair[1]], phiArray[pair[0]], phiArray[pair[1]])) < 0.18f)
	{
		clIso20Array[pair[0]] -= c;
		clIso20Array[pair[1]] -= d;
	}

	/*-----------------------------------------------------------------*/
	/* NTUPLE							   */
	/*-----------------------------------------------------------------*/

	Int_t n = m_Z[dest].n++;

	m_Z[dest].weight1[n] = weight1;
	m_Z[dest].weight2[n] = weight2;
	m_Z[dest].weight3[n] = weight3;

	m_Z[dest].l1_tight[n] = tightArray[pair[0]];
	m_Z[dest].l2_tight[n] = tightArray[pair[1]];

	m_Z[dest].l1_truthMatch[n] = truthMatchArray[pair[0]];
	m_Z[dest].l2_truthMatch[n] = truthMatchArray[pair[1]];
	m_Z[dest].l1_triggerMatch[n] = triggerMatchArray[pair[0]];
	m_Z[dest].l2_triggerMatch[n] = triggerMatchArray[pair[1]];

	m_Z[dest].l1_pt[n] = 1.0e-3f * ptArray[pair[0]];
	m_Z[dest].l2_pt[n] = 1.0e-3f * ptArray[pair[1]];
	m_Z[dest].l1_eta[n] = etaArray[pair[0]];
	m_Z[dest].l2_eta[n] = etaArray[pair[1]];
	m_Z[dest].l1_phi[n] = phiArray[pair[0]];
	m_Z[dest].l2_phi[n] = phiArray[pair[1]];

	m_Z[dest].l1_tkIso20[n] = tkIso20Array[pair[0]];
	m_Z[dest].l2_tkIso20[n] = tkIso20Array[pair[1]];
	m_Z[dest].l1_clIso20[n] = clIso20Array[pair[0]];
	m_Z[dest].l2_clIso20[n] = clIso20Array[pair[1]];
	m_Z[dest].l1_d0sigma[n] = d0sigmaArray[pair[0]];
	m_Z[dest].l2_d0sigma[n] = d0sigmaArray[pair[1]];

	m_Z[dest].Z_m[n] = Pz.M();
	m_Z[dest].Z_et[n] = Pz.Et();
	m_Z[dest].Z_pt[n] = Pz.Pt();
	m_Z[dest].Z_eta[n] = Pz.Eta();
	m_Z[dest].Z_phi[n] = Pz.Phi();

	/*-----------------------------------------------------------------*/

	return true;
}

/*-------------------------------------------------------------------------*/

