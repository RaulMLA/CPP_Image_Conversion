#include "../common/parameters_bmp.hpp"
#include "../common/utilidades.hpp"
#include "lectura_soa.hpp"
#include <cmath>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using std::filesystem::directory_iterator;
using namespace parameters;
using namespace utilidades;
using namespace lectura_soa;


// Función de lectura (rutina de lectura) para SOA.
// Devuelve una estructura tipo imagen de 3 arrays (R, G, B) de enteros mediante la
// iteración byte a byte por el fichero de entrada. Se comprueban errores y se crea el
// array deseado.
lectura_soa::imagen lectura_soa::leer_pixeles_SOA(string file_path, meta_int_data header)
{
  float loader_timer = clock();
  const int padding = utilidades::calculate_padding(header.ancho_data);
  imagen imagen;
  ifstream fichero(file_path, ifstream::binary);
  if (fichero.fail()) { show_error_archivo(file_path, "lectura_SOA", "lectura_soa.cpp");}
  fichero.seekg(header.inicio_image, fichero.beg);
  for (int h = 0; h < static_cast<int>(header.alto_data); h++) {
    for (int w = 0; w < static_cast<int>(header.ancho_data); w++) {
      imagen.B.push_back(fichero.get());
      imagen.G.push_back(fichero.get());
      imagen.R.push_back(fichero.get());
      if (imagen.R[h * header.ancho_data + w] > 255 || imagen.G[h * header.ancho_data + w] > 255 ||
          imagen.B[h * header.ancho_data + w] > 255) {
        cerr << "[ERROR] Error en lectura, byte detectado con valor superior a 255 \n En archivo: "
             << file_path << endl;
        exit(-1);
      }
    }
    for (int i = 0; i < padding; i++) fichero.get();
  }
  cout << "Load time: " << (((clock() - loader_timer) / CLOCKS_PER_SEC)) * 1000000 << endl;
  return imagen;
}
