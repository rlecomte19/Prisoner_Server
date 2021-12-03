#include <stdio.h>
#include <stdlib.h>

#include "./Binomes/binomes.h"
#include "./Communication/net_prisoner_server.h"

Binome *binomes;
// Binome *binomes = malloc(sizeof(Binome) * MAX_CLIENTS);


// void client_disconnect(int id){

// }
// void round(Binome *b){
// 	net_server_send_choice(b->clients_id[0]);
// 	net_server_send_choice(b->clients_id[1]);
// }



int main()
{	
	WaitingRoom *room = malloc(sizeof(WaitingRoom));
	Binome *binomes = malloc(sizeof(Binome)*(MAX_CLIENTS/2));

	if(room != NULL && binomes != NULL){
		initialize_waiting_room(room);
		
		add_to_waiting_room(room, 1);
		add_to_waiting_room(room, 14);
		add_to_waiting_room(room, 2);
		add_to_waiting_room(room, 63);
		//print_waiting_room(room);
		//printf("\n");
		binomes = create_binomes(room);
	}else{
		printf("\n/!\\ La salle d'attente n'a pas pu être initialisée /!\\");
	}
	for(int l=0;l<MAX_CLIENTS/2;l++){
        printf("\n[BINOME %d] - IDS : ", l);
        for(int k=0;k<MAX_CLIENTS/2;k++){
            printf("%d ", binomes[l].clients_id[k]);
        }
        printf("\n");
    }

	free(room);
	free(binomes);

	return (0);
}