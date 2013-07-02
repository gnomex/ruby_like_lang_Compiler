#ifndef TLIST_H
#define TLIST_H

#include "Defs.h"
#include "tokentype.h"

class TList : public TokenType
{
    private:
        QList<TokenType*>       list;
    public:
        TList();
        ~TList();
        void                    setList(TokenType *list);
        void                    insere(TokenType* token);
        TokenType*              getIndexOf(int index);
        void                    showItens();
};

#endif // TLIST_H
