#ifndef TABLESYMBOL_H
#define TABLESYMBOL_H

#include "Defs.h"

class TableSymbol
{
    private:
        QHash<char*,bool> table;
        void initTable();
    public:
        TableSymbol();
        ~TableSymbol();
        bool findSymbol(char *str);
        void showKeysValues();
};

#endif // TABLESYMBOL_H
