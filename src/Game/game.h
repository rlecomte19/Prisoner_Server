
#include "../Communication/net_prisoner_server.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef game_h
#define game_h

// ANSWER STRUCTS
typedef struct {
    char *p1_answer;
    char *p2_answer;
} Answer;

typedef struct {
    /**
     * Evolution : faire un tableau static ayant pour taille le nombre de rounds
     * @todo ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    */
    Answer* answers[10];
    int size;
} AnswerList;

// BINOMES STRUCTS
typedef struct
{
    int clients_id[2];
    Answer *clients_answers;
    int gameIndex;
    int clientIndex;
} Binome;

typedef struct
{
    Binome *list;
    int size;
} BinomeList;

// GAME STRUCTS
typedef struct{
    int nbMaxRounds;
    int currentRound;
    Binome *b;
    AnswerList *list_of_answers;
} Game;

typedef struct {
    Game **gameList;
    int size;
} GameList;


// Done
void game_init(Game *game, Binome *binome);
// Done
void betray();
// Done
void collaborate();
// TODO
void end_game();
// TODO
void end_round();

// Done
void _add_new_game(Game *game);
// Done
Binome* _get_client_binome(int id);
// Done
int _are_answers_written(Binome *b);
// Done
Game* _get_game_binome(Binome *b);

// Done
void reinitializeAnswer(Binome *b);

// ---------------------------------------
//                 BINOMES
// ---------------------------------------

/**
 * @brief Initialize binome struct
 *
 * @param *binome
 */
void initialize_binome(Binome *binome);

void initialize_binome_list(BinomeList *bL);


// ----------------------------------------------
//                 ANSWERS OF PLAYERS
// ----------------------------------------------

/**
 * @brief Initialize default values of Answer struct
 * 
 * @param list 
 */
void initialize_answer(Answer *answer);
/**
 * @brief Initialize default values of AnswerList struct
 * 
 * @param list 
 */
void initialize_answer_list(AnswerList *list);
/**
 * @brief Add an answer to the list of answer (struct used to fill up game's end results)
 * 
 * @param list 
 * @param answer 
 */
void add_to_answer_list(AnswerList *list, Answer *answer);
#endif