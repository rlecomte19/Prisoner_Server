#include "game.h"

BinomeList *binomes;
GameList *list_of_games;


// ----------------------------------------------
//                 GAME INITIALISATIONS
// ----------------------------------------------
void game_init(Game *game, Binome *binome)
{
    // Initializing Game structure elements
    game = malloc(sizeof(Game));
    game->b = binome;
    game->currentRound = 0;
    game->list_of_answers = malloc(sizeof(AnswerList));

    // Size from GameList is added as binome current game
    binome->gameIndex = list_of_games->size;

    // Registering the created game to server's list
    _add_new_game(game);
    // Sending to the client the "order" of displaying game's view
    net_server_send_screen_choice(binome->clients_id[0]);
    net_server_send_screen_choice(binome->clients_id[1]);
}

void _add_new_game(Game *game){
    list_of_games->gameList[list_of_games->size] = game;
    list_of_games->size++;
}



// ----------------------------------------------
//                 GAME MANAGEMENT
// ----------------------------------------------
void betray(int id, ulong answerTime){

    Binome *usedBinome = _get_client_binome(id);
    int playerIdIndex = -1;
    for (int i = 0; i < 2; i++)
    {
        if (usedBinome->clients_id[i] == id)
        {
            playerIdIndex = i;
        }
    }
    if (_are_answers_written(usedBinome))
    {
        switch (playerIdIndex)
        {
        case 0:
            usedBinome->clients_answers->p1_answer = "Trahison";
            break;
        case 1:
            usedBinome->clients_answers->p2_answer = "Trahison";
            break;
        }
        end_round(usedBinome);
    }
    else
    {
        net_server_send_screen_waiting(id);
    }
}

void collaborate(int id, unsigned long answerTime)
{
    Binome *usedBinome = _get_client_binome(id);
    int playerIdIndex = -1;
    for (int i = 0; i < 2; i++)
    {
        if (usedBinome->clients_id[i] == id)
        {
            playerIdIndex = i;
        }
    }
    // If each player has answered, their answers are registered and the round can end.
    // If only the player who calls this function is answering, he is "ordered" to wait the other player's answer
    if (_are_answers_written(usedBinome))
    {
        switch (playerIdIndex)
        {
        case 0:
            usedBinome->clients_answers->p1_answer = "Collaboration";
            break;
        case 1:
            usedBinome->clients_answers->p2_answer = "Collaboration";
            break;
        }
        end_round(usedBinome);
    }
    else
    {
        net_server_send_screen_waiting(id);
    }
}

void reinitializeAnswer(Binome *b)
{
    b->clients_answers->p1_answer = -1;
    b->clients_answers->p2_answer = -1;
}

void end_round(Binome *b){
    Game *binomeGame = _get_game_binome(b);
    reinitializeAnswer(b);
    if(binomeGame->currentRound == binomeGame->nbMaxRounds){
        // end_game();
    }else{
        // net_server_send_screen_score(); (aux deux)
    }
}

// ----------------------------------------------
//                 GAME DATA RECOVERY
// ----------------------------------------------
Binome *_get_client_binome(int id)
{
    Binome *usedBinome;
    for (int i = 0; i < binomes->size; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (binomes->list[i].clients_id[j] == id)
            {
                // asigns address of right binome to a temporary variable
                usedBinome = &(binomes->list[i]);
            }
        }
    }
    return usedBinome;
}

int _are_answers_written(Binome *b)
{
    int answersWritten = 0;
    if (b->clients_answers->p1_answer != -1 && b->clients_answers->p2_answer != -1)
    {
        answersWritten = 1;
    }
    return answersWritten;
}

Game *_get_game_binome(Binome *b)
{
    // Retrieving the affected game from gameIndex contained into "Binome" param  
    Game *usedGame;
    usedGame = list_of_games->gameList[b->gameIndex];
    return usedGame;
}

void end_game(Binome *b){
    Game *g = _get_game_binome(b);
    for(int i=0; i<g->list_of_answers->size;i++){
        // store_results(AnswerList *list)
    }

}
// ------------------------------------
//                 BINOMES
// ------------------------------------
void initialize_binome(Binome *binome){
    binome->gameIndex = -1;
    binome->clientIndex = -1;
}
void initialize_binome_list(BinomeList *bL){
    bL->list = malloc(sizeof(BinomeList));
    bL->size = 0;
}


/** @todo!!! Mettre en place la création des binomes à partir de la liste du fichier de paramétrage */


// ----------------------------------------------
//               ANSWERS OF BINOMES
// ----------------------------------------------
void initialize_answer(Answer *answer) {
    answer = malloc(sizeof(Answer));
}
void initialize_answer_list(AnswerList *list) {
    list = malloc(sizeof(AnswerList));
}
extern BinomeList *binomes;
extern GameList *gameList;
void add_to_answer(Binome *b, int client_id, char *answer){

}
void add_to_answer_list(AnswerList *list, Answer *answer) {
    list->answers[list->size] = answer;
    list->size++;
}