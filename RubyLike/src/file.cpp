#include "file.h"
/*
 *  Abre arquivo para leitura/escrita, de acordo com o type
 *  Type = 1 => leitura
 *  Type = 0 => escrita
 */
File::File(const string& fileIN,const string& fileOut)
{
    in.open(fileIN.c_str(), ios_base::in);
    out.open(fileOut.c_str(), ios_base::out | ios_base::app);

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
void File::open(const string& fileIN,const string& fileOut){

    in.open(fileIN.c_str(), ios_base::in);
    out.open(fileOut.c_str(), ios_base::out | ios_base::app);

}
/*
 *  Verifica se o arquivo esta aberto
 */
bool File::isOpen(){
    if(in) return true;
    if(out) return true;

    return false;
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
/*
 *  Escreve dados no arquivo de saida
 */
void File::writeData(string str){
    if(out) out.write(str.c_str(),str.size());
}
