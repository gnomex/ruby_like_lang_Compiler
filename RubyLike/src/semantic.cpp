#include "semantic.h"

Semantic::Semantic()
{
}

Semantic::~Semantic(){}

Semantic* Semantic::instance = NULL;

Semantic* Semantic::getInstance(){
    if(instance == NULL) instance = new Semantic();
    return instance;
}
