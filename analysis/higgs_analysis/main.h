/*-------------------------------------------------------------------------*/

#ifndef __H_ANALYSIS_H
#define __H_ANALYSIS_H

/*-------------------------------------------------------------------------*/

#include "utils.h"

/*-------------------------------------------------------------------------*/

#define MAX 1024

/*-------------------------------------------------------------------------*/

class THiggsBuilder: public TLeptonAnalysis
{
  public:
	TTree m_tree0;
	TTree m_tree1;
	TTree m_tree2;
	TTree m_tree3;
	TTree m_tree4;
	TTree m_tree5;
	TTree m_tree6;
	TTree m_tree7;
	TTree m_tree8;
	TTree m_tree9;
	TTree m_treeA;
	TTree m_treeB;

	THiggsBuilder(TChain *chain): TLeptonAnalysis(chain)
	{
		m_tree0.SetName("Truth");
		m_tree1.SetName("Event");

		m_tree2.SetName("Z1");
		m_tree3.SetName("Z2");
		m_tree4.SetName("Z3");
		m_tree5.SetName("Z4");

		TTree *ZTreeArray[4] = {&m_tree2, &m_tree3, &m_tree4, &m_tree5};

		m_tree6.SetName("H1");
		m_tree7.SetName("H2");
		m_tree8.SetName("H3");
		m_tree9.SetName("H4");
		m_treeA.SetName("H5");
		m_treeB.SetName("H6");

		TTree *HTreeArray[6] = {&m_tree6, &m_tree7, &m_tree8, &m_tree9, &m_treeA, &m_treeB};

		/*---------------------------------------------------------*/
		/* TRUTH						   */
		/*---------------------------------------------------------*/

		m_truth.eeee_nr = 0;
		m_truth.uuuu_nr = 0;
		m_truth.eeuu_nr = 0;

		m_tree0.Branch("eeee_nr", &m_truth.eeee_nr, "eeee_nr/I");
		m_tree0.Branch("uuuu_nr", &m_truth.uuuu_nr, "uuuu_nr/I");
		m_tree0.Branch("eeuu_nr", &m_truth.eeuu_nr, "eeuu_nr/I");		

		/*---------------------------------------------------------*/
		/* EVENTS						   */
		/*---------------------------------------------------------*/

		m_tree1.Branch("RunNumber", &m_evt.RunNumber, "RunNumber/I");
		m_tree1.Branch("EventNumber", &m_evt.EventNumber, "EventNumber/I");
		m_tree1.Branch("LumiBlock", &m_evt.LumiBlock, "LumiBlock/I");

		m_tree1.Branch("actualIntPerXing", &m_evt.actualIntPerXing, "actualIntPerXing/F");
		m_tree1.Branch("averageIntPerXing", &m_evt.averageIntPerXing, "averageIntPerXing/F");

		m_tree1.Branch("elTrigger", &m_evt.elTrigger, "elTrigger/I");
		m_tree1.Branch("muTrigger", &m_evt.muTrigger, "muTrigger/I");

		m_tree1.Branch("el_raw_n", &m_evt.el_raw_n, "el_raw_n/I");
		m_tree1.Branch("mu_raw_n", &m_evt.mu_raw_n, "mu_raw_n/I");
		m_tree1.Branch("lepton_raw_n", &m_evt.lepton_raw_n, "lepton_raw_n/I");

		m_tree1.Branch("el_1st_n", &m_evt.el_1st_n, "el_1st_n/I");
		m_tree1.Branch("mu_1st_n", &m_evt.mu_1st_n, "mu_1st_n/I");
		m_tree1.Branch("lepton_1st_n", &m_evt.lepton_1st_n, "lepton_1st_n/I");

		m_tree1.Branch("el_2nd_n", &m_evt.el_2nd_n, "el_2nd_n/I");
		m_tree1.Branch("mu_2nd_n", &m_evt.mu_2nd_n, "mu_2nd_n/I");
		m_tree1.Branch("lepton_2nd_n", &m_evt.lepton_2nd_n, "lepton_2nd_n/I");

		/*---------------------------------------------------------*/
		/* Z ANALYSIS						   */
		/*---------------------------------------------------------*/

		for(int i = 0; i < 4; i++)
		{
			TTree *tree = ZTreeArray[i];

			//

			tree->Branch("RunNumber", &m_Z[i].RunNumber, "RunNumber/I");
			tree->Branch("EventNumber", &m_Z[i].EventNumber, "EventNumber/I");
			tree->Branch("LumiBlock", &m_Z[i].LumiBlock, "LumiBlock/I");

			tree->Branch("actualIntPerXing", &m_Z[i].actualIntPerXing, "actualIntPerXing/F");
			tree->Branch("averageIntPerXing", &m_Z[i].averageIntPerXing, "averageIntPerXing/F");

			tree->Branch("elTrigger", &m_Z[i].elTrigger, "elTrigger/I");
			tree->Branch("muTrigger", &m_Z[i].muTrigger, "muTrigger/I");

			tree->Branch("tn", &m_Z[i].tn, "tn/I");
			tree->Branch("ta", m_Z[i].ta, "ta[tn]/i");

			//

			tree->Branch("n", &m_Z[i].n, "n" "/I");
			tree->Branch("nPV2", &m_Z[i].nPV2, "nPV2/I");

			tree->Branch("weight", m_Z[i].weight, "weight[n]/F");

			tree->Branch("l1_tight", m_Z[i].l1_tight, "l1_tight[n]/I");
			tree->Branch("l2_tight", m_Z[i].l2_tight, "l2_tight[n]/I");

			tree->Branch("l1_truthMatch", m_Z[i].l1_truthMatch, "l1_truthMatch[n]/I");
			tree->Branch("l2_truthMatch", m_Z[i].l2_truthMatch, "l2_truthMatch[n]/I");
			tree->Branch("l1_triggerMatch", m_Z[i].l1_triggerMatch, "l1_triggerMatch[n]/I");
			tree->Branch("l2_triggerMatch", m_Z[i].l2_triggerMatch, "l2_triggerMatch[n]/I");

			tree->Branch("l1_pt", m_Z[i].l1_pt, "l1_pt[n]/F");
			tree->Branch("l2_pt", m_Z[i].l2_pt, "l2_pt[n]/F");
			tree->Branch("l1_eta", m_Z[i].l1_eta, "l1_eta[n]/F");
			tree->Branch("l2_eta", m_Z[i].l2_eta, "l2_eta[n]/F");
			tree->Branch("l1_phi", m_Z[i].l1_phi, "l1_phi[n]/F");
			tree->Branch("l2_phi", m_Z[i].l2_phi, "l2_phi[n]/F");

			tree->Branch("l1_tkIso20", m_Z[i].l1_tkIso20, "l1_tkIso20[n]/F");
			tree->Branch("l2_tkIso20", m_Z[i].l2_tkIso20, "l2_tkIso20[n]/F");
			tree->Branch("l1_tkIso30", m_Z[i].l1_tkIso30, "l1_tkIso30[n]/F");
			tree->Branch("l2_tkIso30", m_Z[i].l2_tkIso30, "l2_tkIso30[n]/F");
			tree->Branch("l1_clIso20", m_Z[i].l1_clIso20, "l1_clIso20[n]/F");
			tree->Branch("l2_clIso20", m_Z[i].l2_clIso20, "l2_clIso20[n]/F");
			tree->Branch("l1_clIso30", m_Z[i].l1_clIso30, "l1_clIso30[n]/F");
			tree->Branch("l2_clIso30", m_Z[i].l2_clIso30, "l2_clIso30[n]/F");
			tree->Branch("l1_clIso20_corrected", m_Z[i].l1_clIso20_corrected, "l1_clIso20_corrected[n]/F");
			tree->Branch("l2_clIso20_corrected", m_Z[i].l2_clIso20_corrected, "l2_clIso20_corrected[n]/F");
			tree->Branch("l1_clIso30_corrected", m_Z[i].l1_clIso30_corrected, "l1_clIso30_corrected[n]/F");
			tree->Branch("l2_clIso30_corrected", m_Z[i].l2_clIso30_corrected, "l2_clIso30_corrected[n]/F");
			tree->Branch("l1_d0sigma", m_Z[i].l1_d0sigma, "l1_d0sigma[n]/F");
			tree->Branch("l2_d0sigma", m_Z[i].l2_d0sigma, "l2_d0sigma[n]/F");

			tree->Branch("Z_m", m_Z[i].Z_m, "Z_m[n]/F");
			tree->Branch("Z_et", m_Z[i].Z_et, "Z_et[n]/F");
			tree->Branch("Z_pt", m_Z[i].Z_pt, "Z_pt[n]/F");
			tree->Branch("Z_eta", m_Z[i].Z_eta, "Z_eta[n]/F");
			tree->Branch("Z_phi", m_Z[i].Z_phi, "Z_phi[n]/F");
		}

		/*---------------------------------------------------------*/
		/* H ANALYSIS						   */
		/*---------------------------------------------------------*/

		for(int i = 0; i < 6; i++)
		{
			TTree *tree = HTreeArray[i];

			//

			tree->Branch("RunNumber", &m_H[i].RunNumber, "RunNumber/I");
			tree->Branch("EventNumber", &m_H[i].EventNumber, "EventNumber/I");
			tree->Branch("LumiBlock", &m_H[i].LumiBlock, "LumiBlock/I");

			tree->Branch("actualIntPerXing", &m_H[i].actualIntPerXing, "actualIntPerXing/F");
			tree->Branch("averageIntPerXing", &m_H[i].averageIntPerXing, "averageIntPerXing/F");

			tree->Branch("elTrigger", &m_H[i].elTrigger, "elTrigger/I");
			tree->Branch("muTrigger", &m_H[i].muTrigger, "muTrigger/I");

			tree->Branch("tn", &m_H[i].tn, "tn/I");
			tree->Branch("ta", m_H[i].ta, "ta[tn]/i");

			//

			tree->Branch("n", &m_H[i].n, "n/I");

			tree->Branch("weight", m_H[i].weight, "weight[n]/F");

			tree->Branch("l1_truthMatch", m_H[i].l1_truthMatch, "l1_truthMatch[n]/I");
			tree->Branch("l2_truthMatch", m_H[i].l2_truthMatch, "l2_truthMatch[n]/I");
			tree->Branch("l3_truthMatch", m_H[i].l3_truthMatch, "l3_truthMatch[n]/I");
			tree->Branch("l4_truthMatch", m_H[i].l4_truthMatch, "l4_truthMatch[n]/I");
			tree->Branch("l1_triggerMatch", m_H[i].l1_triggerMatch, "l1_triggerMatch[n]/I");
			tree->Branch("l2_triggerMatch", m_H[i].l2_triggerMatch, "l2_triggerMatch[n]/I");
			tree->Branch("l3_triggerMatch", m_H[i].l3_triggerMatch, "l3_triggerMatch[n]/I");
			tree->Branch("l4_triggerMatch", m_H[i].l4_triggerMatch, "l4_triggerMatch[n]/I");

			tree->Branch("l1_pt", m_H[i].l1_pt, "l1_pt[n]/F");
			tree->Branch("l2_pt", m_H[i].l2_pt, "l2_pt[n]/F");
			tree->Branch("l3_pt", m_H[i].l3_pt, "l3_pt[n]/F");
			tree->Branch("l4_pt", m_H[i].l4_pt, "l4_pt[n]/F");
			tree->Branch("l1_eta", m_H[i].l1_eta, "l1_eta[n]/F");
			tree->Branch("l2_eta", m_H[i].l2_eta, "l2_eta[n]/F");
			tree->Branch("l3_eta", m_H[i].l3_eta, "l3_eta[n]/F");
			tree->Branch("l4_eta", m_H[i].l4_eta, "l4_eta[n]/F");
			tree->Branch("l1_phi", m_H[i].l1_phi, "l1_phi[n]/F");
			tree->Branch("l2_phi", m_H[i].l2_phi, "l2_phi[n]/F");
			tree->Branch("l3_phi", m_H[i].l3_phi, "l3_phi[n]/F");
			tree->Branch("l4_phi", m_H[i].l4_phi, "l4_phi[n]/F");

			tree->Branch("Z12_m", m_H[i].Z12_m, "Z12_m[n]/F");
			tree->Branch("Z34_m", m_H[i].Z34_m, "Z34_m[n]/F");
			tree->Branch("Z12_et", m_H[i].Z12_et, "Z12_et[n]/F");
			tree->Branch("Z34_et", m_H[i].Z34_et, "Z34_et[n]/F");
			tree->Branch("Z12_pt", m_H[i].Z12_pt, "Z12_pt[n]/F");
			tree->Branch("Z34_pt", m_H[i].Z34_pt, "Z34_pt[n]/F");
			tree->Branch("Z12_eta", m_H[i].Z12_eta, "Z12_eta[n]/F");
			tree->Branch("Z34_eta", m_H[i].Z34_eta, "Z34_eta[n]/F");
			tree->Branch("Z12_phi", m_H[i].Z12_phi, "Z12_phi[n]/F");
			tree->Branch("Z34_phi", m_H[i].Z34_phi, "Z34_phi[n]/F");

			tree->Branch("H_m", m_H[i].H_m, "H_m[n]/F");
			tree->Branch("H_et", m_H[i].H_et, "H_et[n]/F");
			tree->Branch("H_pt", m_H[i].H_pt, "H_pt[n]/F");
			tree->Branch("H_eta", m_H[i].H_eta, "H_eta[n]/F");
			tree->Branch("H_phi", m_H[i].H_phi, "H_phi[n]/F");

			tree->Branch("eeuu", m_H[i].eeuu, "eeuu[n]/I");
			tree->Branch("good", m_H[i].good, "good[n]/I");

			tree->Branch("flag", m_H[i].flag, "flag[n]/i");

			tree->Branch("cnt0", &m_H[i].cnt[0], "cnt0/I");
			tree->Branch("cnt1", &m_H[i].cnt[1], "cnt1/I");
			tree->Branch("cnt2", &m_H[i].cnt[2], "cnt2/I");
			tree->Branch("cnt3", &m_H[i].cnt[3], "cnt3/I");
			tree->Branch("cnt4", &m_H[i].cnt[4], "cnt4/I");
			tree->Branch("cnt5", &m_H[i].cnt[5], "cnt5/I");
			tree->Branch("cnt6_eeuu", &m_H[i].cnt[6], "cnt6_eeuu/I");
			tree->Branch("cnt6_uuee", &m_H[i].cnt[7], "cnt6_uuee/I");
			tree->Branch("cnt7_eeuu", &m_H[i].cnt[8], "cnt7_eeuu/I");
			tree->Branch("cnt7_uuee", &m_H[i].cnt[9], "cnt7_uuee/I");
			tree->Branch("cnt8_eeuu", &m_H[i].cnt[10], "cnt8_eeuu/I");
			tree->Branch("cnt8_uuee", &m_H[i].cnt[11], "cnt8_uuee/I");
			tree->Branch("cnt9_eeuu", &m_H[i].cnt[12], "cnt9_eeuu/I");
			tree->Branch("cnt9_uuee", &m_H[i].cnt[13], "cnt9_uuee/I");
		}

		/*---------------------------------------------------------*/
	}

	void Loop(void);

	/* ANALYSIS */

	bool Z_analysis(
		int index1,
		int index2,
		TLeptonType type,
		int dest
	);

	bool H_analysis(
		int index1,
		int index2,
		int index3,
		int index4,
		TLeptonType type1,
		TLeptonType type2,
		int dest
	);

	void selectQuadruplet(int dest, Float_t Z_MASS);

  private:
	struct __truth_s
	{
		Int_t eeee_nr;
		Int_t uuuu_nr;
		Int_t eeuu_nr;

	} m_truth;

	struct __event_s
	{
		Int_t RunNumber;
		Int_t EventNumber;
		Int_t LumiBlock;

		Float_t actualIntPerXing;
		Float_t averageIntPerXing;

		Int_t elTrigger;
		Int_t muTrigger;

		/**/

		Int_t el_raw_n;
		Int_t mu_raw_n;
		Int_t lepton_raw_n;

		Int_t el_1st_n;
		Int_t mu_1st_n;
		Int_t lepton_1st_n;

		Int_t el_2nd_n;
		Int_t mu_2nd_n;
		Int_t lepton_2nd_n;

	} m_evt;

	struct __z_boson_s
	{
		Int_t RunNumber;
		Int_t EventNumber;
		Int_t LumiBlock;

		Float_t actualIntPerXing;
		Float_t averageIntPerXing;

		Int_t elTrigger;
		Int_t muTrigger;

		Int_t tn;
		UInt_t ta[MAX];

		/**/

		Int_t n;
		Int_t nPV2;

		Float_t weight[MAX];

		Int_t l1_tight[MAX];
		Int_t l2_tight[MAX];

		Int_t l1_truthMatch[MAX];
		Int_t l2_truthMatch[MAX];
		Int_t l1_triggerMatch[MAX];
		Int_t l2_triggerMatch[MAX];

		Float_t l1_pt[MAX];
		Float_t l2_pt[MAX];
		Float_t l1_eta[MAX];
		Float_t l2_eta[MAX];
		Float_t l1_phi[MAX];
		Float_t l2_phi[MAX];
		Float_t l1_z0[MAX];
		Float_t l2_z0[MAX];

		Float_t l1_clIso20[MAX];
		Float_t l2_clIso20[MAX];
		Float_t l1_clIso30[MAX];
		Float_t l2_clIso30[MAX];
		Float_t l1_clIso20_corrected[MAX];
		Float_t l2_clIso20_corrected[MAX];
		Float_t l1_clIso30_corrected[MAX];
		Float_t l2_clIso30_corrected[MAX];
		Float_t l1_tkIso20[MAX];
		Float_t l2_tkIso20[MAX];
		Float_t l1_tkIso30[MAX];
		Float_t l2_tkIso30[MAX];
		Float_t l1_d0sigma[MAX];
		Float_t l2_d0sigma[MAX];

		Float_t Z_m[MAX];
		Float_t Z_et[MAX];
		Float_t Z_pt[MAX];
		Float_t Z_eta[MAX];
		Float_t Z_phi[MAX];

	} m_Z[4];

	struct __higgs_boson_s
	{
		Int_t RunNumber;
		Int_t EventNumber;
		Int_t LumiBlock;

		Float_t actualIntPerXing;
		Float_t averageIntPerXing;

		Int_t elTrigger;
		Int_t muTrigger;

		Int_t tn;
		UInt_t ta[MAX];

		/**/

		Int_t n;

		Float_t weight[MAX];

		Int_t l1_truthMatch[MAX];
		Int_t l2_truthMatch[MAX];
		Int_t l3_truthMatch[MAX];
		Int_t l4_truthMatch[MAX];
		Int_t l1_triggerMatch[MAX];
		Int_t l2_triggerMatch[MAX];
		Int_t l3_triggerMatch[MAX];
		Int_t l4_triggerMatch[MAX];

		Float_t l1_pt[MAX];
		Float_t l2_pt[MAX];
		Float_t l3_pt[MAX];
		Float_t l4_pt[MAX];
		Float_t l1_eta[MAX];
		Float_t l2_eta[MAX];
		Float_t l3_eta[MAX];
		Float_t l4_eta[MAX];
		Float_t l1_phi[MAX];
		Float_t l2_phi[MAX];
		Float_t l3_phi[MAX];
		Float_t l4_phi[MAX];

		Float_t Z12_m[MAX];
		Float_t Z34_m[MAX];
		Float_t Z12_et[MAX];
		Float_t Z34_et[MAX];
		Float_t Z12_pt[MAX];
		Float_t Z34_pt[MAX];
		Float_t Z12_eta[MAX];
		Float_t Z34_eta[MAX];
		Float_t Z12_phi[MAX];
		Float_t Z34_phi[MAX];

		Float_t H_m[MAX];
		Float_t H_et[MAX];
		Float_t H_pt[MAX];
		Float_t H_eta[MAX];
		Float_t H_phi[MAX];

		Int_t eeuu[MAX];
		Int_t good[MAX];

		UInt_t flag[MAX];

		Int_t cnt[6 + 2 * 4];

	} m_H[6];
};

/*-------------------------------------------------------------------------*/

#endif /* __H_ANALYSIS_H */

/*-------------------------------------------------------------------------*/

