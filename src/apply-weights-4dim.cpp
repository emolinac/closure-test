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
    if(!check_file_existence(input_dir, file_name_pt2_nominal)) return 1;
    if(!check_file_existence(results_dir, file_name_weights  )) return 1;

    TFile* fin_nominal = new TFile((input_dir+file_name_pt2_nominal).c_str());
    TFile* fin_clt     = new TFile((results_dir+file_name_weights  ).c_str());

    // Open results files
    TFile* fout = new TFile((results_dir+"ct_"+file_name_pt2).c_str(),"RECREATE");
    gROOT->cd();

    // Integrate through all bins and targets
    TH1F* h_Pt2_dat;
    TH1F* h_Pt2_weights;

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
                        h_Pt2_dat     = (TH1F*) fin_nominal->Get(get_acccorr_cleaninterpolated_Pt2_histo_name(vertex_cut_value, dat_target_index,Q2_bin,Nu_bin,Zh_bin).c_str());
                        h_Pt2_weights = (TH1F*) fin_clt->Get(get_weights_name(sim_target_index,Q2_bin,Nu_bin,Zh_bin).c_str());
                        if(h_Pt2_dat==NULL) continue;

                        // Apply weight
                        for(int bin = 1 ; bin <= h_Pt2_dat->GetNbinsX() ; bin++)
                        {
                            // Obtain weight according to value of bin content of acceptance-corrected Pt2
                            double weight = h_Pt2_weights->GetBinContent(h_Pt2_weights->FindBin(h_Pt2_dat->GetBinCenter(bin)));

                            // Replace the content of the bin with the modification given by the weight
                            double content = h_Pt2_dat->GetBinContent(bin);
                            weight > 0 ? h_Pt2_dat->SetBinContent(bin, content/weight) : h_Pt2_dat->SetBinContent(bin, content);
                        }

                        h_Pt2_dat->Write(get_acccorr_cleaninterpolated_Pt2_histo_name(vertex_cut_value, dat_target_index,Q2_bin,Nu_bin,Zh_bin).c_str());
                        h_Pt2_dat->Reset();
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

    return 1;
}
