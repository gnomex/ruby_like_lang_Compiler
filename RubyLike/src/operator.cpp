#include "operator.h"

Operator::Operator()
{
}

Operator::~Operator(){}
/*****************************************************************************************************
 *  setOperator -> seta token operador/logico/relacional
 *
 ****************************************************************************************************/
void Operator::setOperator(TokenType* opr){
    setClasse(opr->getClasse());
    setToken(opr->getToken());
    setColumn(opr->getColumn());
    setLine(opr->getLine());
}
/*****************************************************************************************************
 *  setLeft -> seta expressao ou constante a esquerda
 *
 ****************************************************************************************************/
void Operator::setLeft(TokenType* left){
    this->left = left;
}
/*****************************************************************************************************
 *  setRight -> seta expressao ou constante a direita
 *
 ****************************************************************************************************/
void Operator::setRight(TokenType* right){
    this->right = right;
}
/*****************************************************************************************************
 *  getLeft -> retorna expressao ou constante a esquerda
 *
 ****************************************************************************************************/
TokenType* Operator::getLeft(){
    return left;
}
/*****************************************************************************************************
 *  getRight -> retorna expressao ou constante a direita
 *
 ****************************************************************************************************/
TokenType* Operator::getRight(){
    return right;
}
