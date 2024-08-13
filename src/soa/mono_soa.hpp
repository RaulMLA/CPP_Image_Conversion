#ifndef IMAGE_MONO_SOA_HPP
#define IMAGE_MONO_SOA_HPP

#include "../common/parameters_bmp.hpp"
#include <cstring>

namespace mono_soa {

  void mono(std::string file_path, std::string output_file_path, parameters::meta_int_data header);

}

#endif// IMAGE_MONO_SOA_HPP
