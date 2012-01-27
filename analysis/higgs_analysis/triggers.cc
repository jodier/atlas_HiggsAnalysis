/*-------------------------------------------------------------------------*/

#include <TRandom3.h>

#include "main.h"

/*-------------------------------------------------------------------------*/

Bool_t isElectronMatched(Float_t eta, Float_t phi, Vector_t<int> *hypo, int track_n, Vector_t<float> *trig_eta, Vector_t<float> *trig_phi)
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

Bool_t isMuonMatched(Float_t eta, Float_t phi, Vector_t<int> *hypo, Vector_t<int> *track_n, Vector_t<Vector_t<float> > *trig_eta, Vector_t<Vector_t<float> > *trig_phi)
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

char getPeriod(int RunNumber)
{
	char result;

	/**/ if(RunNumber >= 177986 && RunNumber <= 178109) {
		result = 'B';
	}
	else if(RunNumber >= 178163 && RunNumber <= 178264) {
		result = 'C';
	}
	else if(RunNumber >= 179710 && RunNumber <= 180481) {
		result = 'D';
	}
	else if(RunNumber >= 180614 && RunNumber <= 180776) {
		result = 'E';
	}
	else if(RunNumber >= 182013 && RunNumber <= 182519) {
		result = 'F';
	}
	else if(RunNumber >= 182726 && RunNumber <= 183462) {
		result = 'G';
	}
	else if(RunNumber >= 183544 && RunNumber <= 184169) {
		result = 'H';
	}
	else if(RunNumber >= 185353 && RunNumber <= 186493) {
		result = 'I';
	}
	else if(RunNumber >= 186516 && RunNumber <= 186755) {
		result = 'J';
	}
	else if(RunNumber >= 186873 && RunNumber <= 187815) {
		result = 'K';
	}
	else if(RunNumber >= 188902 && RunNumber <= 190343) {
		result = 'L';
	}
	else if(RunNumber >= 190503 && RunNumber <= 191933) {
		result = 'M';
	}
	else
	{
		result = 0x0;
	}

	return result;
}

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::getElTrigger(void)
{
	Bool_t result = false;

	if(core::OF == false)
	{
#ifdef __IS_MC
		/**/ if(RunNumber == 180164 // B-D
			||
			RunNumber == 183003 // E-H
		 ) {
			result = EF_e20_medium || EF_2e12_medium;
		}
		else if(RunNumber == 186169) // I-K
		{
			TRandom3 random3;

			random3.SetSeed(mc_channel_number * EventNumber);

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
#else
		char period = getPeriod(RunNumber);

		/**/ if(period >= 'B' && period <= 'J') {
			result = EF_e20_medium || EF_2e12_medium;
		}
		else if(period >= 'K' && period <= 'K') {
			result = EF_e22_medium || EF_2e12T_medium;
		}
		else if(period >= 'L' && period <= 'M') {
			result = EF_e22vh_medium1 || EF_2e12Tvh_medium;
		}
#endif
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
	Bool_t result = false;

	if(core::OF == false)
	{
#ifdef __IS_MC
		/**/ if(RunNumber == 180164 // B-D
			||
			RunNumber == 183003 // E-H
		 ) {
			result = EF_mu18_MG || EF_2mu10_loose;
		}
		else if(RunNumber == 186169) // I-K
		{
			TRandom3 random3;

			random3.SetSeed(mc_channel_number * EventNumber);

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
#else
		char period = getPeriod(RunNumber);

		/**/ if(period >= 'B' && period <= 'I') {
			result = EF_mu18_MG || EF_2mu10_loose;
		}
		else if(period >= 'J' && period <= 'M') {
			result = EF_mu18_MG_medium || EF_2mu10_loose;
		}
#endif
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
	Bool_t result;

	switch(type)
	{
		case TYPE_ELECTRON:
			result = true;
			break;

		case TYPE_MUON_STACO:
			result = true;//isMuonMatched(mu_staco_eta->at(index), mu_staco_phi->at(index), trig_EF_trigmuonef_EF_mu18, trig_EF_trigmuonef_track_n, trig_EF_trigmuonef_track_CB_eta, trig_EF_trigmuonef_track_CB_phi);
			break;

		case TYPE_MUON_MUID:
			result = true;//isMuonMatched(mu_muid_eta->at(index) , mu_muid_phi->at(index) , trig_EF_trigmuonef_EF_mu18, trig_EF_trigmuonef_track_n, trig_EF_trigmuonef_track_CB_eta, trig_EF_trigmuonef_track_CB_phi);
			break;

		case TYPE_MUON_CALO:
			result = true;//isMuonMatched(mu_calo_eta->at(index) , mu_calo_phi->at(index) , trig_EF_trigmuonef_EF_mu18, trig_EF_trigmuonef_track_n, trig_EF_trigmuonef_track_CB_eta, trig_EF_trigmuonef_track_CB_phi);
			break;

		default:
			result = false;
	}

	return result;
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

