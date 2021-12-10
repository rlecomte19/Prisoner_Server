#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifndef configuration_h
#define configuration_h

#define MAX_CLIENTS

/**
 * @brief Ip address of the server
 */
extern char config_serv_ip[20];

/**
 * @brief The network port the server should listen to
 */
extern int config_serv_port;

/**
 * @brief define the number of round to play
 */
extern int config_nb_rounds;

typedef struct
{
    /**
     * @brief Define the client id pair
     * basically,
     * config_games[0] and config_games[1] are together
     * config_games[2] and config_games[3] are together
     * etc
     * default to -1
     */
    int pairs[20]; //TODO: changer en define

    /**
     * @brief number of element inside pairs
     */
    int size;
} struct_config_games;

void init_configuration();
bool _start_by(char *str1, char *str2);

#endif