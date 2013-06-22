#ifndef EACH_H
#define EACH_H

#include "tokentype.h"

class Each : public TokenType
{
    private:
        TokenType *expr;
        TokenType *block;
    public:
        Each();
        ~Each();

        void setEach(TokenType *each);
        void setExpression(TokenType *expr);
        void setBlock(TokenType *block);

        TokenType *getExpression();
        TokenType *getBlock();
};

#endif // EACH_H
