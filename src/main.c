#include "./Game/game.h"
#include "./Communication/net_prisoner_server.h"
#include "Configuration/configuration.h"

int main()
{
	// Config à pas bouger atm
	init_configuration();

	GameList gl;
	gl.gameList = (Answer *)malloc(sizeof(Game) * 3);
	gl.size = 3;
	for (int i = 0; i < 3; i++)
	{
		const int RoundSize = 10;

		Game g;
		g.nbMaxRounds = RoundSize;
		g.currentRound = RoundSize;

		Binome b;
		b.clients_id[0] = rand() % 100;
		b.clients_id[1] = rand() % 100;
		b.gameIndex = i;

		AnswerList al;
		al.answers = (Answer *)malloc(sizeof(Answer) * RoundSize);
		al.size = RoundSize;
		for (int j = 0; j < RoundSize; j++)
		{
			if (rand() % 2 == 0)
			{
				al.answers[j].p1 = COLLAB;
				al.answers[j].p2 = BETRAY;
			}
			else
			{
				al.answers[j].p1 = BETRAY;
				al.answers[j].p2 = COLLAB;
			}
		}

		g.list_of_answers = &al;
		gl.gameList[i] = &g;
	}

	return (0);
}