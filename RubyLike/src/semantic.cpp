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
                nott->getIdentificador()->setType(reviewOperation(optt, false)); //seta tipo de acordo com reviewOperation

                return;
            }
            else{ //constante ou variavel ou lista
                //nott->getIdentificador()->setClasse(nott->getExpression()->getClasse());
                nott->getIdentificador()->setType(nott->getExpression()->getClasse());
                return;
            }
        }
        break;
        case RESERVADO:
            if(token->getToken() == "if"){
                IFElse *noif = (IFElse *)token;
                Operator *opif = (Operator *)noif->getExpression();
                reviewOperation(opif, false); //verifica se os lados esquerdo e direito sao do mesmo tipo
                review(noif->getBlockIF()); //recursivamente verifica o bloco do IF
                review(noif->getElseBlock()); //recursivamente verifica o bloco do else
                return; //sai
            }

            if(token->getToken() == "each"){
                Each *noch = (Each *)token;
                Operator *opch = (Operator *)noch->getExpression();
                reviewOperation(opch, true); //verifica se os lados esquerdo e direito sao do mesmo tipo
                review(noch->getBlock()); //recursivamente verifica o bloco
                return; //sai
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
int Semantic::reviewOperation(Operator *op,bool isEach){

    switch(op->getLeft()->getClasse()){
        case IDENTIFIER: //se for variavel
            switch(op->getLeft()->getType()){ //se a esquerda for
                case LIST: if(!isEach) semanticListReview(op->getLeft());
                case FLOAT: return semanticFloatReview(op->getRight());
                case INTEGER: return semanticIntegerReview(op->getRight());
                case STRING: return semanticStringReview(op->getRight());
                default:
                    erro->showError(MSG_ERROR_NON_TYPE,
                                    op->getLeft()->getLine(),
                                    op->getLeft()->getColumn(),
                                    op->getLeft()->getToken());
            }
        case FLOAT: return semanticFloatReview(op->getRight());
        case INTEGER: return semanticIntegerReview(op->getRight());
        case STRING: return semanticStringReview(op->getRight());
        default:
            erro->showError(" Atributo sem classe ",
                        op->getLeft()->getLine(),
                        op->getLeft()->getColumn(),
                        op->getLeft()->getToken());
    }
}

void Semantic::semanticListReview(TokenType *token){
    erro->showError(MSG_ERROR_LIST,
                    token->getLine(),
                    token->getColumn(),
                    token->getToken());
}

int Semantic::semanticFloatReview(TokenType *token){
    switch(token->getClasse()){
        case FLOAT: return FLOAT;
        case IDENTIFIER:
            if(token->getType() == FLOAT) return FLOAT;
        default:
            erro->showError(MSG_ERROR_FLOAT,
                        token->getLine(),
                        token->getColumn(),
                        token->getToken());
    }
}

int Semantic::semanticIntegerReview(TokenType *token){
    switch(token->getClasse()){
        case INTEGER: return INTEGER;
        case IDENTIFIER:
            if(token->getType() == INTEGER) return INTEGER;
        default:
            erro->showError(MSG_ERROR_INT,
                        token->getLine(),
                        token->getColumn(),
                        token->getToken());
    }
}

int Semantic::semanticStringReview(TokenType *token){
    switch(token->getClasse()){
        case STRING: return STRING;
        case IDENTIFIER:
            if(token->getType() == STRING) return STRING;
        default:
            erro->showError(MSG_ERROR_STRING,
                        token->getLine(),
                        token->getColumn(),
                        token->getToken());
    }
}
