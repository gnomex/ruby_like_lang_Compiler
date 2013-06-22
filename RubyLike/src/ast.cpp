#include "ast.h"

AST* AST::instance = NULL;

AST::AST()
{
}

AST::~AST(){}

AST* AST::getInstance(){
    if(instance == NULL) instance = new AST();
    return instance;
}

TokenType* AST::getRoot(){
    return root;
}

void AST::insere(TokenType *no){

    if( root == NULL ){
        root = no;
    }
    else{
        TokenType *atual = root;

        while(atual->getNext() != NULL) atual = atual->getNext();

        atual->setNext(no);
    }
}
