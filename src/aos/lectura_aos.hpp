#ifndef IMAGE_LECTURA_SOA_HPP
#define IMAGE_LECTURA_SOA_HPP

#include "../common/parameters_bmp.hpp"
#include <cstring>

namespace lectura_aos {

  struct pixel {
    float R, G, B;
  } typedef pixel;

  // Función que calcula el padding al final de cada línea de la imagen BMP.

  std::vector<pixel> leer_pixeles_AOS(std::string file_path, parameters::meta_int_data header);

}// namespace lectura_aos

#endif// IMAGE_LECTURA_SOA_HPP
