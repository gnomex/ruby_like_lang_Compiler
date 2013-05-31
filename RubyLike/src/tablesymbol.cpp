#include "tablesymbol.h"

TableSymbol::TableSymbol()
{
    initTable();
}

TableSymbol::~TableSymbol(){

}

void TableSymbol::initTable(){
    table.insert("if", true);
    table.insert("for", true);
    table.insert("while", true);
    table.insert("puts", true);
    table.insert("print", true);
}

void TableSymbol::showKeysValues(){
    QHash<char*,bool>::Iterator it;

    for(it = table.begin(); it != table.end(); ++it)
        cout<<"Key: "<<it.key()<<" Value: "<<it.value()<<endl;
}
