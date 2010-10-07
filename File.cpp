#include <fstream>
#include <cstdlib>
#include <iostream>

#include "File.h"

File::File(const char * path_file) throw(ExceptionBadPath){
    ifstream file(path_file);
    string str_buf;
    size_t com = 0, sep = 0;
    string  param, value;

    if(file.fail()) throw ExceptionBadPath();

    while(getline(file,str_buf)){

        if((com = str_buf.find('#')) != string::npos)
            str_buf.erase(com);

        if((sep = str_buf.find('=')) != string::npos){
            param = str_buf.substr(0,sep);
            sep++; /* jump the '=' char */
            value = str_buf.substr(sep);

            for(size_t i= param.find(' '); i != string::npos; i = param.find(' ',i))
                param.erase(i,1);

            for(size_t i = value.find(' '); i != string::npos; i = value.find(' ',i))
                value.erase(i,1);

            if(!param.empty() && !value.empty())
                lines.insert(pair<string,string>(param,value));
        }
    }
    file.close();
}

int File::getParamInt(const string & param) throw(ExceptionParamInexistent){
    map<string,string>::const_iterator it = lines.find(param);
    
    if(it == lines.end()) throw ExceptionParamInexistent();
   
    return atoi((*it).second.c_str());
}
