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
        int startDot;
        int inputChar;
        int line;

        void nextChar();
        void recognizeIdentifier(TokenType* no);
        void recognizeIntegerOrFloat(TokenType* no);
        void recognizeList(TokenType *no);
        void skipLayoutAndComment();
        string inputToZString(int iStart, int iLength);
        void getNextToken(TokenType* noStatement);
        bool startLex(File &file);
        bool listBlock(TokenType* noStatement, TokenType* current);
        void setAssign(int inputChar, TokenType* no);

        bool isDoubleAssign();
        void showError(int inputChar, const string msg);

        //analise sintatica
        void identifierErrors(int inputChar);
        void digitErrors(int inputChar);
        bool ifStatementBlock(TokenType* noStatement, TokenType* current);
        void assignErrors(int inputChar);

    public:
        Lex();
        ~Lex();

        bool parser(File& file);
};

#endif // LEX_H
