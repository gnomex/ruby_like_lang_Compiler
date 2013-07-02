#ifndef SYNTACTIC_H
#define SYNTACTIC_H

#include "lex.h"
#include "ast.h"
#include "producerlist.h"
#include "operator.h"
#include "attrib.h"
#include "ifelse.h"
#include "each.h"
#include "error.h"
#include "tlist.h"

class Syntactic
{
    private:
        Lex             *lex;
        AST             *ast;
        Error*          erro;
        ProducerList    *prod;
        TokenType       *temp;

        TList           *syntacticList(TokenType *til);
        Operator        *syntacticLogicalOrOperator(TokenType *opr, TokenType *var);
        Attrib          *syntacticAssign(TokenType *attr, TokenType *var);
        IFElse          *syntacticIFstmt(TokenType *token);
        Each            *syntacticEach(TokenType *token);
        Attrib          *syntacticIdentifier(TokenType *token);
        void            syntacticPrivate(TokenType *token);
        void            hasTemp();

        void            expressionIFBlock(IFElse *__if);
        void            blockIFELSEstmt(IFElse *__if, bool who);

        void            eachExpression(Each *each);
        void            eachBlock(Each *each);
    public:
        Syntactic(Lex* lex);
        ~Syntactic();

        void            parser();
        void            show();
};

#endif // SYNTACTIC_H
