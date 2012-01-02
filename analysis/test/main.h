/*-------------------------------------------------------------------------*/

#ifndef __TEST_H
#define __TEST_H

/*-------------------------------------------------------------------------*/

#include "../../core/include/core.h"

/*-------------------------------------------------------------------------*/

class THiggsBuilder: public TNTuple
{
  public:
	THiggsBuilder(TChain *chain): TNTuple(chain)
	{
	}

	Float_t electronGetEtaDirection(Int_t index);
	Float_t electronGetPhiDirection(Int_t index);
	Float_t electronGetEt(Int_t index);

	void Loop(void);
};

/*-------------------------------------------------------------------------*/

#endif /* __TEST_H */

/*-------------------------------------------------------------------------*/

