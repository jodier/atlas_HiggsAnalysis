/*-------------------------------------------------------------------------*/

#include <cmath>
#include <cstring>
#include <iostream>

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

void THiggsBuilder::Loop(void)
{
	Int_t n;

	Int_t nPV2;
	Int_t nPV3;

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

	int muMUIDNr0 = 0;
	int muMUIDNr1 = 0;
	int muMUIDNr2 = 0;
	int muMUIDNr3 = 0;
	int muMUIDNr4 = 0;
	int muMUIDNr5 = 0;
	int muMUIDNr6 = 0;
	int muMUIDNr7 = 0;
	int muMUIDNr8 = 0;
	int muMUIDNr9 = 0;
	int muMUIDNr10 = 0;
	int muMUIDNr11 = 0;
	int muMUIDNr12 = 0;

	const Long64_t eventNr = fChain->GetEntries();

	for(Long64_t event = 0; event < eventNr; event++)
	{
		/*---------------------------------------------------------*/

		LoadEvent(event, eventNr);

		/*---------------------------------------------------------*/
		/* TRIGGER						   */
		/*---------------------------------------------------------*/

//		Bool_t isOkElTrigger = EF_e20_medium;
		Bool_t isOkMuTrigger = EF_mu18_MG;

		/*---------------------------------------------------------*/
		/* AT LEAST 3 PRIMARY TRACKS AND LAR ERROR		   */
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

		Bool_t isOkVertex = (nPV3 > 0) && (larError == false);

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

			if(mu_staco_author->at(i) != 6 && mu_staco_author->at(i) != 7) {
				continue;
			}

			muSTACONr3++;

			if(mu_staco_pt->at(i) < 7000.0f) {
				continue;
			}

			muSTACONr4++;

			if(fabs(mu_staco_eta->at(i)) > 2.5f)
			{
				if(fabs(mu_staco_eta->at(i)) > 2.7f) {
					continue;
				}

				if(mu_staco_isCombinedMuon->at(i) == false)
				{
					if(mu_staco_isStandAloneMuon->at(i) == false
					   ||
					   (mu_staco_nCSCEtaHits->at(i) + mu_staco_nCSCPhiHits->at(i)) == 0
					   ||
					   (mu_staco_nMDTEMHits->at(i)) == 0
					   ||
					   (mu_staco_nMDTEOHits->at(i)) == 0
					 ) {
						continue;
					}
					else {
						muSTACONr5++;
						muSTACONr6++;
						muSTACONr7++;
						muSTACONr8++;
						muSTACONr9++;
						muSTACONr10++;
						goto __okay_staco;
					}
				}
			}

			muSTACONr5++;

			if(mu_staco_expectBLayerHit->at(i) == 1 && mu_staco_nBLHits->at(i) == 0) {
				continue;
			}

			muSTACONr6++;

			if(mu_staco_nPixHits->at(i) + mu_staco_nPixelDeadSensors->at(i) < 2) {
				continue;
			}

			muSTACONr7++;

			if(mu_staco_nSCTHits->at(i) + mu_staco_nSCTDeadSensors->at(i) < 6) {
				continue;
			}

			muSTACONr8++;

			if(mu_staco_nPixHoles->at(i) + mu_staco_nSCTHoles->at(i) > 2 ) {
				continue;
			}

			muSTACONr9++;

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

			muSTACONr10++;
__okay_staco:
			if(fabs(mu_staco_trackd0pvunbiased->at(i)) > 1.0f) {
				continue;
			}

			muSTACONr11++;

			if(fabs(mu_staco_trackz0pvunbiased->at(i)) > 10.0f) {
				continue;
			}

			muSTACONr12++;
		}

		/*---------------------------------------------------------*/
		/* MUON MUID						   */
		/*---------------------------------------------------------*/

		for(Int_t i = 0; i < mu_muid_n; i++)
		{
			muMUIDNr0++;

			if(isOkVertex == false) {
				continue;
			}

			muMUIDNr1++;

			if(isOkMuTrigger == false) {
				continue;
			}

			muMUIDNr2++;

			if(mu_muid_tight->at(i) == 0) {
				continue;
			}

			muMUIDNr3++;

			if(mu_muid_pt->at(i) < 7000.0f) {
				continue;
			}

			muMUIDNr4++;

			if(fabs(mu_muid_eta->at(i)) > 2.5f)
			{
				if(fabs(mu_muid_eta->at(i)) > 2.7f) {
					continue;
				}

				if(mu_muid_isCombinedMuon->at(i) == false)
				{
					if(mu_muid_isStandAloneMuon->at(i) == false
					   ||
					   (mu_muid_nCSCEtaHits->at(i) + mu_muid_nCSCPhiHits->at(i)) == 0
					   ||
					   (mu_muid_nMDTEMHits->at(i)) == 0
					   ||
					   (mu_muid_nMDTEOHits->at(i)) == 0
					 ) {
						continue;
					}
					else {
						muSTACONr5++;
						muSTACONr6++;
						muSTACONr7++;
						muSTACONr8++;
						muSTACONr9++;
						muSTACONr10++;
						goto __okay_muid;
					}
				}
			}

			muMUIDNr5++;

			if(mu_muid_expectBLayerHit->at(i) == 1 && mu_muid_nBLHits->at(i) == 0) {
				continue;
			}

			muMUIDNr6++;

			if(mu_muid_nPixHits->at(i) + mu_muid_nPixelDeadSensors->at(i) < 2) {
				continue;
			}

			muMUIDNr7++;

			if(mu_muid_nSCTHits->at(i) + mu_muid_nSCTDeadSensors->at(i) < 6) {
				continue;
			}

			muMUIDNr8++;

			if(mu_muid_nPixHoles->at(i) + mu_muid_nSCTHoles->at(i) > 2 ) {
				continue;
			}

			muMUIDNr9++;

			n = mu_muid_nTRTHits->at(i) + mu_muid_nTRTOutliers->at(i);

			if(fabs(mu_muid_eta->at(i)) < 1.9f)
			{
				if(n < 6 || mu_muid_nTRTOutliers->at(i) >= n * 0.9) {
					continue;
				}
			}
			else
			{
				if(n > 5 && mu_muid_nTRTOutliers->at(i) >= n * 0.9) {
					continue;
				}
			}

			muMUIDNr10++;
__okay_muid:
			if(fabs(mu_muid_trackd0pvunbiased->at(i)) > 1.0f) {
				continue;
			}

			muMUIDNr11++;

			if(fabs(mu_muid_trackz0pvunbiased->at(i)) > 10.0f) {
				continue;
			}

			muMUIDNr12++;
		}

		/*---------------------------------------------------------*/
	}

	std::cout << std::endl;

	std::cout << "#############################################################################" << std::endl;
	std::cout << "# STACO                                                                     #" << std::endl;
	std::cout << "#############################################################################" << std::endl;

	std::cout << "before any cut     : " << muSTACONr0 << std::endl;
	std::cout << "after vertex       : " << muSTACONr1 << std::endl;
	std::cout << "after trigger\t   : " << muSTACONr2 << std::endl;
	std::cout << "after author=6||7  : " << muSTACONr3 << std::endl;
	std::cout << "after pt>7\t   : " << muSTACONr4 << std::endl;
	std::cout << "after |η|<2.5\t   : " << muSTACONr5 << std::endl;
	std::cout << "after b-Layer\t   : " << muSTACONr6 << std::endl;
	std::cout << "after Pix\t   : " << muSTACONr7 << std::endl;
	std::cout << "after SCT\t   : " << muSTACONr8 << std::endl;
	std::cout << "after Pix/SCT\t   : " << muSTACONr9 << std::endl;
	std::cout << "after TRT/outliers : " << muSTACONr10 << std::endl;
	std::cout << "after d0\t   : " << muSTACONr11 << std::endl;
	std::cout << "after z0\t   : " << muSTACONr12 << std::endl;

	std::cout << "#############################################################################" << std::endl;
	std::cout << "# MUID                                                                      #" << std::endl;
	std::cout << "#############################################################################" << std::endl;

	std::cout << "before any cut     : " << muMUIDNr0 << std::endl;
	std::cout << "after vertex       : " << muMUIDNr1 << std::endl;
	std::cout << "after trigger\t   : " << muMUIDNr2 << std::endl;
	std::cout << "after tight\t   : " << muMUIDNr3 << std::endl;
	std::cout << "after pt>7\t   : " << muMUIDNr4 << std::endl;
	std::cout << "after |η|<2.5\t   : " << muMUIDNr5 << std::endl;
	std::cout << "after b-Layer\t   : " << muMUIDNr6 << std::endl;
	std::cout << "after Pix\t   : " << muMUIDNr7 << std::endl;
	std::cout << "after SCT\t   : " << muMUIDNr8 << std::endl;
	std::cout << "after Pix/SCT\t   : " << muMUIDNr9 << std::endl;
	std::cout << "after TRT/outliers : " << muMUIDNr10 << std::endl;
	std::cout << "after d0\t   : " << muMUIDNr11 << std::endl;
	std::cout << "after z0\t   : " << muMUIDNr12 << std::endl;

	std::cout << "#############################################################################" << std::endl;
}

/*-------------------------------------------------------------------------*/

