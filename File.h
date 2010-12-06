#ifndef _FICHIER_H
#define _FICHIER_H

#include <map>
#include <exception>
#include <string>

using namespace std;

/**
 * Is used to parse a config file of the type
 * 
 * #commentary
 * param1 = value1
 * param2 = value2
 *
 * There is no verification of the syntax of the config
 * file. If the syntax is uncorrect, the behavior is undefined.
 */
class File{
    private:
        map<string,string> lines;

    public:

        class ExceptionBadPath:public std::exception{};
        class ExceptionParamInexistent:public std::exception{};

        File(const char * path) throw(ExceptionBadPath);

        int getParamInt(const string &) const throw(ExceptionParamInexistent);
        const string getParamString(const string &) const throw(ExceptionParamInexistent);
};

#endif
