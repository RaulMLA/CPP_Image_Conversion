#ifndef IMAGE_CALLS_SOA_HPP
#define IMAGE_CALLS_SOA_HPP

#include <iostream>
#include <fstream>
#include <cstring>
#include <filesystem>

namespace calls_soa {

    void call_copy_soa(std::string in_path, std::string out_path, std::filesystem::directory_entry file);

    void call_hist_soa(std::string in_path, std::string out_path, std::filesystem::directory_entry file);

    void call_mono_soa(std::string in_path, std::string out_path, std::filesystem::directory_entry file);

    void call_gauss_soa(std::string in_path, std::string out_path, std::filesystem::directory_entry file);

}

#endif //IMAGE_CALLS_SOA_HPP
