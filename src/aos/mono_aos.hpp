#ifndef IMAGE_MONO_AOS_HPP
#define IMAGE_MONO_AOS_HPP

#include "../common/parameters_bmp.hpp"
#include <cstring>

namespace mono_aos {

  void mono(std::string file_path, parameters::meta_int_data header, std::string output_path);

}

#endif// IMAGE_MONO_AOS_HPP
