#ifndef ERROR_H
#define ERROR_H

#include "Defs.h"

class Error
{
    private:
        static Error*       instance;

    public:
        Error();
        ~Error();

        static Error*       getInstance();
        void                showError(const string msg, int line, int column,const string token);
};

#endif // ERROR_H
