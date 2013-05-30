#include "file.h"

File::File(const char *fileName, int type)
{
    if(type){
        in.open(fileName, ios_base::in);
    }
    else{
        out.open(fileName, ios_base::out | ios_base::app);
    }
}

File::~File(){
    if(in) in.close();
    if(out) out.close();
}

void File::open(const char *fileName, int type){
    if(type){
        in.open(fileName, ios_base::in);
    }
    else{
        out.open(fileName, ios_base::out | ios_base::app);
    }
}

void File::close(){
    if(in) in.close();
    if(out) out.close();
}

char File::readChar(){
    if(in) return (char)in.get();
}

char* File::readString(){
    char *buffer = NULL;

    if(in){
        buffer = new char[255];
        in.read(buffer,254);
    }

    return buffer;
}

/*string* File::readString(){
    char *buffer = NULL;
    string *res;

    if(in){
        buffer = new char[255];
        in.read(buffer,254);
        res = new string(buffer);
    }

    return res;
}*/

void File::writeData(string str){
    if(out) out.write(str.c_str(),str.size());
}
