#include "src/lex.h"

int main(int argc, char *argv[])
{
    File fp("attr.rb", 1);
    Lex lex;

    lex.startLex(fp);
    lex.parser();

    lex.show();

    cin.get();
    return 0;
}
