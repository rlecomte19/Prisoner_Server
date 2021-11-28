#include <stdio.h>
#include <stdlib.h>

#include "../WaitingRoom/waiting_room.h"

typedef struct{
    int clients_id[2];
    int size;
}Binome;

void initialize_binome(Binome *binome);
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

int *randomly_mix_clients(WaitingRoom *room);


