#include "../common/parameters_bmp.hpp"
#include "../common/utilidades.hpp"
#include "lectura_aos.hpp"
#include <filesystem>

using namespace std;
using std::filesystem::directory_iterator;
using namespace utilidades;
using namespace parameters;
using namespace lectura_aos;


// Función de lectura (rutina de lectura) para AOS.
// Devuelve un array de estructuras de tipo pixel mediante la iteración byte a byte por
// el fichero de entrada. Se comprueban errores y se crea el array deseado.
vector<lectura_aos::pixel> lectura_aos::leer_pixeles_AOS(string file_path, meta_int_data header)
{
  float loader_timer = clock();
  const int padding = utilidades::calculate_padding(header.ancho_data);
  vector<lectura_aos::pixel> pixeles(header.ancho_data * header.alto_data);
  ifstream fichero(file_path, ifstream::binary);
  if (fichero.fail()) { show_error_archivo(file_path, "lectura_AOS", "lectura_aos.cpp");}
  fichero.seekg(header.inicio_image, fichero.beg);
  for (int h = 0, position = 0; h < static_cast<int>(header.alto_data); h++) {
    for (int w = 0; w < static_cast<int>(header.ancho_data); w++, position++) {
      pixeles[position].B = fichero.get();
      pixeles[position].G = fichero.get();
      pixeles[position].R = fichero.get();
      if (pixeles[position].B > 255 || pixeles[position].R > 255 || pixeles[position].G > 255) {
        cerr << "[ERROR] Error en lectura, byte detectado con valor superior a 255 \n En archivo: "
             << file_path << endl;
        exit(-1);
      }
    }
    for (int i = 0; i < padding; i++) fichero.get();
  }
  cout << "Load time: " << (((clock() - loader_timer) / CLOCKS_PER_SEC)) * 1000000 << endl;
  return pixeles;
}
