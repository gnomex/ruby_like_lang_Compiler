#include "src/lex.h"
#include "src/syntactic.h"
#include "src/semantic.h"

int main(int argc, char *argv[])
{
    if(argc<3){
        cout<<"Modo de uso:"<<endl;
        cout<<"./AST fileIN fileOUT"<<endl;
    }
    else{
        File fp(argv[1], argv[2]);

        Lex *lex = new Lex();
        lex->startLex(fp);

        Syntactic syn(lex);
        syn.parser();
        fp.close();
        syn.show();

        Semantic sem;
        sem.parsing();
    }

    return 0;
}
