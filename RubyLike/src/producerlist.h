#ifndef PRODUCERLIST_H
#define PRODUCERLIST_H

#include "tokentype.h"

/*
 * Classe que armazena as producoes da analise lexica
 */
class ProducerList
{
    private:
        static ProducerList* instance;  //singleton
        QList<TokenType*> list;         //producoes
        ProducerList();
        string getTypeClass(int classe, int token);
    public:
        ~ProducerList();
        static ProducerList* getInstance(); //singleton
        void insert(TokenType* i);          //salva um token
        TokenType* getTokenOfList(string prod);   //recupera um token
        bool isProducer(string prod);
        string getString();
        void showValues();
        void showValueAt(int index);
};

#endif // PRODUCERTABLE_H
