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
    if(!list.contains(i)) list.push_back(i);
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
    cout<<"+------------------------------------------------------------------------------+"<<endl;
    cout<<"Classe:\t\tToken:\t\tLinha:\t\tColuna:"<<endl;
    cout<<"+------------------------------------------------------------------------------+"<<endl;
    for(it = list.begin(); it != list.end(); ++it){
        TokenType *v = *it;
        cout<<getTypeClass(v->getClasse())
           <<"\t\t"<<v->getToken()<<"\t\t"<<v->getLine()<<"\t\t"<<v->getColumn()<<endl;
        cin.get();
    }
    cout<<"+------------------------------------------------------------------------------+"<<endl;
}

string ProducerList::getTypeClass(int classe){
    switch(classe){
        case FIM: return "FIM";
        case IDENTIFIER: return "VAR";
        case INTEGER: return "INTEIRO";
        case FLOAT: return "REAL";
        case MAIOR: return ">";
        case MAIOR_IGUAL: return ">=";
        case MENOR: return "<";
        case MENOR_IGUAL: return "<=";
        case IGUAL: return "==";
        case NOT_EQUAL: return "!=";
        case SEPARATOR: return "SEPAR";
        case BLOCO: return "{ ou }";
        case LOGICAL: return "LOGICO";
        case IF: return "IF";
        case LIST: return "LIST";
        case ASSIGN: return "=";
        case SETA: return "->";
        case END_CMD: return "!";
        case LOOP: return "LOOP";
        case OPERATOR: return "OP";
        case STRING: return "String";
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
