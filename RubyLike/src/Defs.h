#ifndef DEFS_H
#define DEFS_H

#define FIM         256
#define IDENTIFIER  257
#define INTEGER     258
#define ERRONEOUS   259

typedef struct {
    char* file_name;
    int line_number;
    int char_number;
} PositionInFile;

typedef struct {
    int classe;
    char* repr;
    PositionInFile pos;
} TokenType;

#endif // DEFS_H
