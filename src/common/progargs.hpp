#ifndef IMAGE_PROGARGS_HPP
#define IMAGE_PROGARGS_HPP

#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

namespace progargs {
  void comprobar_argumentos(std::string in_path, std::string out_path, std::string operation);
}

#endif// IMAGE_PROGARGS_HPP
