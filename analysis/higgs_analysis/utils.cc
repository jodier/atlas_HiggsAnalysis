/*-------------------------------------------------------------------------*/

#include <cmath>
#include <cstdlib>

#include "utils.h"

/*-------------------------------------------------------------------------*/

void TLeptonAnalysis::fixeEnergy(void)
{
	if(core::ER == false
	   &&
	   core::SM == false
	 ) {
		return;
	}

	if(core::isMC(RunNumber) == false && core::ER != false)
	{
		/*---------------------------------------------------------*/

		for(Int_t i = 0; i < el_n; i++)
		{
			if(fabs(el_cl_eta->at(i)) > 2.47f)
			{
				continue;
			}

			el_cl_E->at(i) = m_energyRescaler->applyEnergyCorrectionMeV(
				el_cl_eta->at(i),
				el_cl_phi->at(i),
				el_cl_E->at(i),
				electronGetEt(i),
				0, "ELECTRON"
			);
		}

		/*---------------------------------------------------------*/
	}

	if(core::isMC(RunNumber) != false && core::SM != false)
	{
		/*---------------------------------------------------------*/

		for(Int_t i = 0; i < el_n; i++)
		{
			if(fabs(el_cl_eta->at(i)) > 2.47f)
			{
				continue;
			}

			m_energyRescaler->SetRandomSeed(RunNumber + 1001 * i);

			el_cl_E->at(i) = el_cl_E->at(i) * m_energyRescaler->getSmearingCorrectionMeV(
				el_cl_eta->at(i),
				el_cl_E->at(i),
				0, true, "2011"
			);
		}

		/*---------------------------------------------------------*/

		for(Int_t i = 0; i < mu_staco_n; i++)
		{
			if(fabs(mu_staco_eta->at(i)) > 2.7f)
			{
				continue;
			}

			Float_t ptcb = mu_staco_pt->at(i);

			Float_t ptme = (mu_staco_me_qoverp_exPV->at(i) != 0.0f) ? sin(mu_staco_me_theta_exPV->at(i)) / fabs(mu_staco_me_qoverp_exPV->at(i)) : 0.0f;
			Float_t ptid = (mu_staco_id_qoverp_exPV->at(i) != 0.0f) ? sin(mu_staco_id_theta_exPV->at(i)) / fabs(mu_staco_id_qoverp_exPV->at(i)) : 0.0f;

			m_stacoSM->SetSeed(EventNumber, i);

			m_stacoSM->Event(
				ptme,
				ptid,
				ptcb,
				mu_staco_eta->at(i)
			);

			mu_staco_pt->at(i) = (mu_staco_isCombinedMuon->at(i) != false) ?
				m_stacoSM->pTCB()
				:
				m_stacoSM->pTID()
			;
		}

		/*---------------------------------------------------------*/

		for(Int_t i = 0; i < mu_muid_n; i++)
		{
			if(fabs(mu_muid_eta->at(i)) > 2.7f)
			{
				continue;
			}

			Float_t ptcb = mu_muid_pt->at(i);

			Float_t ptme = (mu_muid_me_qoverp_exPV->at(i) != 0.0f) ? sin(mu_muid_me_theta_exPV->at(i)) / fabs(mu_muid_me_qoverp_exPV->at(i)) : 0.0f;
			Float_t ptid = (mu_muid_id_qoverp_exPV->at(i) != 0.0f) ? sin(mu_muid_id_theta_exPV->at(i)) / fabs(mu_muid_id_qoverp_exPV->at(i)) : 0.0f;

			m_muidSM->SetSeed(EventNumber, i);

			m_muidSM->Event(
				ptme,
				ptid,
				ptcb,
				mu_muid_eta->at(i)
			);

			mu_muid_pt->at(i) = (mu_muid_isCombinedMuon->at(i) != false) ?
				m_muidSM->pTCB()
				:
				m_muidSM->pTID()
			;
		}

		/*---------------------------------------------------------*/
	}
}

/*-------------------------------------------------------------------------*/

Float_t TLeptonAnalysis::eventGetWeight(void)
{
#if defined(__IS_MC) || defined(__IS_uD3PD)
	Float_t weight = 1.0f;

	if(mcevt_weight[0].size() > 0)
	{
		if(mcevt_weight[0][0].size() == 1)
		{
			weight = mcevt_weight[0][0][0];
		}
	}

	return (weight != 0.0f) ? weight : 1.0f;
#else
	return 1.00000000000000000000000000000f;
#endif
}

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::checkObjectQuality(
	Int_t index,
	TLeptonType type
) {
	if(type == TYPE_ELECTRON && core::OQ != false)
	{
		return (el_OQ->at(index) & 1446) == 0;
	}

	return true;
}

/*-------------------------------------------------------------------------*/

Float_t TLeptonAnalysis::electronGetEtaDirection(Int_t index)
{
	Int_t n = el_nPixHits->at(index) + el_nSCTHits->at(index);

	return n >= 4 ? el_tracketa->at(index) : el_cl_eta->at(index);
}

/*-------------------------------------------------------------------------*/

Float_t TLeptonAnalysis::electronGetPhiDirection(Int_t index)
{
	Int_t n = el_nPixHits->at(index) + el_nSCTHits->at(index);

	return n >= 4 ? el_trackphi->at(index) : el_cl_phi->at(index);
}

/*-------------------------------------------------------------------------*/

Float_t TLeptonAnalysis::electronGetEt(Int_t index)
{
	Int_t n = el_nPixHits->at(index) + el_nSCTHits->at(index);

	return n >= 4 ? el_cl_E->at(index) / coshf(el_tracketa->at(index)) : el_cl_pt->at(index);
}

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::checkObject(
	Int_t index,
	TLeptonType type,
	Float_t __el_et,
	Float_t __mu_pt,
	Float_t __mu_calo_pt,
	Bool_t useLoose,
	Bool_t useForward
) {
	Int_t n;

	if(useForward != false)
	{
		std::cerr << "Forward electrons not yet implemented !" << std::endl;

		return false;
	}

	switch(type)
	{
		/*---------------------------------------------------------*/
		/* TYPE_ELECTRON					   */
		/*---------------------------------------------------------*/

		case TYPE_ELECTRON:
			if(el_author->at(index) != 1
			   &&
			   el_author->at(index) != 3
			 ) {
				goto __error;
			}

			if(useLoose == false)
			{
				if(el_medium->at(index) == 0) {
					goto __error;
				}
			}
			else
			{
				if(el_loosePP->at(index) == 0) {
					goto __error;
				}
			}

			if(fabs(el_cl_eta->at(index)) > 2.47f) {
				goto __error;
			}

			if(electronGetEt(index) < __el_et) {
				goto __error;
			}

			if(fabs(el_trackz0pvunbiased->at(index)) > 10.0f) {
				goto __error;
			}

			break;

		/*---------------------------------------------------------*/
		/* MUON_STACO						   */
		/*---------------------------------------------------------*/

		case TYPE_MUON_STACO:
			if(mu_staco_author->at(index) != 6
			   &&
			   mu_staco_author->at(index) != 7
			 ) {
				goto __error;
			}

			if(mu_staco_pt->at(index) < __mu_pt) {
				goto __error;
			}

			if(fabs(mu_staco_eta->at(index)) > 2.5f)
			{
				if(fabs(mu_staco_eta->at(index)) > 2.7f) {
					goto __error;
				}

				if(mu_staco_isCombinedMuon->at(index) == false)
				{
					if(mu_staco_isStandAloneMuon->at(index) == false
					   ||
					   (mu_staco_nCSCEtaHits->at(index) + mu_staco_nCSCPhiHits->at(index)) == 0
					   ||
					   (mu_staco_nMDTEMHits->at(index)) == 0
					   ||
					   (mu_staco_nMDTEOHits->at(index)) == 0
					 ) {
						goto __error;
					}
					else {
						goto __okay_staco;
					}
				}
			}

			if(mu_staco_expectBLayerHit->at(index) != 0 && mu_staco_nBLHits->at(index) < 1) {
				goto __error;
			}

			if(mu_staco_nPixHits->at(index) + mu_staco_nPixelDeadSensors->at(index) < 2) {
				goto __error;
			}

			if(mu_staco_nSCTHits->at(index) + mu_staco_nSCTDeadSensors->at(index) < 6) {
				goto __error;
			}

			if(mu_staco_nPixHoles->at(index) + mu_staco_nSCTHoles->at(index) > 2) {
				goto __error;
			}

			n = mu_staco_nTRTHits->at(index) + mu_staco_nTRTOutliers->at(index);

			if(fabs(mu_staco_eta->at(index)) < 1.9f)
			{
				if(n < 6 || mu_staco_nTRTOutliers->at(index) >= n * 0.9) {
					goto __error;
				}
			}
			else
			{
				if(n > 5 && mu_staco_nTRTOutliers->at(index) >= n * 0.9) {
					goto __error;
				}
			}
__okay_staco:
			if(fabs(mu_staco_trackd0pvunbiased->at(index)) > 1.0f) {
				goto __error;
			}

			if(fabs(mu_staco_trackz0pvunbiased->at(index)) > 10.0f) {
				goto __error;
			}

			break;

		/*---------------------------------------------------------*/
		/* MUON_MUID						   */
		/*---------------------------------------------------------*/

		case TYPE_MUON_MUID:
			if(mu_muid_tight->at(index) == 0) {
				goto __error;
			}

			if(mu_muid_pt->at(index) < __mu_pt) {
				goto __error;
			}

			if(fabs(mu_muid_eta->at(index)) > 2.5f)
			{
				if(fabs(mu_muid_eta->at(index)) > 2.7f) {
					goto __error;
				}

				if(mu_muid_isCombinedMuon->at(index) == false)
				{
					if(mu_muid_isStandAloneMuon->at(index) == false
					   ||
					   (mu_muid_nCSCEtaHits->at(index) + mu_muid_nCSCPhiHits->at(index)) == 0
					   ||
					   (mu_muid_nMDTEMHits->at(index)) == 0
					   ||
					   (mu_muid_nMDTEOHits->at(index)) == 0
					 ) {
						goto __error;
					}
					else {
						goto __okay_muid;
					}
				}
			}

			if(mu_muid_expectBLayerHit->at(index) != 0 && mu_muid_nBLHits->at(index) < 1) {
				goto __error;
			}

			if(mu_muid_nPixHits->at(index) + mu_muid_nPixelDeadSensors->at(index) < 2) {
				goto __error;
			}

			if(mu_muid_nSCTHits->at(index) + mu_muid_nSCTDeadSensors->at(index) < 6) {
				goto __error;
			}

			if(mu_muid_nPixHoles->at(index) + mu_muid_nSCTHoles->at(index) > 2) {
				goto __error;
			}

			n = mu_muid_nTRTHits->at(index) + mu_muid_nTRTOutliers->at(index);

			if(fabs(mu_muid_eta->at(index)) < 1.9f)
			{
				if(n < 6 || mu_muid_nTRTOutliers->at(index) >= n * 0.9) {
					goto __error;
				}
			}
			else
			{
				if(n > 5 && mu_muid_nTRTOutliers->at(index) >= n * 0.9) {
					goto __error;
				}
			}
__okay_muid:
			if(fabs(mu_muid_trackd0pvunbiased->at(index)) > 1.0f) {
				goto __error;
			}

			if(fabs(mu_muid_trackz0pvunbiased->at(index)) > 10.0f) {
				goto __error;
			}

			break;

		/*---------------------------------------------------------*/
		/* MUON_CALO						   */
		/*---------------------------------------------------------*/

		case TYPE_MUON_CALO:
			if(mu_calo_author->at(index) != 16) {
				goto __error;
			}

			if(mu_calo_caloMuonIdTag->at(index) <= 10
			   &&
			   mu_calo_caloLRLikelihood->at(index) <= 0.9
			 ) {
				goto __error;
			}

			if(mu_calo_pt->at(index) < __mu_calo_pt) {
				goto __error;
			}

			if(fabs(mu_calo_eta->at(index)) > 0.1f) {
				goto __error;
			}

			if(mu_calo_expectBLayerHit->at(index) != 0 && mu_calo_nBLHits->at(index) < 1) {
				goto __error;
			}

			if(mu_calo_nPixHits->at(index) + mu_calo_nPixelDeadSensors->at(index) < 2) {
				goto __error;
			}

			if(mu_calo_nSCTHits->at(index) + mu_calo_nSCTDeadSensors->at(index) < 6) {
				goto __error;
			}

			if(mu_calo_nPixHoles->at(index) + mu_calo_nSCTHoles->at(index) > 2) {
				goto __error;
			}

			n = mu_calo_nTRTHits->at(index) + mu_calo_nTRTOutliers->at(index);

			if(n > 5 && mu_calo_nTRTOutliers->at(index) >= n * 0.9) {
				goto __error;
			}

			if(fabs(mu_calo_trackz0pvunbiased->at(index)) > 10.0f) {
				goto __error;
			}

			break;

		/*---------------------------------------------------------*/

		__error:
		default:
			return false;
	}

	return true;
}

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::checkStacoOverlapping(
	Int_t index,
	TLeptonType type,
	Float_t __el_et,
	Float_t __mu_pt,
	Float_t __mu_calo_pt,
	Bool_t useLoose,
	Bool_t useForward
) {
	Bool_t result = true;

	if(type == TYPE_ELECTRON)
	{
		/*---------------------------------------------------------*/
		/* ELECTRONS						   */
		/*---------------------------------------------------------*/

		for(Int_t xedni = 0; xedni < el_n; xedni++)
		{
			if(index != xedni
			   &&
			   el_trackd0->at(index) == el_trackd0->at(xedni)
			   &&
			   el_trackz0->at(index) == el_trackz0->at(xedni)
			   &&
			   el_tracktheta->at(index) == el_tracktheta->at(xedni)
			   &&
			   el_trackphi->at(index) == el_trackphi->at(xedni)
			   &&
			   el_trackqoverp->at(index) == el_trackqoverp->at(xedni)
			 ) {
				if(checkObject(xedni, TYPE_ELECTRON, __el_et, __mu_pt, __mu_calo_pt, useLoose, useForward) != false && electronGetEt(index) <= electronGetEt(xedni))
				{
					result = false;

					break;
				}
			}
		}

		/*---------------------------------------------------------*/
		/* MUON STACO						   */
		/*---------------------------------------------------------*/

		for(Int_t xedni = 0; xedni < mu_staco_n; xedni++)
		{
			if(el_trackd0->at(index) == mu_staco_id_d0->at(xedni)
			   &&
			   el_trackz0->at(index) == mu_staco_id_z0->at(xedni)
			   &&
			   el_tracktheta->at(index) == mu_staco_id_theta->at(xedni)
			   &&
			   el_trackphi->at(index) == mu_staco_id_phi->at(xedni)
			   &&
			   el_trackqoverp->at(index) == mu_staco_id_qoverp->at(xedni)
			 ) {
				if(checkObject(xedni, TYPE_MUON_STACO, __el_et, __mu_pt, __mu_calo_pt, useLoose, useForward) != false)
				{
					result = false;

					break;
				}
			}
		}

		/*---------------------------------------------------------*/
	}

	return result;
}

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::checkMuidOverlapping(
	Int_t index,
	TLeptonType type,
	Float_t __el_et,
	Float_t __mu_pt,
	Float_t __mu_calo_pt,
	Bool_t useLoose,
	Bool_t useForward
) {
	Bool_t result = true;

	if(type == TYPE_ELECTRON)
	{
		/*---------------------------------------------------------*/
		/* ELECTRONS						   */
		/*---------------------------------------------------------*/

		for(Int_t xedni = 0; xedni < el_n; xedni++)
		{
			if(index != xedni
			   &&
			   el_trackd0->at(index) == el_trackd0->at(xedni)
			   &&
			   el_trackz0->at(index) == el_trackz0->at(xedni)
			   &&
			   el_tracktheta->at(index) == el_tracktheta->at(xedni)
			   &&
			   el_trackphi->at(index) == el_trackphi->at(xedni)
			   &&
			   el_trackqoverp->at(index) == el_trackqoverp->at(xedni)
			 ) {
				if(checkObject(xedni, TYPE_ELECTRON, __el_et, __mu_pt, __mu_calo_pt, useLoose, useForward) != false && electronGetEt(index) <= electronGetEt(xedni))
				{
					result = false;

					break;
				}
			}
		}

		/*---------------------------------------------------------*/
		/* MUON MUID						   */
		/*---------------------------------------------------------*/

		for(Int_t xedni = 0; xedni < mu_muid_n; xedni++)
		{
			if(el_trackd0->at(index) == mu_muid_id_d0->at(xedni)
			   &&
			   el_trackz0->at(index) == mu_muid_id_z0->at(xedni)
			   &&
			   el_tracktheta->at(index) == mu_muid_id_theta->at(xedni)
			   &&
			   el_trackphi->at(index) == mu_muid_id_phi->at(xedni)
			   &&
			   el_trackqoverp->at(index) == mu_muid_id_qoverp->at(xedni)
			 ) {
				if(checkObject(xedni, TYPE_MUON_MUID, __el_et, __mu_pt, __mu_calo_pt, useLoose, useForward) != false)
				{
					result = false;
	
					break;
				}
			}
		}

		/*---------------------------------------------------------*/
	}

	return result;
}

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::checkCaloOverlapping(
	Int_t index,
	TLeptonType type,
	Float_t __el_et,
	Float_t __mu_pt,
	Float_t __mu_calo_pt,
	Bool_t useLoose,
	Bool_t useForward
) {
	Bool_t result = true;

	if(type == TYPE_ELECTRON)
	{
		/*---------------------------------------------------------*/
		/* ELECTRONS						   */
		/*---------------------------------------------------------*/

		for(Int_t xedni = 0; xedni < el_n; xedni++)
		{
			if(index != xedni
			   &&
			   el_trackd0->at(index) == el_trackd0->at(xedni)
			   &&
			   el_trackz0->at(index) == el_trackz0->at(xedni)
			   &&
			   el_tracktheta->at(index) == el_tracktheta->at(xedni)
			   &&
			   el_trackphi->at(index) == el_trackphi->at(xedni)
			   &&
			   el_trackqoverp->at(index) == el_trackqoverp->at(xedni)
			 ) {
				if(checkObject(xedni, TYPE_ELECTRON, __el_et, __mu_pt, __mu_calo_pt, useLoose, useForward) != false && electronGetEt(index) <= electronGetEt(xedni))
				{
					result = false;

					break;
				}
			}
		}

		/*---------------------------------------------------------*/
		/* MUON STACO						   */
		/*---------------------------------------------------------*/

		for(Int_t xedni = 0; xedni < mu_calo_n; xedni++)
		{
			if(el_trackd0->at(index) == mu_calo_id_d0->at(xedni)
			   &&
			   el_trackz0->at(index) == mu_calo_id_z0->at(xedni)
			   &&
			   el_tracktheta->at(index) == mu_calo_id_theta->at(xedni)
			   &&
			   el_trackphi->at(index) == mu_calo_id_phi->at(xedni)
			   &&
			   el_trackqoverp->at(index) == mu_calo_id_qoverp->at(xedni)
			 ) {
				if(checkObject(xedni, TYPE_MUON_CALO, __el_et, __mu_pt, __mu_calo_pt, useLoose, useForward) != false)
				{
					result = false;
	
					break;
				}
			}
		}

		/*---------------------------------------------------------*/
	}

	return result;
}

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::truthMatch(
	Int_t index,
	TLeptonType type
) {
#ifdef __IS_MC
	if(core::isMC(RunNumber) != false)
	{
		switch(type)
		{
			case TYPE_ELECTRON:
				if((el_type->at(index) != 2 || (((((((((((((((((((el_origin->at(index) != 13))))))))))))))))))))
				   &&
				   (el_type->at(index) != 4 || (el_originbkg->at(index) != 13 && el_originbkg->at(index) != 40))
				 ) {
					goto __error;
				}
				break;

			case TYPE_MUON_STACO:
				if(abs(mu_staco_truth_type->at(index)) != 13 || mu_staco_truth_mothertype->at(index) != 23) {
					goto __error;
				}
				break;

			case TYPE_MUON_MUID:
				if(abs(mu_muid_truth_type->at(index)) != 13 || mu_muid_truth_mothertype->at(index) != 23) {
					goto __error;
				}
				break;

			case TYPE_MUON_CALO:
				if(abs(mu_calo_truth_type->at(index)) != 13 || mu_calo_truth_mothertype->at(index) != 23) {
					goto __error;
				}
				break;

			__error:
			default:
				return false;
		}
	}
#endif
	return true;
}

/*-------------------------------------------------------------------------*/

Float_t __dR2(
	Float_t eta1, Float_t eta2,
	Float_t phi1, Float_t phi2
) {
	Float_t dEta = eta1 - eta2;
	Float_t dPhi = phi1 - phi2;

	while(dPhi < -M_PI) {
		dPhi += 2.0 * M_PI;
	}

	while(dPhi >= +M_PI) {
		dPhi -= 2.0 * M_PI;
	}

	return dEta * dEta + dPhi * dPhi;
}

/*-------------------------------------------------------------------------*/

Bool_t buildPair(
	Int_t pair[2],
	Float_t charge1,
	Float_t charge2
) {
	/**/ if(charge1 < 0.0f
		&&
		charge2 > 0.0f
	 ) {
		pair[0] = 1;
		pair[1] = 0;
	}
	else if(charge1 > 0.0f
		&&
		charge2 < 0.0f
	 ) {
		pair[0] = 0;
		pair[1] = 1;
	}
	else {
		return false;
	}

	return true;
}

/*-------------------------------------------------------------------------*/

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
) {
	if(type1 == type2)
	{
		Int_t negatives[4];
		Int_t positives[4];

		Int_t negativeNr = 0;
		Int_t positiveNr = 0;

		/**/ if(charge1 < 0.0f) {
			negatives[negativeNr++] = 0;
		}
		else if(charge1 > 0.0f) {
			positives[positiveNr++] = 0;
		}

		/**/ if(charge2 < 0.0f) {
			negatives[negativeNr++] = 1;
		}
		else if(charge2 > 0.0f) {
			positives[positiveNr++] = 1;
		}

		/**/ if(charge3 < 0.0f) {
			negatives[negativeNr++] = 2;
		}
		else if(charge3 > 0.0f) {
			positives[positiveNr++] = 2;
		}

		/**/ if(charge4 < 0.0f) {
			negatives[negativeNr++] = 3;
		}
		else if(charge4 > 0.0f) {
			positives[positiveNr++] = 3;
		}

		if(positiveNr != 2
		   ||
		   negativeNr != 2
		 ) {
			return false;
		}

		/* 1st quadruplet */

		pair1[0] = positives[0];
		pair1[1] = negatives[0];

		pair2[0] = positives[1];
		pair2[1] = negatives[1];

		/* 2nd quadruplet */

		pair3[0] = positives[0];
		pair3[1] = negatives[1];

		pair4[0] = positives[1];
		pair4[1] = negatives[0];
	}
	else
	{
		/* 1st quadruplet */

		if(buildPair(pair1, charge1, charge2) == false
		   ||
		   buildPair(pair2, charge3, charge4) == false
		 ) {
			return false;
		}

		pair1[0] += 0;
		pair1[1] += 0;

		pair2[0] += 2;
		pair2[1] += 2;

		/* 2nd quadruplet */

		pair3[0] = pair1[0];
		pair3[1] = pair1[1];

		pair4[0] = pair2[0];
		pair4[1] = pair2[1];
	}

	return true;
}

/*-------------------------------------------------------------------------*/

void reIndex(
	Int_t L[4],
	Float_t M[4],
	Int_t (* func)(const void *, const void *)
) {
	Float_t U[4] = {
		M[0],
		M[1],
		M[2],
		M[3],
	};

	Float_t V[4] = {
		M[0],
		M[1],
		M[2],
		M[3],
	};

	/**/

	qsort(U, 4, sizeof(Float_t), func);

	/**/

	for(Int_t i = 0; i < 4; i++)
	{
		for(Int_t j = 0; j < 4; j++)
		{
			if(U[i] == V[j])
			{
				L[i] =     j    ;
				V[j] = -999999.0;

				break;
			}
		}
	}
}

/*-------------------------------------------------------------------------*/

