#ifndef FILE_H
#define FILE_H

#include "Defs.h"
/*
 *  Classe que abre para leitura ou cria um arquivo
 *  para escrita.
 *  Usado pela classe Lex na producao de tokens
 *
 */
class File
{
    private:
        ifstream in;    //se for arquivo de entrada
        ofstream out;   //se for arquivo de saida
        int type;       //tipo de abertura

    public:
        File(const string& fileName,int type);
        File(){}
        ~File();
        void open(const string& fileName,int type);
        bool isOpen();
        void close();
        char readChar();
        string readString();
        //string *readString();
        void writeData(string str);
};

#endif // FILE_H
