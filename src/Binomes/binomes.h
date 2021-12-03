#include <stdio.h>
#include <stdlib.h>

#include "../WaitingRoom/waiting_room.h"

typedef struct{
    int clients_id[2];
    short answer[2];
    int index;
}Binome;

typedef struct{
    Binome *list; 
    int size;
} BinomeList;

void initialize_binome(Binome *binome);

void initialize_binome_list(BinomeList *bL);
/**
 * @brief Return a list of binomes randomly created from a waiting room
 * 
 * @param room 
 * @return Binome* 
 */
Binome *create_binomes(WaitingRoom *room);

/**
 * @brief Add a client id to the binome
 * 
 * @param binome 
 * @param client_id 
 */
void add_to_binome(Binome *binome, int client_id);

/**
 * @brief Create a copy of clients identifiers that are contained in the waiting room
 * 
 * @param room 
 * @return int* 
 */
int *randomly_mix_clients(WaitingRoom *room);


