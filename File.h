#ifndef _FICHIER_H
#define _FICHIER_H

#include <fstream>
#include <vector>

using namespace std;

class File{
    private:
        ifstream file;

    public:
        File(const char * path);
        void getParamInt(vector<int *>);

        class ExceptionBadPath{};

};

#endif
