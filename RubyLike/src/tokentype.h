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
        int             classe;             //tipo de token
        string          repr;               //token
        int             line;               //linha do arquivo
        int             column;             //coluna do arquivo
        int             type;               //para sub tipo (int/float/string/list)
        TokenType       *next;

    public:
        TokenType();
        ~TokenType();

        void            setClasse(int classe);
        void            setToken(string repr);
        void            setLine(int line);
        void            setColumn(int column);
        void            setNext(TokenType *no);
        void            setType(int type);

        int             getClasse();
        string          getToken();
        int             getLine();
        int             getColumn();
        int             getType();
        TokenType*      getNext();

};

#endif // TOKENTYPE_H
