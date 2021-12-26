
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Communication/net_prisoner_server.h"
#include "../Configuration/configuration.h"

#ifndef game_h
#define game_h



typedef enum{
    NONE = 0,
    COLLAB = 1,
    BETRAY = 2
} e_answer;

// ANSWER STRUCTS
typedef struct {
    e_answer p1;
    e_answer p2;
} Answer;

typedef struct {
    Answer *answers;
    int size;
} AnswerList;

// BINOMES STRUCTS
typedef struct
{
    int isP1Connected;
    int isP2Connected; 
    int clients_id[2];
    Answer *clients_answers;
    int gameIndex;
} Binome;

typedef struct
{
    Binome *list;
    int size;
} BinomeList;

extern BinomeList *binome_config_list;

// GAME STRUCTS
typedef struct{
    int nbMaxRounds;
    int currentRound;
    int isRunning;
    int isP1Ready;
    int isP2Ready;
    Binome *b;
    AnswerList *list_of_answers;
} Game;

typedef struct {
    Game *gameList;
    int size;
  
} GameList;

extern GameList *game_config_list;

// -----------------------------------------------------
//                GAME CONFIG & ENVIRONMENT
// -----------------------------------------------------


/**
 * @brief Initialize server listening, retrieved binomes & games initialized from configuration file
 * 
 */
void init_server();

/**
 * @brief Initialize list of games from configuration file
 * 
 * @param gList : memory address of a GameList struct to initialize 
 */
void _initialize_game_list(GameList *gList);

/**
 * @brief Initialize an item of type : struct Game
 * 
 * @param game : memory address of a Game struct to initialize
 */
void _initialize_game_type(Game *game);


/**
 * @brief Function called by LibPrisonerNetwork when a client answers "betray" during Game
 * 
 */
void betray();

/**
 * @brief Function called by LibPrisonerNetwork when a client answers "collaboration" during Game
 * 
 */
void collaborate();

/**
 * @brief Initialize game's properties if its binome is fully connected
 * 
 * @param gameIndex : index of the game to start in the global games list
 * @param binome  : memory address of a Binome struct
 */
void start_game(int gameIndex, Binome binome);

/**
 * @brief Cloture game by its index in the external GameList
 * 
 * @param int : index of the game to end in the global games list
 */
void end_game(int gameIndex);

/**
 * @brief Clotures current round when each client has answered
 * 
 * @param gameIndex : index of the game in global games list (integer)
 */
void end_round(int gameIndex);

/**
 * @brief Retrieve the binome of client's id given in parameters.
 * This search is done on the global binomes list created with configuration  
 * 
 * @param id : client's id (integer)
 * @return int : index of the binome containing client's id param in the global binomes list
 */
int _get_client_binome(int id);

/**
 * @brief Verifies if each player of a binome has played during the game
 * 
 * @param b : memory address of a Binome struct
 * @return int : 0 if false | 1 if true
 */
int _are_answers_written(Binome *b);

/**
 * @brief Retrieves game from binome game's index in list;
 * 
 * @param b memory address of a Binome struct
 * @return *Game : pointer to a Game struct
 */
Game* _get_game_binome(Binome *b);

/**
 * @brief Put back binome's answers to NONE 
 * 
 * @param b : memory address of a Binome struct
 */
void reinitializeAnswer(Binome *b);

// ---------------------------------------
//                 BINOMES
// ---------------------------------------

/**
 * @brief Initialize Binome struct for each of its properties
 *
 * @param binome : memory address of a Binome struct
 */
void initialize_binome(Binome *binome);

/**
 * @brief Initialize BinomeList struct for each of its properties
 * 
 * @param bL : memory address of a BinomeList struct
 */
void initialize_binome_list(BinomeList *bL);

/**
 * @brief Initialize a BinomeList and its contained binomes according to the configuration file
 * 
 * @param binomes : memory address of a BinomeList struct
 */
void _init_binomes_from_config(BinomeList *binomes);

/**
 * @brief Verifie if each player of a Binome is connected
 * It checks if isP1Connected & isP2Connected Binome's properties are true
 * @param binome : memory address of a Binome struct
 * @return int : 0 if false | 1 if true
 */
int _is_binome_connected(Binome *binome);

/**
 * @brief Function called by LibPrisonerNetwork when a client asks for a connection
 * Launches the game if each client of a Binome is connected
 * Sends waiting screen "order" to the client if he's the only one connected of its binome
 * 
 * @param id : client's id (integer)
 */
void client_connection(int id);

// ----------------------------------------------
//                 ANSWERS OF PLAYERS
// ----------------------------------------------

/**
 * @brief Initialize Answer struct for each of its properties
 * 
 * @param answer : memory address of an Answer struct
 */
void _initialize_answer(Answer *answer);

/**
 * @brief Initialize Answer struct for each of its properties
 * 
 * @param list : memory address of an AnswerList struct
 */
void initialize_answer_list(AnswerList *list);

/**
 * @brief Add an answer to the list of answer (struct used to fill up game's end results)
 * 
 * @param list : memory address of an AnswerList struct
 * @param binome : memory address of a Binome struct
 */
void add_to_answer_list(Game *game);

#endif