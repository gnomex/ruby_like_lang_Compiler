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
        {
            Attrib *nott = (Attrib*)token;
            if(nott->getExpression()->getClasse() == OPERATOR){
                Operator *optt = (Operator*)nott->getExpression();
                nott->getIdentificador()->setType(reviewOperation(optt)); //seta tipo de acordo com reviewOperation
                return;
            }
            else{ //constante ou variavel ou lista
                nott->getIdentificador()->setClasse(nott->getExpression()->getClasse());
                //no->getIdentificador()->setType(no->getExpression()->getType());
                return;
            }
        }
        break;
        case RESERVADO:
            switch(token->getType()){
                case IF:
                {
                    IFElse *noif = (IFElse *)token;
                    Operator *opif = (Operator *)noif->getExpression();
                    reviewOperation(opif); //verifica se os lados esquerdo e direito sao do mesmo tipo
                    review(noif->getBlockIF()); //recursivamente verifica o bloco do IF
                    review(noif->getElseBlock()); //recursivamente verifica o bloco do else
                    return; //sai
                }
                case LOOP:
                {
                    Each *noch = (Each *)token;
                    Operator *opch = (Operator *)noch->getExpression();
                    reviewOperation(opch); //verifica se os lados esquerdo e direito sao do mesmo tipo
                    review(noch->getBlock()); //recursivamente verifica o bloco
                    return; //sai
                }
            }
    }
}

#define MSG_ERROR_FLOAT     " FLOAT esperado mas "
#define MSG_ERROR_INT       " INTEGER esperado mas "
#define MSG_ERROR_STRING    " STRING esperado mas "
#define MSG_ERROR_NON_TYPE  " Variavel sem tipo "
#define MSG_ERROR_LIST      " Lista so pode ser operada no each "

/*****************************************************************************************************
 *  reviewOperation -> Analisa operacoes aritmeticas e logicas
 *  Somente verifica se os lados esquerdo e direito sao do mesmo tipo
 *
 ****************************************************************************************************/
int Semantic::reviewOperation(Operator *op){

    switch(op->getLeft()->getClasse()){
        case IDENTIFIER: //se for variavel
            switch(op->getLeft()->getType()){ //se a esquerda for
                case LIST:
                    erro->showError(MSG_ERROR_LIST,
                                    op->getLeft()->getLine(),
                                    op->getLeft()->getColumn(),
                                    op->getLeft()->getToken());
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

                    return FLOAT;
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

                    return INTEGER;
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

                    return STRING;
                default:
                    erro->showError(MSG_ERROR_NON_TYPE,
                                    op->getLeft()->getLine(),
                                    op->getLeft()->getColumn(),
                                    op->getLeft()->getToken());
            }
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
            return FLOAT;
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
            return INTEGER;
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
            return STRING;
    }
}
