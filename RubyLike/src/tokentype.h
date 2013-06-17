#ifndef TOKENTYPE_H
#define TOKENTYPE_H

#include "Defs.h"
/*
 *  Classe para representar um token
 *
 */
class TokenType
{
    private:
        int classe;            //tipo de token
        string repr;            //token
        int line;               //linha do arquivo
        int column;             //coluna do arquivo
        bool statmentInit;      //inicio da expressao logica
        bool statmentEnd;       //fim da expressao logica
        TokenType *ref;         //referencia ao token que pertence
        TokenType *initBlock;   //se for inicio de bloco {
        TokenType *endBlock;    //se for fim do bloco

    public:
        TokenType();
        ~TokenType();
        void setClasse(int classe);
        void setToken(string repr);
        void setLine(int line);
        void setColumn(int column);
        int getClasse();
        string getToken();
        int getLine();
        int getColumn();

        void setReference(TokenType* ref);
        void setInitBlock(TokenType* init);
        void setEndBlock(TokenType* end);

        TokenType* getReference();
        TokenType* getInitBlock();
        TokenType* getEndBlock();

        void setStatmentInit(bool init);
        void setStatmentEnd(bool end);
        bool getStatmentInit();
        bool getStatmentEnd();
};

#endif // TOKENTYPE_H
