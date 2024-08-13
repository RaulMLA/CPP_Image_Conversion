#include "../common/parameters_bmp.hpp"
#include "copy_soa.hpp"
#include "lectura_soa.hpp"
#include "mono_soa.hpp"
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using std::filesystem::directory_iterator;
using namespace parameters;
using namespace lectura_soa;
using namespace copy_soa;
using namespace mono_soa;

// Función MONO para la versión SOA.
void mono_soa::mono(string file_path, string output_file_path, meta_int_data header)
{
  imagen imagen = leer_pixeles_SOA(file_path, header);
  float mono_timer = clock();
  for (unsigned int i = 0; i < header.alto_data * header.ancho_data; i++) {
    imagen.R[i] = static_cast<float>((imagen.R[i] / 255));
    imagen.G[i] = static_cast<float>((imagen.G[i] / 255));
    imagen.B[i] = static_cast<float>((imagen.B[i] / 255));
    if (imagen.R[i] <= 0.04045) imagen.R[i] = imagen.R[i] / 12.92;
    else imagen.R[i] = pow(((imagen.R[i] + 0.055) / 1.055), 2.4);
    if (imagen.G[i] <= 0.04045) imagen.G[i] = imagen.G[i] / 12.92;
    else imagen.G[i] = pow(((imagen.G[i] + 0.055) / 1.055), 2.4);
    if (imagen.B[i] <= 0.04045) imagen.B[i] = imagen.B[i] / 12.92;
    else imagen.B[i] = pow(((imagen.B[i] + 0.055) / 1.055), 2.4);
    double trans_lineal = 0.2126 * imagen.R[i] + 0.7152 * imagen.G[i] + 0.0722 * imagen.B[i];
    double correccion_gama = 0;
    if (trans_lineal <= 0.0031308) correccion_gama = 12.92 * trans_lineal;
    else correccion_gama = 1.055 * pow(trans_lineal, (1 / 2.4)) - 0.055;
    int desnormalizacion = correccion_gama * 255;
    imagen.R[i] = desnormalizacion;
    imagen.G[i] = desnormalizacion;
    imagen.B[i] = desnormalizacion;
  }
  cout << "Mono time: " << ((clock() - mono_timer) / CLOCKS_PER_SEC) * 1000000 << endl;
  copy_SOA(header, file_path, output_file_path, imagen);
}
