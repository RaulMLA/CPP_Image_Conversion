#ifndef IMAGE_COPY_AOS_HPP
#define IMAGE_COPY_AOS_HPP

#include "../common/parameters_bmp.hpp"
#include "lectura_aos.hpp"
#include <cstring>

namespace copy_aos {

  bool copy_AOS(parameters::meta_int_data header, std::string file_path, std::string output_path,
                std::vector<lectura_aos::pixel> pixeles);
}

#endif// IMAGE_COPY_AOS_HPP