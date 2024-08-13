#ifndef IMAGE_HIST_SOA_HPP
#define IMAGE_HIST_SOA_HPP

#include "../common/parameters_bmp.hpp"
#include "lectura_soa.hpp"
#include <cstring>


namespace hist_soa {


  void hist_checker(int red[256], int green[256], int blue[256], unsigned int imagen);

  void create_hst_file(int red[256], int green[256], int blue[256], std::string output_file);

  void hist(std::string file_path, parameters::meta_int_data header, std::string output_file);
}// namespace hist_soa

#endif// IMAGE_HIST_SOA_HPP
