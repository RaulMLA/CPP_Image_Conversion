#include "utilidades.hpp"
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
using namespace utilidades;


// Función que calcula el padding de una imagen (bytes de relleno).
int utilidades::calculate_padding(unsigned int width) { return ((4 - (width * 3) % 4) % 4); }


// Función que genera un string con los bytes de la cabecera.
string utilidades::generar_string_cabecera(string file_path, int inicio)
{
  string cabecera_string;
  unsigned int byte_leido;
  ifstream fichero(file_path, ifstream::binary);
  if (fichero.fail()) {
    cerr << "[ERROR] Fallo al acceder al archivo: " << file_path
         << "\nEn la función: generar_string_cabecera \nEn el archivo: copy_soa.cpp" << endl;
    exit(-1);
  }
  else {
    for (int i = 0; i < inicio; i++) {
      byte_leido = fichero.get();
      cabecera_string += byte_leido;
    }
  }
  return cabecera_string;
}


// Función que muestra errores al acceder a un archivo concreto.
void utilidades::show_error_archivo(string file_path, string nombre_funcion, string nombre_archivo)
{
  cout << "[ERROR] Fallo al acceder al archivo: " << file_path
       << "\nEn la función: " << nombre_funcion << "\nEn el archivo: " << nombre_archivo << endl;
  exit(-1);
}
