#include "./parameters_bmp.hpp"
#include "./utilidades.hpp"
#include <cmath>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
using std::filesystem::directory_iterator;
using namespace utilidades;
using namespace parameters;


// Función que calcula el ANCHO de una imagen BMP.
unsigned int parameters::ancho_calculator(char cabecera[54])
{

  unsigned int ancho;

  ancho = static_cast<unsigned char>(cabecera[18]) +
          static_cast<unsigned char>(cabecera[19]) * 256 +
          static_cast<unsigned char>(cabecera[20]) * 256 * 256 +
          static_cast<unsigned char>(cabecera[21]) * 256 * 256 * 256;

  if (ancho == 0) {
    cerr << "[ERROR] Error obteniendo los datos de cabecera: valor del ancho de la imagen es cero."
         << endl;
    exit(-1);
  }

  return ancho;
}


// Función que calcula el ALTO de una imagen BMP.
unsigned int parameters::alto_calculator(char cabecera[54])
{

  unsigned int alto;

  alto = static_cast<unsigned char>(cabecera[22]) + static_cast<unsigned char>(cabecera[23]) * 256 +
         static_cast<unsigned char>(cabecera[24]) * 256 * 256 +
         static_cast<unsigned char>(cabecera[25]) * 256 * 256 * 256;

  if (alto == 0) {
    cerr << "[ERROR] Error obteniendo los datos de cabecera: valor del alto de la imagen es cero."
         << endl;
    exit(-1);
  }

  return alto;
}


// Función que calcula el TAMAÑO DEL ARCHIVO de una imagen BMP.
unsigned int parameters::size_calculator(char cabecera[54])
{

  unsigned int size;

  size = static_cast<unsigned char>(cabecera[2]) + static_cast<unsigned char>(cabecera[3]) * 256 +
         static_cast<unsigned char>(cabecera[4]) * 256 * 256 +
         static_cast<unsigned char>(cabecera[5]) * 256 * 256 * 256;

  if (size <= 54) {
    cerr << "[ERROR] Error obteniendo los datos de cabecera: valor del tamaño del archivo no es "
            "válido (demasiado pequeño) \nvalor>: "
         << size << endl;
    exit(-1);
  }

  return size;
}


// Función que calcula el TAMAÑO DE PUNTO EN BITS de una imagen BMP.
unsigned int parameters::color_calculator(char cabecera[54])
{

  unsigned int color;

  color = static_cast<unsigned char>(cabecera[28]) + static_cast<unsigned char>(cabecera[29]) * 256;

  if (color != 24) {
    cerr << "[ERROR] Error obteniendo los datos de cabecera: valor del tamaño de cada punto es "
            "distinto a 24. \nvalor>: "
         << color << endl;
    exit(-1);
  }

  return color;
}


// Función que calcula el INICIO DE DATOS DE IMAGEN de una imagen BMP.
unsigned int parameters::inicio_imagen_calculator(char cabecera[54])
{

  unsigned int inicio;

  inicio = static_cast<unsigned char>(cabecera[10]) +
           static_cast<unsigned char>(cabecera[11]) * 256 +
           static_cast<unsigned char>(cabecera[12]) * 256 * 256 +
           static_cast<unsigned char>(cabecera[13]) * 256 * 256 * 256;

  if (inicio <= 54) {
    cerr << "[ERROR] Error obteniendo los datos de cabecera: valor de inicio de archivo es "
            "distinto a menor al final de cabecera. \nvalor>: "
         << inicio << endl;
    exit(-1);
  }


  return inicio;
}


// Función que calcula el la COMPRESIÓN de una imagen BMP.
unsigned int parameters::compresion_calculator(char cabecera[54])
{

  unsigned int compresion;

  compresion = static_cast<unsigned char>(cabecera[30]) +
               static_cast<unsigned char>(cabecera[31]) * 256 +
               static_cast<unsigned char>(cabecera[32]) * 256 * 256 +
               static_cast<unsigned char>(cabecera[33]) * 256 * 256 * 256;

  if (compresion != 0) {
    cerr << "[ERROR] Error obteniendo los datos de cabecera: valor de compresión es distinto a 0. "
            "\nvalor>: "
         << compresion << endl;
    exit(-1);
  }

  return compresion;
}


// Función que calcula el NÚMERO DE PLANOS de una imagen BMP.
unsigned int parameters::num_planos_calculator(char cabecera[54])
{

  unsigned int num_planos;

  num_planos =
      static_cast<unsigned char>(cabecera[26]) + static_cast<unsigned char>(cabecera[27]) * 256;

  if (num_planos != 1) {
    cerr << "[ERROR] Error obteniendo los datos de cabecera: el número de planos es distinto a 1. "
            "\nvalor>: "
         << num_planos << endl;
    exit(-1);
  }

  return num_planos;
}


// Función que calcula el TAMAÑO DE LA IMAGEN de una imagen BMP.
unsigned int parameters::image_size(char cabecera[54])
{

  unsigned int image_size;

  image_size = static_cast<unsigned char>(cabecera[34]) +
               static_cast<unsigned char>(cabecera[35]) * 256 +
               static_cast<unsigned char>(cabecera[36]) * 256 * 256 +
               static_cast<unsigned char>(cabecera[37]) * 256 * 256 * 256;

  if (image_size <= 0) {
    cerr << "[ERROR] Error obteniendo los datos de cabecera: valor del tamaño de la imagenes menor "
            "o igual a 0. \nvalor>: "
         << image_size << endl;
    exit(-1);
  }

  return image_size;
}


// Función que calcula los metadatos de una imagen BMP.
void parameters::meta_data_calculator(string file_path, unsigned int (&datos_devueltos)[8])
{
  char cabecera[54];
  char marca1, marca2;
  ifstream fichero(file_path, ifstream::binary);
  if (fichero.fail()) {
    show_error_archivo(file_path, "meta_data_calculator", "parameters_bmp.cpp");
  }
  else {
    marca1 = fichero.get();
    marca2 = fichero.get();
    if ((marca1 == 'B') && (marca2 == 'M')) {
      fichero.seekg(0, fichero.beg);
      fichero.read(cabecera, 54);
      fichero.close();
      datos_devueltos[0] = parameters::ancho_calculator(cabecera);
      datos_devueltos[1] = parameters::alto_calculator(cabecera);
      datos_devueltos[2] = parameters::size_calculator(cabecera);
      datos_devueltos[3] = parameters::color_calculator(cabecera);
      datos_devueltos[4] = parameters::inicio_imagen_calculator(cabecera);
      datos_devueltos[5] = parameters::compresion_calculator(cabecera);
      datos_devueltos[6] = parameters::num_planos_calculator(cabecera);
      if (datos_devueltos[7] <= datos_devueltos[2] - 54) {
        datos_devueltos[7] = parameters::image_size(cabecera);
      }
      else {
        cerr << "[ERROR] Error obteniendo los datos de cabecera: valor del tamaño del archivo no "
                "es válido (mayor que el tamaño de archivo) \n"
             << "valor tamaño archivo: " << datos_devueltos[2]
             << "\nvalor tamaño imagen: " << datos_devueltos << endl;
        exit(-1);
      }
    }
    else {
      cerr << "[ERROR] " << file_path << " no es un fichero BMP." << endl;
      exit(-1);
    }
  }
}



// Función que calcula los parámetros de una imagen BMP llamando a la función anterior.
parameters::meta_int_data parameters::meta_data(string path_input)
{
  string file_path = path_input;
  unsigned int meta_data_file[] = {0, 0, 0, 0, 0, 0, 0, 0};
  meta_int_data returned_data;
  parameters::meta_data_calculator(file_path, meta_data_file);
    
  returned_data.ancho_data = meta_data_file[0];
  returned_data.alto_data = meta_data_file[1];
  returned_data.size_data = meta_data_file[2];
  returned_data.colores_data = meta_data_file[3];
  returned_data.inicio_image = meta_data_file[4];
  returned_data.compresion_data = meta_data_file[5];
  returned_data.planos_datos = meta_data_file[6];
  returned_data.tamano_imagen = meta_data_file[7];

  return returned_data;
}
