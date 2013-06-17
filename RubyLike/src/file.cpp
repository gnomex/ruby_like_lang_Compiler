#include "file.h"
/*
 *  Abre arquivo para leitura/escrita, de acordo com o type
 *  Type = 1 => leitura
 *  Type = 0 => escrita
 */
File::File(const string& fileName, int type)
{
    if(type){
        in.open(fileName.c_str(), ios_base::in);
        this->type = type;
    }
    else{
        out.open(fileName.c_str(), ios_base::out | ios_base::app);
        this->type = type;
    }
}

File::~File(){
    if(in) in.close();
    if(out) out.close();
}
/*
 *  Abre arquivo para leitura/escrita, de acordo com o type
 *  Type = 1 => leitura
 *  Type = 0 => escrita
 */
void File::open(const string& fileName, int type){
    if(type){
        in.open(fileName.c_str(), ios_base::in);
        this->type = type;
    }
    else{
        out.open(fileName.c_str(), ios_base::out | ios_base::app);
        this->type = type;
    }
}
/*
 *  Verifica se o arquivo esta aberto
 */
bool File::isOpen(){
    if(type){ //se leitura
        if(in) return true;
        else return false;
    }
    else{//escrita
        if(out) return true;
        else return false;
    }
}
/*
 *  Fecha o arquivo
 */
void File::close(){
    if(in) in.close();
    if(out) out.close();
}
/*
 *  Le um caractere do arquivo
 */
char File::readChar(){
    if(in) return (char)in.get();
}
/*
 *  Le uma linha do arquivo
 */
char* File::readString(){
    char *buffer = NULL;
    in.seekg(0, ios_base::end);
    int length = in.tellg();
    in.seekg(0, ios_base::beg);

    if(in){
        buffer = new char[length];
        in.read(buffer,length);

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
/*
 *  Escreve dados no arquivo de saida
 */
void File::writeData(string str){
    if(out) out.write(str.c_str(),str.size());
}
