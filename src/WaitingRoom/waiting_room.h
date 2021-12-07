#include <stdlib.h>
#include <stdio.h>

#ifndef waiting_room_h
#define waiting_room_h

#define MAX_CLIENTS 4

typedef struct{
    int max_clients;
    int *id_clients;
    int size;
} WaitingRoom;


/**zz
 * @brief Allocates memory for clients array, initialize the values of other values to 0.  
 * 
 * @param room 
 */
void initialize_waiting_room(WaitingRoom *room);

/**
 * @brief Add a client ID to the waiting room, only if it isn't full.
 * 
 * @param room 
 * @param client_id 
 */
void add_to_waiting_room(WaitingRoom *room, int client_id);

/**
 * @brief Withdraws every client from waiting room. Also reinitializes its size to 0. 
 * 
 * @param room 
 */
void close_waiting_room(WaitingRoom *room);



/**
 * @brief Returns 0 if room is not full, 1 if it is.
 * 
 * @param room 
 * @return int 
 */
int is_waiting_room_full(WaitingRoom *room);

/**
 * @brief This function is mostly used for debug. It only displays the elements contained in waiting room's array.
 * 
 * @param room 
 */
void print_waiting_room(WaitingRoom *room);

#endif