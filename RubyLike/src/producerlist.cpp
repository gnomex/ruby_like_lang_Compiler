#include "producerlist.h"
// singleton
ProducerList* ProducerList::instance = NULL;

ProducerList::ProducerList(){

}

ProducerList::~ProducerList(){

}
//  singleton
ProducerList* ProducerList::getInstance(){
    if(instance == NULL) instance = new ProducerList();
    return instance;
}

/*
 *  Insere um token na lista
 */
void ProducerList::insert(TokenType *i){
    list.push_back(i);
}
/*
 *  Sera usado para saida (compilacao)
 */
char* ProducerList::getString(){
    //saida
}
/*
 *  Recupera um token da lista
 */
TokenType* ProducerList::getTokenOfList(int i){
    return list.takeAt(i);
}
/*
 *  Mostra tokens da lista
 */
void ProducerList::showValues(){
    QList<TokenType*>::Iterator it;

    cout<<"Numero de elementos na lista: "<<list.length()<<endl;
    for(it = list.begin(); it != list.end(); ++it){
        TokenType *v = *it;
        cout<<"Classe: "<<v->getClasse()<<endl;
        cout<<"Token: "<<v->getToken()<<endl;
        cin.get();
    }
}
/*
 *  Mostra um token especifico
 */
void ProducerList::showValueAt(int index){
    TokenType *v = list.at(index);

    cout<<endl<<endl;
    cout<<"Classe: "<<v->getClasse()<<endl;
    cout<<"Token: "<<v->getToken()<<endl;
}
