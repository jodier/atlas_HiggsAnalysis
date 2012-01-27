/*-------------------------------------------------------------------------*/

#include <cmath>
#include <cstring>
#include <iostream>

#include <TRandom3.h>

#include <egammaAnalysisUtils/IsEMPlusPlusDefs.h>

#include "main.h"

/*-------------------------------------------------------------------------*/

void core::execute(TChain *chain)
{
	std::cout << "/*-------------------------------------------------------------------------*/" << std::endl;
	std::cout << "/* EXECUTE                                                                 */" << std::endl;
	std::cout << "/*-------------------------------------------------------------------------*/" << std::endl;

	THiggsBuilder algo(chain);
	algo.Loop();
}

/*-------------------------------------------------------------------------*/

Bool_t THiggsBuilder::el_loosePP_at(Int_t index)
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

Float_t THiggsBuilder::electronGetEtaDirection(Int_t index)
{
	Int_t n = el_nPixHits->at(index) + el_nSCTHits->at(index);

	return n >= 4 ? el_tracketa->at(index) : el_cl_eta->at(index);
}

/*-------------------------------------------------------------------------*/

Float_t THiggsBuilder::electronGetPhiDirection(Int_t index)
{
	Int_t n = el_nPixHits->at(index) + el_nSCTHits->at(index);

	return n >= 4 ? el_trackphi->at(index) : el_cl_phi->at(index);
}

/*-------------------------------------------------------------------------*/

Float_t THiggsBuilder::electronGetEt(Int_t index)
{
	Int_t n = el_nPixHits->at(index) + el_nSCTHits->at(index);

	return n >= 4 ? el_cl_E->at(index) / coshf(el_tracketa->at(index)) : el_cl_pt->at(index);
}

/*-------------------------------------------------------------------------*/

#define periodB		11.7377f
#define periodD		166.737f
#define periodE		48.8244f
#define periodF		142.575f
#define periodG		537.542f
#define periodH		259.459f
#define periodI		386.226f
#define periodJ		226.460f
#define periodK		600.069f
#define periodL		1401.87f
#define periodM		1025.62f

const Float_t fracEl = (periodI + periodJ) / (periodI + periodJ + periodK);
const Float_t fracMu = (periodI          ) / (periodI + periodJ + periodK);

/*-------------------------------------------------------------------------*/

void THiggsBuilder::Loop(void)
{
	Int_t n;

	Int_t nPV2;
	Int_t nPV3;

	int elSTACONr0 = 0;
	int elSTACONr1 = 0;
	int elSTACONr2 = 0;
	int elSTACONr3 = 0;
	int elSTACONr4 = 0;
	int elSTACONr5 = 0;
	int elSTACONr6 = 0;
	int elSTACONr7 = 0;
	int elSTACONr8 = 0;

	int muSTACONr0 = 0;
	int muSTACONr1 = 0;
	int muSTACONr2 = 0;
	int muSTACONr3 = 0;
	int muSTACONr4 = 0;
	int muSTACONr5 = 0;
	int muSTACONr6 = 0;
	int muSTACONr7 = 0;
	int muSTACONr8 = 0;
	int muSTACONr9 = 0;
	int muSTACONr10 = 0;
	int muSTACONr11 = 0;
	int muSTACONr12 = 0;

	const Long64_t eventNr = fChain->GetEntries();

	for(Long64_t event = 0; event < eventNr; event++)
	{
		/*---------------------------------------------------------*/

		LoadEvent(event, eventNr);

		/*---------------------------------------------------------*/
		/* AT LEAST 3 PRIMARY TRACKS				   */
		/*---------------------------------------------------------*/

		nPV2 = 0;
		nPV3 = 0;

		for(Int_t i = 0; i < Int_t(vxp_nTracks->size()); i++)
		{
			if(vxp_nTracks->at(i) >= 2) {
				nPV2++;
			}

			if(vxp_nTracks->at(i) >= 3) {
				nPV3++;
			}
		}

		/**/

		Bool_t isOkVertex = (nPV3 > 0);

		/*---------------------------------------------------------*/
		/* TRIGGER						   */
		/*---------------------------------------------------------*/

		Bool_t isOkElTrigger;
		Bool_t isOkMuTrigger;

		/**/ if(RunNumber == 180164 // B-D
			||
			RunNumber == 183003 // E-H
		 ) {
			isOkElTrigger = EF_e20_medium || EF_2e12_medium;
			isOkMuTrigger = EF_mu18_MG || EF_2mu10_loose;
		}
		else if(RunNumber == 186169) // I-K
		{
			TRandom3 random3;
#ifdef __IS_MC
			random3.SetSeed(mc_channel_number * EventNumber);
#endif
			Float_t epsilon = random3.Uniform();

			if(epsilon < fracEl) {
				isOkElTrigger = EF_e20_medium || EF_2e12_medium;
			}
			else {
				isOkElTrigger = EF_e22_medium || EF_2e12T_medium;
			}

			if(epsilon < fracMu) {
				isOkMuTrigger = EF_mu18_MG || EF_2mu10_loose;
			}
			else {
				isOkMuTrigger = EF_mu18_MG_medium || EF_2mu10_loose;
			}
		}
		else if(RunNumber == 186275) // L-M
		{
			isOkElTrigger = EF_e22_medium1 || EF_2e12T_medium;
			isOkMuTrigger = EF_mu18_MG_medium || EF_2mu10_loose;
		}
		else
		{
			std::cout << "Oula !" << std::endl;

			isOkElTrigger = false;
			isOkMuTrigger = false;
		}

		/*---------------------------------------------------------*/
		/* ELECTRON STACO					   */
		/*---------------------------------------------------------*/

		for(Int_t index = 0; index < el_n; index++)
		{
			elSTACONr0++;

			if(isOkVertex == false) {
				continue;
			}

			elSTACONr1++;

			if(isOkElTrigger == false) {
				continue;
			}

			elSTACONr2++;

			if(el_author->at(index) != 1
			   &&
			   el_author->at(index) != 3
			 ) {
				continue;
			}

			elSTACONr3++;

			if(el_loosePP_at(index) == 0) {
				continue;
			}

			elSTACONr4++;

			if(fabs(el_cl_eta->at(index)) > 2.47f) {
				continue;
			}

			elSTACONr5++;

			if(electronGetEt(index) < 7000.0f) {
				continue;
			}

			elSTACONr6++;

			if((el_OQ->at(index) & 1446) != 0) {
				continue;
			}

			elSTACONr7++;

			if(fabs(el_trackz0pvunbiased->at(index)) > 10.0f) {
				continue;
			}

			elSTACONr8++;
		}

		/*---------------------------------------------------------*/
		/* MUON STACO						   */
		/*---------------------------------------------------------*/

		for(Int_t index = 0; index < mu_staco_n; index++)
		{
			muSTACONr0++;

			if(isOkVertex == false) {
				continue;
			}

			muSTACONr1++;

			if(isOkMuTrigger == false) {
				continue;
			}

			muSTACONr2++;

			if(mu_staco_author->at(index) != 6
			   &&
			   mu_staco_author->at(index) != 7
			 ) {
				continue;
			}

			muSTACONr3++;

			if(mu_staco_pt->at(index) < 7000.0f) {
				continue;
			}

			muSTACONr4++;

//			if(fabs(mu_staco_eta->at(index)) > 2.7f) {
//				continue;
//			}

			muSTACONr5++;

			if(mu_staco_expectBLayerHit->at(index) != 0 && mu_staco_nBLHits->at(index) <= 0) {
				continue;
			}

			muSTACONr6++;

			if(mu_staco_nPixHits->at(index) + mu_staco_nPixelDeadSensors->at(index) < 2) {
				continue;
			}

			muSTACONr7++;

			if(mu_staco_nSCTHits->at(index) + mu_staco_nSCTDeadSensors->at(index) < 6) {
				continue;
			}

			muSTACONr8++;

			if(mu_staco_nPixHoles->at(index) + mu_staco_nSCTHoles->at(index) > 2) {
				continue;
			}

			muSTACONr9++;

			n = mu_staco_nTRTHits->at(index) + mu_staco_nTRTOutliers->at(index);

			if(fabs(mu_staco_eta->at(index)) < 1.9f)
			{
				if(n < 6 || mu_staco_nTRTOutliers->at(index) > 0.9f * n) {
					continue;
				}
			}
			else
			{
				if(n > 5 && mu_staco_nTRTOutliers->at(index) > 0.9f * n) {
					continue;
				}
			}

			muSTACONr10++;

			if(fabs(mu_staco_d0_exPV->at(index)) > 1.0f) {
				continue;
			}

			muSTACONr11++;

			if(fabs(mu_staco_z0_exPV->at(index)) > 10.0f) {
				continue;
			}

			muSTACONr12++;
		}

		/*---------------------------------------------------------*/
	}

	std::cout << std::endl;

	std::cout << "#############################################################################" << std::endl;
	std::cout << "# ELECTRON STACO                                                            #" << std::endl;
	std::cout << "#############################################################################" << std::endl;

	std::cout << "before any cut   : " << elSTACONr0 << std::endl;
	std::cout << "after vertex     : " << elSTACONr1 << std::endl;
	std::cout << "after trigger    : " << elSTACONr2 << std::endl;
	std::cout << "after author=1||3: " << elSTACONr3 << std::endl;
	std::cout << "after loose++    : " << elSTACONr4 << std::endl;
	std::cout << "after |η|<2.47   : " << elSTACONr5 << std::endl;
	std::cout << "after pt>7       : " << elSTACONr6 << std::endl;
	std::cout << "after OQ         : " << elSTACONr7 << std::endl;
	std::cout << "after z0         : " << elSTACONr8 << std::endl;

	std::cout << "#############################################################################" << std::endl;
	std::cout << "# MUON STACO                                                                #" << std::endl;
	std::cout << "#############################################################################" << std::endl;

	std::cout << "before any cut     : " << muSTACONr0 << std::endl;
	std::cout << "after vertex       : " << muSTACONr1 << std::endl;
	std::cout << "after trigger      : " << muSTACONr2 << std::endl;
	std::cout << "after author=6||7  : " << muSTACONr3 << std::endl;
	std::cout << "after pt>4.7       : " << muSTACONr4 << std::endl;
	std::cout << "after |η|<2.5      : " << muSTACONr5 << std::endl;
	std::cout << "after b-Layer      : " << muSTACONr6 << std::endl;
	std::cout << "after Pix          : " << muSTACONr7 << std::endl;
	std::cout << "after SCT          : " << muSTACONr8 << std::endl;
	std::cout << "after holes        : " << muSTACONr9 << std::endl;
	std::cout << "after TRT/outliers : " << muSTACONr10 << std::endl;
	std::cout << "after d0           : " << muSTACONr11 << std::endl;
	std::cout << "after z0           : " << muSTACONr12 << std::endl;

	std::cout << "#############################################################################" << std::endl;
}

/*-------------------------------------------------------------------------*/

