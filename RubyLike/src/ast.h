#ifndef AST_H
#define AST_H

#include "tokentype.h"
#include "Defs.h"

class AST
{
    private:
        static AST* instance;
        TokenType *root;
        AST();
    public:
        ~AST();
        static AST* getInstance();
        TokenType* getRoot();
};

#endif // AST_H
