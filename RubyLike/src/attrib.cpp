#include "attrib.h"

Attrib::Attrib()
{
}

Attrib::~Attrib(){

}
/*****************************************************************************************************
 *  setAttrib -> seta token de atribuicao
 *
 ****************************************************************************************************/
void Attrib::setAttrib(TokenType* attrib){
    setClasse(attrib->getClasse());
    setToken(attrib->getToken());
    setColumn(attrib->getColumn());
    setLine(attrib->getLine());
}
/*****************************************************************************************************
 *  setIdentificador -> seta variavel a esquerda da atribuicao
 *
 ****************************************************************************************************/
void Attrib::setIdentificador(TokenType* var){
    this->left = var;
}
/*****************************************************************************************************
 *  setExpression -> seta expressao matematica ou constante a direita
 *
 ****************************************************************************************************/
void Attrib::setExpression(TokenType* exp){
    this->right = exp;
}
/*****************************************************************************************************
 *  getIdentificador -> retorna variavel a esquerda
 *
 ****************************************************************************************************/
TokenType* Attrib::getIdentificador(){
    return left;
}
/*****************************************************************************************************
 *  getExpression -> retorna expressao matematica ou constante a direita
 *
 ****************************************************************************************************/
TokenType* Attrib::getExpression(){
    return right;
}
