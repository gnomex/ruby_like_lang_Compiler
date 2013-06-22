#ifndef LEX_H
#define LEX_H

#include "file.h"
#include "tokentype.h"
#include "ast.h"
#include "attrib.h"

class Lex
{
    private:
        AST             *ast;
        char            *input;
        int             line;
        int             column;

        TokenType*      getToken();
        void            recognizeIdentifier(TokenType* no);
        void            recognizeIntegerOrFloat(TokenType* no);
        void            skipLayoutAndComment();
        void            showError(const string msg);
    public:
        Lex();
        ~Lex();

        void            parser();
        void            startLex(File &file);

        void            show();
};

#endif // LEX_H
