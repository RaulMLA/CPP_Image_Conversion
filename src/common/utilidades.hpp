#ifndef IMAGE_UTILIDADES_HPP
#define IMAGE_UTILIDADES_HPP

#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

namespace utilidades {

  int calculate_padding(unsigned int width);

  std::string generar_string_cabecera(std::string file_path, int inicio);

  void show_error_archivo(std::string file_path, std::string nombre_funcion,
                          std::string nombre_archivo);

}// namespace utilidades

#endif// IMAGE_UTILIDADES_HPP
