/*-------------------------------------------------------------------------*/

#include "utils.h"

#include <egammaAnalysisUtils/IsEMPlusPlusDefs.h>

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::el_loosePP_at(Int_t index)
{
	float eta = el_cl_eta->at(index);
	float eT = el_cl_E->at(index) / coshf(eta);

	if(eT == 0.0f)
	{
		return false;
	}

	float rHad = el_Ethad->at(index) / eT;
	float rHad1 = el_Ethad1->at(index) / eT;
	float Reta = el_reta->at(index);
	float w2 = el_weta2->at(index);
	float f1 = el_f1->at(index);
	float wstot = el_wstot->at(index);
	float DEmaxs1 = (el_emaxs1->at(index) - el_Emax2->at(index)) / (el_emaxs1->at(index) + el_Emax2->at(index));
	float deltaEta = el_deltaeta1->at(index);

	Int_t nSi = el_nSiHits->at(index);
	Int_t nSiOutliers = el_nPixelOutliers->at(index) + el_nSCTOutliers->at(index);
	Int_t nPix = el_nPixHits->at(index);
	Int_t nPixOutliers = el_nPixelOutliers->at(index);

	return isLoosePlusPlus(
		eta,
		eT,
		rHad,
		rHad1,
		Reta,
		w2,
		f1,
		wstot,
		DEmaxs1,
		deltaEta,
		nSi,
		nSiOutliers,
		nPix,
		nPixOutliers,
		false,
		false
	);
}

/*-------------------------------------------------------------------------*/

