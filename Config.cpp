#include "Config.h"

int Config::fetchParam(const string & paramName,int defaultValue,const File & configFile){
    try{
        return configFile.getParamInt(paramName);
    }catch(const File::ExceptionParamInexistent &){
        return defaultValue;
    }
}
