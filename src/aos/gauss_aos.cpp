#include "../common/parameters_bmp.hpp"
#include "../common/utilidades.hpp"
#include "copy_aos.hpp"
#include "gauss_aos.hpp"
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
using namespace gauss_aos;


// Función que devuelve un array de estructuras de pixel con bordes necesarios para la función
// 'gauss'. En nuestro caso, dado que la máscara es de 5x5, rodearemos la imagen con dos
// 'anillos' de píxeles vacios (con R = 0, G = 0 y B = 0).
vector<pixel> gauss_aos::generar_bordes_img_aos(string file_path, meta_int_data header)
{
  const int padding = utilidades::calculate_padding(header.ancho_data);
  vector<pixel> pixeles(header.alto_data * header.ancho_data + 4 * header.alto_data +
                        4 * (4 + header.ancho_data));
  ifstream fichero(file_path, ifstream::binary);
  if (fichero.fail()) { show_error_archivo(file_path, "generar_bordes_im_aos", "gauss_aos.cpp"); }
  fichero.seekg(header.inicio_image, fichero.beg);
  for (int h = 0, position = 2 * (4 + header.ancho_data); h < static_cast<int>(header.alto_data);
       h++) {
    for (int i = 0; i < 2; i++) position++;
    for (int w = 0; w < static_cast<int>(header.ancho_data); w++, position++) {
      pixeles[position].B = fichero.get();
      pixeles[position].G = fichero.get();
      pixeles[position].R = fichero.get();
    }
    for (int i = 0; i < padding; i++) fichero.get();
    for (int i = 0; i < 2; i++) position++;
  }
  return pixeles;
}


// Función GAUSS para la versión AOS.
// Para ello, aplicamos la fórmula con ayuda de la imagen inicial, la imagen con
// los bordes necesarios debido a la máscara aplicada, y la propia máscara de 5x5.
void gauss_aos::gauss(string file_path, string output_file_path, meta_int_data header)
{
  vector<pixel> res = leer_pixeles_AOS(file_path, header);
  float gauss_timer = clock();
  vector<pixel> img = gauss_aos::generar_bordes_img_aos(file_path, header);
  int m[5][5] = {
      {1, 4, 7, 4, 1}, {4, 16, 26, 16, 4}, {7, 26, 41, 26, 7}, {4, 16, 26, 16, 4}, {1, 4, 7, 4, 1}};
  int init = 2 * (4 + header.ancho_data) + 2;
  for (int i = 0, w = 273, position = 0; i < static_cast<int>(header.alto_data); i++) {
    for (int j = 0; j < static_cast<int>(header.ancho_data); j++, position++) {
      int r_R = 0, r_G = 0, r_B = 0;
      for (int s = -2; s < 3; s++) {
        for (int t = -2; t < 3; t++) {
          r_R += m[s + 2][t + 2] * img[(init + (j + t)) - (-(i + s) * (4 + header.ancho_data))].R;
          r_G += m[s + 2][t + 2] * img[(init + (j + t)) - (-(i + s) * (4 + header.ancho_data))].G;
          r_B += m[s + 2][t + 2] * img[(init + (j + t)) - (-(i + s) * (4 + header.ancho_data))].B;
        }
      }
      res[position].R = static_cast<int>(r_R / w);
      res[position].G = static_cast<int>(r_G / w);
      res[position].B = static_cast<int>(r_B / w);
    }
  }
  cout << "Gauss time: " << ((clock() - gauss_timer) / CLOCKS_PER_SEC) * 1000000 << endl;
  copy_AOS(header, file_path, output_file_path, res);
}
