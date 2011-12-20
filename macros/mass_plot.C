/*-------------------------------------------------------------------------*/

#include "utils.C"

/*-------------------------------------------------------------------------*/

using namespace RooFit;

/*-------------------------------------------------------------------------*/

#define MASS_CENTER	90.2f
#define MASS_WINDOW	10.0f

#define SIG_LW		(MASS_CENTER - MASS_WINDOW)
#define SIG_UP		(MASS_CENTER + MASS_WINDOW)

#define FIT_LW		48.0f
#define FIT_UP		130.0f

/*-------------------------------------------------------------------------*/

RooPlot *__fit(TH1F *h)
{
	/*------------------------------------*/
	/* SIDE BAND			      */
	/*------------------------------------*/

	Int_t binLw = h->FindBin(SIG_LW + 0.1f);
	Int_t binUp = h->FindBin(SIG_UP - 0.1f);

	Int_t bin60  = h->FindBin(60.0f + 0.1f);
	Int_t bin120 = h->FindBin(120.0f - 0.1f);

	Float_t alpha = (SIG_UP - SIG_LW) / ((SIG_LW - 60.0f) + (120.0f - SIG_UP));

	Float_t evtNr0 = h->Integral(binLw, binUp);

	Float_t bkgNr0 = alpha * (h->Integral(bin60, binLw - 1) + h->Integral(binUp + 1, bin120)), sigNr0 = evtNr0 - bkgNr0;

	/*------------------------------------*/
	/* X				      */
	/*------------------------------------*/

	RooRealVar X("X", "m_{ee} [GeV]", FIT_LW, FIT_UP);

	X.setBins(10000, "cache");
	X.setRange("peakRange", SIG_LW, SIG_UP);

	/*------------------------------------*/
	/* Crystal Ball			      */
	/*------------------------------------*/

	RooRealVar mass1("mass1", "mass1", 0.0, -5.0, +5.0);
	RooRealVar sigma1("sigma1", "sigma1", 3.5, 1.0, 10.0);
	RooRealVar a("a", "a", 1.0, 0.0, 5.0);
	RooRealVar n("n", "n", 4.0, 0.0, 20.0);

	RooCBShape CB("CB", "CB", X, mass1, sigma1, a, n);

	/*------------------------------------*/
	/* Breit & Wigner		      */
	/*------------------------------------*/

	RooBreitWigner BW("BW", "BW", X, RooRealConstant::value(MASS_CENTER), RooRealConstant::value(2.5));

	/*------------------------------------*/
	/* Breit & Wigner (x) Crystal Ball    */
	/*------------------------------------*/

	RooFFTConvPdf CBBW("CBBW", "CB (x) BW", X, BW, CB);

	CBBW.setBufferFraction(0.2);

	/*------------------------------------*/
	/* Background			      */
	/*------------------------------------*/

	RooRealVar tau("tau", "tau", -0.01, -1.0, 0.0);

	RooExponential BKGD("BKGD", "BKGD", X, tau);

	/*------------------------------------*/
	/* Signal			      */
	/*------------------------------------*/

	RooRealVar rooNSig("n_sig", "n_sig", sigNr0, 0.0, evtNr0);
	RooRealVar rooNBkg("n_bkg", "n_bkg", bkgNr0, 0.0, evtNr0);

	RooExtendPdf sigPdf("sig_pdf", "sig_pdf", CBBW, rooNSig, "peakRange");
	RooExtendPdf bkgPdf("bkg_pdf", "bkg_pdf", BKGD, rooNBkg, "peakRange");

	RooAddPdf fitPdf("fit_pdf", "fit_pdf", RooArgList(sigPdf, bkgPdf));

	/*-----------------------------------------------------------------*/
	/* Frame							   */
	/*-----------------------------------------------------------------*/

	RooPlot *frame = X.frame(Title("CB (x) BW"));

	/*------------------------------------*/
	/* Import & Fit			      */
	/*------------------------------------*/

	RooDataHist import("import", "import", X, RooFit::Import(*h));

	import.plotOn(frame, RooFit::Name("chi2_1"));
	fitPdf.fitTo(import, RooFit::Extended(kTRUE), RooFit::SumW2Error(kFALSE), RooFit::Save(kTRUE));
	fitPdf.plotOn(frame, RooFit::Name("chi2_2"));

	fitPdf.plotOn(frame, Components(RooArgSet(bkgPdf)), LineStyle(kDashed));

	printf("sigNr0: %.1f, bkgNr0: %.1f, evtNr0: %.1f\n", sigNr0, bkgNr0, sigNr0 + bkgNr0);
	printf("sigNr : %.1f, bkgNr : %.1f, evtNr : %.1f\n", rooNSig.getVal(), rooNBkg.getVal(), rooNSig.getVal() + rooNBkg.getVal());
	printf("sigErr: %.1f, bkgErr: %.1f\n", rooNSig.getError(), rooNBkg.getError());

	/*-----------------------------------------------------------------*/

	char buffer1[256];

	sprintf(buffer1, "<m_{ee}>: %.2f #pm %.1e", MASS_CENTER + mass1.getVal(), mass1.getError());

	TLatex *label1 = new TLatex(92.0, 220000.0, buffer1);

	label1->Draw();

	/*-----------------------------------------------------------------*/

	return frame;
}

/*-------------------------------------------------------------------------*/

void mass_plot(void)
{
	SetAtlasStyle();

	/*-----------------------------------------------------------------*/

	TFile *file = new TFile("../mass.root");

	TH1F *h1 = (TH1F *) file->Get("data");
	TH1F *h2 = (TH1F *) file->Get("mc");
	TH1F *h3 = (TH1F *) file->Get("bkgd");

	/*-----------------------------------------------------------------*/

	Float_t norme = h1->GetEntries();

	/*-----------------------------------------------------------------*/

	h2->Scale(norme / h2->GetEntries());
	h3->Scale(norme / h2->GetEntries());

	h3->SetFillColor(kGreen + 1);
	h3->SetLineColor(kGreen + 1);

	/*-----------------------------------------------------------------*/

	TH1F *__frame = __drawFrame(60.0, 115.0, 0.0, 220000.0);
	__frame->SetXTitle("m_{ee} [GeV]");
	__frame->SetYTitle("Events / ( 1 GeV )");

	__frame->Draw();

	__fit(h1)->Draw("same");
//	h1->Draw("same");
	h2->Draw("same");
	h3->Draw("same");

	/*-----------------------------------------------------------------*/

	ATLASLabel2(0.2, 0.875, true, kBlack);

	/*-----------------------------------------------------------------*/

	gPad->Print("mass.pdf");
	gPad->Print("mass.eps");
}

