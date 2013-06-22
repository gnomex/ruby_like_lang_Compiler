#ifndef OPERATOR_H
#define OPERATOR_H

#include "tokentype.h"

class Operator : public TokenType
{
    private:
        TokenType *left;    //para identificador ou constante ou expressao
        TokenType *right;   //para identificador ou constante ou expressao
    public:
        Operator();
        ~Operator();

        void setOperator(TokenType* opr);
        void setLeft(TokenType* left);
        void setRight(TokenType* right);

        TokenType* getLeft();
        TokenType* getRight();
};

#endif // OPERATOR_H
