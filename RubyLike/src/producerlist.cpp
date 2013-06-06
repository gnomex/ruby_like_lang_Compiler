#include "producerlist.h"

ProducerList* ProducerList::instance = NULL;

ProducerList::ProducerList(){

}

ProducerList::~ProducerList(){

}

ProducerList* ProducerList::getInstance(){
    if(instance == NULL) instance = new ProducerList();
    return instance;
}


void ProducerList::insert(TokenType *i){
    list.push_back(i);
}

char* ProducerList::getString(){
    //saida
}

TokenType* ProducerList::getTokenOfList(int i){
    return list.takeAt(i);
}

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

void ProducerList::showValueAt(int index){
    TokenType *v = list.at(index);

    cout<<endl<<endl;
    cout<<"Classe: "<<v->getClasse()<<endl;
    cout<<"Token: "<<v->getToken()<<endl;
}
