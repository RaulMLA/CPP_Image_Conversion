#include "../common/progargs.hpp"
#include "../soa/calls_soa.hpp"
#include <cmath>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace progargs;
using std::filesystem::directory_iterator;
using namespace calls_soa;


// Función MAIN para el programa SOA.
// Se encarga de comprobar los parámertos y de realizar la operación deseada a cada fichero
// del directorio de entrada indicado. Para ello se realizan llamadas a las funciones
// call_oper_soa, que se encargan de preparar la llamada a la función que realizará la
// operación final. Además, se lleva a cabo un cálculo del tiempo total que requiere
// la ejecución de la operación en cada archivo, la cuál es desglosada dependiendo de los
// procesos que se llevan a cabo.
int main(int argc, char * argv[])
{
  if (argc != 4) {
    cerr << "Wrong format:\n  image in_path out_path oper\n    operation: copy, histo, mono, gauss"
         << endl;
    exit(-1);
  }
  string in_path = argv[1];
  string out_path = argv[2];
  string oper = argv[3];
  comprobar_argumentos(in_path, out_path, oper);
  cout << "Input path: " << filesystem::directory_entry(in_path).path() << endl;
  cout << "Output path: " << filesystem::directory_entry(out_path).path() << endl;
  for (const auto & file : directory_iterator(in_path)) {
    float total_timer = clock();
    if (oper == "copy") call_copy_soa(in_path, out_path, file);
    if (oper == "histo") call_hist_soa(in_path, out_path, file);
    if (oper == "mono") call_mono_soa(in_path, out_path, file);
    if (oper == "gauss") call_gauss_soa(in_path, out_path, file);
    cout << "File: " << file << " (time " << ((clock() - total_timer) / CLOCKS_PER_SEC) * 1000000
         << ")" << endl;
  }
}