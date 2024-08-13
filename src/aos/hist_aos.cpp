#include "../common/parameters_bmp.hpp"
#include "hist_aos.hpp"
#include "lectura_aos.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using std::filesystem::directory_iterator;
using namespace parameters;
using namespace lectura_aos;
using namespace hist_aos;

// Función para comprobar el histograma y ver que no se han producido errores.
void hist_aos::hist_checker(int red[256], int green[256], int blue[256], unsigned int imagen)
{
  int sum_red = 0, sum_green = 0, sum_blue = 0, total = 0;
  for (int i = 0; i < 256; i++) {
    sum_red = sum_red + red[i];
    sum_green = sum_green + blue[i];
    sum_blue = sum_blue + green[i];
  }
  total = sum_red + sum_green + sum_blue;
  if (total != static_cast<int>((imagen))) {
    cerr << "[ERROR] Error en el checker de histograma. La suma de los contandores de bits es "
            "distinta al total de bytes de la imagen"
         << endl;
    exit(-1);
  }
}


// Función que crea el archivo hist en el formato esperado.
void hist_aos::create_hst_file(int red[256], int green[256], int blue[256], string output_file)
{
  float store_timer = clock();
  ofstream fichero_out(output_file, ifstream::binary);
  if (fichero_out.fail()) {
    cerr << "[ERROR] Error al crear el archivo de datos del histograma.";
    cerr << " Fallo al acceder al archivo: " << output_file
         << "\nEn la función: create_hst_file \nEn el archivo: hist_aos.cpp" << endl;
    exit(-1);
  }
  for (int i = 0; i < 256; i++) fichero_out << red[i] << endl;
  for (int i = 0; i < 256; i++) fichero_out << green[i] << endl;
  for (int i = 0; i < 255; i++) fichero_out << blue[i] << endl;
  fichero_out << blue[255];
  cout << "Store time: " << ((clock() - store_timer) / CLOCKS_PER_SEC) * 1000000 << endl;
}


// Función HISTO para la versión AOS.
void hist_aos::hist(string file_path, meta_int_data header, string output_file)
{
  vector<pixel> content_of_file = leer_pixeles_AOS(file_path, header);
  float histo_timer = clock();
  int red_counter[256] = {0}, green_counter[256] = {0}, blue_counter[256] = {0};
  pixel pixel_data;
  for (int i = 0; i < static_cast<int>(content_of_file.size()); i++) {
    pixel_data = content_of_file[i];
    red_counter[(unsigned int) pixel_data.R]++;
    green_counter[(unsigned int) pixel_data.G]++;
    blue_counter[(unsigned int) pixel_data.B]++;
  }
  hist_aos::hist_checker(red_counter, green_counter, blue_counter, content_of_file.size() * 3);
  cout << "Histo time: " << ((clock() - histo_timer) / CLOCKS_PER_SEC) * 1000000 << endl;
  hist_aos::create_hst_file(red_counter, green_counter, blue_counter, output_file);
}
