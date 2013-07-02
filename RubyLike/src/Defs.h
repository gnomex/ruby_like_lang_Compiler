#ifndef DEFS_H
#define DEFS_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <QHash>
#include <QList>
#include <QStack>

using namespace std;
/*
 *  Definiçoes para identificaçao de elementos da linguagem
 *
 */
#define FIM         256 //fim do arquivo de entrada e da producao de tokens
#define IDENTIFIER  257
#define INTEGER     258
#define FLOAT       259
#define MAIOR       260
#define MENOR       261
#define MAIOR_IGUAL 262
#define MENOR_IGUAL 263
#define IGUAL       264
#define NOT_EQUAL   265
#define SEPARATOR   266
#define BLOCO       267
#define SETA        268
#define IF          269
#define LIST        270
#define ASSIGN      271
#define END_CMD     272
#define LOOP        273
#define OPERATOR    274
#define STRING      275
#define LOGICAL     276
#define RESERVADO   277
#define ERRONEOUS   278
#define CONST       279
#define NON_TYPE    -2

#endif // DEFS_H
