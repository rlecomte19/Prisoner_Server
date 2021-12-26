#include "./Game/game.h"
#include "./Communication/net_prisoner_server.h"
#include "Results/results.h"
#include "Configuration/configuration.h"


int main()
{
	// Config à pas bouger atm
	init_configuration();

	init_server();
	
	// while(1){
	// 	sleep(2);
	// }

	// Binome *b = malloc(sizeof(Binome));
	// b = _get_client_binome(3);
	// printf("[BinomeList][Taile : %d] - \t\n [Binome 0] - \n [ReponseP1 : %d] \n [ReponseP2 : %d] \n [GameIndex : %d] \n [ID client 1 : %d] \n [ID client 2: %d]", 
	// 	binome_config_list->size,
	// 	binome_config_list->list[1].clients_answers->p1, 
	// 	binome_config_list->list[1].clients_answers->p2, 
	// 	binome_config_list->list[1].gameIndex,
	// 	binome_config_list->list[1].clients_id[0],
	// 	binome_config_list->list[1].clients_id[1]
	// );

	// printf("\n================================\n");
 
 	// printf("[BinomeTest] - \t\n [Binome 0] - \n [ReponseP1 : %d] \n [ReponseP2 : %d] \n [GameIndex : %d] \n [ID client 1 : %d] \n [ID client 2: %d]", 
	// 	binome_config_list->list[2].clients_answers->p1, 
	// 	binome_config_list->list[2].clients_answers->p1, 
	// 	binome_config_list->list[2].gameIndex,
	// 	binome_config_list->list[2].clients_id[0],
	// 	binome_config_list->list[2].clients_id[1]
	// );

	return (0);
}