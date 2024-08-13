#include "../common/parameters_bmp.hpp"
#include "../common/utilidades.hpp"
#include "copy_soa.hpp"
#include "gauss_soa.hpp"
#include "lectura_soa.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using std::filesystem::directory_iterator;
using namespace utilidades;
using namespace parameters;
using namespace lectura_soa;
using namespace copy_soa;
using namespace gauss_soa;


// Función que devuelve un array de estructuras de pixel con bordes necesarios para la función
// 'gauss'. En nuestro caso, dado que la máscara es de 5x5, rodearemos la imagen con dos
// 'anillos' de píxeles vacios (con R = 0, G = 0 y B = 0).
imagen gauss_soa::generar_bordes_img(string file_path, meta_int_data header)
{
  const int padding = calculate_padding(header.ancho_data);
  imagen imagen;
  for (unsigned int i = 0; i < header.alto_data * header.ancho_data + 4 * header.alto_data +
                                   4 * (4 + header.ancho_data);
       i++) {
    imagen.R.push_back(0);
    imagen.G.push_back(0);
    imagen.B.push_back(0);
  }
  ifstream fichero(file_path, ifstream::binary);
  if (fichero.fail()) { show_error_archivo(file_path, "generar_bordes_img", "gauss_soa.cpp");}
  fichero.seekg(header.inicio_image, fichero.beg);
  for (int h = 0, position = 2 * (4 + header.ancho_data); h < static_cast<int>(header.alto_data);
       h++) {
    for (int i = 0; i < 2; i++) position++;
    for (int w = 0; w < static_cast<int>(header.ancho_data); w++, position++) {
      imagen.B[position] = fichero.get();
      imagen.G[position] = fichero.get();
      imagen.R[position] = fichero.get();
    }
    for (int i = 0; i < padding; i++) fichero.get();
    for (int i = 0; i < 2; i++) position++;
  }
  return imagen;
}


// Función GAUSS para la versión SOA.
// Para ello, aplicamos la fórmula con ayuda de la imagen inicial, la imagen con
// los bordes necesarios debido a la máscara aplicada, y la propia máscara de 5x5.
void gauss_soa::gauss(string file_path, string output_file_path, meta_int_data header)
{
  imagen res = leer_pixeles_SOA(file_path, header);
  float gauss_timer = clock();
  imagen img = generar_bordes_img(file_path, header);
  int w = 273, position = 0;
  int m[5][5] = {
      {1, 4, 7, 4, 1}, {4, 16, 26, 16, 4}, {7, 26, 41, 26, 7}, {4, 16, 26, 16, 4}, {1, 4, 7, 4, 1}};
  int init = 2 * (4 + header.ancho_data) + 2;
  for (int i = 0; i < static_cast<int>(header.alto_data); i++) {
    for (int j = 0; j < static_cast<int>(header.ancho_data); j++) {
      int r_R = 0, r_G = 0, r_B = 0;
      for (int s = -2; s < 3; s++) {
        for (int t = -2; t < 3; t++) {
          r_R += m[s + 2][t + 2] * img.R[(init + (j + t)) - (-(i + s) * (4 + header.ancho_data))];
          r_G += m[s + 2][t + 2] * img.G[(init + (j + t)) - (-(i + s) * (4 + header.ancho_data))];
          r_B += m[s + 2][t + 2] * img.B[(init + (j + t)) - (-(i + s) * (4 + header.ancho_data))];
        }
      }
      res.R[position] = static_cast<int>(r_R / w);
      res.G[position] = static_cast<int>(r_G / w);
      res.B[position] = static_cast<int>(r_B / w);
      position++;
    }
  }
  cout << "Gauss time: " << ((clock() - gauss_timer) / CLOCKS_PER_SEC) * 1000000 << endl;
  copy_SOA(header, file_path, output_file_path, res);
}
