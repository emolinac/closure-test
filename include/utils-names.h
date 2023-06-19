#ifndef UTILS_NAMES_H
#define UTILS_NAMES_H

#include "names.h"

std::string get_sim_name(int sim_target_index)
{
    return sim_dir+sim_targets[sim_target_index]+sim_ext;
}

std::string get_dat_name(int dat_target_index)
{
    return dat_dir+dat_targets[dat_target_index]+dat_ext;
}

std::string get_acc_file_name(int vertex_cut_value, int dat_target_index, int Q2_bin, int Nu_bin, int Zh_bin)
{
    return results_dir+"acc"+targets[vertex_cut_value-1][dat_target_index]+"_"+std::to_string(Q2_bin)+std::to_string(Nu_bin)+std::to_string(Zh_bin)+".root";
}

std::string get_acc_file_name(int vertex_cut_value, int dat_target_index)
{
    return results_dir+"acc"+targets[vertex_cut_value-1][dat_target_index]+".root";
}

std::string get_clt_file_name(int sim_target_index)
{
    return results_dir+"ct_"+sim_targets[sim_target_index]+"_ntuple.root";
}

std::string get_cltacc_file_name(int sim_target_index)
{
    return results_dir+"ctacc_"+sim_targets[sim_target_index]+".root";
}

std::string get_accf_histo_name(int vertex_cut_value, int dat_target_index, int Q2_bin, int Nu_bin, int Zh_bin, int Pt2_bin)
{
    return histo_accf+targets[vertex_cut_value-1][dat_target_index]+"_"+std::to_string(Q2_bin)+std::to_string(Nu_bin)+std::to_string(Zh_bin)+std::to_string(Pt2_bin);
}

std::string get_accf_histo_name(int sim_target_index, int Q2_bin, int Nu_bin, int Zh_bin, int Pt2_bin)
{
    return histo_accf+sim_targets[sim_target_index]+"_"+std::to_string(Q2_bin)+std::to_string(Nu_bin)+std::to_string(Zh_bin)+std::to_string(Pt2_bin);
}

std::string get_data_histo_name(int vertex_cut_value, int dat_target_index, int Q2_bin, int Nu_bin, int Zh_bin, int Pt2_bin)
{
    return histo_data+targets[vertex_cut_value-1][dat_target_index]+"_"+std::to_string(Q2_bin)+std::to_string(Nu_bin)+std::to_string(Zh_bin)+std::to_string(Pt2_bin);
}

std::string get_data_histo_name(int sim_target_index, int Q2_bin, int Nu_bin, int Zh_bin, int Pt2_bin)
{
    return histo_data+sim_targets[sim_target_index]+"_"+std::to_string(Q2_bin)+std::to_string(Nu_bin)+std::to_string(Zh_bin)+std::to_string(Pt2_bin);
}

std::string get_acccorr_histo_name(int vertex_cut_value, int dat_target_index, int Q2_bin, int Nu_bin, int Zh_bin, int Pt2_bin)
{
    return histo_acc+targets[vertex_cut_value-1][dat_target_index]+"_"+std::to_string(Q2_bin)+std::to_string(Nu_bin)+std::to_string(Zh_bin)+std::to_string(Pt2_bin);
}

std::string get_acccorr_histo_name(int sim_target_index, int Q2_bin, int Nu_bin, int Zh_bin, int Pt2_bin)
{
    return histo_acc+sim_targets[sim_target_index]+"_"+std::to_string(Q2_bin)+std::to_string(Nu_bin)+std::to_string(Zh_bin)+std::to_string(Pt2_bin);
}

std::string get_acccorr_histo_name(int sim_target_index, int Q2_bin, int Nu_bin, int Zh_bin)
{
    return histo_acc+sim_targets[sim_target_index]+"_"+std::to_string(Q2_bin)+std::to_string(Nu_bin)+std::to_string(Zh_bin);
}

std::string get_thrown_histo_name(int sim_target_index, int Q2_bin, int Nu_bin, int Zh_bin, int Pt2_bin)
{
    return histo_thr+sim_targets[sim_target_index]+"_"+std::to_string(Q2_bin)+std::to_string(Nu_bin)+std::to_string(Zh_bin)+std::to_string(Pt2_bin);
}

std::string get_thrown_histo_name(int sim_target_index, int Q2_bin, int Nu_bin, int Zh_bin)
{
    return histo_thr+sim_targets[sim_target_index]+"_"+std::to_string(Q2_bin)+std::to_string(Nu_bin)+std::to_string(Zh_bin);
}

std::string get_acccorr_Pt2_histo_name(int sim_target_index, int Q2_bin, int Nu_bin, int Zh_bin)
{
    return get_acccorr_histo_name(sim_target_index,Q2_bin,Nu_bin,Zh_bin);
}

std::string get_acccorr_clean_Pt2_histo_name(int sim_target_index, int Q2_bin, int Nu_bin, int Zh_bin)
{
    return get_acccorr_histo_name(sim_target_index,Q2_bin,Nu_bin,Zh_bin)+"_clean";
}

std::string get_acccorr_cleaninterpolated_Pt2_histo_name(int sim_target_index, int Q2_bin, int Nu_bin, int Zh_bin)
{
    return get_acccorr_histo_name(sim_target_index,Q2_bin,Nu_bin,Zh_bin)+"_clean_interpolated";
}

#endif