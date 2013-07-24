#include "semantic.h"

Semantic::Semantic()
{
    ast = AST::getInstance();
    erro = Error::getInstance();
}

Semantic::~Semantic(){}

/*****************************************************************************************************
 *  parsing -> faz a analise semantica da AST
 *  Inicia a verificacao atribuindo o primeiro elemento da AST para ATUAL, chama REVIEW
 *  e se sair sem erros do REVIEW pega o proximo token ate ser NULL
 *
 ****************************************************************************************************/
void Semantic::parsing(){
    TokenType *root = ast->getRoot(), *atual;

    while(root){
        atual = root;
        review(atual);
        root = root->getNext();
    }
}
/*****************************************************************************************************
 *  review -> Analise cada item da AST iterativa e recursivamente
 *  Analise a atribuicao iterativamente
 *  IF e EACH analisa recursivamente
 *  Ponto de parada sempre sera uma atribuicao
 *
 ****************************************************************************************************/
void Semantic::review(TokenType *token){

    switch(token->getClasse()){
        case ASSIGN:
            Attrib *no = (Attrib*)token;
            if(no->getExpression()->getClasse() == OPERATOR){
                Operator *op = (Operator*)no->getExpression();
                reviewOperation(op);
            }
            else{ //constante ou variavel ou lista
                no->getIdentificador()->setClasse(no->getExpression()->getClasse());
                no->getIdentificador()->setType(no->getExpression()->getType());
            }
            return;
        case RESERVADO:
            switch(token->getType()){
                case IF:
                    IFElse *no = (IFElse *)token;
                    Operator *op = (Operator *)no->getExpression();
                    reviewOperation(op); //verifica se os lados esquerdo e direito sao do mesmo tipo
                    review(no->getBlockIF()); //recursivamente verifica o bloco do IF
                    review(no->getElseBlock()); //recursivamente verifica o bloco do else
                    return; //sai
                case LOOP:
                    Each *no = (Each *)token;
                    Operator *op = (Operator *)no->getExpression();
                    reviewOperation(op); //verifica se os lados esquerdo e direito sao do mesmo tipo
                    review(no->getBlock()); //recursivamente verifica o bloco
                    return; //sai
            }
            return;
    }
}

#define MSG_ERROR_FLOAT     " FLOAT esperado mas "
#define MSG_ERROR_INT       " INTEGER esperado mas "
#define MSG_ERROR_STRING    " STRING esperado mas "

/*****************************************************************************************************
 *  reviewOperation -> Analisa operacoes aritmeticas e logicas
 *  Somente verifica se os lados esquerdo e direito sao do mesmo tipo
 *
 ****************************************************************************************************/
void Semantic::reviewOperation(Operator *op){

    switch(op->getLeft()->getClasse()){
        case IDENTIFIER: //se for variavel
            switch(op->getLeft()->getType()){ //se a esquerda for
                case FLOAT:
                    if(op->getRight()->getClasse() == IDENTIFIER && op->getRight()->getType() != FLOAT)
                        erro->showError(MSG_ERROR_FLOAT,
                                        op->getRight()->getLine(),
                                        op->getRight()->getColumn(),
                                        op->getRight()->getToken());
                    else if(op->getRight()->getClasse() != FLOAT)
                        erro->showError(MSG_ERROR_FLOAT,
                                        op->getRight()->getLine(),
                                        op->getRight()->getColumn(),
                                        op->getRight()->getToken());

                    return;
                case INTEGER:
                    if(op->getRight()->getClasse() == IDENTIFIER && op->getRight()->getType() != INTEGER)
                        erro->showError(MSG_ERROR_INT,
                                        op->getRight()->getLine(),
                                        op->getRight()->getColumn(),
                                        op->getRight()->getToken());
                    else if(op->getRight()->getClasse() != INTEGER)
                        erro->showError(MSG_ERROR_INT,
                                        op->getRight()->getLine(),
                                        op->getRight()->getColumn(),
                                        op->getRight()->getToken());

                    return;
                case STRING:
                    if(op->getRight()->getClasse() == IDENTIFIER && op->getRight()->getType() != STRING)
                        erro->showError(MSG_ERROR_STRING,
                                        op->getRight()->getLine(),
                                        op->getRight()->getColumn(),
                                        op->getRight()->getToken());
                    else if(op->getRight()->getClasse() != STRING)
                        erro->showError(MSG_ERROR_STRING,
                                        op->getRight()->getLine(),
                                        op->getRight()->getColumn(),
                                        op->getRight()->getToken());

                    return;
            }
        case FLOAT:
            if(op->getRight()->getClasse() != FLOAT)
                erro->showError(MSG_ERROR_FLOAT,
                                op->getRight()->getLine(),
                                op->getRight()->getColumn(),
                                op->getRight()->getToken());
            return;
        case INTEGER:
            if(op->getRight()->getClasse() != FLOAT)
                erro->showError(MSG_ERROR_INT,
                                op->getRight()->getLine(),
                                op->getRight()->getColumn(),
                                op->getRight()->getToken());
            return;
        case STRING:
            if(op->getRight()->getClasse() != FLOAT)
                erro->showError(MSG_ERROR_STRING,
                                op->getRight()->getLine(),
                                op->getRight()->getColumn(),
                                op->getRight()->getToken());
            return;
    }
}
