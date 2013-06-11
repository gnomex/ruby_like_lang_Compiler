#ifndef LEX_H
#define LEX_H

#include "file.h"
#include "producerlist.h"
#include "tablesymbol.h"
#include "tokentype.h"

class Lex
{
    private:
        ProducerList *list;
        string input;
        int dot;
        int inputChar;

        void nextChar();
        void recognizeIdentifier(TokenType *no);
        void recognizeInteger(TokenType *no);
        void skipLayoutAndComment();
        void noteTokenPosition();
        string inputToZString(int iStart, int iLength);
        void getNextToken();
        bool startLex(File &file);

    public:
        Lex();
        ~Lex();

        bool parser(File& file);
};

#endif // LEX_H
