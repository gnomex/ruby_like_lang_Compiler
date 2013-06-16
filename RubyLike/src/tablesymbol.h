#ifndef TABLESYMBOL_H
#define TABLESYMBOL_H

#include "Defs.h"

class TableSymbol
{
    private:
        static TableSymbol* instance;
        QHash<const char*,bool> table;
        void initTable();
    public:
        TableSymbol();
        ~TableSymbol();
        bool findSymbol(string str);
        void showKeysValues();
        static TableSymbol* getInstance();
};

#endif // TABLESYMBOL_H
