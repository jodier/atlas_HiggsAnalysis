/*-------------------------------------------------------------------------*/

#include <TRandom3.h>

#include "main.h"

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::isElectronMatched(Float_t eta, Float_t phi, Vector_t<int> *hypo)
{
	if(hypo == NULL)
	{
		return false;
	}

	Int_t EFindex;

	return PassedTriggerEF(eta, phi, hypo, EFindex, trig_EF_el_n, trig_EF_el_eta, trig_EF_el_phi);
}

/*-------------------------------------------------------------------------*/

Bool_t TLeptonAnalysis::isMuonMatched(Float_t eta, Float_t phi, Vector_t<int> *hypo)
{
	if(hypo == NULL)
	{
		return false;
	}

	Float_t the_dr = 000.0f;
	Float_t min_dr = 100.0f;

	for(UInt_t i = 0; i < hypo->size(); i++)
	{
		if(hypo->at(i) == 1)
		{
			for(Int_t j = 0; j < trig_EF_trigmugirl_n->at(i); j++)
			{
				the_dr = sqrtf(__dR2(trig_EF_trigmugirl_track_CB_eta->at(i).at(j), eta, trig_EF_trigmugirl_track_CB_phi->at(i).at(j), phi));

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

char getlumiPeriod(int RunNumber)
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

UInt_t TLeptonAnalysis::getElTrigger(void)
{
	if(core::OF == false)
	{
		elTrigger = 0x00;
#ifdef __IS_MC
		/**/ if(RunNumber == 180164 // B-D
			||
			RunNumber == 183003 // E-H
		 ) {
			if(EF_e20_medium) {
				elTrigger |= (1 << 0);
			}
			if(EF_2e12_medium) {
				elTrigger |= (1 << 1);
			}
		}
		else if(RunNumber == 186169) // I-K
		{
			TRandom3 random3;

			random3.SetSeed(mc_channel_number * EventNumber);

			const Float_t fracEl = (lumiPeriodI + lumiPeriodJ) / (lumiPeriodI + lumiPeriodJ + lumiPeriodK);

			if(random3.Uniform() < fracEl)
			{
				if(EF_e20_medium) {
					elTrigger |= (1 << 0);
				}
				if(EF_2e12_medium) {
					elTrigger |= (1 << 1);
				}
			}
			else
			{
				if(EF_e22_medium) {
					elTrigger |= (1 << 0);
				}
				if(EF_2e12T_medium) {
					elTrigger |= (1 << 1);
				}
			}
		}
		else if(RunNumber == 186275) // L-M
		{
			if(EF_e22_medium1) {
				elTrigger |= (1 << 0);
			}
			if(EF_2e12T_medium) {
				elTrigger |= (1 << 1);
			}
		}
#else
		char lumiPeriod = getlumiPeriod(RunNumber);

		/**/ if(lumiPeriod >= 'B' && lumiPeriod <= 'J')
		{
			if(EF_e20_medium) {
				elTrigger |= (1 << 0);
			}
			if(EF_2e12_medium) {
				elTrigger |= (1 << 1);
			}
		}
		else if(lumiPeriod >= 'K' && lumiPeriod <= 'K')
		{
			if(EF_e22_medium) {
				elTrigger |= (1 << 0);
			}
			if(EF_2e12T_medium) {
				elTrigger |= (1 << 1);
			}
		}
		else if(lumiPeriod >= 'L' && lumiPeriod <= 'M')
		{
			if(EF_e22vh_medium1) {
				elTrigger |= (1 << 0);
			}
			if(EF_2e12Tvh_medium) {
				elTrigger |= (1 << 1);
			}
		}
#endif
	}
	else
	{
		elTrigger = 0x03;
	}

	return elTrigger;
}

/*-------------------------------------------------------------------------*/

UInt_t TLeptonAnalysis::getMuTrigger(void)
{
	if(core::OF == false)
	{
		muTrigger = 0x00;
#ifdef __IS_MC
		/**/ if(RunNumber == 180164 // B-D
			||
			RunNumber == 183003 // E-H
		 ) {
			if(EF_mu18_MG) {
				muTrigger |= (1 << 0);
			}
			if(EF_2mu10_loose) {
				muTrigger |= (1 << 1);
			}
		}
		else if(RunNumber == 186169) // I-K
		{
			TRandom3 random3;

			random3.SetSeed(mc_channel_number * EventNumber);

			const Float_t fracMu = (lumiPeriodI) / (lumiPeriodI + lumiPeriodJ + lumiPeriodK);

			if(random3.Uniform() < fracMu)
			{
				if(EF_mu18_MG) {
					muTrigger |= (1 << 0);
				}
				if(EF_2mu10_loose) {
					muTrigger |= (1 << 1);
				}
			}
			else
			{
				if(EF_mu18_MG_medium) {
					muTrigger |= (1 << 0);
				}
				if(EF_2mu10_loose) {
					muTrigger |= (1 << 1);
				}
			}
		}
		else if(RunNumber == 186275) // L-M
		{
			if(EF_mu18_MG_medium) {
				muTrigger |= (1 << 0);
			}
			if(EF_2mu10_loose) {
				muTrigger |= (1 << 1);
			}
		}
#else
		char lumiPeriod = getlumiPeriod(RunNumber);

		/**/ if(lumiPeriod >= 'B' && lumiPeriod <= 'I')
		{
			if(EF_mu18_MG) {
				muTrigger |= (1 << 0);
			}
			if(EF_2mu10_loose) {
				muTrigger |= (1 << 1);
			}
		}
		else if(lumiPeriod >= 'J' && lumiPeriod <= 'M')
		{
			if(EF_mu18_MG_medium) {
				muTrigger |= (1 << 0);
			}
			if(EF_2mu10_loose) {
				muTrigger |= (1 << 1);
			}
		}
#endif
	}
	else
	{
		muTrigger = 0x03;
	}

	return muTrigger;
}

/*-------------------------------------------------------------------------*/

UInt_t TLeptonAnalysis::triggerMatch(
	Int_t index,
	TLeptonType type
) {
	UInt_t result = 0x00;

	Float_t plateau = 0.0f;

	std::vector<int> *hypo1 = NULL;
	std::vector<int> *hypo2 = NULL;

	switch(type)
	{
		case TYPE_ELECTRON:
#ifdef __IS_MC
			/**/ if(RunNumber == 180164 // B-D
				||
				RunNumber == 183003 // E-H
			 ) {
				plateau = 21000.0f;
				hypo1 = trig_EF_el_EF_e20_medium;
				hypo2 = trig_EF_el_EF_2e12_medium;
			}
			else if(RunNumber == 186169) // I-K
			{
				TRandom3 random3;

				random3.SetSeed(mc_channel_number * EventNumber);

				const Float_t fracEl = (lumiPeriodI + lumiPeriodJ) / (lumiPeriodI + lumiPeriodJ + lumiPeriodK);

				if(random3.Uniform() < fracEl)
				{
					plateau = 21000.0f;
					hypo1 = trig_EF_el_EF_e20_medium;
					hypo2 = trig_EF_el_EF_2e12_medium;
				}
				else
				{
					plateau = 23000.0f;
					hypo1 = trig_EF_el_EF_e22_medium;
					hypo2 = trig_EF_el_EF_2e12_medium;
				}
			}
			else if(RunNumber == 186275) // L-M
			{
				plateau = 23000.0f;
				hypo1 = trig_EF_el_EF_e22_medium;
				hypo2 = trig_EF_el_EF_2e12_medium;
			}
#else
			char lumiPeriod = getlumiPeriod(RunNumber);

			/**/ if(lumiPeriod >= 'B' && lumiPeriod <= 'J')
			{
				plateau = 21000.0f;
				hypo1 = trig_EF_el_EF_e20_medium;
				hypo2 = trig_EF_el_EF_2e12_medium;
			}
			else if(lumiPeriod >= 'K' && lumiPeriod <= 'M')
			{
				plateau = 23000.0f
				hypo1 = trig_EF_el_EF_e22_medium;
				hypo2 = trig_EF_el_EF_2e12_medium;
			}
#endif
			if(isElectronMatched(el_tracketa->at(index), el_trackphi->at(index), hypo1) != false)
			{
				if(el_cl_E->at(index) > plateau)
				{
					result |= (1 << 0);
				}
			}
			if(isElectronMatched(el_tracketa->at(index), el_trackphi->at(index), hypo2) != false)
			{
				result |= (1 << 1);
			}
			break;

		case TYPE_MUON_STACO:
			plateau = 20000.0f;
			hypo1 = trig_EF_trigmugirl_EF_mu18;
			hypo2 = trig_EF_trigmugirl_EF_2mu10;

			if(isMuonMatched(mu_staco_eta->at(index), mu_staco_phi->at(index), hypo1) == false)
			{
				if(mu_staco_E->at(index) > plateau)
				{
					result |= (1 << 0);
				}
			}
			if(isMuonMatched(mu_staco_eta->at(index), mu_staco_phi->at(index), hypo2) == false)
			{
				result |= (1 << 1);
			}
			break;

		case TYPE_MUON_MUID:
			plateau = 20000.0f;
			hypo1 = trig_EF_trigmugirl_EF_mu18;
			hypo2 = trig_EF_trigmugirl_EF_2mu10;

			if(isMuonMatched(mu_muid_eta->at(index), mu_muid_phi->at(index), hypo1) == false)
			{
				if(mu_muid_E->at(index) > plateau)
				{
					result |= (1 << 0);
				}
			}
			if(isMuonMatched(mu_muid_eta->at(index), mu_muid_phi->at(index), hypo2) == false)
			{
				result |= (1 << 1);
			}
			break;

		case TYPE_MUON_CALO:
			result = 0x03;
			break;
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

