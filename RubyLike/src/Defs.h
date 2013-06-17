#ifndef DEFS_H
#define DEFS_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <QHash>
#include <QList>

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
#define REFERENCIA  265
#define BLOCO       266
#define RESERVADO   267
#define IF          268
#define LIST        269
#define ASSIGN      270
#define END_CMD     271
#define ERRONEOUS   272

#endif // DEFS_H
