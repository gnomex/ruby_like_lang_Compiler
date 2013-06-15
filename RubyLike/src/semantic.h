#ifndef SEMANTIC_H
#define SEMANTIC_H

class Semantic
{
    private:
        static Semantic* instance;
        Semantic();
    public:
        ~Semantic();
        static Semantic* getInstance();
};

#endif // SEMANTIC_H
