#include "each.h"

Each::Each()
{
}

Each::~Each(){}
/*****************************************************************************************************
 *  setEach -> seta o token each
 *
 ****************************************************************************************************/
void Each::setEach(TokenType *each){
    setClasse(each->getClasse());
    setToken(each->getToken());
    setColumn(each->getColumn());
    setLine(each->getLine());
    setType(each->getType());
}
/*****************************************************************************************************
 *  setExpression -> seta expressao logica a esquerda
 *
 ****************************************************************************************************/
void Each::setExpression(TokenType *expr){
    this->expr = expr;
}
/*****************************************************************************************************
 *  setBlock -> seta bloco do each a direita
 *
 ****************************************************************************************************/
void Each::setBlock(TokenType *block){
    this->block = block;
}
/*****************************************************************************************************
 *  getExpression -> retorna expressao logica a esquerda
 *
 ****************************************************************************************************/
TokenType* Each::getExpression(){
    return expr;
}
/*****************************************************************************************************
 *  getBlock -> retorna o bloco do each a direita
 *
 ****************************************************************************************************/
TokenType* Each::getBlock(){
    return block;
}
