#ifndef TOKENTYPE_H
#define TOKENTYPE_H

/*
 *  Classe para representar um token
 *
 */
class TokenType
{
    private:
        char classe;    //tipo de token
        char *repr;     //token
        int line;       //linha do arquivo
        int column;     //coluna do arquivo

    public:
        TokenType();
        ~TokenType();
        void setClasse(char classe);
        void setToken(char *repr);
        void setLine(int line);
        void setColumn(int column);
        char getClasse();
        char *getToken();
        int getLine();
        int getColumn();
};

#endif // TOKENTYPE_H
