#ifndef LEX_H
#define LEX_H

#include "file.h"
#include "producerlist.h"
#include "tablesymbol.h"
#include "tokentype.h"

class Lex
{
    private:
        ProducerList    *list;
        char            *input;
        int             line;
        int             column;

        TokenType*      getToken();
        void            recognizeIdentifier(TokenType* no);
        void            recognizeIntegerOrFloat(TokenType* no);
        void            skipLayoutAndComment();

    public:
        Lex();
        ~Lex();

        void            parser();
        void            startLex(File &file);
};

#endif // LEX_H
