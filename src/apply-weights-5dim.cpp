#include <iostream>
#include "TH1F.h"
#include "TFile.h"
#include "TSystem.h"
#include "TROOT.h"
#include "names.h"
#include "utils.h"
#include "utils-names.h"
#include "analysis-constants.h"


int main(int argc, char* argv[])
{
    // Open files
    if(!check_file_existence(input_dir, file_name_phi_nominal)) return 1;
    if(!check_file_existence(results_dir, file_name_weights  )) return 1;

    TFile* fin_nominal = new TFile((input_dir+file_name_phi_nominal).c_str());
    TFile* fin_clt     = new TFile((results_dir+file_name_weights  ).c_str());

    // Open results files
    TFile* fout = new TFile((results_dir+"ct_"+file_name_phi).c_str(),"RECREATE");
    gROOT->cd();

    // Integrate through all bins and targets
    TH1F* h_Phi_dat;
    TH1F* h_Phi_weights;

    fout->cd();
    for(int vertex_cut_value = 1 ; vertex_cut_value < 3 ; vertex_cut_value++)
    {
        for(int dat_target_index = 0 ; dat_target_index < 3 ; dat_target_index++)
        {
            int sim_target_index = (vertex_cut_value==1 ? 3 : dat_target_index);

            for(int Q2_bin = 0 ; Q2_bin < N_Q2 ; Q2_bin++)
            {
                for(int Nu_bin = 0 ; Nu_bin < N_Nu ; Nu_bin++)
                {
                    for(int Zh_bin = 0 ; Zh_bin < N_Zh ; Zh_bin++)
                    {
                        for(int Pt2_bin = 0 ; Pt2_bin < N_Pt2 ; Pt2_bin++)
                        {
                            h_Phi_dat     = (TH1F*) fin_nominal->Get(get_acccorr_histo_name(vertex_cut_value, dat_target_index,Q2_bin,Nu_bin,Zh_bin,Pt2_bin).c_str());
                            h_Phi_weights = (TH1F*) fin_clt->Get(get_weights_name(sim_target_index,Q2_bin,Nu_bin,Zh_bin,Pt2_bin).c_str());
                            if(h_Phi_dat==NULL) continue;

                            //Apply weight
                            h_Phi_dat->Divide(h_Phi_weights);
                            h_Phi_dat->Write(get_acccorr_histo_name(vertex_cut_value, dat_target_index,Q2_bin,Nu_bin,Zh_bin,Pt2_bin).c_str());
                            h_Phi_dat->Reset();

                        }// End Pt2 loop
                    }// End Zh loop
                }// End Nu loop
            }// End Q2 loop
        }// End Targets loop
    }

    // Close files
    fin_nominal->Close();
    fin_clt->Close();
    fout->Close();

    // Release memory
    delete fin_nominal;
    delete fin_clt;
    delete fout;
    delete h_Phi_dat;
    delete h_Phi_weights;
    delete h_Phi_dat;
}
