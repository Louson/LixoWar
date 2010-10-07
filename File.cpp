#include <fstream>

#include "File.h"


File::File(const char * path_file){

   file.open(path_file);
   if(!file.is_open()) throw ExceptionBadPath();


}
