#ifndef IFELSE_H
#define IFELSE_H

#include "tokentype.h"

class IFElse : public TokenType
{
    private:
        TokenType *expr;        //expressao logica
        TokenType *block;       //bloco do if
        TokenType *elseBlock;   //se tiver else, se nao eh NULL
    public:
        IFElse();
        ~IFElse();

        void setIF(TokenType *_if);
        void setExpression(TokenType *expr);
        void setBlockIF(TokenType *block);
        void setElseBlock(TokenType *block);

        TokenType* getExpression();
        TokenType* getBlockIF();
        TokenType* getElseBlock();
};

#endif // IFELSE_H
