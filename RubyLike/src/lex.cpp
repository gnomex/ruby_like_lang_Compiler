#include "lex.h"

#define isEndOfLine(ch)                     ((ch) == '\n')
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

#define isOperator(ch)                      (strchr("+-*/", (ch)) != 0)
#define isSeparator(ch)                     (strchr(",(){}=;", (ch)) != 0)

Lex::Lex()
{

}

Lex::~Lex(){}

void Lex::nextChar(){
    inputChar = input[++dot];
    cout<<"nextChar: "<<(char)inputChar<<endl;
}

void Lex::recognizeIdentifier(TokenType *no) {
    no->setClasse(IDENTIFIER);
    nextChar();
    while(isLetterOrDigit(inputChar)) {
        nextChar();
    }
    while (isUnderscore(inputChar) && isLetterOrDigit(input[dot+1])) {
        nextChar();
        while (isLetterOrDigit(inputChar)) {
            nextChar();
        }
    }
}

void Lex::recognizeInteger(TokenType *no) {
    no->setClasse(INTEGER);
    nextChar();
    while (isDigit(inputChar)) {
        nextChar();
    }
}

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

void Lex::noteTokenPosition() {
    //Token.pos.charNumber = dot;
}

bool Lex::startLex(File& file) {
    input = file.readString(); //le uma linha do arquivo
    if(!input.empty()){
        dot = 0;
        inputChar = input[dot];
        cout<<"Entrada: "<<input<<" dot: "<<dot<<" inputChar: "<<(char)inputChar<<endl;
        cin.get();
        list = ProducerList::getInstance(); //pega referencia da lista de produçoes
        return true;
    }
    return false;
}

string Lex::inputToZString (int iStart, int iLength) {
    int i;
    //char *ch = (char *)malloc(sizeof(char) * (iLength+1));
    string buffer;
    for (i = 0; i < iLength; i++) {
        //ch[i] = input[i+iStart];
        buffer += input[i+iStart];
    }
    //ch[i] = '\0';
    cout<<"Token criado: "<<buffer<<endl;
    cin.get();
    return buffer;
}
/*
 * Le o buffer e classifica a entrada, podendo ser:
 * Fim do arquivo, identificador, inteiro, operador, ou um erro
 */
void Lex::getNextToken() {
    TokenType no; //cria nova na lista
    int startDot;

    skipLayoutAndComment();
    noteTokenPosition();
    startDot = dot;

    if(isEndOfLine(inputChar)){
        return;
    }
    if (isEndOfInput(inputChar)) {
        no.setClasse(FIM);
        no.setToken("<FIM>");
        return;
    }
    if (isLetter(inputChar)) {
        recognizeIdentifier(&no);
        no.setToken(inputToZString(startDot, dot-startDot));
        cout<<"Token produzido: "<<no.getToken()<<endl;
        getNextToken();
    }
    else if (isOperator(inputChar) || isSeparator(inputChar)) {
        no.setClasse(inputChar);
        no.setToken(inputToZString(startDot, dot-startDot));
        cout<<"Operador/Separador: "<<no.getClasse()<<endl;
        nextChar();
        getNextToken();
    }
    else if (isDigit(inputChar)) {
        recognizeInteger(&no);
        no.setToken(inputToZString(startDot, dot-startDot));
        getNextToken();
    }
    else {
        no.setClasse(ERRONEOUS);
        nextChar();
    }

    list->insert(no); //nova entrada na lista
}

bool Lex::parser(File& file){
    if(startLex(file)){
        getNextToken();
        return true;
    }
    return false;
}
