#ifndef TOKENTYPE_H
#define TOKENTYPE_H

class TokenType
{
    private:
        char classe;
        char *repr;
        int line;
        int column;

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
