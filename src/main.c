#include "./Game/game.h"
#include "./Communication/net_prisoner_server.h"
#include "Configuration/configuration.h"
#include "Results/results.h"

// triggered when a client is successfully connected to server
void new_client(int client_id)
{
	printf("new_client id %d\n", client_id);
	net_server_send_screen_waiting(432);

	sleep(2);

	net_server_send_screen_choice(432);
    
    //additionnal server logic here when a new client arrived
}

//triggered when a server is disconnecting from the server
void client_disconnecting(int client_id)
{
	printf("client disconnecting: %d\n", client_id);
}

//triggered when a client has clicked the cooperate button
void client_cooperate(int client_id, ulong tps)
{
	printf("client #%d coop (%ld ms)\n", client_id, tps);
}

//triggered when a client has clicked the betray button
void client_betray(int client_id, ulong tps)
{
	printf("client #%d betray (%ld ms)\n", client_id, tps);
}

int main()
{
	// Config à pas bouger atm
	init_configuration();

	net_server_set_func_new_client(new_client);
	net_server_set_func_client_disconnect(client_disconnecting);
	net_server_set_func_cooperate(client_cooperate);
	net_server_set_func_betray(client_betray);
	
	char *addrServer = "0.0.0.0";
	net_server_init(addrServer, 7799);

	net_server_wait();

	while(1){};

    //this line isn't reached, it's here to make the compiler happy :)
	return (EXIT_SUCCESS);

	// GameList gl;
	// gl.gameList = (Game *)malloc(sizeof(Game) * 3);
	// gl.size = 3;
	// for (int i = 0; i < 3; i++)
	// {
	// 	const int RoundSize = 10;

	// 	Game *g = &gl.gameList[i];
	// 	g->nbMaxRounds = RoundSize;
	// 	g->currentRound = RoundSize;
	// 	g->b = (Binome *)malloc(sizeof(Binome));
	// 	g->list_of_answers = (AnswerList *)malloc(sizeof(AnswerList));

	// 	Binome *b = g->b;
	// 	b->clients_id[0] = rand() % 100;
	// 	b->clients_id[1] = rand() % 100;
	// 	b->gameIndex = i;

	// 	AnswerList *al = g->list_of_answers;
	// 	al->answers = (Answer *)malloc(sizeof(Answer) * RoundSize);
	// 	al->size = RoundSize;
	// 	for (int j = 0; j < RoundSize; j++)
	// 	{
	// 		if (rand() % 2 == 0)
	// 		{
	// 			al->answers[j].p1 = COLLAB;
	// 			al->answers[j].p2 = BETRAY;
	// 		}
	// 		else
	// 		{
	// 			al->answers[j].p1 = BETRAY;
	// 			al->answers[j].p2 = COLLAB;
	// 		}
	// 	}
	// }

	// store_results("rapport.csv", gl);

	return (0);
}