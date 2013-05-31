#include "ast.h"

AST* AST::instance = NULL;

AST::AST()
{
    root = NULL;
}

AST::~AST(){

}

AST* AST::getInstance(){
    if(instance == NULL) instance = new AST();
    return instance;
}

TokenType* AST::getRoot(){
    if(root == NULL) root = new TokenType();
    return root;
}
