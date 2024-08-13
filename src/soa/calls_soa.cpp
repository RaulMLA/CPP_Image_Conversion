#include "../common/parameters_bmp.hpp"
#include "../soa/calls_soa.hpp"
#include "../soa/copy_soa.hpp"
#include "../soa/gauss_soa.hpp"
#include "../soa/hist_soa.hpp"
#include "../soa/lectura_soa.hpp"
#include "../soa/mono_soa.hpp"
#include <filesystem>
#include <iostream>
#include <vector>

using namespace std;
using std::filesystem::directory_iterator;
using namespace parameters;
using namespace lectura_soa;
using namespace copy_soa;
using namespace mono_soa;
using namespace hist_soa;
using namespace gauss_soa;
using namespace calls_soa;


// Función que prepara la llamada a la función COPY para SOA.
void calls_soa::call_copy_soa(string in_path, string out_path, filesystem::directory_entry file)
{

  string path = filesystem::directory_entry(in_path).path();
  string output_file_path;
  meta_int_data header;
  imagen vector_lectura;

  output_file_path = (static_cast<string>(file.path())).substr(path.size());
  output_file_path = (static_cast<string>((filesystem::directory_entry(out_path).path()))) +
                     output_file_path.substr(0, (output_file_path.size() - 4)) + "_copy.bmp";

  header = meta_data(file.path());
  vector_lectura = leer_pixeles_SOA(file.path(), header);
  copy_SOA(header, file.path(), output_file_path, vector_lectura);
}


// Función que prepara la llamada a la función HIST para SOA.
void calls_soa::call_hist_soa(string in_path, string out_path, filesystem::directory_entry file)
{

  string path = filesystem::directory_entry(in_path).path();
  string output_file_path;
  meta_int_data header;

  output_file_path = (static_cast<string>(file.path())).substr(path.size());
  output_file_path = (static_cast<string>((filesystem::directory_entry(out_path).path()))) +
                     output_file_path.substr(0, (output_file_path.size() - 4)) + ".hst";

  header = meta_data(file.path());
  hist(file.path(), header, output_file_path);
}


// Función que prepara la llamada a la función MONO para SOA.
void calls_soa::call_mono_soa(string in_path, string out_path, filesystem::directory_entry file)
{

  string path = filesystem::directory_entry(in_path).path();
  string output_file_path;
  meta_int_data header;

  output_file_path = (static_cast<string>(file.path())).substr(path.size());
  output_file_path = (static_cast<string>(filesystem::directory_entry(out_path).path())) +
                     output_file_path.substr(0, (output_file_path.size() - 4)) + "_mono.bmp";

  header = meta_data(file.path());
  mono(file.path(), output_file_path, header);
}


// Función que prepara la llamada a la función GAUSS para SOA.
void calls_soa::call_gauss_soa(string in_path, string out_path, filesystem::directory_entry file)
{

  string path = filesystem::directory_entry(in_path).path();
  string output_file_path;
  meta_int_data header;

  output_file_path = (static_cast<string>(file.path())).substr(path.size());
  output_file_path = (static_cast<string>((filesystem::directory_entry(out_path).path()))) +
                     output_file_path.substr(0, (output_file_path.size() - 4)) + "_gauss.bmp";

  header = meta_data(file.path());
  gauss(file.path(), output_file_path, header);
}
