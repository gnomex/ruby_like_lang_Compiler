#ifndef FILE_H
#define FILE_H

#include "Defs.h"

class File
{
    private:
        ifstream in;
        ofstream out;
        int type;

    public:
        File(const char *fileName,int type);
        File(){}
        ~File();
        void open(const char *fileName,int type);
        bool isOpen();
        void close();
        char readChar();
        char* readString();
        //string *readString();
        void writeData(string str);
};

#endif // FILE_H
