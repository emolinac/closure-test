#include <iostream>
#include "TROOT.h"
#include "TFile.h"
#include "TH1F.h"
#include "integrals.h"
#include "analysis-constants.h"
#include "utils.h"
#include "utils-names.h"

int main(int argc , char *argv[])
{
    std::cout<<"Starting phipq integration."<<std::endl;
    
    // Open files
    if(!check_file_existence(input_dir, file_name_phi)) return 1;
    TFile* fin  = new TFile((input_dir+file_name_phi).c_str());
    
    TFile* fout = new TFile((results_dir+file_name_weights).c_str(),"RECREATE");
    gROOT->cd();

    // Integrate through all bins and targets
    TH1F* h_Phi_pdat;
    TH1F* h_Phi_ref;
    TH1F* h_Phi_weights = new TH1F("","",N_Phi, Phi_min, Phi_max);

    TH1F* h_Pt2_pdat    = new TH1F("","",N_Pt2,Pt2_min,Pt2_max);
    TH1F* h_Pt2_ref     = new TH1F("","",N_Pt2,Pt2_min,Pt2_max);
    TH1F* h_Pt2_weights = new TH1F("","",N_Pt2,Pt2_min,Pt2_max);

    for(int sim_target_index = 0 ; sim_target_index < sizeof(sim_targets)/sizeof(std::string) ; sim_target_index++)
    {
        for(int Q2_bin = 0 ; Q2_bin < N_Q2 ; Q2_bin++)
        {
            for(int Nu_bin = 0 ; Nu_bin < N_Nu ; Nu_bin++)
            {
                for(int Zh_bin = 0 ; Zh_bin < N_Zh ; Zh_bin++)
                {
                    for(int Pt2_bin = 0 ; Pt2_bin < N_Pt2 ; Pt2_bin++)
                    {
                        h_Phi_pdat = (TH1F*) fin->Get(get_acccorr_histo_name(sim_target_index,Q2_bin,Nu_bin,Zh_bin,Pt2_bin).c_str());
                        h_Phi_ref  = (TH1F*) fin->Get(get_thrown_histo_name(sim_target_index,Q2_bin,Nu_bin,Zh_bin,Pt2_bin).c_str());
                        if(h_Phi_pdat==NULL||h_Phi_ref==NULL) continue;

                        ////Obtain 5dim weight
                        //h_Phi_weights->Divide(h_Phi_pdat,h_Phi_ref,1,1);
                        //h_Phi_weights->Write(get_weights_name(sim_target_index,Q2_bin,Nu_bin,Zh_bin,Pt2_bin).c_str());
                        //h_Phi_weights->Reset();

                        // Proceed by integrating
                        phi_integration(h_Phi_pdat, h_Pt2_pdat, Pt2_bin);
                        phi_integration(h_Phi_ref , h_Pt2_ref , Pt2_bin);
                    }// End Pt2 loop

                    fout->cd();
                    h_Pt2_pdat->Write(get_acccorr_histo_name(sim_target_index,Q2_bin,Nu_bin,Zh_bin).c_str());
                    h_Pt2_ref->Write(get_thrown_histo_name(sim_target_index,Q2_bin,Nu_bin,Zh_bin).c_str());

                    //Obtain 4dim weight
                    h_Pt2_weights->Divide(h_Pt2_pdat, h_Pt2_ref,1,1);
                    h_Pt2_weights->Write(get_weights_name(sim_target_index,Q2_bin,Nu_bin,Zh_bin).c_str());
                    h_Pt2_weights->Reset();
                    gROOT->cd();
                    
                    h_Pt2_pdat->Reset();
                    h_Pt2_ref->Reset();
                }// End Zh loop
            }// End Nu loop
        }// End Q2 loop
    }// End Targets loop
    
    fin->Close(); 
    fout->Close();
    
    delete fin;
    delete fout;
    delete h_Phi_pdat;
    delete h_Phi_ref;
    delete h_Pt2_pdat;
    delete h_Pt2_ref;

    std::cout<<"Finished phipq integration."<<std::endl;

    return 1;
}
