#ifndef COMMON_PARAMETERS_HPP
#define COMMON_PARAMETERS_HPP

#include <cmath>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

namespace parameters {
  unsigned int ancho_calculator(char cabecera[]);
  unsigned int alto_calculator(char cabecera[]);
  unsigned int size_calculator(char cabecera[]);
  unsigned int color_calculator(char cabecera[]);
  unsigned int inicio_imagen_calculator(char cabecera[]);
  unsigned int compresion_calculator(char cabecera[]);
  unsigned int num_planos_calculator(char cabecera[]);
  unsigned int image_size(char cabecera[]);
  void meta_data_calculator(std::string file_path, unsigned int (&datos_devueltos)[8]);
  struct meta_int_data {
    unsigned int ancho_data, alto_data, size_data, colores_data, inicio_image, compresion_data,
        planos_datos, tamano_imagen;
  } typedef meta_int_data;
  meta_int_data meta_data(std::string path_input);
}// namespace parameters

#endif
