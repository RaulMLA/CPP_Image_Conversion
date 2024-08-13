#ifndef IMAGE_GAUSS_SOA_HPP
#define IMAGE_GAUSS_SOA_HPP

#include "../common/parameters_bmp.hpp"
#include "lectura_soa.hpp"
#include <cstring>

namespace gauss_soa {


  // Función que devuelve un array de estructuras de pixel con bordes necesarios para la función
  // 'gauss'.
  lectura_soa::imagen generar_bordes_img(std::string file_path, parameters::meta_int_data header);

  void gauss(std::string file_path, std::string output_file_path, parameters::meta_int_data header);
}// namespace gauss_soa

#endif// IMAGE_GAUSS_SOA_HPP
