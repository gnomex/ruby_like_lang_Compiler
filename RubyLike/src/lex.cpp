#include "lex.h"

#define isEndOfLine(ch)                     ((ch) == ';')
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
#define isSeparator(ch)                     (strchr(",(){};!", (ch)) != 0)

#define isAssign(ch)                        (strchr("=",(ch)) != 0)
#define isLogicalOperator(ch)               (strchr("&|", (ch)) != 0)
#define isMajor(ch)                         ((ch) == '>')
#define isMinor(ch)                         ((ch) == '<')
#define isTil(ch)                           ((ch) == '~')

Lex::Lex()
{
    line = 0;
    ifstmt = false;
    liststmt = false;
}

Lex::~Lex(){}

void Lex::nextChar(){
    inputChar = input[++dot];
}
/*****************************************************************************************************
 *  recognizeIdentifier -> Cria identificador comecando com letra
 *
 ****************************************************************************************************/
void Lex::recognizeIdentifier(TokenType* no) {
    no->setClasse(IDENTIFIER);
    nextChar();
    while(isLetterOrDigit(inputChar)) {
        nextChar();
    }
    while (isUnderscore(inputChar)) {
        nextChar();
        while (isLetterOrDigit(inputChar)) {
            nextChar();
        }
    }
    //se n~ao tiver erros
    no->setLine(line);
    no->setColumn(startDot);
    no->setToken(inputToZString(startDot, dot-startDot));

    //se for palavra reservada
    if(TableSymbol::getInstance()->findSymbol(no->getToken().c_str())){
        no->setClasse(IF);
        ifstmt = true;
        return;
    }

    //se ja existir o token
    if(list->isProducer(no->getToken())){
        no->setClasse(REFERENCIA);
        no->setReference(list->getTokenOfList(no->getToken()));
    }
    //verifica erros
    identifierErrors(inputChar, no);

}
/*****************************************************************************************************
 *  identifierErrors -> Faz analise sintatica do identificador
 *
 ****************************************************************************************************/
void Lex::identifierErrors(int inputChar, TokenType* no){
    if(isOperator(inputChar)) {
        //se apos um identificador vier operador logico e tiver caracteres invalidos
        if(isDot(input[dot + 1]) || isSeparator(input[dot + 1])
          || isMajor(input[dot + 1]) || isMinor(input[dot + 1])
          || isLogicalOperator(input[dot + 1]) || isAssign(input[dot + 1]))
            showError(inputChar, " Letra ou numero ou underscore esperado mas: ");

    }
    if(isSeparator(inputChar)) {
        if(inputChar != ';' && no->getClasse() != IF && !ifstmt) showError(inputChar, " Letra ou numero ou underscore esperado mas: ");
        //if(inputChar != ';' && no->getClasse() != IF &&!liststmt) showError(inputChar, " Letra ou numero ou underscore esperado mas: ");
        //else showError(inputChar, " Letra ou numero ou underscore esperado mas: ");
    }
    if(isDot(inputChar)) showError(inputChar, " Letra ou numero ou underscore esperado mas: ");
    if(isMajor(inputChar)) {
        //se apos um identificador vier operador logico e tiver caracteres invalidos
        if(isDot(input[dot + 1]) || isSeparator(input[dot + 1]) || isOperator(input[dot + 1])
          || isMinor(input[dot + 1]) || isLogicalOperator(input[dot + 1]))
            showError(inputChar, " Letra ou numero ou underscore esperado mas: ");
    }
    if(isMinor(inputChar)) {
        //se apos um identificador vier operador logico e tiver caracteres invalidos
        if(isDot(input[dot + 1]) || isSeparator(input[dot + 1]) || isOperator(input[dot + 1])
          || isMajor(input[dot + 1]) || isLogicalOperator(input[dot + 1]))
            showError(inputChar, " Letra ou numero ou underscore esperado mas: ");
    }
    if(isLogicalOperator(inputChar)) {
        //se apos um identificador vier operador logico e tiver caracteres invalidos
        if(isDot(input[dot + 1]) || isSeparator(input[dot + 1]) || isOperator(input[dot + 1])
          || isMinor(input[dot + 1]) || isMajor(input[dot + 1]))
            showError(inputChar, " Letra ou numero ou underscore esperado mas: ");
    }
}
/*****************************************************************************************************
 *  recognizeIntegerOrFloat -> Cria constante numerica (inteiro/real)
 *
 ****************************************************************************************************/
void Lex::recognizeIntegerOrFloat(TokenType* no) {
    no->setClasse(INTEGER);
    nextChar();
    while (isDigit(inputChar)) {
        nextChar();
        if(isDot(inputChar)){
            no->setClasse(FLOAT);
            nextChar();
        }
    }
    //se tiver erros
    digitErrors(inputChar);
    //se nao tiver
    no->setLine(line);
    no->setColumn(startDot);
    no->setToken(inputToZString(startDot, dot-startDot));
}
/*****************************************************************************************************
 *  digitErrors -> faz analise sintatica dos digitos
 *
 ****************************************************************************************************/
void Lex::digitErrors(int inputChar){
    if(isLetter(inputChar)) showError(inputChar, " digitor esperado mas: ");
    if(isSeparator(inputChar) && inputChar != ';') {
        if(!liststmt && inputChar != ',' && inputChar != '(' && inputChar != ')') showError(inputChar, " digitor esperado mas: ");
    }
    if(isAssign(inputChar)) showError(inputChar, " digitor esperado mas: ");
    if(isUnderscore(inputChar)) showError(inputChar, " digitor esperado mas: ");
}
/*****************************************************************************************************
 *  showError -> Mostra mensagem de erro
 *  inputChar => caractere invalido
 *  msg => mensagem
 *
 ****************************************************************************************************/
void Lex::showError(int inputChar,const string msg){
    cout<<"Erro na linha: "<<(line+1)<<" coluna: "<<(dot+1)<<msg<<(char)inputChar<<" encontrado!"<<endl;
    cin.get();
    exit(1);
}
/*****************************************************************************************************
 *  skipLayoutAndComment -> iguinora ' ' e comentario
 *
 ****************************************************************************************************/
void Lex::skipLayoutAndComment() {
    while (isLayout(inputChar)) {
        nextChar();
    }
    while (isCommentStarter(inputChar)) {
        nextChar();
        while (!isCommentStopper(inputChar)) {
            if (isEndOfInput(inputChar)) {
                return;
            }
            nextChar();
        }
        nextChar();
        while (isLayout(inputChar)) {
            nextChar();
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
        dot = 0;
        inputChar = input[dot];
        cout<<"Entrada: "<<input<<" dot: "<<dot<<" inputChar: "<<(char)inputChar<<endl;
        list = ProducerList::getInstance(); //pega referencia da lista de produçoes
    }
    else{
        cout<<"Erro na leitura do arquivo!"<<endl;
        cin.get();
        exit(1);
    }
}
/*****************************************************************************************************
 *  inputToZString -> Copia uma substring de uma string
 *  copia uma substring do buffer 'input'
 *
 ****************************************************************************************************/
string Lex::inputToZString (int iStart, int iLength) {
    int i;
    string buffer;
    for (i = 0; i < iLength; i++) {
        buffer += input[i+iStart];
    }

    cout<<"Token criado: "<<buffer<<endl;
    cin.get();
    return buffer;
}
/*****************************************************************************************************
 *  getNextToken -> Separa os tokens e salva na lista de producoes
 *  Se for '\n'                 incrementa line e retorna liberando a pilha
 *  Se for '\0' e´              fim do arquivo
 *  Se for letra >>             valida o identificador
 *  Se for '=='                 alguma expressao logica
 *  Se for '>' ou '>='          expressao logica
 *  Se for '<' ou '<='          expressao logica
 *  Se for '='                  atribuicao
 *  Se for '~'                  lista
 *  Se for Operador/Separador
 *  Se for digito               constante
 ****************************************************************************************************/
bool Lex::getNextToken(TokenType* noStatement) {
    TokenType *no = new TokenType(); //cria novo token
    no->setInitBlock(NULL);
    no->setEndBlock(NULL);
    no->setReference(NULL);

    skipLayoutAndComment();
    startDot = dot;

    if(isEndOfLine(inputChar)){
        no->setClasse(END_CMD);
        no->setToken(";");
        list->insert(no);
        nextChar();
        line++;
        return false;   //libera a pilha
    }
    if (isEndOfInput(inputChar)) {
        no->setClasse(FIM);
        no->setToken("<FIM>");
        list->insert(no);
        return true; //fim do arquivo
    }
    if (isLetter(inputChar)) {
        recognizeIdentifier(no);

        list->insert(no);

        //se if
        if(no->getClasse() == IF) return getNextToken(no); //recursao
        else return getNextToken(NULL);
    }
    else if(isDoubleAssign()){
        no->setClasse(IGUAL);
        nextChar();
        no->setToken(inputToZString(startDot, dot-startDot));
        list->insert(no);
        nextChar();
        if(noStatement) return getNextToken(noStatement);
        else return getNextToken(NULL);
    }
    else if(isMajor(inputChar)){
        if(isAssign(input[dot+1])) {
            nextChar();
            no->setClasse(MAIOR_IGUAL);
            no->setToken(inputToZString(startDot, dot-startDot));
            list->insert(no);
            nextChar();
            if(noStatement) return getNextToken(noStatement);
            else return getNextToken(NULL);
        }
        else{
            no->setClasse(MAIOR);
            no->setToken(inputToZString(startDot, dot-startDot));
            list->insert(no);
            nextChar();
            if(noStatement) return getNextToken(noStatement);
            else return getNextToken(NULL);
        }
    }
    else if(isMinor(inputChar)){
        if(isAssign(input[dot+1])) {
            nextChar();
            no->setClasse(MENOR_IGUAL);
            no->setToken(inputToZString(startDot, dot-startDot));
            list->insert(no);
            nextChar();
            if(noStatement) return getNextToken(noStatement);
            else return getNextToken(NULL);
        }
        else{
            no->setClasse(MENOR);
            no->setToken(inputToZString(startDot, dot-startDot));
            list->insert(no);
            nextChar();
            if(noStatement) return getNextToken(noStatement);
            else return getNextToken(NULL);
        }
    }
    else if(isAssign(inputChar)){
        setAssign(inputChar, no);
        list->insert(no);
        nextChar();
        return getNextToken(NULL);
    }
    else if(isTil(inputChar)){
        //lista
        no->setClasse(LIST);
        no->setToken(inputToZString(startDot, dot-startDot));
        nextChar();
        return getNextToken(no);
    }
    else if (isOperator(inputChar) || isSeparator(inputChar)) {
        no->setClasse(inputChar);
        no->setToken(inputToZString(startDot, dot-startDot));

        if(noStatement){
            if(noStatement->getClasse() == IF && !ifStatementBlock(noStatement, no)){
                list->insert(no);
                nextChar();
                return getNextToken(noStatement);
            }
            else if(noStatement->getClasse() == LIST && !listBlock(noStatement, no)){
                list->insert(no);
                nextChar();
                return getNextToken(noStatement);
            }
        }
        else{
            list->insert(no);
            nextChar();
            return getNextToken(NULL);
        }
    }
    else if (isDigit(inputChar)) { //pode ser int ou float
        recognizeIntegerOrFloat(no);
        list->insert(no);
        if(noStatement) return getNextToken(noStatement);
        else return getNextToken(NULL);
    }
    /*else {
        no->setClasse(ERRONEOUS);
        list->insert(no);
        nextChar();
        return false;
    }*/

    //list->insert(no); //nova entrada na lista
}
/*****************************************************************************************************
 *  setAssign -> Apenas para tirar um pouco do getNextToken
 *  Seta as informacoes do '='
 ****************************************************************************************************/
void Lex::setAssign(int inputChar, TokenType *no){
    no->setClasse(ASSIGN);
    no->setToken(inputToZString(startDot, dot-startDot));
    skipLayoutAndComment();
    //se tiver erros
    assignErrors(inputChar);
    //se nao tiver
    no->setLine(line);
    no->setColumn(startDot);
}
/*****************************************************************************************************
 *  assignErrors -> Verifica a sintax da atribuicao,
 *  se tem um '=' entao logo em seguida deve ser digito ou identificador
 *
 ****************************************************************************************************/
void Lex::assignErrors(int inputChar){
    if(isDot(inputChar)) showError(inputChar, " digito ou identificador esperado mas: ");
    if(isSeparator(inputChar)) showError(inputChar, " digito ou identificador esperado mas: ");
    if(isMajor(inputChar)) showError(inputChar, " digito ou identificador esperado mas: ");
    if(isMinor(inputChar)) showError(inputChar, " digito ou identificador esperado mas: ");
    if(isLogicalOperator(inputChar)) showError(inputChar, " digito ou identificador esperado mas: ");
}
/*****************************************************************************************************
 *  listBlock -> Cria o bloco da lista ~(1,2,3)
 *  Verifica a sintax
 *
 ****************************************************************************************************/
bool Lex::listBlock(TokenType* noStatement, TokenType* current){
    if(!noStatement->getInitBlock()){
        if(inputChar == '(') noStatement->setInitBlock(current);
        else showError(inputChar, " ( esperado mas: ");
    }
    else if(noStatement->getInitBlock() && !noStatement->getEndBlock()){
        if(inputChar == ')') {
            noStatement->setEndBlock(current);
            return true;
        }
        else if(inputChar != ',') showError(inputChar, " ) esperado mas: ");
    }
    //se nao qualquer coisa incluindo ,
    return false;
}
/*****************************************************************************************************
 *  ifStatementBlock -> Cria o <expression> do IF e o bloco {}
 *  Faz analise sintatica do <expression> e do bloco, verificando o inicio do
 *  <expression> entre () obrigatoriamente e {} obrigatorio tambem
 *
 ****************************************************************************************************/
bool Lex::ifStatementBlock(TokenType* noStatement, TokenType* current){

    if(!noStatement->getStatmentInit()){
        if(inputChar == '(') noStatement->setStatmentInit(true);
        else showError(inputChar, " ( esperado mas: ");
    }
    else if(!noStatement->getStatmentEnd()){
        if(inputChar == ')') noStatement->setStatmentEnd(true);
        else if(inputChar == '{' || inputChar == '}') showError(inputChar, " ( esperado mas: ");
        //se nao eh apenas expressao logica
    }
    else if(noStatement->getStatmentInit() && noStatement->getStatmentEnd() && !noStatement->getInitBlock()){
        if(inputChar == '{') noStatement->setInitBlock(current);
        else showError(inputChar, " { esperado mas: ");
    }
    else if(noStatement->getStatmentInit() && noStatement->getStatmentEnd()){
        if(noStatement->getInitBlock()){
            if(inputChar == '}') {
                noStatement->setEndBlock(current);
                nextChar();//proximo caractere para continuar
                ifstmt = false;
                return true; //sai da criacao do if(<expr>){<block>}
            }
            //se nao continua pegando os comandos do bloco
        }
        else showError(inputChar, " { esperado mas: ");
    }

    return false;
}
/*****************************************************************************************************
 *  isDoubleAssign -> Verifica se e´ ==
 *
 ****************************************************************************************************/
bool Lex::isDoubleAssign(){
    if(input[dot] == '=' && input[dot-1] == '=') return true;
    return false;
}
/*****************************************************************************************************
 *  Parser -> inicia a producao de tokens e analise sintatica
 *  Primeiro chama startLex() que seta todas as informacoes necessarias
 *  Segundo chama getNextToken(NULL) que vai quebrando e empilhando os tokens
 *  quando acha ';' retorna um false (nao e´ o fim do arquivo)
 *  e quando for true - fim do arquivo
 ****************************************************************************************************/
void Lex::parser(){

    while(!getNextToken(NULL));

}
