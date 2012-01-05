/*-------------------------------------------------------------------------*/

#include <cmath>
#include <cstring>
#include <iostream>

#include <TRandom3.h>

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

#define periodAll	(periodB + periodD + periodE + periodF + periodG + periodH + periodI + periodJ + periodK + periodL + periodM)

const Float_t fracEl = (periodB + periodD + periodE + periodF + periodG + periodH + periodI + periodJ) / (periodAll);
const Float_t fracMu = (periodB + periodD + periodE + periodF + periodG + periodH + periodI          ) / (periodAll);

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

		for(Int_t i = 0; i < vxp_n; i++)
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

		TRandom3 random3;

		Bool_t isOkElTrigger;
		Bool_t isOkMuTrigger;
#ifdef __IS_MC
		random3.SetSeed(mc_channel_number * RunNumber);
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

		/*---------------------------------------------------------*/
		/* ELECTRON STACO					   */
		/*---------------------------------------------------------*/

		for(Int_t i = 0; i < el_n; i++)
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

			if(el_author->at(i) != 1
			   &&
			   el_author->at(i) != 3
			 ) {
				continue;
			}

			elSTACONr3++;

			if(el_loosePP->at(i) == 0) {
				continue;
			}

			elSTACONr4++;

			if(fabs(el_cl_eta->at(i)) > 2.47f) {
				continue;
			}

			elSTACONr5++;

			if(electronGetEt(i) < 7000.0f) {
				continue;
			}

			elSTACONr6++;

			if(fabs(el_trackz0pvunbiased->at(i)) > 10.0f) {
				continue;
			}

			elSTACONr7++;
		}

		/*---------------------------------------------------------*/
		/* MUON STACO						   */
		/*---------------------------------------------------------*/

		for(Int_t i = 0; i < mu_staco_n; i++)
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

			if(mu_staco_author->at(i) != 6
			   &&
			   mu_staco_author->at(i) != 7
			 ) {
				continue;
			}

			muSTACONr3++;

			if(fabs(mu_staco_d0_exPV->at(i)) > 1.0f) {
				continue;
			}

			muSTACONr4++;

			/* ETA */
			/* ETA */
			/* ETA */

			muSTACONr5++;

			if(mu_staco_pt->at(i) < 7000.0f) {
				continue;
			}

			muSTACONr6++;

			if(mu_staco_expectBLayerHit->at(i) != 0 && mu_staco_nBLHits->at(i) == 0) {
				continue;
			}

			muSTACONr7++;

			if(mu_staco_nPixHits->at(i) + mu_staco_nPixelDeadSensors->at(i) < 2) {
				continue;
			}

			muSTACONr8++;

			if(mu_staco_nSCTHits->at(i) + mu_staco_nSCTDeadSensors->at(i) < 6) {
				continue;
			}

			muSTACONr9++;

			if(mu_staco_nPixHoles->at(i) + mu_staco_nSCTHoles->at(i) > 2 ) {
				continue;
			}

			muSTACONr10++;

			n = mu_staco_nTRTHits->at(i) + mu_staco_nTRTOutliers->at(i);

			if(fabs(mu_staco_eta->at(i)) < 1.9f)
			{
				if(n < 6 || mu_staco_nTRTOutliers->at(i) >= n * 0.9) {
					continue;
				}
			}
			else
			{
				if(n > 5 && mu_staco_nTRTOutliers->at(i) >= n * 0.9) {
					continue;
				}
			}

			muSTACONr11++;

			if(fabs(mu_staco_z0_exPV->at(i)) > 10.0f) {
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
	std::cout << "after pt>7       : " << elSTACONr5 << std::endl;
	std::cout << "after |η|<2.47   : " << elSTACONr6 << std::endl;
	std::cout << "after z0         : " << elSTACONr7 << std::endl;

	std::cout << "#############################################################################" << std::endl;
	std::cout << "# MUON STACO                                                                #" << std::endl;
	std::cout << "#############################################################################" << std::endl;

	std::cout << "before any cut     : " << muSTACONr0 << std::endl;
	std::cout << "after vertex       : " << muSTACONr1 << std::endl;
	std::cout << "after trigger      : " << muSTACONr2 << std::endl;
	std::cout << "after author=6||7  : " << muSTACONr3 << std::endl;
	std::cout << "after pt>7         : " << muSTACONr4 << std::endl;
	std::cout << "after |η|<2.5      : " << muSTACONr5 << std::endl;
	std::cout << "after b-Layer      : " << muSTACONr6 << std::endl;
	std::cout << "after Pix          : " << muSTACONr7 << std::endl;
	std::cout << "after SCT          : " << muSTACONr8 << std::endl;
	std::cout << "after Pix/SCT      : " << muSTACONr9 << std::endl;
	std::cout << "after TRT/outliers : " << muSTACONr10 << std::endl;
	std::cout << "after d0           : " << muSTACONr11 << std::endl;
	std::cout << "after z0           : " << muSTACONr12 << std::endl;

	std::cout << "#############################################################################" << std::endl;
}

/*-------------------------------------------------------------------------*/

