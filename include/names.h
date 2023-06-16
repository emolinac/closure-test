#ifndef NAMES_H
#define NAMES_H

#include <string>

// Directories
std::string dat_dir = "/work/emolina/";
std::string sim_dir = "/work/emolina/";

std::string input_dir  = "../input-files/";
std::string result_dir = "../output-files-acc/";

std::string file_name_phi      = "phi-distributions.root";
std::string file_name_pt2      = "pt2-distributions.root";
std::string file_name_pt2_bg   = "pt2-distributions-bgtreated.root";
std::string file_name_pt2_fits = "pt2-distributions-fits.root";
std::string file_name_meanpt2  = "results-meanpt2.root";
std::string file_name_broad    = "results-broadening.root";

// Extensions
std::string dat_ext = "_data_Npion.root";
std::string sim_ext = "1_simul.root";

// TNtuples
const char* ntuple_thr_name = "ntuple_thrown";
const char* ntuple_rec_name = "ntuple_accept";
const char* ntuple_dat_name = "ntuple_data";
const char* ntuple_rad_name = "ntuple_rad";
const char* ntuple_ctr_name = "ntuple_centroids";
const char* ntuple_ref_name = "ntuple_corrdata";

// Targets
std::string sim_targets[4] = { "C" , "Fe" , "Pb" , "D" };
std::string dat_targets[3] = { "C" , "Fe" , "Pb" };

std::string targets[2][3] = { { "DC" , "DFe" , "DPb" } , { "C" , "Fe" , "Pb" } };

std::string histo_data  = "data_";
std::string histo_thr   = "thrown_";
std::string histo_accf  = "accf_";
std::string histo_acc   = "acc_data_";
std::string histo_accrc = "accrc_data_";

#endif
