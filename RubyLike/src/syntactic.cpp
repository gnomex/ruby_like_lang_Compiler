#include "syntactic.h"

//algumas macros...
#define isLogical(value)        ( (value) == LOGICAL )
#define isRelational(value)     ( ((value) == IGUAL) || ((value) == MAIOR) || ((value) == MENOR) || ((value) == NOT_EQUAL) || ((value) == MAIOR_IGUAL) || ((value) == MENOR_IGUAL) )
#define isAccept(value)         ( ((value) == IDENTIFIER) || ((value) == INTEGER) || ((value) == FLOAT) || ((value) == STRING) )

Syntactic::Syntactic(Lex* lex)
{
    this->lex = lex;
    ast = AST::getInstance();
    erro = Error::getInstance();
    prod = ProducerList::getInstance();
    temp = NULL;
}

Syntactic::~Syntactic(){}
/*****************************************************************************************************
 *  Parser -> faz analise sintatica dos tokens que a analise lexica produz
 *  Verifica se eh IDENTIFICADOR (variavel) se for produz uma atribuicao
 *  Verifica se eh IF ou EACH, se for cria sua arvore
 *  Se nao for variavel ou if, ou each entao eh erro
 *  Ou seja, no inicio de cada linha, cada instrucao tem que começar com uma VARIAVEL ou IF ou EACH
 ****************************************************************************************************/
void Syntactic::parser(){
    TokenType *token;

    while( (token = lex->getToken()) != NULL){

        if(token->getClasse() == FIM) break;

        switch(token->getClasse()){
            case IDENTIFIER: ast->insere(syntacticIdentifier(token)); break;
            case RESERVADO: syntacticPrivate(token); break;
            default: erro->showError(" algo sem sentido ", token->getLine(), token->getColumn(), token->getToken());
        }

    }

}
/*****************************************************************************************************
 *  syntacticPrivate -> faz a analise de palavras reservadas
 *  NOTA: no IF, por ter que verificar se existe um ELSE logo em seguida, nem sempre sera um ELSE
 *  por isso o hasTemp()
 *
 ****************************************************************************************************/
void Syntactic::syntacticPrivate(TokenType *token){
    if(token->getToken() == "if")
        ast->insere(syntacticIFstmt(token));

    if(token->getToken() == "each")
        ast->insere(syntacticEach(token));

    hasTemp();

}
/*****************************************************************************************************
 *  hasTemp -> verifica o que eh, se eh uma variavel trata ela
 *
 ****************************************************************************************************/
void Syntactic::hasTemp(){
    if(temp && temp->getClasse() != FIM){
        switch(temp->getClasse()){
            case IDENTIFIER:
                ast->insere(syntacticIdentifier(temp));
                break;
            case RESERVADO:
                syntacticPrivate(temp);
            default:
                erro->showError(" variavel esperado mas: ", temp->getLine(), temp->getColumn(), temp->getToken());
        }
        temp = NULL;
    }
}
/*****************************************************************************************************
 *  syntacticIdentifier -> faz a analise de uma variavel que necessariamente eh uma atribuicao
 *  Token   =>  identificador (variavel) que sera colocada a esquerda da Atribuicao
 *  Retorna =>  um token especializado
 *
 ****************************************************************************************************/
Attrib* Syntactic::syntacticIdentifier(TokenType *token){
    TokenType *buffer = lex->getToken(); //pega o =

    switch (buffer->getClasse()) {
        case ASSIGN:
            return syntacticAssign(buffer, token); //chama analise de uma atribuicao
            break;
        default: erro->showError(" '=' esperado mas: ", buffer->getLine(), buffer->getColumn(), buffer->getToken());
    }
}
/*****************************************************************************************************
 *  syntacticAssign -> faz analise de uma atribuicao
 *  ATTR    => token com o '='
 *  VAR     => token com a variavel que ficara a esquerda
 *  Retorna => tipo especializado
 ****************************************************************************************************/
Attrib* Syntactic::syntacticAssign(TokenType *attr, TokenType *var){
    TokenType *buffer, *token;
    Attrib *attrib = new Attrib();
    attrib->setAttrib(attr);  // =
    attrib->setIdentificador(var);    //var

    buffer = lex->getToken();   //expressao ou var ou constante ou lista

    switch(buffer->getClasse()){
        case LIST:
            attrib->setExpression(syntacticList(buffer)); //coloca a lista a direita
            var->setType(LIST); //seta novo tipo da variavel
            prod->insert(var); //coloca na lista de producoes
            break;
        case INTEGER:
        case FLOAT:
        case STRING:
        case IDENTIFIER:
            token = lex->getToken(); //pode ser Operador (logico/aritmetico) ou ! (fim de instrucao)
            switch(token->getClasse()){
                case OPERATOR:
                case LOGICAL:
                    attrib->setExpression(syntacticLogicalOrOperator(token, buffer)); //coloca operacao logica/aritmetica a direita

                    prod->insert(var); //sem tipo definido ainda (analise semantica)
                    break;
                case END_CMD:
                    attrib->setExpression(buffer);
                    var->setType(buffer->getClasse()); //seta novo tipo da variavel
                    prod->insert(var);
                    break;
                default: erro->showError(" Operador ou ! esperado mas: ", token->getLine(), token->getColumn(), token->getToken());
            }
            break;
        default: erro->showError(" digito ou variavel esperado mas: ", buffer->getLine(), buffer->getColumn(), buffer->getToken());
    }

    return attrib;
}
/*****************************************************************************************************
 *  syntacticList -> faz analise de uma lista
 *  TIL     => token com o '~'
 *  Retorna => tipo especializado
 *
 ****************************************************************************************************/
TList* Syntactic::syntacticList(TokenType *til){
    TokenType *buffer, *token;
    TList *list = new TList();
    list->setList(til);  //seta token lista ~

    buffer = lex->getToken(); //pega o '('

    if(buffer->getToken() == "("){
        buffer = lex->getToken(); //pega o primeiro elemento da lista

        if(buffer->getToken() == ",") //se for ',' erro
            erro->showError(" digito, string, variavel esperado mas: ", buffer->getLine(), buffer->getColumn(), buffer->getToken());

        while(buffer->getToken() != ")"){ //enquanto nao for ')'

            list->insere(buffer); //coloca o valor na lista

            token = lex->getToken(); //pega as virgulas

            if(token->getToken() != "," && token->getToken() != ")")
                erro->showError(" , esperado mas: ", token->getLine(), token->getColumn(), token->getToken());
            else if(token->getToken() != "," && token->getToken() == ")") break;
            else buffer = lex->getToken(); //pega os valores
        }

        buffer = lex->getToken(); //proximo token tem que ser '!'
        if(buffer->getClasse() != END_CMD) erro->showError(" ! esperado mas: ", buffer->getLine(), buffer->getColumn(), buffer->getToken());
    }
    else erro->showError(" ( esperado mas: ", buffer->getLine(), buffer->getColumn(), buffer->getToken());

    return list;
}

/*****************************************************************************************************
 *  syntacticLogicalOrOperator -> faz analise de um operador logico ou aritmetico
 *  OPR     => token com a operacao
 *  VAR     => variavel que ficara a esquerda
 *  Retorna => tipo especializado
 ****************************************************************************************************/
Operator* Syntactic::syntacticLogicalOrOperator(TokenType *opr, TokenType *var){
    TokenType *buffer, *temp;
    Operator *op = new Operator();
    op->setOperator(opr); //operador
    op->setLeft(var); //coloca var ou constante a esquerda

    //verifica se o token existe e coloca o tipo no novo token
    if( (temp = prod->getTokenOfList(var->getToken())) != NULL ) var->setType(temp->getType());

    buffer = lex->getToken(); //pega var ou constante

    switch(buffer->getClasse()){
        case INTEGER:
        case FLOAT:
        case STRING:
        case IDENTIFIER:
            op->setRight(buffer); //coloca a direita

            if( (temp = prod->getTokenOfList(buffer->getToken())) != NULL) buffer->setType(temp->getType());

            prod->insert(buffer); //pode ser contante (int/float/string) ou sem tipo identificador (analise semantica)

            buffer = lex->getToken();
            if(buffer->getClasse() != END_CMD) //se nao terminar com ! erro
                erro->showError(" ! esperado mas: ", buffer->getLine(), buffer->getColumn(), buffer->getToken());
            break;
        default:
            erro->showError(" digito ou string ou variavel esperado mas: ",
                           buffer->getLine(), buffer->getColumn(), buffer->getToken());
    }

    return op;
}

/*****************************************************************************************************
 *  syntacticIFstmt -> faz analise do if/else
 *  Token   => token com a palavra IF
 *  Retorna => tipo especializado
 ****************************************************************************************************/
IFElse* Syntactic::syntacticIFstmt(TokenType *token){
    TokenType *buffer;
    IFElse *__if = new IFElse();
    __if->setIF(token); //seta token if

    expressionIFBlock(__if); //faz a expressao logica
    blockIFELSEstmt(__if, true); //true para fazer o bloco do IF

    buffer = lex->getToken(); //verifica se eh o ELSE

    if(buffer->getClasse() == RESERVADO && buffer->getToken() == "else") blockIFELSEstmt(__if, false);
    else{
        __if->setElseBlock(NULL); //sem else
        temp = buffer; //se for each, puts, print ou identificador
    }

    return __if;
}

/*****************************************************************************************************
 *  expressionIFBlock -> faz analise da expressao logica do IF
 *  __IF    => referencia para a raiz
 ****************************************************************************************************/
void Syntactic::expressionIFBlock(IFElse *__if){
    TokenType *buffer, *token;
    buffer = lex->getToken();

    if(buffer->getToken() == "("){
        buffer = lex->getToken();

        if(isAccept(buffer->getClasse())){
            token = lex->getToken();
            prod->insert(buffer); //analize semantica

            if(isLogical(token->getClasse()) || isRelational(token->getClasse())){
                Operator *op = new Operator();
                op->setOperator(token); //seta operador logico/relacional
                op->setLeft(buffer); //coloca var ou digito ou string a esquerda

                buffer = lex->getToken();

                if(isAccept(buffer->getClasse())) {
                    op->setRight(buffer); //coloca var ou digito ou string a direita
                    prod->insert(buffer); //analize semantica
                }
                else
                    erro->showError(" variavel, inteiro, real ou string esperado mas: ", buffer->getLine(), buffer->getColumn(), buffer->getToken());

                __if->setExpression(op); //seta expressao logica
            }
            else
                erro->showError(" & ou | esperado mas: ", token->getLine(), token->getColumn(), token->getToken());
        }
        else erro->showError(" variavel, inteiro, real ou string esperado mas: ", buffer->getLine(), buffer->getColumn(), buffer->getToken());

        buffer = lex->getToken();   //verifica se tem o fecha parenteses

        if(buffer->getToken() != ")")
            erro->showError(" ) esperado mas: ", buffer->getLine(), buffer->getColumn(), buffer->getToken());
    }
    else erro->showError(" ( esperado mas: ", buffer->getLine(), buffer->getColumn(), buffer->getToken());
}

/*****************************************************************************************************
 *  blockIFELSEstmt -> faz analise do bloco do IF ou ELSE
 *  __IF    => referencia para a raiz
 *  WHO     => TRUE se for o bloco IF, FALSE se for o bloco ELSE
 ****************************************************************************************************/
void Syntactic::blockIFELSEstmt(IFElse *__if, bool who){
    TokenType *buffer, *token;
    buffer = lex->getToken();

    if(buffer->getToken() == "{"){

        token = lex->getToken();    //var ou simbolo reservado

        switch(token->getClasse()){
            case IDENTIFIER:
                prod->insert(token); //analize semantica
                buffer = lex->getToken(); //pega o =
                if(buffer->getClasse() != ASSIGN)
                    erro->showError(" = esperado mas: ", buffer->getLine(), buffer->getColumn(), buffer->getToken());

                if(who) __if->setBlockIF(syntacticAssign(buffer, token)); //se for o bloco do if
                else __if->setElseBlock(syntacticAssign(buffer, token)); //se for o bloco do else
                break;
            case RESERVADO:
                if(token->getToken() == "if"){//ou if
                    if(who) __if->setBlockIF(syntacticIFstmt(token));
                    else __if->setElseBlock(syntacticIFstmt(token));
                }
                else if(token->getToken() == "each"){//ou each
                    if(who) __if->setBlockIF(syntacticEach(token));
                    else __if->setElseBlock(syntacticEach(token));
                }
                break;
            default:
                erro->showError(" variavel ou reservado esperado mas: ", buffer->getLine(), buffer->getColumn(), buffer->getToken());
        }

        buffer = lex->getToken(); //pega o } do if ou do else

        if(buffer->getToken() != "}")
            erro->showError(" } esperado mas: ", buffer->getLine(), buffer->getColumn(), buffer->getToken());
    }
    else erro->showError(" { esperado mas: ", buffer->getLine(), buffer->getColumn(), buffer->getToken());
}

/*****************************************************************************************************
 *  syntacticEach -> faz analise do each
 *  TOKEN   => token com o simbolo 'each'
 *  Retorna => tipo especializado
 ****************************************************************************************************/
Each* Syntactic::syntacticEach(TokenType *token){
    Each *each = new Each();
    each->setEach(token);

    eachExpression(each);
    eachBlock(each);

    return each;
}

/*****************************************************************************************************
 *  eachExpression -> faz analise da condicao do each
 *  EACH    => referencia para a raiz
 ****************************************************************************************************/
void Syntactic::eachExpression(Each *each){
    TokenType *buffer, *token;
    buffer = lex->getToken();

    if(buffer->getToken() == "("){
        buffer = lex->getToken();
        if(buffer->getClasse() == IDENTIFIER){
            prod->insert(buffer); //analize semantica
            token = lex->getToken(); // ->

            if(token->getClasse() == SETA){
                Operator *op = new Operator();
                op->setOperator(token);
                op->setLeft(buffer);

                buffer = lex->getToken();
                if(buffer->getClasse() == IDENTIFIER){
                    prod->insert(buffer); //analize semantica
                    op->setRight(buffer);
                    each->setExpression(op);
                }
                else
                    erro->showError(" variavel esperado mas: ", buffer->getLine(), buffer->getColumn(), buffer->getToken());
            }
            else
                erro->showError(" -> esperado mas: ", token->getLine(), token->getColumn(), token->getToken());

            buffer = lex->getToken();

            if(buffer->getToken() != ")")
                erro->showError(" ) esperado mas: ", buffer->getLine(), buffer->getColumn(), buffer->getToken());
        }
        else erro->showError(" variavel esperado mas: ", buffer->getLine(), buffer->getColumn(), buffer->getToken());
    }
    else erro->showError(" ( esperado mas: ", buffer->getLine(), buffer->getColumn(), buffer->getToken());
}

/*****************************************************************************************************
 *  eachBlock -> faz analise do bloco do each
 *  EACH    => referencia para a raiz
 ****************************************************************************************************/
void Syntactic::eachBlock(Each *each){
    TokenType *buffer;
    buffer = lex->getToken();
    if(buffer->getToken() == "{"){
        buffer = lex->getToken();

        switch(buffer->getClasse()){
            case RESERVADO:
                if(buffer->getToken() == "if"){
                    each->setBlock(syntacticIFstmt(buffer));
                    hasTemp();
                }
                if(buffer->getToken() == "each"){
                    each->setBlock(syntacticEach(buffer));
                }

                //if(token->getClasse() != IDENTIFIER)
                    //erro->showError("simbolo reservado ou variavel esperado mas: ", token->getLine(), token->getColumn(), token->getToken());
                break;
            case IDENTIFIER:
                each->setBlock(syntacticIdentifier(buffer));
                prod->insert(buffer); //analize semantica
        }

        buffer = lex->getToken(); //pega o }

        if(buffer->getToken() != "}")
            erro->showError(" } esperado mas: ", buffer->getLine(), buffer->getColumn(), buffer->getToken());
    }
    else erro->showError(" { esperado mas: ", buffer->getLine(), buffer->getColumn(), buffer->getToken());
}


/*****************************************************************************************************
 *  show -> debug
 *
 ****************************************************************************************************/
void Syntactic::show(){
    TokenType *token = ast->getRoot();
    Attrib *attrib;
    TList *list;
    Operator *op;
    IFElse *__ift;
    Each *each;

    while( token ){
        switch(token->getClasse()){
            case ASSIGN:
                attrib = (Attrib *)token;
                cout<<attrib->getIdentificador()->getToken()<<endl;
                cout<<attrib->getToken()<<endl;
                switch(attrib->getExpression()->getClasse()){
                    case LIST:
                        list = (TList *) attrib->getExpression();
                        list->showItens();
                        break;
                    case OPERATOR:
                        op = (Operator *) attrib->getExpression();
                        cout<<op->getLeft()->getToken()<<op->getToken()<<op->getRight()->getToken()<<endl;
                        break;
                    case INTEGER:
                    case FLOAT:
                    case STRING:
                        cout<<attrib->getExpression()->getToken()<<endl;
                        break;
                }
                break;
            case RESERVADO:
                if(token->getToken() == "if"){
                    __ift = (IFElse *) token;
                    op = (Operator *) __ift->getExpression();

                    cout<<"if("<<op->getLeft()->getToken()<<op->getToken()<<op->getRight()->getToken()<<")"<<endl;

                    switch(__ift->getBlockIF()->getClasse()){
                        case ASSIGN:
                            attrib = (Attrib *) __ift->getBlockIF();
                            cout<<"{"<<attrib->getIdentificador()->getToken()<<attrib->getToken();
                            switch(attrib->getExpression()->getClasse()){
                                case LIST:
                                    list = (TList *) attrib->getExpression();
                                    cout<<"~(";
                                    list->showItens();
                                    cout<<")}"<<endl;
                                    break;
                                case OPERATOR:
                                    op = (Operator *) attrib->getExpression();
                                    cout<<op->getLeft()->getToken()<<op->getToken()<<op->getRight()->getToken()<<"}"<<endl;
                                    break;
                                case INTEGER:
                                case FLOAT:
                                case STRING:
                                    cout<<attrib->getExpression()->getToken()<<"}"<<endl;
                                    break;
                            }
                    }

                    if(__ift->getElseBlock()){
                        switch(__ift->getElseBlock()->getClasse()){
                            case ASSIGN:
                                attrib = (Attrib *) __ift->getElseBlock();
                                cout<<"{"<<attrib->getIdentificador()->getToken()<<attrib->getToken();
                                switch(attrib->getExpression()->getClasse()){
                                    case LIST:
                                        list = (TList *) attrib->getExpression();
                                        cout<<"~(";
                                        list->showItens();
                                        cout<<")}"<<endl;
                                        break;
                                    case OPERATOR:
                                        op = (Operator *) attrib->getExpression();
                                        cout<<op->getLeft()->getToken()<<op->getToken()<<op->getRight()->getToken()<<"}"<<endl;
                                        break;
                                    case INTEGER:
                                    case FLOAT:
                                    case STRING:
                                        cout<<attrib->getExpression()->getToken()<<"}"<<endl;
                                        break;
                                }
                        }
                    }
                }
                else{
                    each = (Each *) token;
                    op = (Operator *) each->getExpression();
                    __ift = (IFElse *) each->getBlock();

                    cout<<"each("<<op->getLeft()->getToken()<<op->getToken()<<op->getRight()->getToken()<<")"<<endl;
                    cout<<"{"<<__ift->getToken();

                    op = (Operator *) __ift->getExpression();

                    cout<<"("<<op->getLeft()->getToken()<<op->getToken()<<op->getRight()->getToken()<<")"<<endl;

                    attrib = (Attrib *) __ift->getBlockIF();

                    cout<<"{"<<attrib->getIdentificador()->getToken()<<attrib->getToken();

                    op = (Operator *) attrib->getExpression();

                    cout<<op->getLeft()->getToken()<<op->getToken()<<op->getRight()->getToken()<<"}"<<endl;

                    attrib = (Attrib *) __ift->getElseBlock();

                    cout<<"else{"<<attrib->getIdentificador()->getToken()<<attrib->getToken();

                    op = (Operator *) attrib->getExpression();

                    cout<<op->getLeft()->getToken()<<op->getToken()<<op->getRight()->getToken()<<"}}";
                }

        }

        token = token->getNext();
    }

}
