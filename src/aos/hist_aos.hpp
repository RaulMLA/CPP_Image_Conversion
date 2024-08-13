#ifndef IMAGE_HIST_AOS_HPP
#define IMAGE_HIST_AOS_HPP

#include "../common/parameters_bmp.hpp"
#include <cstring>


namespace hist_aos {


  void hist_checker(int red[256], int green[256], int blue[256], unsigned int imagen);

  void create_hst_file(int red[256], int green[256], int blue[256], std::string output_file);
  void hist(std::string file_path, parameters::meta_int_data header, std::string output_file);
}// namespace hist_aos

#endif// IMAGE_HIST_AOS_HPP
