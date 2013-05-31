#include "tokentype.h"

TokenType::TokenType()
{
}


void TokenType::setClasse(char classe)
{
    this->classe = classe;
}

void TokenType::setToken(char *repr){
    this->repr = repr;
}

void TokenType::setLine(int line){
    this->line = line;
}

void TokenType::setColumn(int column){
    this->column = column;
}

char TokenType::getClasse(){
    return classe;
}

char* TokenType::getToken(){
    return repr;
}

int TokenType::getLine(){
    return line;
}

int TokenType::getColumn(){
    return column;
}
