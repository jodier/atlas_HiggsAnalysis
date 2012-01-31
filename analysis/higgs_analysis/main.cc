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

	/**/

	TFile file(core::output.c_str(), "recreate");

	file.cd();

	algo.m_tree0.Write();
	algo.m_tree1.Write();
	algo.m_tree2.Write();
	algo.m_tree3.Write();
	algo.m_tree4.Write();
	algo.m_tree5.Write();
	algo.m_tree6.Write();
	algo.m_tree7.Write();
	algo.m_tree8.Write();
	algo.m_tree9.Write();
	algo.m_treeA.Write();
	algo.m_treeB.Write();
	algo.m_treeC.Write();
	algo.m_treeD.Write();
	algo.m_treeE.Write();
	algo.m_treeF.Write();
	algo.m_treeG.Write();

	file.Close();
}

/*-------------------------------------------------------------------------*/

extern Float_t getMassCut(Float_t H_mass);

/*-------------------------------------------------------------------------*/

void THiggsBuilder::selectQuadruplet(Int_t dest, Float_t Z_MASS)
{
	Float_t currDMass;
	Float_t currAMass;

	Float_t goodDMass = 999999.0f;
	Float_t goodAMass = 000000.0f;

	/*-------------------------------------------------*/
	/* PASS 1					   */
	/*-------------------------------------------------*/

	for(Int_t i = 0; i < m_H[dest].n; i++) if((m_H[dest].flag[i] & 127) == 127)
	{
		currDMass = fabs(Z_MASS - m_H[dest].Z12_m[i]);

		if(goodDMass > currDMass)
		{
			goodDMass = currDMass;
		}	
	}

	/*-------------------------------------------------*/
	/* PASS 2					   */
	/*-------------------------------------------------*/

	for(Int_t i = 0; i < m_H[dest].n; i++) if((m_H[dest].flag[i] & 127) == 127)
	{
		currDMass = fabs(Z_MASS - m_H[dest].Z12_m[i]);

		if(goodDMass == currDMass)
		{
			currAMass = fabs(0.000f - m_H[dest].Z34_m[i]);

			if(goodAMass < currAMass)
			{
				goodAMass = currAMass;
			}
		}
	}

	/*-------------------------------------------------*/
	/* PASS 3					   */
	/*-------------------------------------------------*/

	for(Int_t i = 0; i < m_H[dest].n; i++) if((m_H[dest].flag[i] & 127) == 127)
	{
		currDMass = fabs(Z_MASS - m_H[dest].Z12_m[i]);
		currAMass = fabs(0.000f - m_H[dest].Z34_m[i]);

		if(currDMass == goodDMass
		   &&
		   currAMass == goodAMass
		 ) {
			m_H[dest].good[i] = true;

/*			if(dest == ???)
			{
				std::cout << "Event number    : " << m_H[dest].EventNumber << std::endl;

				std::cout << "  M_4l          = " << m_H[dest].H_m[i] << std::endl;

				std::cout << "  M_Z1          = " << m_H[dest].Z12_m[i] << std::endl;
				std::cout << "  M_Z1-M_Z      = " << fabs(Z_MASS - m_H[dest].Z12_m[i]) << std::endl;

				std::cout << "  M_Z2          = " << m_H[dest].Z34_m[i] << std::endl;
				std::cout << "  M_Z2-M_Z      = " << fabs(Z_MASS - m_H[dest].Z34_m[i]) << std::endl;

				std::cout << "  CutM_34       = " << getMassCut(m_H[dest].H_m[i]) << std::endl;
				std::cout << "  Pass cut M_Z2 = " << (m_H[dest].flag[i] >= 0x3F) << std::endl;

				std::cout << "  pT_l1 = " << m_H[dest].l1_pt[i]
					  << ", pT_l2 = " << m_H[dest].l2_pt[i]
					  << ", pT_l3 = " << m_H[dest].l3_pt[i]
					  << ", pT_l4 = " << m_H[dest].l4_pt[i]
					  << std::endl;
			}
*/		}
	}

	/*-------------------------------------------------*/
	/* PASS 4					   */
	/*-------------------------------------------------*/

	Bool_t eeuu;

	for(Int_t i = 0; i < m_H[dest].n; i++)
	{
		if((m_H[dest].flag[i] &   1) ==   1) m_H[dest].cnt[0] = true;
		if((m_H[dest].flag[i] &   3) ==   3) m_H[dest].cnt[1] = true;
		if((m_H[dest].flag[i] &   7) ==   7) m_H[dest].cnt[2] = true;
		if((m_H[dest].flag[i] &  15) ==  15) m_H[dest].cnt[3] = true;
		if((m_H[dest].flag[i] &  31) ==  31) m_H[dest].cnt[4] = true;
		if((m_H[dest].flag[i] &  63) ==  63) m_H[dest].cnt[5] = true;
		if((m_H[dest].flag[i] & 127) == 127) m_H[dest].cnt[6] = true;

		if(m_H[dest].good[i] != false)
		{
			eeuu = m_H[dest].eeuu[i] != 0;

			if((m_H[dest].flag[i] &  255) ==  255) m_H[dest].cnt[eeuu ?  7 :  8] = true;
			if((m_H[dest].flag[i] &  511) ==  511) m_H[dest].cnt[eeuu ?  9 : 10] = true;
			if((m_H[dest].flag[i] & 1023) == 1023) m_H[dest].cnt[eeuu ? 11 : 12] = true;
		}
	}
}

/*-------------------------------------------------------------------------*/

void THiggsBuilder::Loop(void)
{
	Int_t elStacoNr1 = 0;
	Int_t elMuidNr1 = 0;
	Int_t elCaloNr1 = 0;
	Int_t muStacoNr1 = 0;
	Int_t muMuidNr1 = 0;
	Int_t muCaloNr1 = 0;

	Int_t elStacoNr2 = 0;
	Int_t elMuidNr2 = 0;
	Int_t elCaloNr2 = 0;
	Int_t muStacoNr2 = 0;
	Int_t muMuidNr2 = 0;
	Int_t muCaloNr2 = 0;

	Int_t elStacoIndexNr1;
	Int_t elMuidIndexNr1;
	Int_t elCaloIndexNr1;
	Int_t muStacoIndexNr1;
	Int_t muMuidIndexNr1;
	Int_t muCaloIndexNr1;

	Int_t elStacoIndexNr2;
	Int_t elMuidIndexNr2;
	Int_t elCaloIndexNr2;
	Int_t muStacoIndexNr2;
	Int_t muMuidIndexNr2;
	Int_t muCaloIndexNr2;

	Int_t elStacoIndexArray1[1024];
	Int_t elMuidIndexArray1[1024];
	Int_t elCaloIndexArray1[1024];
	Int_t muStacoIndexArray1[1024];
	Int_t muMuidIndexArray1[1024];
	Int_t muCaloIndexArray1[1024];

	Int_t elStacoIndexArray2[1024];
	Int_t elMuidIndexArray2[1024];
	Int_t elCaloIndexArray2[1024];
	Int_t muStacoIndexArray2[1024];
	Int_t muMuidIndexArray2[1024];
	Int_t muCaloIndexArray2[1024];

	Float_t Z_MASS = core::configFltLookup("Z_MASS");

	Float_t higgs_el_et = core::configFltLookup("higgs_el_et");
	Float_t higgs_mu_pt = core::configFltLookup("higgs_mu_pt");
	Float_t higgs_mu_calo_pt = core::configFltLookup("higgs_mu_calo_pt");

	const Long64_t eventNr = fChain->GetEntries();

	for(Long64_t event = 0; event < eventNr; event++)
	{
		/*---------------------------------------------------------*/

		LoadEvent(event, eventNr);

		fixeEnergy();

		/*---------------------------------------------------------*/
		/* INIT							   */
		/*---------------------------------------------------------*/

		elStacoIndexNr1 = 0;
		elMuidIndexNr1 = 0;
		elCaloIndexNr1 = 0;
		muStacoIndexNr1 = 0;
		muMuidIndexNr1 = 0;
		muCaloIndexNr1 = 0;

		elStacoIndexNr2 = 0;
		elMuidIndexNr2 = 0;
		elCaloIndexNr2 = 0;
		muStacoIndexNr2 = 0;
		muMuidIndexNr2 = 0;
		muCaloIndexNr2 = 0;

		memset(&m_evt, 0x00, sizeof(m_evt));
		memset(  m_Z , 0x00, sizeof( m_Z ));
		memset(  m_H , 0x00, sizeof( m_H ));

		/**/

		m_evt.RunNumber = -1;
		m_evt.EventNumber = -1;
		m_evt.LumiBlock = -1;

		m_evt.nPV2 = -1;
		m_evt.nIntPerXing = -1.0f;

		m_evt.elTrigger = -1;
		m_evt.muTrigger = -1;

		for(Int_t i = 0; i < 6; i++)
		{
			m_Z[i].RunNumber = -1;
			m_Z[i].EventNumber = -1;
			m_Z[i].LumiBlock = -1;

			m_Z[i].nPV2 = -1;
			m_Z[i].nIntPerXing = -1.0f;

			m_Z[i].elTrigger = -1;
			m_Z[i].muTrigger = -1;
		}

		for(Int_t i = 0; i < 9; i++)
		{
			m_H[i].RunNumber = -1;
			m_H[i].EventNumber = -1;
			m_H[i].LumiBlock = -1;

			m_H[i].nPV2 = -1;
			m_H[i].nIntPerXing = -1.0f;

			m_H[i].elTrigger = -1;
			m_H[i].muTrigger = -1;
		}

		/*---------------------------------------------------------*/
		/* AT LEAST 3 PRIMARY TRACKS AND LAR ERROR		   */
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
#ifdef __IS_MC
		Bool_t isOkVertex = (nPV3 > 0) && (0x00000000001);
#else
		Bool_t isOkVertex = (nPV3 > 0) && (larError != 2);
#endif
		/*---------------------------------------------------------*/
		/* SELECTION 4e or 4mu					   */
		/*---------------------------------------------------------*/

		Bool_t isOkElTrigger = getElTrigger();
		Bool_t isOkMuTrigger = getMuTrigger();

		Bool_t useLoose = core::configFltLookup("EL_USE_LOOSE") != 0.0f;
		Bool_t useForward = core::configFltLookup("EL_USE_FORWARD") != 0.0f;

		/*---------------------------------------------------------*/

		if(isOkElTrigger != false && isOkVertex != false)
		{
			for(Int_t i = 0; i < el_n; i++)
			{
				if(checkObject(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					if(checkStacoOverlapping(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
					{
						elStacoNr1++;

						elStacoIndexArray1[elStacoIndexNr1++] = i;
					}

					if(checkMuidOverlapping(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
					{
						elMuidNr1++;

						elMuidIndexArray1[elMuidIndexNr1++] = i;
					}

					if(checkCaloOverlapping(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
					{
						elCaloNr1++;

						elCaloIndexArray1[elCaloIndexNr1++] = i;
					}
				}
			}
		}

		if(isOkMuTrigger != false && isOkVertex != false)
		{
			for(Int_t i = 0; i < mu_staco_n; i++)
			{
				if(checkObject(i, TYPE_MUON_STACO, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					muStacoNr1++;

					muStacoIndexArray1[muStacoIndexNr1++] = i;
				}
			}

			for(Int_t i = 0; i < mu_muid_n; i++)
			{
				if(checkObject(i, TYPE_MUON_MUID, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					muMuidNr1++;

					muMuidIndexArray1[muMuidIndexNr1++] = i;
				}
			}

			for(Int_t i = 0; i < mu_calo_n; i++)
			{
				if(checkObject(i, TYPE_MUON_CALO, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					muCaloNr1++;

					muCaloIndexArray1[muCaloIndexNr1++] = i;
				}
			}
		}

		/*---------------------------------------------------------*/
		/* SELECTION 2e2mµ					   */
		/*---------------------------------------------------------*/

		if((isOkElTrigger != false || isOkMuTrigger != false) && isOkVertex != false)
		{
			for(Int_t i = 0; i < el_n; i++)
			{
				if(checkObject(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					if(checkStacoOverlapping(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
					{
						elStacoNr2++;

						elStacoIndexArray2[elStacoIndexNr2++] = i;
					}

					if(checkMuidOverlapping(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
					{
						elMuidNr2++;

						elMuidIndexArray2[elMuidIndexNr2++] = i;
					}

					if(checkCaloOverlapping(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
					{
						elCaloNr2++;

						elCaloIndexArray2[elCaloIndexNr2++] = i;
					}
				}
			}

			for(Int_t i = 0; i < mu_staco_n; i++)
			{
				if(checkObject(i, TYPE_MUON_STACO, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					muStacoNr2++;

					muStacoIndexArray2[muStacoIndexNr2++] = i;
				}
			}

			for(Int_t i = 0; i < mu_muid_n; i++)
			{
				if(checkObject(i, TYPE_MUON_MUID, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					muMuidNr2++;

					muMuidIndexArray2[muMuidIndexNr2++] = i;
				}
			}

			for(Int_t i = 0; i < mu_calo_n; i++)
			{
				if(checkObject(i, TYPE_MUON_CALO, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					muCaloNr2++;

					muCaloIndexArray2[muCaloIndexNr2++] = i;
				}
			}
		}

		/*---------------------------------------------------------*/
		/* TRUTH						   */
		/*---------------------------------------------------------*/
#ifdef __IS_MC
		Int_t cnt_e = 0;
		Int_t cnt_u = 0;

		for(Int_t i = 0; i < mc_n; i++)
		{
			if(mc_pdgId->at(i) == 25)
			{
				for(Int_t j = 0; j < (Int_t) (mc_children->at(i).size() + mc_child_index->at(i).size()) / 2; j++)
				{
					Int_t m = mc_children->at(i).at(j);
					Int_t n = mc_child_index->at(i).at(j);

					if(mc_pdgId->at(n) == 23)
					{
						Int_t pdg = mc_pdgId->at(m);

						switch(pdg < 0 ? -pdg : +pdg)
						{
							case 11:
								cnt_e++;
								break;

							case 13:
								cnt_u++;
								break;
						}
					}
				}
			}
		}

		/**/ if(cnt_e == 4 && cnt_u == 0) {
			m_truth.eeee_nr++;
		}
		else if(cnt_e == 0 && cnt_u == 4) {
			m_truth.uuuu_nr++;
		}
		else if(cnt_e == 2 && cnt_u == 2) {
			m_truth.eeuu_nr++;
		}
#endif
		/*---------------------------------------------------------*/
		/* EVENTS						   */
		/*---------------------------------------------------------*/

		m_evt.RunNumber   =  RunNumber ;
		m_evt.EventNumber = EventNumber;
		m_evt.LumiBlock   =     lbn    ;

		m_evt.nPV2 = nPV2;
		m_evt.nIntPerXing = averageIntPerXing;

		m_evt.elTrigger = isOkElTrigger;
		m_evt.muTrigger = isOkMuTrigger;

		/*---------------------------------------------------------*/
		/*---------------------------------------------------------*/

		Int_t mu_n = mu_staco_n;

		/*---------------------------------------------------------*/
		/*---------------------------------------------------------*/

		m_evt.el_raw_n = el_n;
		m_evt.mu_raw_n = mu_n;

		if((isOkElTrigger != false || isOkMuTrigger != false) && isOkVertex != false)
		{
			m_evt.el_1st_n = el_n;
			m_evt.mu_1st_n = mu_n;

			m_evt.el_2nd_n = elStacoIndexNr2;
			m_evt.mu_2nd_n = muStacoIndexNr2;
		}

		m_evt.lepton_raw_n = m_evt.el_raw_n + m_evt.mu_raw_n;
		m_evt.lepton_1st_n = m_evt.el_1st_n + m_evt.mu_1st_n;
		m_evt.lepton_2nd_n = m_evt.el_2nd_n + m_evt.mu_2nd_n;

		/*---------------------------------------------------------*/
		/* Z->ee, H->ZZ->eeee (STACO)				   */
		/*---------------------------------------------------------*/

		Bool_t result_Z1 = false;
		Bool_t result_H1 = false;

		if(elStacoIndexNr1 >= 2)
		{
			for(Int_t i = 0 + 0; i < elStacoIndexNr1; i++)
			{
				for(Int_t j = i + 1; j < elStacoIndexNr1; j++)
				{
					if(Z_analysis(
						elStacoIndexArray1[i],
						elStacoIndexArray1[j],
						TYPE_ELECTRON, 0
					 ) != false) {
						result_Z1 = true;
					}

					for(Int_t k = j + 1; k < elStacoIndexNr1; k++)
					{
						for(Int_t l = k + 1; l < elStacoIndexNr1; l++)
						{
							if(H_analysis(
								elStacoIndexArray1[i],
								elStacoIndexArray1[j],
								elStacoIndexArray1[k],
								elStacoIndexArray1[l],
								TYPE_ELECTRON, TYPE_ELECTRON, 0
							 ) != false) {
								result_H1 = true;
							}
						}
					}
				}
			}

			selectQuadruplet(0, Z_MASS);
		}
		/*---------------------------------------------------------*/
		/* Z->ee, H->ZZ->eeee (MUID)				   */
		/*---------------------------------------------------------*/

		Bool_t result_Z2 = false;
		Bool_t result_H2 = false;

		if(elMuidIndexNr1 >= 2)
		{
			for(Int_t i = 0 + 0; i < elMuidIndexNr1; i++)
			{
				for(Int_t j = i + 1; j < elMuidIndexNr1; j++)
				{
					if(Z_analysis(
						elMuidIndexArray1[i],
						elMuidIndexArray1[j],
						TYPE_ELECTRON, 1
					 ) != false) {
						result_Z2 = true;
					}

					for(Int_t k = j + 1; k < elMuidIndexNr1; k++)
					{
						for(Int_t l = k + 1; l < elMuidIndexNr1; l++)
						{
							if(H_analysis(
								elMuidIndexArray1[i],
								elMuidIndexArray1[j],
								elMuidIndexArray1[k],
								elMuidIndexArray1[l],
								TYPE_ELECTRON, TYPE_ELECTRON, 1
							 ) != false) {
								result_H2 = true;
							}
						}
					}
				}
			}

			selectQuadruplet(1, Z_MASS);
		}

		/*---------------------------------------------------------*/
		/* Z->ee, H->ZZ->eeee (CALO)				   */
		/*---------------------------------------------------------*/

		Bool_t result_Z3 = false;
		Bool_t result_H3 = false;

		if(elCaloIndexNr1 >= 2)
		{
			for(Int_t i = 0 + 0; i < elCaloIndexNr1; i++)
			{
				for(Int_t j = i + 1; j < elCaloIndexNr1; j++)
				{
					if(Z_analysis(
						elCaloIndexArray1[i],
						elCaloIndexArray1[j],
						TYPE_ELECTRON, 2
					 ) != false) {
						result_Z3 = true;
					}

					for(Int_t k = j + 1; k < elCaloIndexNr1; k++)
					{
						for(Int_t l = k + 1; l < elCaloIndexNr1; l++)
						{
							if(H_analysis(
								elCaloIndexArray1[i],
								elCaloIndexArray1[j],
								elCaloIndexArray1[k],
								elCaloIndexArray1[l],
								TYPE_ELECTRON, TYPE_ELECTRON, 2
							 ) != false) {
								result_H3 = true;
							}
						}
					}
				}
			}

			selectQuadruplet(2, Z_MASS);
		}

		/*---------------------------------------------------------*/
		/* Z->µµ, H->ZZ->µµµµ (STACO)				   */
		/*---------------------------------------------------------*/

		Bool_t result_Z4 = false;
		Bool_t result_H4 = false;

		if(muStacoIndexNr1 >= 2)
		{
			for(Int_t i = 0 + 0; i < muStacoIndexNr1; i++)
			{
				for(Int_t j = i + 1; j < muStacoIndexNr1; j++)
				{
					if(Z_analysis(
						muStacoIndexArray1[i],
						muStacoIndexArray1[j],
						TYPE_MUON_STACO, 3
					 ) != false) {
						result_Z4 = true;
					}

					for(Int_t k = j + 1; k < muStacoIndexNr1; k++)
					{
						for(Int_t l = k + 1; l < muStacoIndexNr1; l++)
						{
							if(H_analysis(
								muStacoIndexArray1[i],
								muStacoIndexArray1[j],
								muStacoIndexArray1[k],
								muStacoIndexArray1[l],
								TYPE_MUON_STACO, TYPE_MUON_STACO, 3
							 ) != false) {
								result_H4 = true;
							}
						}
					}
				}
			}

			selectQuadruplet(3, Z_MASS);
		}

		/*---------------------------------------------------------*/
		/* Z->µµ, H->ZZ->µµµµ (MUID)				   */
		/*---------------------------------------------------------*/

		Bool_t result_Z5 = false;
		Bool_t result_H5 = false;

		if(muMuidIndexNr1 >= 2)
		{
			for(Int_t i = 0 + 0; i < muMuidIndexNr1; i++)
			{
				for(Int_t j = i + 1; j < muMuidIndexNr1; j++)
				{
					if(Z_analysis(
						muMuidIndexArray1[i],
						muMuidIndexArray1[j],
						TYPE_MUON_MUID, 4
					 ) != false) {
						result_Z5 = true;
					}

					for(Int_t k = j + 1; k < muMuidIndexNr1; k++)
					{
						for(Int_t l = k + 1; l < muMuidIndexNr1; l++)
						{
							if(H_analysis(
								muMuidIndexArray1[i],
								muMuidIndexArray1[j],
								muMuidIndexArray1[k],
								muMuidIndexArray1[l],
								TYPE_MUON_MUID, TYPE_MUON_MUID, 4
							 ) != false) {
								result_H5 = true;
							}
						}
					}
				}
			}

			selectQuadruplet(4, Z_MASS);
		}

		/*---------------------------------------------------------*/
		/* Z->µµ, H->ZZ->µµµµ (CALO)				   */
		/*---------------------------------------------------------*/

		Bool_t result_Z6 = false;
		Bool_t result_H6 = false;

		if(muCaloIndexNr1 >= 2)
		{
			for(Int_t i = 0 + 0; i < muCaloIndexNr1; i++)
			{
				for(Int_t j = i + 1; j < muCaloIndexNr1; j++)
				{
					if(Z_analysis(
						muCaloIndexArray1[i],
						muCaloIndexArray1[j],
						TYPE_MUON_CALO, 5
					 ) != false) {
						result_Z6 = true;
					}

					for(Int_t k = j + 1; k < muCaloIndexNr1; k++)
					{
						for(Int_t l = k + 1; l < muCaloIndexNr1; l++)
						{
							if(H_analysis(
								muCaloIndexArray1[i],
								muCaloIndexArray1[j],
								muCaloIndexArray1[k],
								muCaloIndexArray1[l],
								TYPE_MUON_CALO, TYPE_MUON_CALO, 5
							 ) != false) {
								result_H6 = true;
							}
						}
					}
				}
			}

			selectQuadruplet(5, Z_MASS);
		}

		/*---------------------------------------------------------*/
		/* H->ZZ->eeµµ (STACO)					   */
		/*---------------------------------------------------------*/

		Bool_t result_H7 = false;

		if(elStacoIndexNr2 >= 2 && muStacoIndexNr2 >= 2)
		{
			for(Int_t i = 0 + 0; i < elStacoIndexNr2; i++)
			{
				for(Int_t j = i + 1; j < elStacoIndexNr2; j++)
				{
					for(Int_t k = 0 + 0; k < muStacoIndexNr2; k++)
					{
						for(Int_t l = k + 1; l < muStacoIndexNr2; l++)
						{
							if(H_analysis(
								elStacoIndexArray2[i],
								elStacoIndexArray2[j],
								muStacoIndexArray2[k],
								muStacoIndexArray2[l],
								TYPE_ELECTRON, TYPE_MUON_STACO, 6
							 ) != false) {
								result_H7 = true;
							}
						}
					}
				}
			}

			selectQuadruplet(6, Z_MASS);
		}

		/*---------------------------------------------------------*/
		/* H->ZZ->eeµµ (MUID)					   */
		/*---------------------------------------------------------*/

		Bool_t result_H8 = false;

		if(elMuidIndexNr2 >= 2 && muMuidIndexNr2 >= 2)
		{
			for(Int_t i = 0 + 0; i < elMuidIndexNr2; i++)
			{
				for(Int_t j = i + 1; j < elMuidIndexNr2; j++)
				{
					for(Int_t k = 0 + 0; k < muMuidIndexNr2; k++)
					{
						for(Int_t l = k + 1; l < muMuidIndexNr2; l++)
						{
							if(H_analysis(
								elMuidIndexArray2[i],
								elMuidIndexArray2[j],
								muMuidIndexArray2[k],
								muMuidIndexArray2[l],
								TYPE_ELECTRON, TYPE_MUON_MUID, 7
							 ) != false) {
								result_H8 = true;
							}
						}
					}
				}
			}

			selectQuadruplet(7, Z_MASS);
		}

		/*---------------------------------------------------------*/
		/* H->ZZ->eeµµ (CALO)					   */
		/*---------------------------------------------------------*/

		Bool_t result_H9 = false;

		if(elCaloIndexNr2 >= 2 && muCaloIndexNr2 >= 2)
		{
			for(Int_t i = 0 + 0; i < elCaloIndexNr2; i++)
			{
				for(Int_t j = i + 1; j < elCaloIndexNr2; j++)
				{
					for(Int_t k = 0 + 0; k < muCaloIndexNr2; k++)
					{
						for(Int_t l = k + 1; l < muCaloIndexNr2; l++)
						{
							if(H_analysis(
								elCaloIndexArray2[i],
								elCaloIndexArray2[j],
								muCaloIndexArray2[k],
								muCaloIndexArray2[l],
								TYPE_ELECTRON, TYPE_MUON_CALO, 8
							 ) != false) {
								result_H9 = true;
							}
						}
					}
				}
			}

			selectQuadruplet(8, Z_MASS);
		}

		/*---------------------------------------------------------*/

		m_tree1.Fill();

		if(result_Z1 != false) {
			m_tree2.Fill();
		}
		if(result_Z2 != false) {
			m_tree3.Fill();
		}
		if(result_Z3 != false) {
			m_tree4.Fill();
		}
		if(result_Z4 != false) {
			m_tree5.Fill();
		}
		if(result_Z5 != false) {
			m_tree6.Fill();
		}
		if(result_Z6 != false) {
			m_tree7.Fill();
		}

		if(result_H1 != false) {
			m_tree8.Fill();
		}
		if(result_H2 != false) {
			m_tree9.Fill();
		}
		if(result_H3 != false) {
			m_treeA.Fill();
		}
		if(result_H4 != false) {
			m_treeB.Fill();
		}
		if(result_H5 != false) {
			m_treeC.Fill();
		}
		if(result_H6 != false) {
			m_treeD.Fill();
		}
		if(result_H7 != false) {
			m_treeE.Fill();
		}
		if(result_H8 != false) {
			m_treeF.Fill();
		}
		if(result_H9 != false) {
			m_treeG.Fill();
		}

		/*---------------------------------------------------------*/
	}

	m_tree0.Fill();

	std::cout << "Done:" << std::endl;

	std::cout << std::endl;
	std::cout << "H->eeee, H->µµµµµ" << std::endl;
	std::cout << "electons (staco): " << elStacoNr1 << std::endl;
	std::cout << "electons (muid): " << elMuidNr1 << std::endl;
	std::cout << "electons (calo): " << elCaloNr1 << std::endl;
	std::cout << "muons (staco): " << muStacoNr1 << std::endl;
	std::cout << "muons (muid): " << muMuidNr1 << std::endl;
	std::cout << "muons (calo): " << muCaloNr1 << std::endl;

	std::cout << std::endl;
	std::cout << "H->eeµµ, H->µµµee" << std::endl;
	std::cout << "electons (staco): " << elStacoNr2 << std::endl;
	std::cout << "electons (muid): " << elMuidNr2 << std::endl;
	std::cout << "electons (calo): " << elCaloNr2 << std::endl;
	std::cout << "muons (staco): " << muStacoNr2 << std::endl;
	std::cout << "muons (muid): " << muMuidNr2 << std::endl;
	std::cout << "muons (calo): " << muCaloNr2 << std::endl;
}

/*-------------------------------------------------------------------------*/

