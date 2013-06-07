#include "tokentype.h"

TokenType::TokenType()
{
}

TokenType::~TokenType(){

}
/*
 *  Seta classe do token
 */
void TokenType::setClasse(char classe)
{
    this->classe = classe;
}
/*
 *  Seta token
 */
void TokenType::setToken(char *repr){
    this->repr = repr;
}
/*
 *  Seta linha do token no arquivo
 */
void TokenType::setLine(int line){
    this->line = line;
}
/*
 *  Seta coluna do token no arquivo
 */
void TokenType::setColumn(int column){
    this->column = column;
}
/*
 *  Recupera classe do token
 */
char TokenType::getClasse(){
    return classe;
}
/*
 *  Recupera o token
 */
char* TokenType::getToken(){
    return repr;
}
/*
 *  Recupera a linha onde o token se encontra no arquivo
 */
int TokenType::getLine(){
    return line;
}
/*
 *  Recupera a coluna do token no arquivo
 */
int TokenType::getColumn(){
    return column;
}
