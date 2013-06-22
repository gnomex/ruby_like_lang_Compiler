#ifndef AST_H
#define AST_H

#include "tokentype.h"

class AST
{
    private:
        static AST* instance;
        TokenType* root;
        AST();
    public:
        ~AST();
        static AST* getInstance();
        TokenType* getRoot();
        void insere(TokenType *no);
};

#endif // AST_H
