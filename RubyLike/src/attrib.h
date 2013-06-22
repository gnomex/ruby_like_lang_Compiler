#ifndef ATTRIB_H
#define ATTRIB_H

#include "tokentype.h"

class Attrib : public TokenType
{
    private:
        TokenType *left;    //para identificador
        TokenType *right;   //para contante ou expressao a direita
    public:
        Attrib();
        ~Attrib();

        void setAttrib(TokenType* attrib);
        void setIdentificador(TokenType* var);
        void setExpression(TokenType* exp);

        TokenType* getIdentificador();
        TokenType* getExpression();

};

#endif // ATTRIB_H
