#ifndef TOKENTYPE_H
#define TOKENTYPE_H

#include "Defs.h"
/*
 *  Classe para representar um token
 *
 */
class TokenType
{
    private:
        int classe;            //tipo de token
        string repr;            //token
        int line;               //linha do arquivo
        int column;             //coluna do arquivo
        TokenType *next;

    public:
        TokenType();
        ~TokenType();
        void setClasse(int classe);
        void setToken(string repr);
        void setLine(int line);
        void setColumn(int column);
        int getClasse();
        string getToken();
        int getLine();
        int getColumn();
        void setNext(TokenType *no);
        TokenType* getNext();

};

#endif // TOKENTYPE_H
