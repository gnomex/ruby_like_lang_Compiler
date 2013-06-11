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
        char classe;    //tipo de token
        string repr;     //token
        int line;       //linha do arquivo
        int column;     //coluna do arquivo

    public:
        TokenType();
        ~TokenType();
        void setClasse(char classe);
        void setToken(string repr);
        void setLine(int line);
        void setColumn(int column);
        char getClasse();
        string getToken();
        int getLine();
        int getColumn();
};

#endif // TOKENTYPE_H
