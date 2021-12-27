#include "./game.h"

/** 
 * --------------------------------------------------------------------------------------
 *                                   INITIALISATIONS - GAME & SERVER
 * --------------------------------------------------------------------------------------
 *
 * @brief : This part of code defines what is necessary for the game & the server to start
 * 
*/
GameList *game_config_list;
BinomeList *binome_config_list;

void init_server(){

    net_server_set_func_betray(betray);
    net_server_set_func_cooperate(collaborate);
    net_server_set_func_new_client(client_connection);
    net_server_set_func_client_disconnect(client_disconnect);

    // Initializing server
    net_server_init(config_serv_ip, config_serv_port);

    // Allocation of external structs given in game.h
    game_config_list = malloc(sizeof(GameList));
    binome_config_list = malloc(sizeof(BinomeList));

    _init_binomes_from_config(binome_config_list);
    _initialize_game_list(game_config_list);

    for(int i=0;i<game_config_list->size;i++){
        game_config_list->gameList[i].b = &binome_config_list->list[i];
    }
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
    game->isRunning = 0;
    game->isP1Ready = 1;
    game->isP2Ready = 1;
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

void betray(int id, ulong answerTime){
    // Retrieve player data
    int binomeIndex = _get_client_binome(id);
    int playerIdIndex = _get_player_index(binomeIndex, id);

    int gameIndex = binome_config_list->list[binomeIndex].gameIndex;

    switch (playerIdIndex)
    {
    case 0:
        game_config_list->gameList[gameIndex].b->clients_answers->p1 = BETRAY;
        break;
    case 1:
        game_config_list->gameList[gameIndex].b->clients_answers->p2 = BETRAY;
        break;
    }

    // If each player has answered, their answers are registered and the round can end.
    // If only the player who calls this function is answering, he is "ordered" to wait the other player's answer
    if (_are_answers_written(&(binome_config_list->list[binomeIndex])))
    {
        end_round(gameIndex);
    }
    else
    {
        net_server_send_screen_waiting(id);
    }
}

void collaborate(int id, ulong answerTime)
{
    int binomeIndex = _get_client_binome(id);
    int playerIdIndex = _get_player_index(binomeIndex, id);

    int gameIndex = binome_config_list->list[binomeIndex].gameIndex;

    switch (playerIdIndex)
    {
    case 0:
        game_config_list->gameList[gameIndex].b->clients_answers->p1 = COLLAB;
        break;
    case 1:
        game_config_list->gameList[gameIndex].b->clients_answers->p2 = COLLAB;
        break;
    }
   
    // If each player has answered, their answers are registered and the round can end.
    // If only the player who calls this function is answering, he is "ordered" to wait the other player's answer
    if (_are_answers_written(&(binome_config_list->list[binomeIndex])))
    {
        end_round(gameIndex);
    }
    else
    {
        net_server_send_screen_waiting(id);
    }
}

int _get_player_index(int binomeIndex, int client_id){
    int playerIdIndex = -1;

    for (int i = 0; i < 2; i++)
    {
        if (binome_config_list->list[binomeIndex].clients_id[i] == client_id)
        {
            playerIdIndex = i;
        }
    }
    
    return playerIdIndex;
}

void reinitializeAnswer(Binome *b)
{
    b->clients_answers->p1 = NONE;
    b->clients_answers->p2 = NONE;
}

void start_game(int gameIndex, Binome binome){
    game_config_list->gameList[gameIndex].isRunning = 1;
    game_config_list->gameList[gameIndex].currentRound = 1;

    game_config_list->gameList[gameIndex].b = &binome;

    net_server_send_screen_choice(game_config_list->gameList[gameIndex].b->clients_id[0]);
    net_server_send_screen_choice(game_config_list->gameList[gameIndex].b->clients_id[1]);
}

void end_round(int gameIndex){
    int client1 = game_config_list->gameList[gameIndex].b->clients_id[0];
    int client2 = game_config_list->gameList[gameIndex].b->clients_id[1];

    if(game_config_list->gameList[gameIndex].currentRound == 
                game_config_list->gameList[gameIndex].nbMaxRounds)
    {
        // end_game();
    }
    // Sending score screen to clients
    else
    {
        net_server_send_screen_score_round(client1, false, 0, 0, 0);
        net_server_send_screen_score_round(client2, false, 0, 0, 0);
    }

    add_to_answer_list(&(game_config_list->gameList[gameIndex]));
    reinitializeAnswer(game_config_list->gameList[gameIndex].b);
    game_config_list->gameList[gameIndex].currentRound++;
}

void end_game(int gameIndex){
    // TODO
}

/** 
 * --------------------------------------------------------------------------------------
 *                                     GAME DATA RECOVERY
 * --------------------------------------------------------------------------------------
 * 
 * @brief
 * 
*/
int _get_client_binome(int id)
{
    int binomeIndex = 0;
    
    // Loops throughout binomes extern list
    for (int i = 0; i < binome_config_list->size; i++)
    {
        // Loops 2 times to search between 2 client's id
        for (int j = 0; j < 2; j++)
        {
            if (binome_config_list->list[i].clients_id[j] == id)
            {
                // return rank of the binome in list
                binomeIndex  = i;
            }
        }
    }
    return binomeIndex;
}

int _are_answers_written(const Binome *b)
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
    binome->isP1Connected = 0;
    binome->isP2Connected = 0;
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
        binomes->list[listIndex].gameIndex = listIndex;
    }
}

void client_connection(int id){
    // Retrieve player data
    int binomeIndex = _get_client_binome(id);
    int playerIndex = _get_player_index(binomeIndex, id);
    
    switch(playerIndex){
        case 0 : 
            binome_config_list->list[binomeIndex].isP1Connected = 1;
        break;

        case 1 :
            binome_config_list->list[binomeIndex].isP2Connected = 1;
        break;
    }

    // Retrieve game for this binome
    int gameIndex = binome_config_list->list[binomeIndex].gameIndex;
    
    // Game for this binome is started if it is connected 
    if(_is_binome_connected(&(binome_config_list->list[binomeIndex]))){
        printf("\n CLIENT %d EST CONNECTE \n", id);
        start_game(gameIndex, binome_config_list->list[binomeIndex]);
    }else{
        net_server_send_screen_waiting(id);
    }
}

void client_disconnect(int id) {
    //todo ?
}

int _is_binome_connected(Binome *binome){
    int isConnected = 0;

    if(binome->isP1Connected && binome->isP2Connected){
        isConnected = 1;
    }

    return isConnected;
}



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

void add_to_answer_list(Game *game) {
    game->list_of_answers[(game->currentRound-1)].answers = game->b->clients_answers;
}

