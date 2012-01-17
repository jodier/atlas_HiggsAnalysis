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

void THiggsBuilder::selectQuadruplet(Int_t dest, Float_t Z_MASS)
{
	Float_t currDMass;
	Float_t currAMass;

	Float_t goodDMass = 999999.0f;
	Float_t goodAMass = 000000.0f;

	/*-------------------------------------------------*/
	/* PASS 1					   */
	/*-------------------------------------------------*/

	for(Int_t i = 0; i < m_H[dest].n; i++) if(m_H[dest].flag[i] >= 0x3F)
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

	for(Int_t i = 0; i < m_H[dest].n; i++) if(m_H[dest].flag[i] >= 0x3F)
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

	for(Int_t i = 0; i < m_H[dest].n; i++) if(m_H[dest].flag[i] >= 0x3F)
	{
		currDMass = fabs(Z_MASS - m_H[dest].Z12_m[i]);
		currAMass = fabs(0.000f - m_H[dest].Z34_m[i]);

		if(currDMass == goodDMass
		   &&
		   currAMass == goodAMass
		 ) {
			m_H[dest].good[i] = true;
		}
		else {
			m_H[dest].flag[i] = 0x3F;
		}
	}

	/*-------------------------------------------------*/
	/* PASS 4					   */
	/*-------------------------------------------------*/

	for(Int_t i = 0; i < m_H[dest].n; i++)
	{
		if((m_H[dest].flag[i] & (1 << 0)) != 0 /*---------------------*/) m_H[dest].cnt[ 0] = true;
		if((m_H[dest].flag[i] & (1 << 1)) != 0 /*---------------------*/) m_H[dest].cnt[ 1] = true;
		if((m_H[dest].flag[i] & (1 << 2)) != 0 /*---------------------*/) m_H[dest].cnt[ 2] = true;
		if((m_H[dest].flag[i] & (1 << 3)) != 0 /*---------------------*/) m_H[dest].cnt[ 3] = true;
		if((m_H[dest].flag[i] & (1 << 4)) != 0 && m_H[dest].eeuu[i] != 0) m_H[dest].cnt[ 4] = true;
		if((m_H[dest].flag[i] & (1 << 4)) != 0 && m_H[dest].eeuu[i] == 0) m_H[dest].cnt[ 5] = true;
		if((m_H[dest].flag[i] & (1 << 5)) != 0 && m_H[dest].eeuu[i] != 0) m_H[dest].cnt[ 6] = true;
		if((m_H[dest].flag[i] & (1 << 5)) != 0 && m_H[dest].eeuu[i] == 0) m_H[dest].cnt[ 7] = true;
		if((m_H[dest].flag[i] & (1 << 6)) != 0 && m_H[dest].eeuu[i] != 0) m_H[dest].cnt[ 8] = true;
		if((m_H[dest].flag[i] & (1 << 6)) != 0 && m_H[dest].eeuu[i] == 0) m_H[dest].cnt[ 9] = true;
		if((m_H[dest].flag[i] & (1 << 7)) != 0 && m_H[dest].eeuu[i] != 0) m_H[dest].cnt[10] = true;
		if((m_H[dest].flag[i] & (1 << 7)) != 0 && m_H[dest].eeuu[i] == 0) m_H[dest].cnt[11] = true;
		if((m_H[dest].flag[i] & (1 << 8)) != 0 && m_H[dest].eeuu[i] != 0) m_H[dest].cnt[12] = true;
		if((m_H[dest].flag[i] & (1 << 8)) != 0 && m_H[dest].eeuu[i] == 0) m_H[dest].cnt[13] = true;
		if((m_H[dest].flag[i] & (1 << 9)) != 0 && m_H[dest].eeuu[i] != 0) m_H[dest].cnt[14] = true;
		if((m_H[dest].flag[i] & (1 << 9)) != 0 && m_H[dest].eeuu[i] == 0) m_H[dest].cnt[15] = true;
	}
}

/*-------------------------------------------------------------------------*/

void THiggsBuilder::Loop(void)
{
	Int_t electronStacoNr1 = 0;
	Int_t electronMuidNr1 = 0;
	Int_t electronCaloNr1 = 0;
	Int_t muonStacoNr1 = 0;
	Int_t muonMuidNr1 = 0;
	Int_t muonCaloNr1 = 0;

	Int_t electronStacoNr2 = 0;
	Int_t electronMuidNr2 = 0;
	Int_t electronCaloNr2 = 0;
	Int_t muonStacoNr2 = 0;
	Int_t muonMuidNr2 = 0;
	Int_t muonCaloNr2 = 0;

	Int_t electronStacoIndexNr1;
	Int_t electronMuidIndexNr1;
	Int_t electronCaloIndexNr1;
	Int_t muonStacoIndexNr1;
	Int_t muonMuidIndexNr1;
	Int_t muonCaloIndexNr1;

	Int_t electronStacoIndexNr2;
	Int_t electronMuidIndexNr2;
	Int_t electronCaloIndexNr2;
	Int_t muonStacoIndexNr2;
	Int_t muonMuidIndexNr2;
	Int_t muonCaloIndexNr2;

	Int_t electronStacoIndexArray1[1024];
	Int_t electronMuidIndexArray1[1024];
	Int_t electronCaloIndexArray1[1024];
	Int_t muonStacoIndexArray1[1024];
	Int_t muonMuidIndexArray1[1024];
	Int_t muonCaloIndexArray1[1024];

	Int_t electronStacoIndexArray2[1024];
	Int_t electronMuidIndexArray2[1024];
	Int_t electronCaloIndexArray2[1024];
	Int_t muonStacoIndexArray2[1024];
	Int_t muonMuidIndexArray2[1024];
	Int_t muonCaloIndexArray2[1024];

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

		electronStacoIndexNr1 = 0;
		electronMuidIndexNr1 = 0;
		electronCaloIndexNr1 = 0;
		muonStacoIndexNr1 = 0;
		muonMuidIndexNr1 = 0;
		muonCaloIndexNr1 = 0;

		electronStacoIndexNr2 = 0;
		electronMuidIndexNr2 = 0;
		electronCaloIndexNr2 = 0;
		muonStacoIndexNr2 = 0;
		muonMuidIndexNr2 = 0;
		muonCaloIndexNr2 = 0;

		memset(&m_evt, 0x00, sizeof(m_evt));
		memset(  m_Z , 0x00, sizeof( m_Z ));
		memset(  m_H , 0x00, sizeof( m_H ));

		m_evt.RunNumber = -1;
		m_evt.EventNumber = -1;
		m_evt.LumiBlock = -1;

		m_evt.actualIntPerXing = -1.0f;
		m_evt.averageIntPerXing = -1.0f;

		m_evt.elTrigger = -1;
		m_evt.muTrigger = -1;

		for(Int_t i = 0; i < 6; i++)
		{
			m_Z[i].RunNumber = -1;
			m_Z[i].EventNumber = -1;
			m_Z[i].LumiBlock = -1;

			m_Z[i].actualIntPerXing = -1.0f;
			m_Z[i].averageIntPerXing = -1.0f;

			m_Z[i].elTrigger = -1;
			m_Z[i].muTrigger = -1;
		}

		for(Int_t i = 0; i < 9; i++)
		{
			m_H[i].RunNumber = -1;
			m_H[i].EventNumber = -1;
			m_H[i].LumiBlock = -1;

			m_H[i].actualIntPerXing = -1.0f;
			m_H[i].averageIntPerXing = -1.0f;

			m_H[i].elTrigger = -1;
			m_H[i].muTrigger = -1;
		}

		/*---------------------------------------------------------*/
		/* FLAGS						   */
		/*---------------------------------------------------------*/

		Bool_t isOkElTrigger = getElTrigger();
		Bool_t isOkMuTrigger = getMuTrigger();

		Bool_t useLoose = core::configFltLookup("EL_USE_LOOSE") != 0.0f;
		Bool_t useForward = core::configFltLookup("EL_USE_FORWARD") != 0.0f;

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

		if(isOkElTrigger != false && isOkVertex != false)
		{
			for(Int_t i = 0; i < el_n; i++)
			{
				if(checkObject(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					if(checkStacoOverlapping(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
					{
						electronStacoNr1++;

						electronStacoIndexArray1[electronStacoIndexNr1++] = i;
					}

					if(checkMuidOverlapping(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
					{
						electronMuidNr1++;

						electronMuidIndexArray1[electronMuidIndexNr1++] = i;
					}

					if(checkCaloOverlapping(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
					{
						electronCaloNr1++;

						electronCaloIndexArray1[electronCaloIndexNr1++] = i;
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
					muonStacoNr1++;

					muonStacoIndexArray1[muonStacoIndexNr1++] = i;
				}
			}

			for(Int_t i = 0; i < mu_muid_n; i++)
			{
				if(checkObject(i, TYPE_MUON_MUID, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					muonMuidNr1++;

					muonMuidIndexArray1[muonMuidIndexNr1++] = i;
				}
			}

			for(Int_t i = 0; i < mu_calo_n; i++)
			{
				if(checkObject(i, TYPE_MUON_CALO, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					muonCaloNr1++;

					muonCaloIndexArray1[muonCaloIndexNr1++] = i;
				}
			}
		}

		/*---------------------------------------------------------*/
		/* SELECTION 2e2mu					   */
		/*---------------------------------------------------------*/

		if((isOkElTrigger != false || isOkMuTrigger != false) && isOkVertex != false)
		{
			for(Int_t i = 0; i < el_n; i++)
			{
				if(checkObject(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					if(checkStacoOverlapping(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
					{
						electronStacoNr2++;

						electronStacoIndexArray2[electronStacoIndexNr2++] = i;
					}

					if(checkMuidOverlapping(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
					{
						electronMuidNr2++;

						electronMuidIndexArray2[electronMuidIndexNr2++] = i;
					}

					if(checkCaloOverlapping(i, TYPE_ELECTRON, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
					{
						electronCaloNr2++;

						electronCaloIndexArray2[electronCaloIndexNr2++] = i;
					}
				}
			}

			for(Int_t i = 0; i < mu_staco_n; i++)
			{
				if(checkObject(i, TYPE_MUON_STACO, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					muonStacoNr2++;

					muonStacoIndexArray2[muonStacoIndexNr2++] = i;
				}
			}

			for(Int_t i = 0; i < mu_muid_n; i++)
			{
				if(checkObject(i, TYPE_MUON_MUID, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					muonMuidNr2++;

					muonMuidIndexArray2[muonMuidIndexNr2++] = i;
				}
			}

			for(Int_t i = 0; i < mu_calo_n; i++)
			{
				if(checkObject(i, TYPE_MUON_CALO, higgs_el_et, higgs_mu_pt, higgs_mu_calo_pt, useLoose, useForward) != false)
				{
					muonCaloNr2++;

					muonCaloIndexArray2[muonCaloIndexNr2++] = i;
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

		m_evt.actualIntPerXing = actualIntPerXing;
		m_evt.averageIntPerXing = averageIntPerXing;

		m_evt.elTrigger = isOkElTrigger;
		m_evt.muTrigger = isOkMuTrigger;

		/*---------------------------------------------------------*/

		Int_t mu_n = (mu_staco_n > mu_muid_n) ? mu_staco_n : mu_muid_n;

		/*---------------------------------------------------------*/

		m_evt.el_raw_n = el_n;
		m_evt.mu_raw_n = mu_n;

		if((isOkElTrigger != false || isOkMuTrigger != false) && isOkVertex != false)
		{
			m_evt.el_1st_n = el_n;
			m_evt.mu_1st_n = mu_n;

			m_evt.el_2nd_n = (electronStacoIndexNr2 > electronMuidIndexNr2) ? electronStacoIndexNr2 : electronMuidIndexNr2;
			m_evt.mu_2nd_n = (  muonStacoIndexNr2   >   muonMuidIndexNr2  ) ?   muonStacoIndexNr2   :   muonMuidIndexNr2  ;
		}

		m_evt.lepton_raw_n = m_evt.el_raw_n + m_evt.mu_raw_n;
		m_evt.lepton_1st_n = m_evt.el_1st_n + m_evt.mu_1st_n;
		m_evt.lepton_2nd_n = m_evt.el_2nd_n + m_evt.mu_2nd_n;

		/*---------------------------------------------------------*/
		/* Z->ee, H->ZZ->eeee (STACO)				   */
		/*---------------------------------------------------------*/

		Bool_t result_Z1 = false;
		Bool_t result_H1 = false;

		if(electronStacoIndexNr1 >= 2)
		{
			for(Int_t i = 0 + 0; i < electronStacoIndexNr1; i++)
			{
				for(Int_t j = i + 1; j < electronStacoIndexNr1; j++)
				{
					if(Z_analysis(
						electronStacoIndexArray1[i],
						electronStacoIndexArray1[j],
						TYPE_ELECTRON, 0
					 ) != false) {
						result_Z1 = true;
					}

					for(Int_t k = j + 1; k < electronStacoIndexNr1; k++)
					{
						for(Int_t l = k + 1; l < electronStacoIndexNr1; l++)
						{
							if(H_analysis(
								electronStacoIndexArray1[i],
								electronStacoIndexArray1[j],
								electronStacoIndexArray1[k],
								electronStacoIndexArray1[l],
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

		if(electronMuidIndexNr1 >= 2)
		{
			for(Int_t i = 0 + 0; i < electronMuidIndexNr1; i++)
			{
				for(Int_t j = i + 1; j < electronMuidIndexNr1; j++)
				{
					if(Z_analysis(
						electronMuidIndexArray1[i],
						electronMuidIndexArray1[j],
						TYPE_ELECTRON, 1
					 ) != false) {
						result_Z2 = true;
					}

					for(Int_t k = j + 1; k < electronMuidIndexNr1; k++)
					{
						for(Int_t l = k + 1; l < electronMuidIndexNr1; l++)
						{
							if(H_analysis(
								electronMuidIndexArray1[i],
								electronMuidIndexArray1[j],
								electronMuidIndexArray1[k],
								electronMuidIndexArray1[l],
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

		if(electronCaloIndexNr1 >= 2)
		{
			for(Int_t i = 0 + 0; i < electronCaloIndexNr1; i++)
			{
				for(Int_t j = i + 1; j < electronCaloIndexNr1; j++)
				{
					if(Z_analysis(
						electronCaloIndexArray1[i],
						electronCaloIndexArray1[j],
						TYPE_ELECTRON, 2
					 ) != false) {
						result_Z3 = true;
					}

					for(Int_t k = j + 1; k < electronCaloIndexNr1; k++)
					{
						for(Int_t l = k + 1; l < electronCaloIndexNr1; l++)
						{
							if(H_analysis(
								electronCaloIndexArray1[i],
								electronCaloIndexArray1[j],
								electronCaloIndexArray1[k],
								electronCaloIndexArray1[l],
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

		if(muonStacoIndexNr1 >= 2)
		{
			for(Int_t i = 0 + 0; i < muonStacoIndexNr1; i++)
			{
				for(Int_t j = i + 1; j < muonStacoIndexNr1; j++)
				{
					if(Z_analysis(
						muonStacoIndexArray1[i],
						muonStacoIndexArray1[j],
						TYPE_MUON_STACO, 3
					 ) != false) {
						result_Z4 = true;
					}

					for(Int_t k = j + 1; k < muonStacoIndexNr1; k++)
					{
						for(Int_t l = k + 1; l < muonStacoIndexNr1; l++)
						{
							if(H_analysis(
								muonStacoIndexArray1[i],
								muonStacoIndexArray1[j],
								muonStacoIndexArray1[k],
								muonStacoIndexArray1[l],
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

		if(muonMuidIndexNr1 >= 2)
		{
			for(Int_t i = 0 + 0; i < muonMuidIndexNr1; i++)
			{
				for(Int_t j = i + 1; j < muonMuidIndexNr1; j++)
				{
					if(Z_analysis(
						muonMuidIndexArray1[i],
						muonMuidIndexArray1[j],
						TYPE_MUON_MUID, 4
					 ) != false) {
						result_Z5 = true;
					}

					for(Int_t k = j + 1; k < muonMuidIndexNr1; k++)
					{
						for(Int_t l = k + 1; l < muonMuidIndexNr1; l++)
						{
							if(H_analysis(
								muonMuidIndexArray1[i],
								muonMuidIndexArray1[j],
								muonMuidIndexArray1[k],
								muonMuidIndexArray1[l],
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

		if(muonCaloIndexNr1 >= 2)
		{
			for(Int_t i = 0 + 0; i < muonCaloIndexNr1; i++)
			{
				for(Int_t j = i + 1; j < muonCaloIndexNr1; j++)
				{
					if(Z_analysis(
						muonCaloIndexArray1[i],
						muonCaloIndexArray1[j],
						TYPE_MUON_CALO, 5
					 ) != false) {
						result_Z6 = true;
					}

					for(Int_t k = j + 1; k < muonCaloIndexNr1; k++)
					{
						for(Int_t l = k + 1; l < muonCaloIndexNr1; l++)
						{
							if(H_analysis(
								muonCaloIndexArray1[i],
								muonCaloIndexArray1[j],
								muonCaloIndexArray1[k],
								muonCaloIndexArray1[l],
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

		if(electronStacoIndexNr2 >= 2 && muonStacoIndexNr2 >= 2)
		{
			for(Int_t i = 0 + 0; i < electronStacoIndexNr2; i++)
			{
				for(Int_t j = i + 1; j < electronStacoIndexNr2; j++)
				{
					for(Int_t k = 0 + 0; k < muonStacoIndexNr2; k++)
					{
						for(Int_t l = k + 1; l < muonStacoIndexNr2; l++)
						{
							if(H_analysis(
								electronStacoIndexArray2[i],
								electronStacoIndexArray2[j],
								muonStacoIndexArray2[k],
								muonStacoIndexArray2[l],
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

		if(electronMuidIndexNr2 >= 2 && muonMuidIndexNr2 >= 2)
		{
			for(Int_t i = 0 + 0; i < electronMuidIndexNr2; i++)
			{
				for(Int_t j = i + 1; j < electronMuidIndexNr2; j++)
				{
					for(Int_t k = 0 + 0; k < muonMuidIndexNr2; k++)
					{
						for(Int_t l = k + 1; l < muonMuidIndexNr2; l++)
						{
							if(H_analysis(
								electronMuidIndexArray2[i],
								electronMuidIndexArray2[j],
								muonMuidIndexArray2[k],
								muonMuidIndexArray2[l],
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

		if(electronCaloIndexNr2 >= 2 && muonCaloIndexNr2 >= 2)
		{
			for(Int_t i = 0 + 0; i < electronCaloIndexNr2; i++)
			{
				for(Int_t j = i + 1; j < electronCaloIndexNr2; j++)
				{
					for(Int_t k = 0 + 0; k < muonCaloIndexNr2; k++)
					{
						for(Int_t l = k + 1; l < muonCaloIndexNr2; l++)
						{
							if(H_analysis(
								electronCaloIndexArray2[i],
								electronCaloIndexArray2[j],
								muonCaloIndexArray2[k],
								muonCaloIndexArray2[l],
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
	std::cout << "electons (staco): " << electronStacoNr1 << std::endl;
	std::cout << "electons (muid): " << electronMuidNr1 << std::endl;
	std::cout << "electons (calo): " << electronCaloNr1 << std::endl;
	std::cout << "muons (staco): " << muonStacoNr1 << std::endl;
	std::cout << "muons (muid): " << muonMuidNr1 << std::endl;
	std::cout << "muons (calo): " << muonCaloNr1 << std::endl;

	std::cout << std::endl;
	std::cout << "H->eeµµ, H->µµµee" << std::endl;
	std::cout << "electons (staco): " << electronStacoNr2 << std::endl;
	std::cout << "electons (muid): " << electronMuidNr2 << std::endl;
	std::cout << "electons (calo): " << electronCaloNr2 << std::endl;
	std::cout << "muons (staco): " << muonStacoNr2 << std::endl;
	std::cout << "muons (muid): " << muonMuidNr2 << std::endl;
	std::cout << "muons (calo): " << muonCaloNr2 << std::endl;
}

/*-------------------------------------------------------------------------*/

