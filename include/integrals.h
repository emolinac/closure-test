#include "TH1F.h"
#include "analysis-constants.h"
#include "utils.h"
#include "utils-names.h"

void phi_integration(TH1F* h_Phi, TH1F* h_Pt2, int Pt2_bin)
{
	if(h_Phi==NULL)
	{
		h_Pt2->SetBinContent(Pt2_bin+1, 0);
		h_Pt2->SetBinError(Pt2_bin+1, 0.);

		return;
	}
	
    double error[1] = {};
	double integral = h_Phi->IntegralAndError(1,N_Phi,*error);

	h_Pt2->SetBinContent(Pt2_bin+1, integral);
	h_Pt2->SetBinError(Pt2_bin+1, error[0]);

    return;
}

