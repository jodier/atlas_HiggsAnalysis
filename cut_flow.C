/*-------------------------------------------------------------------------*/

Double_t myBinomialError(Double_t yes_probe, Double_t all_probe)
{
	Double_t error = TMath::Sqrt(
		TMath::Beta(yes_probe + 3, all_probe - yes_probe + 1)
		/
		TMath::Beta(yes_probe + 1, all_probe - yes_probe + 1)
		-
		TMath::Power(
			TMath::Beta(yes_probe + 2, all_probe - yes_probe + 1)
			/
			TMath::Beta(yes_probe + 1, all_probe - yes_probe + 1)
		, 2.0)
	);

	if(TMath::IsNaN(error) != false)
	{
		Double_t eff = yes_probe / all_probe;

		error = TMath::Sqrt(eff * (1.0 - eff) / all_probe);
	}

	return error;
}

/*-------------------------------------------------------------------------*/

bool localLoader(TChain *chain, const char *fname, bool verbose = false)
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
		if(verbose != false)
		{
			std::cout << "Reading: " << fName.c_str() << "..." << std::endl;
		}

		chain->AddFile(fName.c_str());
	}

	/**/

	stream.close();

	return true;
}

/*-------------------------------------------------------------------------*/

void print(const char *name, const char *fname, const char *title, int chanel)
{
	TChain *chain0 = new TChain("Truth");
	TChain *chain1 = new TChain("Event");
	TChain *chain2 = new TChain(  name );

	if(localLoader(chain0, fname, true) == false
	   ||
	   localLoader(chain1, fname, false) == false
	   ||
	   localLoader(chain2, fname, false) == false
	 ) {
		return;
	}

	std::cout << "\033[36m";
	std::cout << "/*-------------------------------------------------------------------------*/" << std::endl;
	std::cout << title << std::endl;
	std::cout << "/*-------------------------------------------------------------------------*/" << std::endl;
	std::cout << "\033[0m";

	Float_t n = chain1->GetEntries();

	Int_t eeee_nr;
	Int_t uuuu_nr;
	Int_t eeuu_nr;
	TBranch *b_eeee_nr;
	TBranch *b_uuuu_nr;
	TBranch *b_eeuu_nr;
	chain0->SetBranchAddress("eeee_nr", &eeee_nr, &b_eeee_nr);
	chain0->SetBranchAddress("uuuu_nr", &uuuu_nr, &b_uuuu_nr);
	chain0->SetBranchAddress("eeuu_nr", &eeuu_nr, &b_eeuu_nr);

	chain0->GetEntry(0);

	Float_t cnt0 = chain2->Draw("cnt0", "cnt0>0");
	Float_t cnt1 = chain2->Draw("cnt1", "cnt1>0");
	Float_t cnt2 = chain2->Draw("cnt2", "cnt2>0");
	Float_t cnt3 = chain2->Draw("cnt3", "cnt3>0");
	Float_t cnt4 = chain2->Draw("cnt4", "cnt4>0");
	Float_t cnt5 = chain2->Draw("cnt5", "cnt5>0");
	Float_t cnt6_eeuu = chain2->Draw("cnt6_eeuu", "cnt6_eeuu>0");
	Float_t cnt6_uuee = chain2->Draw("cnt6_uuee", "cnt6_uuee>0");
	Float_t cnt7_eeuu = chain2->Draw("cnt7_eeuu", "cnt7_eeuu>0");
	Float_t cnt7_uuee = chain2->Draw("cnt7_uuee", "cnt7_uuee>0");
	Float_t cnt8_eeuu = chain2->Draw("cnt8_eeuu", "cnt8_eeuu>0");
	Float_t cnt8_uuee = chain2->Draw("cnt8_uuee", "cnt8_uuee>0");
	Float_t cnt9_eeuu = chain2->Draw("cnt9_eeuu", "cnt9_eeuu>0");
	Float_t cnt9_uuee = chain2->Draw("cnt9_uuee", "cnt9_uuee>0");

	printf("0 - 4 leptons\t%.0f - %.2f\% ± %.2f\%\n", cnt0, 100.0f * cnt0 / n, 100.0f * myBinomialError(cnt0, n));
	printf("1 - DILS/SFOS\t%.0f - %.2f\% ± %.2f\%\n", cnt1, 100.0f * cnt1 / cnt0, 100.0f * myBinomialError(cnt1, cnt0));
	printf("2 - Kin.\t%.0f - %.2f\% ± %.2f\%\n", cnt2, 100.0f * cnt2 / cnt1, 100.0f * myBinomialError(cnt2, cnt1));
	printf("3 - Z1\t\t%.0f - %.2f\% ± %.2f\%\n", cnt3, 100.0f * cnt3 / cnt2, 100.0f * myBinomialError(cnt3, cnt2));
	printf("4 - Z2\t\t%.0f - %.2f\% ± %.2f\%\n", cnt4, 100.0f * cnt4 / cnt3, 100.0f * myBinomialError(cnt4, cnt3));
	printf("5 - min[ΔR]\t%.0f - %.2f\% ± %.2f\%\n", cnt5, 100.0f * cnt5 / cnt4, 100.0f * myBinomialError(cnt5, cnt4));

	/**/ if(chanel == 1)
	{
		Float_t cnt6 = cnt6_eeuu + cnt6_uuee;
		Float_t cnt7 = cnt7_eeuu + cnt7_uuee;
		Float_t cnt8 = cnt8_eeuu + cnt8_uuee;
		Float_t cnt9 = cnt9_eeuu + cnt9_uuee;

		printf("6 - One quad\t%.0f - %.2f\% ± %.2f\%\n", cnt6, 100.0f * cnt6 / cnt5, 100.0f * myBinomialError(cnt6, cnt5));
		printf("7 - Track iso.\t%.0f - %.2f\% ± %.2f\%\n", cnt7, 100.0f * cnt7 / cnt6, 100.0f * myBinomialError(cnt7, cnt6));
		printf("8 - Calo iso.\t%.0f - %.2f\% ± %.2f\%\n", cnt8, 100.0f * cnt8 / cnt7, 100.0f * myBinomialError(cnt8, cnt7));
		printf("9 - d0sigd0\t%.0f - %.2f\% ± %.2f\%\n", cnt9, 100.0f * cnt9 / cnt8, 100.0f * myBinomialError(cnt9, cnt8));

		printf("\033[32mε = %.2f\% ± %.2f\%\033[0m\n", 100.0f * cnt9 / eeee_nr, 100.0f * myBinomialError(cnt9, eeee_nr));
	}
	else if(chanel == 2)
	{
		Float_t cnt6 = cnt6_eeuu + cnt6_uuee;
		Float_t cnt7 = cnt7_eeuu + cnt7_uuee;
		Float_t cnt8 = cnt8_eeuu + cnt8_uuee;
		Float_t cnt9 = cnt9_eeuu + cnt9_uuee;

		printf("6 - One quad\t%.0f - %.2f\% ± %.2f\%\n", cnt6, 100.0f * cnt6 / cnt5, 100.0f * myBinomialError(cnt6, cnt5));
		printf("7 - Track iso.\t%.0f - %.2f\% ± %.2f\%\n", cnt7, 100.0f * cnt7 / cnt6, 100.0f * myBinomialError(cnt7, cnt6));
		printf("8 - Calo iso.\t%.0f - %.2f\% ± %.2f\%\n", cnt8, 100.0f * cnt8 / cnt7, 100.0f * myBinomialError(cnt8, cnt7));
		printf("9 - d0sigd0\t%.0f - %.2f\% ± %.2f\%\n", cnt9, 100.0f * cnt9 / cnt8, 100.0f * myBinomialError(cnt9, cnt8));

		printf("\033[32mε = %.2f\% ± %.2f\%\033[0m\n", 100.0f * cnt9 / uuuu_nr, 100.0f * myBinomialError(cnt9, uuuu_nr));
	}
	else if(chanel == 3)
	{
		Float_t cnt9 = cnt9_eeuu + cnt9_uuee;

		printf("6 - One quad\t%.0f|%.0f - %.2f|%.2f\% ± %.2f|%.2f\%\n", cnt6_eeuu, cnt6_uuee, 100.0f * cnt6_eeuu / cnt6_eeuu, 100.0f * cnt6_uuee / cnt6_uuee, 100.0f * myBinomialError(cnt6_eeuu, cnt6_eeuu), 100.0f * myBinomialError(cnt6_uuee, cnt6_uuee));
		printf("7 - Track iso.\t%.0f|%.0f - %.2f|%.2f\% ± %.2f|%.2f\%\n", cnt7_eeuu, cnt7_uuee, 100.0f * cnt7_eeuu / cnt6_eeuu, 100.0f * cnt7_uuee / cnt6_uuee, 100.0f * myBinomialError(cnt7_eeuu, cnt6_eeuu), 100.0f * myBinomialError(cnt7_uuee, cnt6_uuee));
		printf("8 - Calo iso.\t%.0f|%.0f - %.2f|%.2f\% ± %.2f|%.2f\%\n", cnt8_eeuu, cnt8_uuee, 100.0f * cnt8_eeuu / cnt7_eeuu, 100.0f * cnt8_uuee / cnt7_uuee, 100.0f * myBinomialError(cnt8_eeuu, cnt7_eeuu), 100.0f * myBinomialError(cnt8_uuee, cnt7_uuee));
		printf("9 - d0sigd0\t%.0f|%.0f - %.2f|%.2f\% ± %.2f|%.2f\%\n", cnt9_eeuu, cnt9_uuee, 100.0f * cnt9_eeuu / cnt8_eeuu, 100.0f * cnt9_uuee / cnt8_uuee, 100.0f * myBinomialError(cnt9_eeuu, cnt8_eeuu), 100.0f * myBinomialError(cnt9_uuee, cnt8_uuee));

		printf("\033[32mε = %.2f\% ± %.2f\%\033[0m\n", 100.0f * cnt9 / eeuu_nr, 100.0f * myBinomialError(cnt9, eeuu_nr));
	}

	/**/

//	chain2->Scan("RunNumber:EventNumber:LumiBlock", "RunNumber>=0&&EventNumber>=0&&LumiBlock>=0&&flag==0x3FF&&good!=0");
}

/*-------------------------------------------------------------------------*/

void cut_flow(void)
{
	TCanvas c1;

	const char *fname = "./yok2.txt";

	print("H1", fname, "H->eeee (STACO)", 1);
//	print("H1", fname, "H->eeee (MUID)", 1);
	print("H3", fname, "H->µµµµ (STACO)", 2);
	print("H4", fname, "H->µµµµ (MUID)", 2);
	print("H5", fname, "H->eeµµ|µµee (STACO)", 3);
	print("H6", fname, "H->eeµµ|µµee (MUID)", 3);
}

/*-------------------------------------------------------------------------*/

