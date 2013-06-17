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
        char *input;
        int dot;
        int startDot;
        int inputChar;
        int line;
        bool ifstmt;
        bool liststmt;

        void nextChar();
        void recognizeIdentifier(TokenType* no);
        void recognizeIntegerOrFloat(TokenType* no);
        void recognizeList(TokenType *no);
        void skipLayoutAndComment();
        string inputToZString(int iStart, int iLength);
        bool getNextToken(TokenType* noStatement);

        bool listBlock(TokenType* noStatement, TokenType* current);
        void setAssign(int inputChar, TokenType* no);

        bool isDoubleAssign();
        void showError(int inputChar, const string msg);

        //analise sintatica
        void identifierErrors(int inputChar, TokenType *no);
        void digitErrors(int inputChar);
        bool ifStatementBlock(TokenType* noStatement, TokenType* current);
        void assignErrors(int inputChar);

    public:
        Lex();
        ~Lex();

        void parser();
        void startLex(File &file);
};

#endif // LEX_H
