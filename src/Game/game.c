#include "./game.h"

/** 
 * --------------------------------------------------------------------------------------
 *                                   GAME INITIALISATIONS
 * --------------------------------------------------------------------------------------
 *
 * 
 * 
*/
GameList *game_config_list;
BinomeList *binome_config_list;

void game_init()
{
    // Allocation of external structs given in game.h
    game_config_list = malloc(sizeof(GameList));
    binome_config_list = malloc(sizeof(BinomeList));

    _init_binomes_from_config(binome_config_list);
    _initialize_game_list(game_config_list);


    // Sending to the client the "order" of displaying game's view
    // net_server_send_screen_choice(binome->clients_id[0]);
    // net_server_send_screen_choice(binome->clients_id[1]);
}


void _initialize_game_list(GameList *gList){
    gList->size = MAX_CLIENTS/2;
    gList->gameList = malloc(sizeof(Game)*gList->size);

    for(int i=0;i<gList->size;i++){
        _initialize_game_type(&(gList->gameList[i]));
    }

}

void _initialize_game_type(Game *game){
    game->b = malloc(sizeof(Binome));
    game->list_of_answers = malloc(sizeof(AnswerList));
    game->currentRound = 0;
    game->nbMaxRounds = config_nb_rounds;
    initialize_answer_list(game->list_of_answers);
}



/** 
 * --------------------------------------------------------------------------------------
 *                                     GAME MANAGEMENT
 * --------------------------------------------------------------------------------------
 * This section concerns everything which will interact with the game's course of events.  
 * We might quote : round management, starting and ending of the game, choices beget....
 * 
*/


// @TODO FACTORIZE betray and collaborate methods (if possible with network coupling)

void betray(int id, ulong answerTime){
    // Retrieves a pointer of the Binome containing client's id (param given)
    Binome *usedBinome = _get_client_binome(id);
    
    // Retrieving the player "calling" this function on the Binome 
    int playerIdIndex = -1;
    for (int i = 0; i < 2; i++)
    {
        if (usedBinome->clients_id[i] == id)
        {
            playerIdIndex = i;
        }
    }
    // Here we test if each player of the Binome has registered his answer ; in which case we 
    if (_are_answers_written(usedBinome))
    {
        switch (playerIdIndex)
        {
        case 0:
            usedBinome->clients_answers->p1 = BETRAY;
            break;
        case 1:
            usedBinome->clients_answers->p2 = BETRAY;
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
            usedBinome->clients_answers->p1 = COLLAB;
            break;
        case 1:
            usedBinome->clients_answers->p2 = COLLAB;
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
    b->clients_answers->p1 = NONE;
    b->clients_answers->p2 = NONE;
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

/** 
 * --------------------------------------------------------------------------------------
 *                                     GAME DATA RECOVERY
 * --------------------------------------------------------------------------------------
 * 
 * @brief
 * 
*/
Binome *_get_client_binome(int id)
{
    Binome *usedBinome;
    for (int i = 0; i < binome_config_list->size; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (binome_config_list->list[i].clients_id[j] == id)
            {
                // asigns address of the good binome to a temporary variable
                usedBinome = &(binome_config_list->list[i]);
            }
        }
    }
    return usedBinome;
}

int _are_answers_written(Binome *b)
{
    int answersWritten = 0;
    if (b->clients_answers->p1 != NONE && b->clients_answers->p2 != NONE)
    {
        answersWritten = 1;
    }
    return answersWritten;
}

Game *_get_game_binome(Binome *b)
{
    // Retrieving the affected game from gameIndex contained into "Binome" param  
    Game *usedGame;
    usedGame = &(game_config_list->gameList[b->gameIndex]);
    return usedGame;
}

void end_game(Binome *b){
    Game *g = _get_game_binome(b);
    for(int i=0; i<g->list_of_answers->size;i++){
        // store_results(AnswerList *list)
    }

}

/** 
 * --------------------------------------------------------------------------------------
 *                                          BINOMES
 * --------------------------------------------------------------------------------------
 * 
 * @brief
 * 
*/
void initialize_binome(Binome *binome){
    binome->clients_answers = malloc(sizeof(Answer));
    binome->clients_answers->p1 = NONE;
    binome->clients_answers->p2 = NONE;
    binome->gameIndex = 0;
    binome->clients_id[0] = -1;
    binome->clients_id[1] = -1;
}


void initialize_binome_list(BinomeList *bL){
    bL->list = malloc(sizeof(Binome)*(MAX_CLIENTS/2));
    bL->size = 0;

    for(int i=0; i<(MAX_CLIENTS/2); i++){
        initialize_binome(&(bL->list[i]));
        bL->size++;
    }
}
 
void _init_binomes_from_config(BinomeList *binomes){
    initialize_binome_list(binomes);

    int listIndex = 0;

    for(int i=0;i<(MAX_CLIENTS/2);i+=2){
        binomes->list[listIndex].clients_id[0] = config_games.pairs[i]; 
        binomes->list[listIndex].clients_id[1] = config_games.pairs[i+1];
        listIndex++;
    }
}

int _is_binome_connected(Binome *binome){
    int isConnected = 0;
    if(binome->clients_id[0] != (-1) && binome->clients_id[1] != (-1)){
        isConnected = 1; 
    }

    return isConnected;
}

/** @todo!!! Mettre en place la création des binomes à partir de la liste du fichier de paramétrage */


/** 
 * --------------------------------------------------------------------------------------
 *                                    ANSWERS OF CLIENTS
 * --------------------------------------------------------------------------------------
 * 
 * @brief
 * 
*/
void _initialize_answer(Answer *answer) {
    answer->p1 = NONE;
    answer->p2 = NONE;
}  


void initialize_answer_list(AnswerList *list) {
    list->size = MAX_CLIENTS/2;

    list->answers = malloc(sizeof(Answer)*list->size);

    for(int i=0;i<list->size;i++){
        _initialize_answer(&list->answers[i]);
    }
}

void add_to_answer(Binome *b, int client_id, e_answer answer){
    // TODO 
}

void add_to_answer_list(AnswerList *list, Binome *binome) {
    // TODO 
}

