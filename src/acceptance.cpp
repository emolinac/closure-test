#include <iostream>
#include <string>
#include "TROOT.h"
#include "TFile.h"
#include "TH1F.h"
#include "TNtuple.h"
#include "TCut.h"
#include "names.h"
#include "utils.h"
#include "utils-names.h"
#include "analysis-constants.h"

int main(int argc, char* argv[])
{
    // Target settings
    int sim_target_index = std::stoi(argv[1]);
    
    // Q2, Nu, Zh bin settings
    int Q2_bin = std::stoi(argv[2]);
    int Nu_bin = std::stoi(argv[3]);
    int Zh_bin = std::stoi(argv[4]);

    double Q2_min = Q2_limits[Q2_bin  ];
    double Q2_max = Q2_limits[Q2_bin+1];
    double Nu_min = Nu_limits[Nu_bin  ];
    double Nu_max = Nu_limits[Nu_bin+1];
    double Zh_min = Zh_limits[Zh_bin  ];
    double Zh_max = Zh_limits[Zh_bin+1];
    
    // Open the simulations and data
    TFile* f = new TFile(get_clt_file_name(sim_target_index).c_str(),"READ");
    
    if(!f->IsOpen()){std::cout<<"ERROR! Files were not opened!"<<std::endl; return 1;}

    // Create results folder
    TFile* fresult = new TFile(get_cltacc_file_name(sim_target_index, Q2_bin, Nu_bin, Zh_bin).c_str(),"RECREATE");
    gROOT->cd();

    // Obtain the tuples
    TNtuple* ntuple_thr = (TNtuple*) f->Get(ntuple_thr_name);
    TNtuple* ntuple_rec = (TNtuple*) f->Get(ntuple_rec_name);
    TNtuple* ntuple_dat = (TNtuple*) f->Get(ntuple_dat_name);
    TNtuple* ntuple_ref = (TNtuple*) f->Get(ntuple_ref_name);

    if(ntuple_thr==NULL||ntuple_rec==NULL||ntuple_dat==NULL||ntuple_ref==NULL){std::cout<<"ERROR! One of the tuples could not be loaded!"<<std::endl; return 1;}

    // Setting the base cuts
    int vertex_cut_value = (sim_target_index==3 ? 1 : 2);
    
    std::cout<<"The bin selected was:"<<std::endl;
    std::cout<<Q2_min<<" < Q2 < "<<Q2_max<<std::endl;
    std::cout<<Nu_min<<" < Nu < "<<Nu_max<<std::endl;
    std::cout<<Zh_min<<" < Zh < "<<Zh_max<<std::endl;
    std::cout<<" The vertex cut is "<<vertex_cut_value<<std::endl;

    TCut Q2_cut = Form("Q2>%f&&Q2<%f",Q2_min,Q2_max);
    TCut Nu_cut = Form("Nu>%f&&Nu<%f",Nu_min,Nu_max);
    TCut Zh_cut = Form("Zh>%f&&Zh<%f",Zh_min,Zh_max);
    
    TCut cuts_dat = Q2_cut&&Nu_cut&&Zh_cut;
    TCut cuts_ref = Q2_cut&&Nu_cut&&Zh_cut;
    TCut cuts_thr = Q2_cut&&Nu_cut&&Zh_cut;
    TCut cuts_rec = Q2_cut&&Nu_cut&&Zh_cut;

    // Setting additional data cuts
    for(int i = 0 ; i < sizeof(dat_add_cut)/sizeof(TCut) ; i++) cuts_dat += dat_add_cut[i];

    
    // Setting additional cuts to thrown
    for(int i = 0 ; i < sizeof(thr_add_cut)/sizeof(TCut) ; i++) cuts_thr += thr_add_cut[i];

    for(int i = 0 ; i < sizeof(thr_add_cut)/sizeof(TCut) ; i++) cuts_ref += thr_add_cut[i];

    // Setting additional cuts to reconstructed
    for(int i = 0 ; i < sizeof(rec_add_cut)/sizeof(TCut) ; i++) cuts_rec += rec_add_cut[i];

    // Check cuts in lists
    std::cout<<"data list cuts           : "<<cuts_dat<<std::endl;
    std::cout<<"thrown and ref list cuts : "<<cuts_thr<<std::endl;
    std::cout<<"recons list cuts         : "<<cuts_rec<<std::endl;

    // Set TEventLists to make everything faster
    ntuple_thr->Draw(">>list_thr",cuts_thr);
    ntuple_ref->Draw(">>list_ref",cuts_ref);
    ntuple_rec->Draw(">>list_rec",cuts_rec);
    ntuple_dat->Draw(">>list_dat",cuts_dat);

    TEventList* evnt_thr = (TEventList*) gDirectory->Get("list_thr");
    TEventList* evnt_ref = (TEventList*) gDirectory->Get("list_ref");
    TEventList* evnt_rec = (TEventList*) gDirectory->Get("list_rec");
    TEventList* evnt_dat = (TEventList*) gDirectory->Get("list_dat");
    
    ntuple_thr->SetEventList(evnt_thr);
    ntuple_ref->SetEventList(evnt_ref);
    ntuple_rec->SetEventList(evnt_rec);
    ntuple_dat->SetEventList(evnt_dat);

    // Declare the necessary histograms
    TH1F* hdat      = new TH1F("hdat"     ,"",N_Phi,Phi_min,Phi_max);
    TH1F* hrec      = new TH1F("hrec"     ,"",N_Phi,Phi_min,Phi_max);
    TH1F* hthr      = new TH1F("hthr"     ,"",N_Phi,Phi_min,Phi_max);
    TH1F* hacc      = new TH1F("hacc"     ,"",N_Phi,Phi_min,Phi_max);
    TH1F* hacc_corr = new TH1F("hacc_corr","",N_Phi,Phi_min,Phi_max);
    TH1F* href      = new TH1F("href"     ,"",N_Phi,Phi_min,Phi_max);

    hdat->Sumw2();
    hrec->Sumw2();
    hthr->Sumw2();

    // Start the acceptance correction process
    for(int Pt2_bin = 0 ; Pt2_bin < N_Pt2 ; Pt2_bin++)
    {
        // Stablish the Pt2 cut
        double Pt2_bin_min = delta_Pt2 *  Pt2_bin;
        double Pt2_bin_max = delta_Pt2 * (Pt2_bin+1);
        TCut loop_cut = Form("Pt2>%f&&Pt2<%f",Pt2_bin_min,Pt2_bin_max);

        // Fill the histos and skip the loop if the bin is empty
        ntuple_dat->Project("hdat","PhiPQ",loop_cut);
        if(empty_histo(hdat)==1){hdat->Reset();continue;}
        ntuple_thr->Project("hthr","PhiPQ",loop_cut);
        if(empty_histo(hthr)==1){hdat->Reset();hthr->Reset();continue;}
        ntuple_rec->Project("hrec","PhiPQ",loop_cut);
        if(empty_histo(hrec)==1){hdat->Reset();hrec->Reset();hthr->Reset();continue;}
        ntuple_ref->Project("href","PhiPQ",loop_cut);

        // Setting nominal condition N_accept>1
        rec_histo_process(hrec);

        // Obtain acceptance factor as an histo
        hacc->Divide(hrec,hthr,1,1,"B");

        // Setting the acc<1 condition
        acc_histo_process(hacc);

        // Obtain acceptance corrected data
        hacc_corr->Divide(hdat,hacc,1,1);

        // Write the histos on the output file
        fresult->cd();
        hacc_corr->Write(get_acccorr_histo_name(sim_target_index,Q2_bin,Nu_bin,Zh_bin,Pt2_bin).c_str());
        href->Write(get_thrown_histo_name(sim_target_index,Q2_bin,Nu_bin,Zh_bin,Pt2_bin).c_str());
        gROOT->cd();

        hdat->Reset();
        hrec->Reset();
        hthr->Reset();
        hacc->Reset();
        href->Reset();
        hacc_corr->Reset();
    }

    // Close TFiles
    f->Close();
    fresult->Close();
    
    return 1;
}
