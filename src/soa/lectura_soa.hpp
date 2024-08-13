#ifndef IMAGE_LECTURA_SOA_HPP
#define IMAGE_LECTURA_SOA_HPP

#include "../common/parameters_bmp.hpp"
#include <cstring>

namespace lectura_soa {

  struct imagen {
    std::vector<float> R;
    std::vector<float> G;
    std::vector<float> B;
  } typedef imagen;

  struct pixel {
    int R, G, B;
  } typedef pixel;


  imagen leer_pixeles_SOA(std::string file_path, parameters::meta_int_data header);
}// namespace lectura_soa

#endif// IMAGE_LECTURA_SOA_HPP
