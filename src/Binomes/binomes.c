#include "./binomes.h"
#include <time.h>

void initialize_binome_list(BinomeList *bL){
    bL->list = malloc(sizeof(BinomeList));
    bL->size = 0;
}
void initialize_binome(Binome *binome){
    binome->gameIndex = -1;
    binome->clientIndex = -1;
}

/** @todo!!! Mettre en place la création des binomes à partir de la liste du fichier de paramétrage */




