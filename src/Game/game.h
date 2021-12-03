#include "../Binomes/binomes.h"

typedef struct{
    int nbMaxRounds;
    int currentRound;
    Binome *b; 
} Game;

void betray();
void collaborate();
void endGame();
int are_answers_written(Binome *b); 
Binome* get_client_binome(int id);