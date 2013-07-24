#include "lex.h"

#define isEndOfLine(ch)                     ((ch) == '!' || (ch) == '\n')
#define isEndOfInput(ch)                    ((ch) == '\0')
#define isLayout(ch)                        (!isEndOfInput(ch) && (ch) <= ' ')
#define isCommentStarter(ch)                ((ch) == '#')
#define isCommentStopper(ch)                ((ch) == '#' || (ch) == '\n')

#define UC_LETTER_MASK                      (1<<1)
#define LC_LETTER_MASK                      (1<<2)
#define is_uc_letter(ch)                    (charbits[(int)ch] & UC_LETTER_MASK)
#define is_lc_letter(ch)                    (charbits[(int)ch] & LC_LETTER_MASK)
#define isLetter(ch)                        (is_uc_letter(ch) || is_lc_letter(ch))
#define isDigit(ch)                         ('0' <= (ch) && (ch) <= '9')
#define isLetterOrDigit(ch)                 (isLetter(ch) || isDigit(ch))
#define isUnderscore(ch)                    ((ch) == '_')
#define isDot(ch)                           ((ch) == '.')

//#define isOperator(ch)                      (strchr("+-*/", (ch)) != 0)
//#define isSeparator(ch)                     (strchr(",(){};!-", (ch)) != 0)

//#define isAssign(ch)                        (strchr("=",(ch)) != 0)
//#define isLogicalOperator(ch)               (strchr("&|", (ch)) != 0)
//#define isMajor(ch)                         ((ch) == '>')
//#define isMinor(ch)                         ((ch) == '<')
//#define isTil(ch)                           ((ch) == '~')
//#define isP(ch)                             ((ch) == '(')
//#define isString(ch)                        (strchr("'", (ch)) != 0)


static const char charbits[256] = {
0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,
0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0040,0040,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0002,0002,0002,0002,0002,0002,0002,
0002,0002,0002,0002,0002,0002,0002,0002,0002,0002,0002,0002,0002,0002,0002,0002,0002,0002,0002,0000,0000,0000,0000,0000,0000,0004,0004,0004,0004,0004,0004,0004,0004,0004,0004,0004,0004,0004,0004,0004,0004,
0004,0004,0004,0004,0004,0004,0004,0004,0004,0004,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,
0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,
0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,
0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000,0000
};

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

    //se for if, each
    if(reser->findSymbol(s)){
        no->setClasse(RESERVADO);
        if(s == "if") no->setType(IF);
        else no->setType(LOOP);
    }
    no->setToken(s);
}

/*****************************************************************************************************
 *  recognizeIntegerOrFloat -> Cria constante numerica (inteiro/real)
 *
 ****************************************************************************************************/
void Lex::recognizeIntegerOrFloat(TokenType* no) {
    no->setClasse(INTEGER);
    no->setType(CONST);
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
        line++;
        column = 0;
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
    if(!input){
        cout<<"Erro na leitura do arquivo!"<<endl;
        cin.get();
        exit(1);
    }

    reser = TableSymbol::getInstance();
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
        token->setType(FIM);

        return token;
    }

    //bloco
    if(strchr("{}", *input)){
        token->setClasse(BLOCO);
        if(*input == '{') token->setToken("{");
        else token->setToken("}");
        token->setColumn(column);
        token->setLine(line);
        token->setType(BLOCO);
        input++;
        line++;
        column = 0;

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
                    token->setType(IGUAL);
                    return token;
                }
                break;
            case '!':
                if(*(input+1) == '='){
                    token->setColumn(column);
                    token->setLine(line);
                    input++; input++; column++; column++;
                    token->setClasse(NOT_EQUAL);
                    token->setType(NOT_EQUAL);
                    token->setToken("!=");

                    return token;
                }
                else{
                    token->setColumn(column);
                    token->setLine(line);
                    input++; column++;
                    token->setClasse(END_CMD);
                    token->setType(END_CMD);
                    token->setToken("!");
                    line++;
                    column = 0;

                    return token;
                }
                break;
            case '-':
                if(*(input+1) == '>'){
                    token->setColumn(column);
                    token->setLine(line);
                    input++; input++; column++; column++;
                    token->setClasse(SETA);
                    token->setType(SETA);
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
                    token->setType(MENOR_IGUAL);
                    token->setToken("<=");

                    return token;
                }
                else{
                    token->setColumn(column);
                    token->setLine(line);
                    input++; column++;
                    token->setClasse(MENOR);
                    token->setType(MENOR);
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
                    token->setType(MAIOR_IGUAL);
                    token->setToken(">=");

                    return token;
                }
                else{
                    token->setColumn(column);
                    token->setLine(line);
                    input++; column++;
                    token->setClasse(MAIOR);
                    token->setType(MAIOR);
                    token->setToken(">");

                    return token;
                }
                break;
        }
    }

    //operadores logico
    if(strchr("|&",*input)){
        token->setClasse(LOGICAL);
        token->setType(LOGICAL);
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
        token->setType(OPERATOR);
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
                token->setType(ASSIGN);
                token->setToken("=");
                token->setColumn(column);
                token->setLine(line);
                column++;

                return token;
            case '(':
                input++;
                token->setClasse(SEPARATOR);
                token->setType(SEPARATOR);
                token->setToken("(");
                token->setColumn(column);
                token->setLine(line);
                column++;

                return token;
            case ')':
                input++;
                token->setClasse(SEPARATOR);
                token->setType(SEPARATOR);
                token->setToken(")");
                token->setColumn(column);
                token->setLine(line);
                column++;

                return token;
            case ',':
                input++;
                token->setClasse(SEPARATOR);
                token->setType(SEPARATOR);
                token->setToken(",");
                token->setColumn(column);
                token->setLine(line);
                column++;

                return token;
            case '~':
                input++;
                token->setClasse(LIST);
                token->setType(LIST);
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
        token->setType(STRING);
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

    //se nao for token permitido entao eh erro
    token->setClasse(ERRONEOUS);
    string s;
    s.push_back(*input);
    token->setToken(s);
    token->setLine(line);
    token->setColumn(column);

    return token; //token errado
}
