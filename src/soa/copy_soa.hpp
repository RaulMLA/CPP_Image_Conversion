#ifndef IMAGE_COPY_AOS_HPP
#define IMAGE_COPY_AOS_HPP

#include "../common/parameters_bmp.hpp"
#include "lectura_soa.hpp"
#include <cstring>

namespace copy_soa {

  bool copy_SOA(parameters::meta_int_data header, std::string file_path,
                std::string output_file_path, lectura_soa::imagen imagen);

}

#endif// IMAGE_COPY_SOA_HPP