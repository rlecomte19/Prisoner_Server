#include "test.h"

Answer *answerToTest;
Binome *binomeToTest;
Game *gameToTest;

AnswerList *aListToTest;
BinomeList *bListToTest;
GameList *gListToTest;

BinomeList *bListFromConfig;


void test_initializations(){
    answerToTest = malloc(sizeof(Answer));
    binomeToTest = malloc(sizeof(Binome));
    gameToTest = malloc(sizeof(Game));
    
    aListToTest = malloc(sizeof(Answer) * 10);
    bListToTest = malloc(sizeof(Binome) * 10);
    gListToTest = malloc(sizeof(Game) * 10);

    // Server Configuration
    init_configuration();
 
    // Answers initializations
    _initialize_answer(answerToTest);
    assert(answerToTest->p1 == NONE);
    assert(answerToTest->p2 == NONE);
    initialize_answer_list(aListToTest);
    assert(aListToTest->size == 10);
    assert(aListToTest->answers[5].p1 == NONE);
    assert(aListToTest->answers[5].p2 == NONE);

    //Binome initializations
    initialize_binome(binomeToTest);
    assert(binomeToTest->gameIndex == 0);
    assert(binomeToTest->clients_answers->p1 == NONE);
    assert(binomeToTest->clients_answers->p2 == NONE);
    assert(binomeToTest->clients_id[0] == -1);
    assert(binomeToTest->clients_id[1] == -1);
    assert(binomeToTest->isP1Connected == 0);
    assert(binomeToTest->isP2Connected == 0);
    initialize_binome_list(bListToTest);
    assert(bListToTest->size == 10);
    assert(bListToTest->list[5].gameIndex == 0);
    assert(bListToTest->list[5].clients_answers->p1 == NONE);
    assert(bListToTest->list[5].clients_answers->p2 == NONE);
    assert(bListToTest->list[5].clients_id[0] == -1);
    assert(bListToTest->list[5].clients_id[1] == -1);
    assert(bListToTest->list[5].isP1Connected == 0);
    assert(bListToTest->list[5].isP2Connected== 0);

    bListFromConfig = malloc(sizeof(BinomeList)*MAX_CLIENTS/2);

    _init_binomes_from_config(bListFromConfig);
    assert(bListFromConfig->list[0].clients_id[0] == 1);
    assert(bListFromConfig->list[0].clients_id[1] == 2);
    assert(bListFromConfig->list[1].clients_id[0] == 3);
    assert(bListFromConfig->list[1].clients_id[1] == 4);
    assert(bListFromConfig->list[0].gameIndex == 0);
    assert(bListFromConfig->list[1].gameIndex == 1);
    
    // Game Initializations
    _initialize_game_type(gameToTest);
    assert(gameToTest->isP1Ready == 1);
    assert(gameToTest->isP2Ready == 1);
    assert(gameToTest->isRunning == 0);
    assert(gameToTest->currentRound == 0);
    assert(gameToTest->nbMaxRounds == config_nb_rounds);
    assert(gameToTest->list_of_answers->answers[1].p1 == NONE);
    assert(gameToTest->list_of_answers->answers[1].p2 == NONE);
    _initialize_game_list(gListToTest);
    assert(gListToTest->size == 10);
    assert(gListToTest->gameList[1].isP1Ready == 1);
    assert(gListToTest->gameList[1].isP2Ready == 1);
    assert(gListToTest->gameList[1].isRunning == 0);
    assert(gListToTest->gameList[1].currentRound == 0);
    assert(gListToTest->gameList[1].nbMaxRounds == config_nb_rounds);
    assert(gListToTest->gameList[1].list_of_answers->answers[1].p1 == NONE);
    assert(gListToTest->gameList[1].list_of_answers->answers[1].p2 == NONE);

    for(int i=0;i<gListToTest->size;i++){
        gListToTest->gameList[i].b = &bListFromConfig->list[i];
    }
    assert(gListToTest->gameList[1].b->gameIndex == 1);
    // Server correctly thanks to everything up

    printf("\n===== SERVER IS UP TO BE SETUP =====");
    printf("\n                ||             ");
    printf("\n===== EVERY INIT IS A SUCCESS =====\n\n");
}

void test_game_management(){
    // Assumes that game initializations have been well done
    init_server();

    assert(_get_client_binome(3) == 1);
    assert(_get_player_index(1, 3) == 0);
    // Using betray() and collaborate() on the same client to avoid end_round() to be called here
    Binome *binome_management_test = game_config_list->gameList[1].b;
    betray(3, 0);
    int answerP1 = binome_management_test->clients_answers->p1;
    int answerP2 = binome_management_test->clients_answers->p2;
    assert(answerP1 == BETRAY);
    assert(answerP2 == NONE);
    collaborate(3, 0);
    int answerP1Second = binome_management_test->clients_answers->p1;
    int answerP2Second = binome_management_test->clients_answers->p2;
    assert(answerP1Second == COLLAB);
    assert(answerP2Second == NONE);
    reinitializeAnswer(binome_management_test);
    int answerP1Third = binome_management_test->clients_answers->p1;
    int answerP2Third = binome_management_test->clients_answers->p2;
    assert(answerP1Third == NONE);
    assert(answerP2Third == NONE);
    binome_management_test->clients_answers->p1 = BETRAY;
    binome_management_test->clients_answers->p2 = COLLAB;
    _are_answers_written(game_config_list->gameList[1].b);
    binome_management_test->isP1Connected = 1;
    binome_management_test->isP2Connected = 1;
    assert(_is_binome_connected(binome_management_test) == 1);

    
    printf("\n===== GAME MANAGEMENT WORKING WELL SO FAR... =====\n\n");


// void start_game(int gameIndex, Binome binome);
// void end_round(int gameIndex);
// void end_game(int gameIndex);
// void add_to_answer_list(Game *game);
}


void test_connections(){
    void client_connection(int id);
    void client_disconnect(int id);
}