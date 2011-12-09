/*-------------------------------------------------------------------------*/

#include <cmath>
#include <sstream>
#include <iostream>

#include <time.h>
#include <TRandom3.h>

#include "main.h"

/*-------------------------------------------------------------------------*/

static unsigned hash(const char *key)
{
	unsigned hash = 0;

	for(unsigned i = 0; i < strlen(key); i++)
	{
		hash +=     key[i]    ;
		hash += (hash << 0x0A);
		hash ^= (hash >> 0x06);
	}

	hash += (hash << 0x03);
	hash ^= (hash >> 0x0B);
	hash += (hash << 0x0F);

	return hash;
}

/*-------------------------------------------------------------------------*/

static Vector_t<unsigned> elVector;
static Vector_t<unsigned> muVector;

/*-------------------------------------------------------------------------*/

void TLeptonAnalysis::initTriggers(void)
{
	elVector.clear();
	muVector.clear();

	std::string element;

	std::stringstream ss1(core::configStrLookup("EL_EF_TRIGGER"));
	std::stringstream ss2(core::configStrLookup("MU_EF_TRIGGER"));

	/*-----------------------------------------------------------------*/
	/* ELECTRONS							   */
	/*-----------------------------------------------------------------*/

	std::cout << "El trigger(s): ";

	while(std::getline(ss1, element, '|'))
	{
		std::cout << "\033[32m" << element << "\033[0m, ";

		elVector.push_back(
			hash(element.c_str())
		);
	}

	std::cout << "Ø" << std::endl;

	/*-----------------------------------------------------------------*/
	/* MUONS							   */
	/*-----------------------------------------------------------------*/

	std::cout << "Mu trigger(s): ";

	while(std::getline(ss2, element, '|'))
	{
		std::cout << "\033[32m" << element << "\033[0m, ";

		muVector.push_back(
			hash(element.c_str())
		);
	}

	std::cout << "Ø" << std::endl;

	/*-----------------------------------------------------------------*/
}

/*-------------------------------------------------------------------------*/

Bool_t getIsElectronMatched(Float_t eta, Float_t phi, Vector_t<int> *hypo, int track_n, Vector_t<float> *trig_eta, Vector_t<float> *trig_phi)
{
	if(hypo == NULL
	   ||
	   trig_eta == NULL
	   ||
	   trig_phi == NULL
	 ) {
		return false;
	}

	Int_t foo;

	return PassedTriggerEF(eta, phi, hypo, foo, track_n, trig_eta, trig_phi);
}

/*-------------------------------------------------------------------------*/

Bool_t getIsMuonMatched(Float_t eta, Float_t phi, Vector_t<int> *hypo, Vector_t<int> *track_n, Vector_t<Vector_t<float> > *trig_eta, Vector_t<Vector_t<float> > *trig_phi)
{
	if(hypo == NULL
	   ||
	   track_n == NULL
	   ||
	   trig_eta == NULL
	   ||
	   trig_phi == NULL
	 ) {
		return false;
	}

	Float_t the_dr;
	Float_t min_dr = 100;

	for(UInt_t i = 0; i < hypo->size(); i++)
	{
		if(hypo->at(i) == 1)
		{
			for(Int_t j = 0; j < track_n->at(i); j++)
			{
				the_dr = sqrtf(__dR2(trig_eta->at(i).at(j), eta, trig_phi->at(i).at(j), phi));

				if(min_dr > the_dr)
				{
					min_dr = the_dr;
				}
			}
		}
	}

	return min_dr < 0.05f;
}

/*-------------------------------------------------------------------------*/

#define periodB 16.7121f
#define periodD 178.132f
#define periodE 49.9275f
#define periodF 151.251f
#define periodG 558.218f
#define periodH 277.340f
#define periodI 399.206f
#define periodJ 232.931f
#define periodK 660.211f
#define periodL 1540.28f
#define periodM 960.327f

const Float_t frac1 = (     periodI     ) / (periodI + periodJ + periodK);
const Float_t frac2 = (periodI + periodJ) / (periodI + periodJ + periodK);

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::getElTrigger(void)
{
	Bool_t result;

	if(core::OF == false)
	{
		result = false;

		if(core::isMC(RunNumber) != false)
		{
			TRandom3 random3;

			random3.SetSeed(time(NULL));

			if(random3.Uniform() < frac2) {
				result = EF_e20_medium || EF_2e12_medium;
			}
			else {
				result = EF_e22_medium || EF_2e12T_medium;
			}
		}
		else for(Vector_t<unsigned>::iterator it = elVector.begin(); it != elVector.end(); it++)
		{
			switch(*it)
			{
				case 0xD4CD729C: /* EF_e20_medium */
					if(EF_e20_medium != false) {
						return true;
					}
					break;

				case 0xB784EC93: /* EF_e22_medium */
					if(EF_e22_medium != false) {
						return true;
					}
					break;

				case 0xADCD942C: /* EF_e22_medium1 */
					if(EF_e22_medium1 != false) {
						return true;
					}
					break;

				case 0x69EA9F52: /* EF_e22vh_medium1 */
					if(EF_e22vh_medium1 != false) {
						return true;
					}
					break;

				case 0xABF2CA73: /* EF_2e12_medium */
					if(EF_2e12_medium != false) {
						return true;
					}
					break;

				case 0x80D5CCB8: /* EF_2e12T_medium */
					if(EF_2e12T_medium != false) {
						return true;
					}
					break;

				case 0xD84960ED: /* EF_2e12Tvh_medium */
					if(EF_2e12Tvh_medium != false) {
						return true;
					}
					break;
			}
		}
	}
	else
	{
		result = true;
	}

	return result;
}

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::getMuTrigger(void)
{
	Bool_t result;

	if(core::OF == false)
	{
		result = false;

		if(core::isMC(RunNumber) != false)
		{
			TRandom3 random3;

			random3.SetSeed(time(NULL));

			if(random3.Uniform() < frac1) {
				result = EF_mu18_MG;
			}
			else {
				result = EF_mu18_MG_medium;
			}
		}
		else for(Vector_t<unsigned>::iterator it = muVector.begin(); it != muVector.end(); it++)
		{
			switch(*it)
			{
				case 0x0803E760: /* EF_mu18_MG */
					if(EF_mu18_MG != false) {
						return true;
					}
					break;

				case 0x869B9356: /* EF_mu18_MG_medium */
					if(EF_mu18_MG_medium != false) {
						return true;
					}
					break;

				case 0xD92F4787: /* EF_2mu10_loose */
					if(EF_2mu10_loose != false) {
						return true;
					}
					break;
			}
		}
	}
	else
	{
		result = true;
	}

	return false;
}

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::triggerMatch(
	Int_t index,
	TLeptonType type
) {
	Int_t EF_idx;
	Vector_t<Int_t> *hypo;

	switch(type)
	{
		case TYPE_ELECTRON:
			EF_idx = el_EF_index->at(index);
			goto __el;

		case TYPE_MUON_STACO:
			EF_idx = mu_staco_EFCB_index->at(index);
			goto __mu;

		case TYPE_MUON_MUID:
			EF_idx = mu_muid_EFCB_index->at(index);
			goto __mu;

		__el:
			for(Vector_t<unsigned>::iterator it = elVector.begin(); it != elVector.end(); it++)
			{
				switch(*it)
				{
					case 0xD4CD729C: /* EF_e20_medium */
						if(EF_e20_medium != false)
						{
							hypo = trig_EF_el_EF_e20_medium;
							goto __elOk;
						}
						break;

					case 0xB784EC93: /* EF_e22_medium */
					case 0xADCD942C: /* EF_e22_medium1 */
					case 0x69EA9F52: /* EF_e22vh_medium1 */
						if(EF_e22_medium != false
						   ||
						   EF_e22_medium1 != false
						   ||
						   EF_e22vh_medium1 != false
						 ) {
							hypo = trig_EF_el_EF_e22_medium;
							goto __elOk;
						}
						break;

					case 0xABF2CA73: /* EF_2e12_medium */
					case 0x80D5CCB8: /* EF_2e12T_medium */
					case 0xD84960ED: /* EF_2e12Tvh_medium */
						if(EF_2e12_medium != false
						   ||
						   EF_2e12T_medium != false
						   ||
						   EF_2e12Tvh_medium != false
						 ) {
							hypo = trig_EF_el_EF_2e12_medium;
							goto __elOk;
						}
						break;

					__elOk:
						if(getIsElectronMatched(el_tracketa->at(index), el_trackphi->at(index), hypo, trig_EF_el_n, trig_EF_el_eta, trig_EF_el_phi) != false)
						{
							return true;
						}
				}
			}

			break;

		__mu:
			/* TODO */
			/* TODO */
			/* TODO */
			/* TODO */

			return true;
	}

	return false;
}

/*-------------------------------------------------------------------------*/

Int_t TLeptonAnalysis::triggerTrace(UInt_t result[])
{
	Int_t nr = 0;

	if(core::OF != false)
	{
		if(EF_e20_medium != 0) {
			result[nr++] = 0xD4CD729C;
		}

		if(EF_e22_medium != 0) {
			result[nr++] = 0xB784EC93;
		}

		if(EF_e22_medium1 != 0) {
			result[nr++] = 0xADCD942C;
		}

		if(EF_e22vh_medium1 != 0) {
			result[nr++] = 0x69EA9F52;
		}

		if(EF_2e12_medium != 0) {
			result[nr++] = 0xF48A09FA;
		}

		if(EF_2e12T_medium != 0) {
			result[nr++] = 0x80D5CCB8;
		}

		if(EF_2e12Tvh_medium != 0) {
			result[nr++] = 0xD84960ED;
		}

		if(EF_mu18_MG != 0) {
			result[nr++] = 0x0803E760;
		}

		if(EF_mu18_MG_medium != 0) {
			result[nr++] = 0x869B9356;
		}

		if(EF_2mu10_loose != 0) {
			result[nr++] = 0xD92F4787;
		}
	}

	return nr;
}

/*-------------------------------------------------------------------------*/

