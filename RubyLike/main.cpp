#include "src/lex.h"

int main(int argc, char *argv[])
{
    File file("text.txt", 1);
    Lex lex;

    while(lex.parser(file));

    ProducerList *list = ProducerList::getInstance();

    list->showValues();

    cin.get();

    return 0;
}
