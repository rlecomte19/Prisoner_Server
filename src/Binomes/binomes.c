#include "./binomes.h"
#include <time.h>

Binome *create_binomes(WaitingRoom *room){
    // Retrieves a copy of mixed clients identifiers in an array
    int *ids = randomly_mix_clients(room);

    // Array of binomes which will be used to create rounds
    Binome *binomes = malloc(sizeof(Binome) * (MAX_CLIENTS/2));

    int idIndex = 0; // Used to fill binomes client identifiers at the right positions
    
    // Used to save binomes to the correct index
    for(int i=0; i<room->size/2;i++){
        // Used to retrieve clients id 2 by 2
        for(int j=0;j<room->size/2;j+=2){
            Binome b;
            initialize_binome(&b);
            add_to_binome(&b, ids[idIndex]);
            add_to_binome(&b, ids[idIndex+1]);
            binomes[i] = b;
            idIndex+=2;
        }
    }

    return binomes;
}

int* randomly_mix_clients(WaitingRoom *room){
    
    srand(time(0));

    int *clients_id = room->id_clients;
    
    // Randomly mix half of the clients id
    for(int i=0;i<room->size/2;i++){
        int randomIndex = rand() % ((room->size-1) - 0 + 1) + 0;

        int id_client_to_move = clients_id[i];
        clients_id[i] = clients_id[randomIndex];
        clients_id[randomIndex] = id_client_to_move;
    }

    return clients_id;
}

void add_to_binome(Binome *binome, int client_id){
    binome->clients_id[binome->size] = client_id;
    binome->size++;
}
void initialize_binome(Binome *binome){
    binome->size = 0;
}



