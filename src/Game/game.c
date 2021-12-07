#include "game.h"

BinomeList *binomes;
GameList *gameList;

void game_init(GameList *list, Game *game, Binome *binome)
{
    game = malloc(sizeof(Game));
    binome->gameIndex = list->index;

    // Registering the created game to server's list
    add_to_game_list(list, game);

    // Sending to the client the "order" of displaying game's view
    net_server_send_screen_choice(binome->clients_id[0]);
    net_server_send_screen_choice(binome->clients_id[1]);
}
void betray(int id, unsigned long answerTime)
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

void end_round(Binome *b)
{
    reinitializeAnswer(b);
    // AFFICHER RESULTATS ROUNDS : net_server_send_end_round ?
    // tester si le nombre max de rounds n'a pas été atteint
    // renvoyer fin de partie si c'est le cas
}

Game *_get_game_binome(Binome *b)
{
    //todo
}

void reinitializeAnswer(Binome *b)
{
    b->clients_answers->p1_answer = -1;
    b->clients_answers->p2_answer = -1;
}

void add_to_game_list(GameList *list, Game *game)
{
    //todo
}