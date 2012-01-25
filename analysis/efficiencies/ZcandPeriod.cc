/*-------------------------------------------------------------------------*/

#include <cmath>
#include <fstream>
#include <iostream>

#include <TH1.h>

/*-------------------------------------------------------------------------*/

#define ZStudy_cxx
#include "ZStudy.h"

#include "../../tools/PileupReweighting/PileupReweighting/TPileupReweighting.h"

static bool isMC = false;
static const char *DataType = "";

TFile *file;

/*-------------------------------------------------------------------------*/

#define ET_MIN		20.0f		/* GeV */
#define ET_MAX		9000.0f		/* GeV */
#define MASS_CENTER	91.1876f	/* GeV */
#define MASS_WINDOW	15.0f		/* GeV */

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
	if(argc != 8)
	{
		std::cerr << argv[0] << " mc0.txt mc1.txt mc2.txt mc3.txt mc4.txt mc5.txt data.txt" << std::endl;
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
	TChain *chain3 = new TChain("Z1");
	TChain *chain4 = new TChain("Z1");
	TChain *chain5 = new TChain("Z1");
	TChain *chain6 = new TChain("Z1");
	TChain *chain7 = new TChain("Z1");

	if(localLoader(chain1, argv[1]) == false
	   ||
	   localLoader(chain2, argv[2]) == false
	   ||
	   localLoader(chain3, argv[3]) == false
	   ||
	   localLoader(chain4, argv[4]) == false
	   ||
	   localLoader(chain5, argv[5]) == false
	   ||
	   localLoader(chain6, argv[6]) == false
	   ||
	   localLoader(chain7, argv[7]) == false
	 ) {
		delete chain1;
		delete chain2;
		delete chain3;
		delete chain4;
		delete chain5;
		delete chain6;
		delete chain7;

		delete pileupReweightingBD;
		delete pileupReweightingEH;
		delete pileupReweightingIK;
		delete pileupReweightingLM;

		return 1;
	}

	ZStudy alg1(chain1); //MC
	ZStudy alg2(chain2); //MC
	ZStudy alg3(chain3); //MC
	ZStudy alg4(chain4); //MC
	ZStudy alg5(chain5); //MC
	ZStudy alg6(chain6); //MC
	ZStudy alg7(chain7); //DATA

	file = new TFile("ZcandPeriod.root", "recreate");

	if(file != NULL)
	{
		isMC = true;

		DataType = "mc0";
		alg1.Loop();
		std::cout << std::endl;

		DataType = "mc1";
		alg2.Loop();
		std::cout << std::endl;

		DataType = "mc2";
		alg3.Loop();
		std::cout << std::endl;

		DataType = "mc3";
		alg4.Loop();
		std::cout << std::endl;

		DataType = "mc4";
		alg5.Loop();
		std::cout << std::endl;

		DataType = "mc5";
		alg6.Loop();
		std::cout << std::endl;

		isMC = false;

		DataType = "data";
		alg7.Loop();
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

	TH1D h(DataType, DataType, 11, 1, 12);

	/**/

	Long64_t eventNr = fChain->GetEntries();

	/**/

	Long64_t ZCand[11] = {0,0,0,0,0,0,0,0,0,0,0};

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
			   fabs(Z_m[i] - MASS_CENTER) > MASS_WINDOW
			 ) {
				continue;
			}

			//if(bkgd != false && (l1_truthMatch[i] != false && l2_truthMatch[i] != false))
			//{
			//	continue;
			//}

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

			if(isMC != false)
			{
				/**/ if(RunNumber == 180164)
				{
					h.Fill(1, theWeight);
					h.Fill(2, theWeight);
				}
				else if(RunNumber == 183003)
				{
					h.Fill(3, theWeight);
					h.Fill(4, theWeight);
					h.Fill(5, theWeight);
					h.Fill(6, theWeight);
				}
				else if(RunNumber == 186169)
				{
					h.Fill(7, theWeight);
					h.Fill(8, theWeight);
					h.Fill(9, theWeight);
				}
				else if(RunNumber == 186275)
				{
					h.Fill(10, theWeight);
					h.Fill(11, theWeight);
				}
			}
			else
			{
				/**/ if(RunNumber >= 177986 && RunNumber <= 178109) { h.Fill(1, theWeight); ZCand[0]++;}
				else if(RunNumber >= 179710 && RunNumber <= 180481) { h.Fill(2, theWeight); ZCand[1]++;}
				else if(RunNumber >= 180614 && RunNumber <= 180776) { h.Fill(3, theWeight); ZCand[2]++;}
				else if(RunNumber >= 182013 && RunNumber <= 182519) { h.Fill(4, theWeight); ZCand[3]++;}
				else if(RunNumber >= 182726 && RunNumber <= 183462) { h.Fill(5, theWeight); ZCand[4]++;}
				else if(RunNumber >= 183544 && RunNumber <= 184169) { h.Fill(6, theWeight); ZCand[5]++;}
				else if(RunNumber >= 185353 && RunNumber <= 186493) { h.Fill(7, theWeight); ZCand[6]++;}
				else if(RunNumber >= 186516 && RunNumber <= 186755) { h.Fill(8, theWeight); ZCand[7]++;}
				else if(RunNumber >= 186873 && RunNumber <= 187815) { h.Fill(9, theWeight); ZCand[8]++;}
				else if(RunNumber >= 188902 && RunNumber <= 190343) { h.Fill(10, theWeight); ZCand[9]++;}
				else if(RunNumber >= 190503 && RunNumber <= 191933) { h.Fill(11, theWeight); ZCand[10]++;}
			}
		}
	}

	/**/

	file->cd();

	h.Write();

//	std::cout  << "****************" << std::endl;
//	std::cout  << "Z period B :" << ZCand[0] << std::endl;
//	std::cout  << "Z period D :" << ZCand[1] << std::endl;
//	std::cout  << "Z period E :" << ZCand[2] << std::endl;
//	std::cout  << "Z period F :" << ZCand[3] << std::endl;
//	std::cout  << "Z period G :" << ZCand[4] << std::endl;
//	std::cout  << "Z period H :" << ZCand[5] << std::endl;
//	std::cout  << "Z period I :" << ZCand[6] << std::endl;
//	std::cout  << "Z period J :" << ZCand[7] << std::endl;
//	std::cout  << "Z period K :" << ZCand[8] << std::endl;
//	std::cout  << "Z period L :" << ZCand[9] << std::endl;
//	std::cout  << "Z period M :" << ZCand[10] << std::endl;


}

/*-------------------------------------------------------------------------*/

