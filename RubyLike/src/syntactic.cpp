#include "syntactic.h"

Syntactic::Syntactic()
{
}

Syntactic::~Syntactic(){}

Syntactic* Syntactic::instance = NULL;

Syntactic* Syntactic::getInstance(){
    if(instance == NULL) instance = new Syntactic();
    return instance;
}
