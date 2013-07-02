#include "attrib.h"

Attrib::Attrib()
{
}

Attrib::~Attrib(){

}
/*****************************************************************************************************
 *  setAttrib -> seta informacoes do token '='
 *
 ****************************************************************************************************/
void Attrib::setAttrib(TokenType* attrib){
    setClasse(attrib->getClasse());
    setToken(attrib->getToken());
    setColumn(attrib->getColumn());
    setLine(attrib->getLine());
    setType(attrib->getType());
}
/*****************************************************************************************************
 *  setIdentificador -> coloca a variavel a esquerda
 *
 ****************************************************************************************************/
void Attrib::setIdentificador(TokenType* var){
    this->left = var;
}
/*****************************************************************************************************
 *  setExpression -> coloca a constante ou expressao a direita
 *
 ****************************************************************************************************/
void Attrib::setExpression(TokenType* exp){
    this->right = exp;
}
/*****************************************************************************************************
 *  getIdentificador -> retorna variavel
 *
 ****************************************************************************************************/
TokenType* Attrib::getIdentificador(){
    return left;
}
/*****************************************************************************************************
 *  getExpression -> retorna constante ou expressao
 *
 ****************************************************************************************************/
TokenType* Attrib::getExpression(){
    return right;
}
