#include "../common/parameters_bmp.hpp"
#include "copy_aos.hpp"
#include "lectura_aos.hpp"
#include "mono_aos.hpp"
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using std::filesystem::directory_iterator;
using namespace parameters;
using namespace lectura_aos;
using namespace copy_aos;
using namespace mono_aos;


// Función MONO para la versión AOS.
void mono_aos::mono(string file_path, meta_int_data header, string output_path)
{
  vector<pixel> pixeles = leer_pixeles_AOS(file_path, header);
  float mono_timer = clock();
  for (int i = 0; i < (int) pixeles.size(); i++) {
    pixeles[i].R = static_cast<float>((pixeles[i].R / 255));
    pixeles[i].G = static_cast<float>((pixeles[i].G / 255));
    pixeles[i].B = static_cast<float>((pixeles[i].B / 255));
    if (pixeles[i].R <= 0.04045) pixeles[i].R = pixeles[i].R / 12.92;
    else pixeles[i].R = pow(((pixeles[i].R + 0.055) / 1.055), 2.4);
    if (pixeles[i].G <= 0.04045) pixeles[i].G = pixeles[i].G / 12.92;
    else pixeles[i].G = pow(((pixeles[i].G + 0.055) / 1.055), 2.4);
    if (pixeles[i].B <= 0.04045) pixeles[i].B = pixeles[i].B / 12.92;
    else pixeles[i].B = pow(((pixeles[i].B + 0.055) / 1.055), 2.4);
    double transformacion_lineal = 0.2126 * pixeles[i].R + 0.7152 * pixeles[i].G + 0.0722 * pixeles[i].B;
    double correccion_gama = 0;
    if (transformacion_lineal <= 0.0031308) correccion_gama = 12.92 * transformacion_lineal;
    else correccion_gama = 1.055 * pow(transformacion_lineal, (1 / 2.4)) - 0.055;
    int desnormalizacion = correccion_gama * 255;
    pixeles[i].R = desnormalizacion;
    pixeles[i].G = desnormalizacion;
    pixeles[i].B = desnormalizacion;
  }
  cout << "Mono time: " << ((clock() - mono_timer) / CLOCKS_PER_SEC) * 1000000 << endl;
  copy_AOS(header, file_path, output_path, pixeles);
}
