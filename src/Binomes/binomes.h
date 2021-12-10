#include <stdio.h>
#include <stdlib.h>

#include "../Answer/answer.h"

#ifndef binomes_h
#define binomes_h

typedef struct
{
    int clients_id[2];
    Answer *clients_answers;
    int gameIndex;
    int clientIndex;
} Binome;

typedef struct
{
    Binome *list;
    int size;
} BinomeList;

/**
 * @brief Initialize binome struct
 *
 * @param *binome
 */
void initialize_binome(Binome *binome);

void initialize_binome_list(BinomeList *bL);

#endif