#include "lex.h"

#define isEndOfLine(ch)                     ((ch) == '!' || (ch) == '\n')
#define isEndOfInput(ch)                    ((ch) == '\0')
#define isLayout(ch)                        (!isEndOfInput(ch) && (ch) <= ' ')
#define isCommentStarter(ch)                ((ch) == '#')
#define isCommentStopper(ch)                ((ch) == '#' || (ch) == '\n')

#define is_uc_letter(ch)                    ('A' <= (ch) && (ch) <= 'Z')
#define is_lc_letter(ch)                    ('a' <= (ch) && (ch) <= 'z')
#define isLetter(ch)                        (is_uc_letter(ch) || is_lc_letter(ch))
#define isDigit(ch)                         ('0' <= (ch) && (ch) <= '9')
#define isLetterOrDigit(ch)                 (isLetter(ch) || isDigit(ch))
#define isUnderscore(ch)                    ((ch) == '_')
#define isDot(ch)                           ((ch) == '.')

#define isOperator(ch)                      (strchr("+-*/", (ch)) != 0)
#define isSeparator(ch)                     (strchr(",(){};!-", (ch)) != 0)

#define isAssign(ch)                        (strchr("=",(ch)) != 0)
#define isLogicalOperator(ch)               (strchr("&|", (ch)) != 0)
#define isMajor(ch)                         ((ch) == '>')
#define isMinor(ch)                         ((ch) == '<')
#define isTil(ch)                           ((ch) == '~')
#define isP(ch)                             ((ch) == '(')
#define isString(ch)                        (strchr("'", (ch)) != 0)

Lex::Lex()
{
    line = column = 0;
}

Lex::~Lex(){}

/*****************************************************************************************************
 *  recognizeIdentifier -> Cria identificador comecando com letra
 *
 ****************************************************************************************************/
void Lex::recognizeIdentifier(TokenType* no) {
    no->setClasse(IDENTIFIER);
    no->setColumn(column);
    no->setLine(line);
    string s;

    while(isLetterOrDigit(*input)) {
        s.push_back(*input);
        input++;
        column++;
    }
    while (isUnderscore(*input)) {
        s.push_back(*input);
        input++;
        column++;
        while (isLetterOrDigit(*input)) {
            s.push_back(*input);
            input++;
            column++;
        }
    }

    no->setToken(s);
}

/*****************************************************************************************************
 *  recognizeIntegerOrFloat -> Cria constante numerica (inteiro/real)
 *
 ****************************************************************************************************/
void Lex::recognizeIntegerOrFloat(TokenType* no) {
    no->setClasse(INTEGER);
    no->setColumn(column);
    no->setLine(line);
    string s;

    while (isDigit(*input) && *input) {

        if(isDot(*input)){
            no->setClasse(FLOAT);
            s.push_back(*input);
            input++;
            column++;
        }
        else{
            s.push_back(*input);
            input++;
            column++;
        }
    }

    no->setToken(s);
}

/*****************************************************************************************************
 *  skipLayoutAndComment -> iguinora ' ' e comentario
 *
 ****************************************************************************************************/
void Lex::skipLayoutAndComment() {
    while (isLayout(*input)) {
        input++;
        column++;
    }
    while (isCommentStarter(*input)) {
        input++;
        column++;
        while (!isCommentStopper(*input)) {
            if (isEndOfInput(*input)) {
                return;
            }
            input++;
            column++;
        }
        input++;
        column++;
        while (isLayout(*input)) {
            input++;
            column++;
        }
    }
}
/*****************************************************************************************************
 *  startLex -> Da inicio a producao de tokens inicializando as variaveis
 *  necessarias
 *
 ****************************************************************************************************/
void Lex::startLex(File& file) {
    input = file.readString(); //le uma linha do arquivo
    if(input){
        ast = AST::getInstance();
    }
    else{
        cout<<"Erro na leitura do arquivo!"<<endl;
        cin.get();
        exit(1);
    }
}

void Lex::showError(const string msg){
    cout<<"Erro na linha: "<<(line+1)<<" coluna: "<<(column+1)<<msg<<*input<<" encontrado!"<<endl;
    cin.get();
    exit(1);
}

/*****************************************************************************************************
 *  Parser -> inicia a producao de tokens e analise sintatica
 *  Primeiro chama startLex() que seta todas as informacoes necessarias
 *  Segundo chama getNextToken(NULL) que vai quebrando e empilhando os tokens
 *  quando acha ';' retorna um false (nao e´ o fim do arquivo)
 *  e quando for true - fim do arquivo
 ****************************************************************************************************/
void Lex::parser(){
    TokenType *token, *buffer;
    Attrib *attrib;

    while( (token = getToken()) != NULL){
        switch(token->getClasse()){
            case IDENTIFIER://eh identificador
                buffer = getToken();

                switch (buffer->getClasse()) {
                    case ASSIGN://eh atribuicao
                        attrib = new Attrib();
                        attrib->setAttrib(buffer); //cria token atribuicao
                        attrib->setIdentificador(token); //seta identificador a esquerda

                        buffer = getToken();

                        switch(buffer->getClasse()){
                            case INTEGER:
                                attrib->setExpression(buffer); //seta constante a direita
                                buffer = getToken();
                                switch(buffer->getClasse()){
                                    case END_CMD: ast->insere(attrib); break; //se for ! coloca na AST
                                    default: showError(" ! esperado mas: ");
                                }
                                break;
                            case FLOAT:
                                attrib->setExpression(buffer);
                                buffer = getToken();
                                switch(buffer->getClasse()){
                                    case END_CMD: ast->insere(attrib); break;
                                    default: showError(" ! esperado mas: ");
                                }
                                break;
                            case STRING:
                                attrib->setExpression(buffer);
                                buffer = getToken();
                                switch(buffer->getClasse()){
                                    case END_CMD: ast->insere(attrib); break;
                                    default: showError(" ! esperado mas: ");
                                }
                                break;
                        }
                        break;
                    default:
                        showError(" '=' esperado mas: ");
                        break;
                }
                break;
        }

        if(token->getClasse() == FIM) break;

    }

}

void Lex::show(){
    Attrib *attrib = (Attrib*) ast->getRoot();

    cout<<attrib->getIdentificador()->getToken()<<endl;
    cout<<attrib->getToken()<<endl;
    cout<<attrib->getExpression()->getToken()<<endl;
}
/*****************************************************************************************************
 *  getToken -> cria um token
 *
 ****************************************************************************************************/
TokenType* Lex::getToken(){
    TokenType *token = new TokenType();

    skipLayoutAndComment();

    //nova linha
    if(*input == '\n'){
        ++input;
        line++;
        column = 0;
        skipLayoutAndComment();
    }

    //fim do arquivo
    if(*input == '\0'){
        token->setClasse(FIM);
        token->setToken("<FIM>");
        token->setLine(line);
        token->setColumn(column);
        return token;
    }

    //bloco
    if(strchr("{}", *input)){
        token->setClasse(BLOCO);
        if(*input == '{') token->setToken("{");
        else token->setToken("}");
        token->setColumn(column);
        token->setLine(line);
        input++; column++;

        return token;
    }

    //relacional
    if(strchr("!<>=-", *input)){
        switch(*input){
            case '=':
                if(*(input+1) == '='){
                    token->setColumn(column);
                    token->setLine(line);
                    input++; input++; column++; column++;
                    token->setClasse(IGUAL);
                    token->setToken("==");
                    return token;
                }
                break;
            case '!':
                if(*(input+1) == '='){
                    token->setColumn(column);
                    token->setLine(line);
                    input++; input++; column++; column++;
                    token->setClasse(NOT_EQUAL);
                    token->setToken("!=");
                    return token;
                }
                else{
                    token->setColumn(column);
                    token->setLine(line);
                    input++; column++;
                    token->setClasse(END_CMD);
                    token->setToken("!");
                    return token;
                }
                break;
            case '-':
                if(*(input+1) == '>'){
                    token->setColumn(column);
                    token->setLine(line);
                    input++; input++; column++; column++;
                    token->setClasse(SETA);
                    token->setToken("->");
                    return token;
                }
                break;
            case '<':
                if(*(input+1) == '='){
                    token->setColumn(column);
                    token->setLine(line);
                    input++; input++; column++; column++;
                    token->setClasse(MENOR_IGUAL);
                    token->setToken("<=");
                    return token;
                }
                else{
                    token->setColumn(column);
                    token->setLine(line);
                    input++; column++;
                    token->setClasse(MENOR);
                    token->setToken("<");
                    return token;
                }
                break;
            case '>':
                if(*(input+1) == '='){
                    token->setColumn(column);
                    token->setLine(line);
                    input++; input++; column++; column++;
                    token->setClasse(MAIOR_IGUAL);
                    token->setToken(">=");
                    return token;
                }
                else{
                    token->setColumn(column);
                    token->setLine(line);
                    input++; column++;
                    token->setClasse(MAIOR);
                    token->setToken(">");
                    return token;
                }
                break;
        }
    }

    //operadores logico
    if(strchr("|&",*input)){
        token->setClasse(LOGICAL);
        switch(*input){
            case '|':
                input++;
                token->setToken("|");
                token->setColumn(column);
                token->setLine(line);
                column++;
                return token;
            case '&':
                input++;
                token->setToken("&");
                token->setColumn(column);
                token->setLine(line);
                column++;
                return token;
        }
    }

    //operadores
    if(strchr("+-*/%", *input)){
        token->setClasse(OPERATOR);
        switch(*input){
            case '+':
                input++;
                token->setToken("+");
                token->setColumn(column);
                token->setLine(line);
                column++;
                return token;
            case '-':
                input++;
                token->setToken("-");
                token->setColumn(column);
                token->setLine(line);
                column++;
                return token;
            case '*':
                input++;
                token->setToken("*");
                token->setColumn(column);
                token->setLine(line);
                column++;
                return token;
            case '/':
                input++;
                token->setToken("/");
                token->setLine(line);
                token->setColumn(column);
                column++;
                return token;
            case '%':
                input++;
                token->setToken("%");
                token->setColumn(column);
                token->setLine(line);
                column++;
                return token;
        }
    }

    //separadores
    if(strchr("=(),~", *input)){
        switch(*input){
            case '=':
                input++;
                token->setClasse(ASSIGN);
                token->setToken("=");
                token->setColumn(column);
                token->setLine(line);
                column++;
                return token;
            case '(':
                input++;
                token->setClasse(SEPARATOR);
                token->setToken("(");
                token->setColumn(column);
                token->setLine(line);
                column++;
                return token;
            case ')':
                input++;
                token->setClasse(SEPARATOR);
                token->setToken(")");
                token->setColumn(column);
                token->setLine(line);
                column++;
                return token;
            case ',':
                input++;
                token->setClasse(SEPARATOR);
                token->setToken(",");
                token->setColumn(column);
                token->setLine(line);
                column++;
                return token;
            case '~':
                input++;
                token->setClasse(LIST);
                token->setToken("~");
                token->setColumn(column);
                token->setLine(line);
                column++;
                return token;
        }
    }

    //string
    if(*input == '"'){
        string s;
        token->setColumn(column);
        token->setLine(line);
        column++;
        input++;
        while(*input != '"' && *input != '\r') {
            s.push_back(*input);
            input++;
            column++;
        }
        token->setClasse(STRING);
        token->setToken(s);
        input++; //sem isso buga por causa o ' ou " finalizando a string
        column++;
        return token;
    }

    //numeros
    if(isDigit(*input)){
        recognizeIntegerOrFloat(token);
        return token;
    }

    //variaveis
    if(isalpha(*input)){
        recognizeIdentifier(token);
        return token;
    }

    return NULL; //algo sem sentido ou caractere de formataçao fdp
}
