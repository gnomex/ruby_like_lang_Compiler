#ifndef LEX_H
#define LEX_H

#include "file.h"
#include "tokentype.h"
#include "error.h"
#include "producerlist.h"
#include "tablesymbol.h"

class Lex
{
    private:
        Error*          erro;       //para mensagens de erros
        TableSymbol*    reser;      //simbolos reservados
        char            *input;
        int             line;
        int             column;


        void            recognizeIdentifier(TokenType* no);
        void            recognizeIntegerOrFloat(TokenType* no);
        void            skipLayoutAndComment();
    public:
        Lex();
        ~Lex();

        void            startLex(File &file);
        TokenType*      getToken();

};

#endif // LEX_H
