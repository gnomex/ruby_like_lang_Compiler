#ifndef PRODUCERLIST_H
#define PRODUCERLIST_H

#include "tokentype.h"
#include "Defs.h"

/*
 * Classe que armazena as producoes da analise lexica
 */
class ProducerList
{
    private:
        static ProducerList* instance;  //singleton
        QList<TokenType> list;         //producoes
        ProducerList();
    public:
        ~ProducerList();
        static ProducerList* getInstance(); //singleton
        void insert(TokenType i);          //salva um token
        TokenType getTokenOfList(int i);   //recupera um token
        char* getString();
        void showValues();
        void showValueAt(int index);
};

#endif // PRODUCERTABLE_H
