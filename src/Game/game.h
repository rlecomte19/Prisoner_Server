#include "../Binomes/binomes.h"
#include "../Answer/answer.h"
#include "../Communication/net_prisoner_server.h"


typedef struct{
    int nbMaxRounds;
    int currentRound;
    Binome *b; 
} Game;

typedef struct {
    Game *gameList;
    int index;
} GameList;


void game_init(GameList *list, Game *game, Binome *binome);
void betray();
void collaborate();
void endGame();
void endRound();
int _are_answers_written(Binome *b); 
void _add_new_game(G);
Binome* _get_client_binome(int id);
Game* _get_game_binome(Binome *b);
void add_to_game_list(GameList *list, Game *game);