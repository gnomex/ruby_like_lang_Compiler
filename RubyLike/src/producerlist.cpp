#include "producerlist.h"
// singleton
ProducerList* ProducerList::instance = NULL;

ProducerList::ProducerList(){

}

ProducerList::~ProducerList(){

}
/*****************************************************************************************************
 *  getInstance -> retorna instancia unica da classe
 *
 ****************************************************************************************************/
ProducerList* ProducerList::getInstance(){
    if(instance == NULL) instance = new ProducerList();
    return instance;
}

/*****************************************************************************************************
 *  insert -> insere novo token na lista de producoes
 *
 ****************************************************************************************************/
void ProducerList::insert(TokenType *i){
    list.push_front(i);
}
/*****************************************************************************************************
 *  getString -> backend
 *
 ****************************************************************************************************/
string ProducerList::getString(){
    //saida
}
/*****************************************************************************************************
 *  getTokenOfList -> retorna token se existe na lista
 *
 ****************************************************************************************************/
TokenType *ProducerList::getTokenOfList(string prod){
    QList<TokenType*>::Iterator it;

    for(it = list.begin(); it != list.end(); ++it){
        TokenType *v = *it;
        if(v->getToken() == prod) return v;
    }
    return NULL;
}
/*****************************************************************************************************
 *  showValues ->
 *
 ****************************************************************************************************/
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
/*****************************************************************************************************
 *  showValueAt ->
 *
 ****************************************************************************************************/
void ProducerList::showValueAt(int index){
    TokenType *v = list.at(index);

    cout<<endl<<endl;
    cout<<"Classe: "<<v->getClasse()<<endl;
    cout<<"Token: "<<v->getToken()<<endl;
}
/*****************************************************************************************************
 *  isProducer -> verifica se existe um token na lista
 *  True => existe
 *  False => ...
 ****************************************************************************************************/
bool ProducerList::isProducer(string prod){
    QList<TokenType*>::Iterator it;

    for(it = list.begin(); it != list.end(); ++it){
        TokenType *v = *it;
        if(v->getToken() == prod) return true;
    }
}
