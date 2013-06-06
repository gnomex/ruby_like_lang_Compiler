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
        static ProducerList* instance;
        QList<TokenType*> list;
        ProducerList();
    public:
        ~ProducerList();
        static ProducerList* getInstance();
        void insert(TokenType *i);
        TokenType* getTokenOfList(int i);
        char* getString();
        void showValues();
        void showValueAt(int index);
};

#endif // PRODUCERTABLE_H
