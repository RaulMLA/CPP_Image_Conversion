#include "../common/parameters_bmp.hpp"
#include "../common/utilidades.hpp"
#include "copy_aos.hpp"
#include "lectura_aos.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using std::filesystem::directory_iterator;
using namespace utilidades;
using namespace parameters;
using namespace lectura_aos;
using namespace copy_aos;


// Función COPY para la versión AOS.
// Esta función equivale a la rutina de escritura para la versión AOS, por lo que se
// encarga de copiar la imagen en las otras 3 operaciones que el usuario puede usar.
// Para ello, se copia byte a byte en el orden correcto cada byte de la imagen, al que
// se le une la cabecera para poder formar la imagen final.
bool copy_aos::copy_AOS(meta_int_data header, string file_path, string output_file_path,
                        vector<pixel> pixeles)
{
  float store_timer = clock();
  const int padding = utilidades::calculate_padding(header.ancho_data);
  ofstream fichero_out(output_file_path, ifstream::binary);
  if (fichero_out.fail()) { show_error_archivo(output_file_path, "copy_AOS", "copy_aos.cpp"); }
  string string_cabecera;
  string_cabecera = utilidades::generar_string_cabecera(file_path, header.inicio_image);
  fichero_out << string_cabecera;
  for (int h = 0, position = 0; h < static_cast<int>(header.alto_data); h++) {
    for (int w = 0; w < static_cast<int>(header.ancho_data); w++, position++) {
      fichero_out << static_cast<char>(pixeles[position].B);
      fichero_out << static_cast<char>(pixeles[position].G);
      fichero_out << static_cast<char>(pixeles[position].R);
    }
    for (int i = 0; i < padding; i++) fichero_out << 0;
  }
  cout << "Store time: " << ((clock() - store_timer) / CLOCKS_PER_SEC) * 1000000 << endl;
  return true;
}
