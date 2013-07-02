#include "tlist.h"

TList::TList()
{
}

TList::~TList(){

}
/*****************************************************************************************************
 *  setList -> seta informaçoes da lista
 *
 ****************************************************************************************************/
void TList::setList(TokenType *list){
    setClasse(list->getClasse());
    setToken(list->getToken());
    setLine(list->getLine());
    setColumn(list->getColumn());
    setType(list->getType());
}
/*****************************************************************************************************
 *  insere -> coloca um token na lista de itens
 *
 ****************************************************************************************************/
void TList::insere(TokenType *token){
    list.push_back(token);
}
/*****************************************************************************************************
 *  getIndexOf -> retorna um token de acordo com o indice
 *
 ****************************************************************************************************/
TokenType* TList::getIndexOf(int index){
    if(index < 0 || index > list.size()) return NULL;
    return list[index];
}
/*****************************************************************************************************
 *  showItens -> apenas para ver o que tem
 *
 ****************************************************************************************************/
void TList::showItens(){
    QList<TokenType*>::Iterator it;
    TokenType *t;

    for(it = list.begin(); it != list.end(); ++it){
        t = *it;
        cout<<t->getToken()<<" ";
    }
    cout<<endl;
}
