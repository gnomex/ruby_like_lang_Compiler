#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "Defs.h"
#include "ast.h"
#include "attrib.h"
#include "each.h"
#include "error.h"
#include "ifelse.h"
#include "operator.h"
#include "tlist.h"

class Semantic
{
    private:
        AST *ast;
        Error *erro;
        void review(TokenType *token);
        void reviewOperation(Operator *op);
    public:
        Semantic();
        ~Semantic();
        void parsing();
};

#endif // SEMANTIC_H
