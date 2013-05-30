#include "lex.h"

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
#define isSeparator(ch)                     (strchr(";,(){}", (ch)) != 0)

Lex::Lex()
{
}

Lex::~Lex(){}

/*void Lex::nextChar(){
    inputChar = input[++dot];
}


char* Lex::getInput() {
    char *ch = (char *) malloc(50);
    cout << "Informe o texto de entrada: " << endl;
    fgets(ch, 50, stdin);
    return ch;
}

void Lex::recognizeIdentifier() {
    Token.classe = IDENTIFIER;
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

void Lex::recognizeInteger() {
    Token.classe = INTEGER;
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
    Token.pos.charNumber = dot;
}

void Lex::startLex() {
    input = getInput();
    dot = 0;
    inputChar = input[dot];
}

char* Lex::inputToZString (int iStart, int iLength) {
    int i;
    char *ch = (char *)malloc(sizeof(char) * (iLength+1));
    for (i = 0; i < iLength; i++) {
        ch[i] = input[i+iStart];
    }
    ch[i] = '\0';
    return ch;
}

void Lex::getNextToken() {
    int startDot;

    skipLayoutAndComment();
    noteTokenPosition();
    startDot = dot;

    if (isEndOfInput(inputChar)) {
        Token.classe = FIM;
        Token.repr = "<FIM>";
        return;
    }
    if (isLetter(inputChar)) {
        recognizeIdentifier();
    }
    else if (isDigit(inputChar)) {
        recognizeInteger();
    }
    else if (isOperator(inputChar) || isSeparator(inputChar)) {
        Token.classe = inputChar;
        nextChar();
    }
    else {
        Token.classe = ERRONEOUS;
        nextChar();
    }
    Token.repr = inputToZString(startDot, dot-startDot);
}
*/
