#include "src/lex.h"
#include "src/syntactic.h"
#include "src/semantic.h"

int main(int argc, char *argv[])
{
    File fp("test03.rb", "out.rb");

    Lex *lex = new Lex();
    lex->startLex(fp);

    Syntactic syn(lex);
    syn.parser();
    syn.show();

    Semantic sem;
    sem.parsing();

    cin.get();
    return 0;
}
