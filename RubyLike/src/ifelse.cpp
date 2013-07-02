#include "ifelse.h"

IFElse::IFElse()
{
}

IFElse::~IFElse(){}
/*****************************************************************************************************
 *  setIF -> seta token if
 *
 ****************************************************************************************************/
void IFElse::setIF(TokenType *_if){
    setClasse(_if->getClasse());
    setToken(_if->getToken());
    setColumn(_if->getColumn());
    setLine(_if->getLine());
    setType(_if->getType());
}
/*****************************************************************************************************
 *  setExpression -> seta expressao logica a esquerda
 *
 ****************************************************************************************************/
void IFElse::setExpression(TokenType *expr){
    this->expr = expr;
}
/*****************************************************************************************************
 *  setBlockIF -> seta o bloco do if no meio
 *
 ****************************************************************************************************/
void IFElse::setBlockIF(TokenType *block){
    this->block = block;
}
/*****************************************************************************************************
 *  setElseBlock -> seta o bloco do else a direita
 *
 ****************************************************************************************************/
void IFElse::setElseBlock(TokenType *block){
    this->elseBlock = block;
}
/*****************************************************************************************************
 *  getExpression -> retorna expressao logica a esquerda
 *
 ****************************************************************************************************/
TokenType* IFElse::getExpression(){
    return expr;
}
/*****************************************************************************************************
 *  getBlockIF -> retorna bloco do if (meio)
 *
 ****************************************************************************************************/
TokenType* IFElse::getBlockIF(){
    return block;
}
/*****************************************************************************************************
 *  getElseBlock -> retorna bloco do else
 *
 ****************************************************************************************************/
TokenType* IFElse::getElseBlock(){
    return elseBlock;
}
