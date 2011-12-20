/*-------------------------------------------------------------------------*/

#include <RooPlot.h>
#include <RooAddPdf.h>
#include <RooRealVar.h>
#include <RooDataHist.h>

/*-------------------------------------------------------------------------*/

#include <RooCBShape.h>
#include <RooGaussian.h>
#include <RooChebychev.h>
#include <RooBreitWigner.h>

/*-------------------------------------------------------------------------*/

#include <iostream>

/*-------------------------------------------------------------------------*/

#include "atlasstyle-00-03-01/AtlasStyle.C"
#include "atlasstyle-00-03-01/AtlasLabels.C"
#include "atlasstyle-00-03-01/AtlasUtils.C"

/*-------------------------------------------------------------------------*/

using namespace RooFit;

/*-------------------------------------------------------------------------*/

Double_t __getSigma(RooAddPdf *pdf, RooRealVar *var, Double_t mean)
{
	Double_t Xs = 0.0;
	Double_t cIs = 0.0;
	Double_t intf2 = 0.68 * pdf->createIntegral(*var)->getVal();

	while(cIs < intf2 && Xs < 200.0)
	{
		Xs += 0.01;

		var->setRange(
			mean - Xs
			,
			mean + Xs
		);

		cIs = pdf->createIntegral(*var)->getVal();
	}

	return Xs;
}

/*-------------------------------------------------------------------------*/

Double_t __sum(TH1F *obj, Int_t min = 1, Int_t max = 20)
{
	return obj->Integral(min, max);
}

/*-------------------------------------------------------------------------*/

Double_t __normalized(TH1F *obj, Int_t min = 1, Int_t max = 20)
{
	Double_t integral = __sum(obj, min, max);

	for(int ibin = 0; ibin <= obj->GetNbinsX() + 1; ibin++)
	{
		Double_t a = obj->GetBinContent(ibin);

		obj->SetBinContent(ibin, a / integral);
		obj->SetBinError(ibin, sqrt(a / integral * (1 - a /integral) / integral));
	}

	return integral;
}

/*-------------------------------------------------------------------------*/

TH1F *__drawFrame(Double_t xmin, Double_t xmax, Double_t ymin, Double_t ymax, const char *title = "", const char *option = "")
{
	static Int_t cnt = 0;

	std::ostringstream oss;

	oss << "dummy" << cnt++;

	/**/

	TH1F *dummy = new TH1F(oss.str().c_str(), title, int(xmax - xmin), xmin, xmax);

	dummy->SetMinimum(ymin);
	dummy->SetMaximum(ymax);

	dummy->SetStats(kFALSE);
	dummy->Draw(option);

	return dummy;
}

/*-------------------------------------------------------------------------*/

TGraphErrors *GetGraphFromHisto(TH1F *h, Bool_t low = false, Float_t shift = 0.0f)
{
	Int_t i_point = 0;

	TGraphErrors *result = new TGraphErrors();

	for(Int_t i = 1, i_max = h->GetNbinsX(); i <= i_max; i++)
	{
		if((low != false || h->GetBinCenter(i) > 10.0) && h->GetBinContent(i) != 0.0)
		{
			result->SetPoint/***/(i_point, h->GetBinCenter(i), h->GetBinContent(i) + shift);
			result->SetPointError(i_point, 0x0000000000000000, h->GetBinError  (i) + 0.00f);

			i_point++;
		}
	}
	
	result->SetMarkerStyle(h->GetMarkerStyle());
	result->SetMarkerColor(h->GetMarkerColor());
	result->SetLineColor(h->GetLineColor());

	result->SetTitle(h->GetTitle());

	return result;
}

/*-------------------------------------------------------------------------*/

