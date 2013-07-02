#include "error.h"

Error* Error::instance = NULL;

Error::Error()
{
}

Error::~Error(){

}

Error* Error::getInstance(){
    if(instance == NULL) instance = new Error();
    return instance;
}

void Error::showError(const string msg, int line, int column, const string token){
    cout<<"Erro na linha: "<<(line+1)<<" coluna: "<<(column+1)<<msg<<" "<<token<<" encontrado!"<<endl;
    cin.get();
    exit(1);
}
