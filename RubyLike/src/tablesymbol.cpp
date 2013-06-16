#include "tablesymbol.h"

TableSymbol* TableSymbol::instance = NULL;

TableSymbol::TableSymbol()
{
    initTable();
}

TableSymbol::~TableSymbol(){

}
/*****************************************************************************************************
 *  initTable -> inicializa tabela de palavras reservadas
 *
 ****************************************************************************************************/
void TableSymbol::initTable(){
    table.insert("if", true);
    table.insert("for", true);
    table.insert("while", true);
    table.insert("puts", true);
    table.insert("print", true);
}
/*****************************************************************************************************
 *  showKeysValues ->
 *
 ****************************************************************************************************/
void TableSymbol::showKeysValues(){
    QHash<const char*,bool>::Iterator it;

    for(it = table.begin(); it != table.end(); ++it)
        cout<<"Key: "<<it.key()<<" Value: "<<it.value()<<endl;
}
/*****************************************************************************************************
 *  findSymbol -> verifica se o token existe na tabela
 *
 ****************************************************************************************************/
bool TableSymbol::findSymbol(string str){
    return table.contains(str.c_str());
}
/*****************************************************************************************************
 *  getIntance -> retorna instancia unica da classe
 *
 ****************************************************************************************************/
TableSymbol* TableSymbol::getInstance(){
    if(instance == NULL) instance = new TableSymbol();
    return instance;
}
