#ifndef LEX_H
#define LEX_H

#include "Defs.h"

class Lex
{
    private:

        char *input;
        int dot;
        int inputChar;

        void nextChar();
        void recognizeIdentifier();
        void recognizeInteger();
        void skipLayoutAndComment();
        void noteTokenPosition();
        void startLex();
        char* inputToZString (int iStart, int iLength);
        void getNextToken();

    public:
        Lex();
        ~Lex();
        char* getInput();


};

#endif // LEX_H
