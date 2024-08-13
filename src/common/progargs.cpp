#include "progargs.hpp"
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
using namespace progargs;


// Función que comprueba los argumentos introducidos por terminal en la ejecución de los
// programas una vez que se ha comprobado que son 3 argumentos. Las comprobaciones que se
// realizan son:
// 1.- Operación correcta (copy, histo, mono o gauss).
// 2.- Directorio de entrada existe (más adelante se comprobará si se puede abrir).
// 2.- Directorio de salida existe (más adelante se comprobará si se puede abrir).
void progargs::comprobar_argumentos(string in_path, string out_path, string operation)
{
  if ((operation != "copy") and (operation != "histo") and (operation != "mono") and
      (operation != "gauss")) {
    cerr << "Unexpected operation:" << operation
         << "\nimage in_path out_path oper\noperation: copy, histo, mono, gauss" << endl;
    exit(-1);
  }
  if (!filesystem::directory_entry(in_path).exists()) {
    cerr << "Input path: " << in_path << "\nOutput path: " << out_path << "\nCannot open directory["
         << in_path << "]\n  image in_path out_path oper"
         << "\n    operation: copy, histo, mono, gauss" << endl;
    exit(-1);
  }
  if (!filesystem::directory_entry(out_path).exists()) {
    cerr << "Input path: " << in_path << "\nOutput path: " << out_path << "\nCannot open directory["
         << out_path << "]\n  image out_path out_path oper\n    operation: copy, histo, mono, gauss"
         << endl;
    exit(-1);
  }
}