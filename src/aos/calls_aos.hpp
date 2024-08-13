#ifndef IMAGE_CALLS_AOS_HPP
#define IMAGE_CALLS_AOS_HPP

#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace calls_aos {

  void call_copy_aos(std::string in_path, std::string out_path,
                     std::filesystem::directory_entry file);

  void call_hist_aos(std::string in_path, std::string out_path,
                     std::filesystem::directory_entry file);

  void call_mono_aos(std::string in_path, std::string out_path,
                     std::filesystem::directory_entry file);

  void call_gauss_aos(std::string in_path, std::string out_path,
                      std::filesystem::directory_entry file);

}// namespace calls_aos

#endif// IMAGE_CALLS_AOS_HPP
