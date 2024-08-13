#ifndef IMAGE_GAUSS_AOS_HPP
#define IMAGE_GAUSS_AOS_HPP

#include "../common/parameters_bmp.hpp"
#include "lectura_aos.hpp"
#include <cstring>

namespace gauss_aos {


  // Función que devuelve un array de estructuras de pixel con bordes necesarios para la función
  // 'gauss'.
  std::vector<lectura_aos::pixel> generar_bordes_img_aos(std::string file_path,
                                                         parameters::meta_int_data header);

  void gauss(std::string file_path, std::string output_file_path, parameters::meta_int_data header);
}// namespace gauss_aos

#endif// IMAGE_GAUSS_AOS_HPP
