#ifndef SYNTACTIC_H
#define SYNTACTIC_H

#include "Defs.h"

class Syntactic
{
    private:
        static Syntactic* instance;
        Syntactic();
    public:
        ~Syntactic();
        static Syntactic* getInstance();
};

#endif // SYNTACTIC_H
