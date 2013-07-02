#include "src/lex.h"
#include "src/syntactic.h"

int main(int argc, char *argv[])
{
    File fp("srctest.rb", 1);
    Lex *lex = new Lex();
    lex->startLex(fp);
    Syntactic syn(lex);

    syn.parser();
    syn.show();

    cin.get();
    return 0;
}
