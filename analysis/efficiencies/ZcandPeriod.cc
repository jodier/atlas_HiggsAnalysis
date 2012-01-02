/*-------------------------------------------------------------------------*/

#include <cmath>
#include <fstream>
#include <iostream>

#include <TH1.h>

/*-------------------------------------------------------------------------*/

#define ZStudy_cxx
#include "ZStudy.h"

#include "../../tools/PileupReweighting/PileupReweighting/TPileupReweighting.h"

static bool bkgd = false;
static bool isMC = false;

TFile *file;

/*-------------------------------------------------------------------------*/

#define ET_MIN		10.0f	/* GeV */
#define ET_MAX		5000.0f	/* GeV */

/*-------------------------------------------------------------------------*/

static Root::TPileupReweighting *pileupReweightingBD = NULL;
static Root::TPileupReweighting *pileupReweightingEH = NULL;
static Root::TPileupReweighting *pileupReweightingIK = NULL;
static Root::TPileupReweighting *pileupReweightingLM = NULL;

/*-------------------------------------------------------------------------*/

bool localLoader(TChain *chain, const char *fname)
{
	std::ifstream stream;

	stream.open(fname);

	if(stream.is_open() == false)
	{
		std::cerr << "Could not open '" << fname << "' !" << std::endl;

		return false;
	}

	/**/

	std::string fName;

	while(stream >> fName)
	{
//		std::cout << "Loading '" << fName << "'..." << std::endl;

		chain->AddFile(fName.c_str());
	}

	/**/

	stream.close();

	return true;
}

/*-------------------------------------------------------------------------*/

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		std::cerr << argv[0] << " mc.txt data.txt" << std::endl;

		return 1;
	}

	pileupReweightingBD = new Root::TPileupReweighting("TPileupReweightingBD");
	pileupReweightingEH = new Root::TPileupReweighting("TPileupReweightingEH");
	pileupReweightingIK = new Root::TPileupReweighting("TPileupReweightingIK");
	pileupReweightingLM = new Root::TPileupReweighting("TPileupReweightingLM");

	if(pileupReweightingBD->initialize("analysis/ilumicalc_period_BD_Atlas_Ready.root", "avgintperbx", "analysis/Mu_MC11bprime_analysis.root", "mc11b_BD") != 0
	   ||
	   pileupReweightingEH->initialize("analysis/ilumicalc_period_EH_Atlas_Ready.root", "avgintperbx", "analysis/Mu_MC11bprime_analysis.root", "mc11b_EH") != 0
	   ||
	   pileupReweightingIK->initialize("analysis/ilumicalc_period_IK_Atlas_Ready.root", "avgintperbx", "analysis/Mu_MC11bprime_analysis.root", "mc11b_IK") != 0
	   ||
	   pileupReweightingLM->initialize("analysis/ilumicalc_period_LM_Atlas_Ready.root", "avgintperbx", "analysis/Mu_MC11bprime_analysis.root", "mc11b_LM") != 0
	 ) {
		delete pileupReweightingBD;
		delete pileupReweightingEH;
		delete pileupReweightingIK;
		delete pileupReweightingLM;

		return 1;
	}

	TChain *chain1 = new TChain("Z1");
	TChain *chain2 = new TChain("Z1");

	if(localLoader(chain1, argv[1]) == false
	   ||
	   localLoader(chain2, argv[2]) == false
	 ) {
		delete chain1;
		delete chain2;

		delete pileupReweightingBD;
		delete pileupReweightingEH;
		delete pileupReweightingIK;
		delete pileupReweightingLM;

		return 1;
	}

	ZStudy alg1(chain1);
	ZStudy alg2(chain2);

	file = new TFile("ZcandPeriod.root", "recreate");

	if(file != NULL)
	{
		bkgd = false;
		isMC = true;
		alg1.Loop();

		std::cout << std::endl;

		bkgd = true;
		isMC = true;
		alg1.Loop();

		std::cout << std::endl;

		bkgd = false;
		isMC = false;
		alg2.Loop();

		std::cout << std::endl;

		file->Close();

		delete file;
	}

	delete chain1;
	delete chain2;

	delete pileupReweightingBD;
	delete pileupReweightingEH;
	delete pileupReweightingIK;
	delete pileupReweightingLM;

	std::cout << "Bye." << std::endl;

	return 0;
}

/*-------------------------------------------------------------------------*/

void ZStudy::Loop(void)
{
	if(fChain == 0)
	{
		return;
	}	

	/**/

	TH1D h("", "", 11, 0, 11);

	if(isMC != false)
	{
		if(bkgd != false)
		{
			h.SetName("bkgd");
		}
		else
		{
			h.SetName("mc");
		}
	}
	else
	{
		h.SetName("data");
	}

	/**/

	Long64_t eventNr = fChain->GetEntries();

	/**/

	for(Long64_t event = 0; event < eventNr; event++)
	{
		if(this->LoadTree(event) < 0)
		{
			break;
		}

		fChain->GetEntry(event);

		if((event % 1000) == 0)
		{
			std::cout << "\033[sEvent " << event << "/" << eventNr << "\033[u" << std::flush;
		}

		/**/

		if(isMC == false)
		{
			Bool_t isOk = true;

			#include "grl.h"

			if(isOk == false)
			{
				continue;
			}
		}

		/**/

		for(int i = 0; i < n; i++)
		{
			if(l1_pt[i] < ET_MIN || l1_pt[i] > ET_MAX
			   ||
			   l2_pt[i] < ET_MIN || l2_pt[i] > ET_MAX
			   ||
			   fabs(l1_eta[i]) > 2.47f
			   ||
			   fabs(l2_eta[i]) > 2.47f
			 ) {
				continue;
			}

			if(bkgd != false && (l1_truthMatch[i] != false && l2_truthMatch[i] != false))
			{
				continue;
			}

			Float_t theWeight = weight[i];

			if(isMC != false)
			{
				/**/ if(RunNumber == 180164) {
					theWeight *= 1.06f * pileupReweightingBD->getPileupWeight(averageIntPerXing);
				}
				else if(RunNumber == 183003) {
					theWeight *= 1.08f * pileupReweightingEH->getPileupWeight(averageIntPerXing);
				}
				else if(RunNumber == 186169) {
					theWeight *= 0.87f * pileupReweightingIK->getPileupWeight(averageIntPerXing);
				}
				else if(RunNumber == 186275) {
					theWeight *= 1.03f * pileupReweightingLM->getPileupWeight(averageIntPerXing);
				}
				else
				{
					std::cout << "Oula !" << std::endl;

					continue;
				}

				if(theWeight < 0.0f)
				{
					std::cout << "Oula !" << std::endl;

					continue;
				}
			}

			if(RunNumber >= 177986 && RunNumber <= 178109) h.Fill(1, theWeight);
			if(RunNumber >= 179710 && RunNumber <= 180481) h.Fill(2, theWeight);
			if(RunNumber >= 180614 && RunNumber <= 180776) h.Fill(3, theWeight);
			if(RunNumber >= 182013 && RunNumber <= 182519) h.Fill(4, theWeight);
			if(RunNumber >= 182726 && RunNumber <= 183462) h.Fill(5, theWeight);
			if(RunNumber >= 183544 && RunNumber <= 184169) h.Fill(6, theWeight);
			if(RunNumber >= 185353 && RunNumber <= 186493) h.Fill(7, theWeight);
			if(RunNumber >= 186516 && RunNumber <= 186755) h.Fill(8, theWeight);
			if(RunNumber >= 186873 && RunNumber <= 187815) h.Fill(9, theWeight);
			if(RunNumber >= 188902 && RunNumber <= 190343) h.Fill(10, theWeight);
			if(RunNumber >= 190503 && RunNumber <= 191933) h.Fill(11, theWeight);
		}
	}

	/**/

	file->cd();

	h.Write();
}

/*-------------------------------------------------------------------------*/

