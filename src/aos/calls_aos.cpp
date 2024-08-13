#include "../aos/calls_aos.hpp"
#include "../aos/copy_aos.hpp"
#include "../aos/gauss_aos.hpp"
#include "../aos/hist_aos.hpp"
#include "../aos/lectura_aos.hpp"
#include "../aos/mono_aos.hpp"
#include "../common/parameters_bmp.hpp"
#include <ctime>
#include <filesystem>
#include <iostream>
#include <vector>

using namespace std;
using std::filesystem::directory_iterator;
using namespace parameters;
using namespace lectura_aos;
using namespace copy_aos;
using namespace mono_aos;
using namespace hist_aos;
using namespace gauss_aos;
using namespace calls_aos;

// Función que prepara la llamada a la función COPY para AOS.
void calls_aos::call_copy_aos(string in_path, string out_path, filesystem::directory_entry file)
{
  string path = filesystem::directory_entry(in_path).path();
  string output_file_path;
  meta_int_data header;
  vector<pixel> vector_lectura;

  output_file_path = (static_cast<string>(file.path())).substr(path.size());
  output_file_path = (static_cast<string>((filesystem::directory_entry(out_path).path()))) +
                     output_file_path.substr(0, (output_file_path.size() - 4)) + "_copy.bmp";

  header = meta_data(file.path());
  vector_lectura = leer_pixeles_AOS(file.path(), header);
  copy_AOS(header, file.path(), output_file_path, vector_lectura);
}


// Función que prepara la llamada a la función HIST para AOS.
void calls_aos::call_hist_aos(string in_path, string out_path, filesystem::directory_entry file)
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


// Función que prepara la llamada a la función MONO para AOS.
void calls_aos::call_mono_aos(string in_path, string out_path, filesystem::directory_entry file)
{

  string path = filesystem::directory_entry(in_path).path();
  string output_file_path;
  meta_int_data header;

  output_file_path = (static_cast<string>(file.path())).substr(path.size());
  output_file_path = (static_cast<string>(filesystem::directory_entry(out_path).path())) +
                     output_file_path.substr(0, (output_file_path.size() - 4)) + "_mono.bmp";

  header = meta_data(file.path());
  mono(file.path(), header, output_file_path);
}


// Función que prepara la llamada a la función GAUSS para AOS.
void calls_aos::call_gauss_aos(string in_path, string out_path, filesystem::directory_entry file)
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
