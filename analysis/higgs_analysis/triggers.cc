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

	Float_t the_dr = 000.0f;
	Float_t min_dr = 100.0f;

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

#define periodB		11.7377f
#define periodD		166.737f
#define periodE		48.8244f
#define periodF		142.575f
#define periodG		537.542f
#define periodH		259.459f
#define periodI		386.226f
#define periodJ		226.460f
#define periodK		600.069f
#define periodL		1401.87f
#define periodM		1025.62f

const Float_t fracEl = (periodI + periodJ) / (periodI + periodJ + periodK);
const Float_t fracMu = (periodI          ) / (periodI + periodJ + periodK);

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::getElTrigger(void)
{
	Bool_t result;

	if(core::OF == false)
	{
		result = false;

		if(core::isMC(RunNumber) != false)
		{
			/**/ if(RunNumber == 180164 // B-D
				||
				RunNumber == 183003 // E-H
			 ) {
				result = EF_e20_medium || EF_2e12_medium;
			}
			else if(RunNumber == 186169) // I-K
			{
				TRandom3 random3;
#ifdef __IS_MC
				random3.SetSeed(mc_channel_number * EventNumber);
#endif
				if(random3.Uniform() < fracEl) {
					result = EF_e20_medium || EF_2e12_medium;
				}
				else {
					result = EF_e22_medium || EF_2e12T_medium;
				}
			}
			else if(RunNumber == 186275) // L-M
			{
				result = EF_e22_medium1 || EF_2e12T_medium;
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
			/**/ if(RunNumber == 180164 // B-D
				||
				RunNumber == 183003 // E-H
			 ) {
				result = EF_mu18_MG || EF_2mu10_loose;
			}
			else if(RunNumber == 186169) // I-K
			{
				TRandom3 random3;
#ifdef __IS_MC
				random3.SetSeed(mc_channel_number * EventNumber);
#endif
				if(random3.Uniform() < fracMu) {
					result = EF_mu18_MG || EF_2mu10_loose;
				}
				else {
					result = EF_mu18_MG_medium || EF_2mu10_loose;
				}
			}
			else if(RunNumber == 186275) // L-M
			{
				result = EF_mu18_MG_medium || EF_2mu10_loose;
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

	return result;
}

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::triggerMatch(
	Int_t index,
	TLeptonType type
) {
	Vector_t<Int_t> *hypo;

	switch(type)
	{
		case TYPE_ELECTRON:
			for(Vector_t<unsigned>::iterator it = elVector.begin(); it != elVector.end(); it++)
			{
				switch(*it)
				{
					case 0xD4CD729C: /* EF_e20_medium */
						hypo = trig_EF_el_EF_e20_medium;
						goto __elOk;

					case 0xB784EC93: /* EF_e22_medium */
					case 0xADCD942C: /* EF_e22_medium1 */
					case 0x69EA9F52: /* EF_e22vh_medium1 */
						hypo = trig_EF_el_EF_e22_medium;
						goto __elOk;

					case 0xABF2CA73: /* EF_2e12_medium */
					case 0x80D5CCB8: /* EF_2e12T_medium */
					case 0xD84960ED: /* EF_2e12Tvh_medium */
						hypo = trig_EF_el_EF_2e12_medium;
						goto __elOk;

					__elOk:
						if(getIsElectronMatched(el_tracketa->at(index), el_trackphi->at(index), hypo, trig_EF_el_n, trig_EF_el_eta, trig_EF_el_phi) != false)
						{
							return true;
						}
				}
			}

			break;

		case TYPE_MUON_STACO:
			for(Vector_t<unsigned>::iterator it = muVector.begin(); it != muVector.end(); it++)
			{
				switch(*it)
				{
					case 0x0803E760: /* EF_mu18_MG */
					case 0x869B9356: /* EF_mu18_MG_medium */
						hypo = trig_EF_trigmuonef_EF_mu18;
						goto __muOkStaco;

					case 0xD92F4787: /* EF_2mu10_loose */
						hypo = trig_EF_trigmuonef_EF_2mu10;
						goto __muOkStaco;

					__muOkStaco:
						if(getIsMuonMatched(mu_staco_eta->at(index), mu_staco_phi->at(index), hypo, trig_EF_trigmuonef_track_n, trig_EF_trigmuonef_track_CB_eta, trig_EF_trigmuonef_track_CB_phi) != false)
						{
							return true;
						}
				}
			}

			break;

		case TYPE_MUON_MUID:
			for(Vector_t<unsigned>::iterator it = muVector.begin(); it != muVector.end(); it++)
			{
				switch(*it)
				{
					case 0x0803E760: /* EF_mu18_MG */
					case 0x869B9356: /* EF_mu18_MG_medium */
						hypo = trig_EF_trigmuonef_EF_mu18;
						goto __muOkMuid;

					case 0xD92F4787: /* EF_2mu10_loose */
						hypo = trig_EF_trigmuonef_EF_2mu10;
						goto __muOkMuid;

					__muOkMuid:
						if(getIsMuonMatched(mu_muid_eta->at(index), mu_muid_phi->at(index), hypo, trig_EF_trigmuonef_track_n, trig_EF_trigmuonef_track_CB_eta, trig_EF_trigmuonef_track_CB_phi) != false)
						{
							return true;
						}
				}
			}

			break;

		case TYPE_MUON_CALO:
			for(Vector_t<unsigned>::iterator it = muVector.begin(); it != muVector.end(); it++)
			{
				switch(*it)
				{
					case 0x0803E760: /* EF_mu18_MG */
					case 0x869B9356: /* EF_mu18_MG_medium */
						hypo = trig_EF_trigmuonef_EF_mu18;
						goto __muOkCalo;

					case 0xD92F4787: /* EF_2mu10_loose */
						hypo = trig_EF_trigmuonef_EF_2mu10;
						goto __muOkCalo;

					__muOkCalo:
						if(getIsMuonMatched(mu_calo_eta->at(index), mu_calo_phi->at(index), hypo, trig_EF_trigmuonef_track_n, trig_EF_trigmuonef_track_CB_eta, trig_EF_trigmuonef_track_CB_phi) != false)
						{
							return true;
						}
				}
			}

			break;
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

