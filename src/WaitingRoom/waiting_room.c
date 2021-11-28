#include "./waiting_room.h"

void initialize_waiting_room(WaitingRoom *room){
    room->max_clients = MAX_CLIENTS;
    room->id_clients = malloc(sizeof(int) * MAX_CLIENTS);
    room->size = 0;
}

void add_to_waiting_room(WaitingRoom *room, int client_id){
/**
 * @todo Si la room n'est pas full
 * net_server_send_screen_choice(client_id)
*/

    if(room->max_clients != room->size){
        room->id_clients[room->size] = client_id;
        room->size++;
    }else{
        printf("Waiting room is full, binomes will soon be created...");
    }
}
void close_waiting_room(WaitingRoom *room){
    for(int i=0;i<MAX_CLIENTS;i++){
        *(room->id_clients + i) = 0;
    }
    room->size = 0;
}

void print_waiting_room(WaitingRoom *room){
    for(int i=0;i<room->size;i++){
        printf("\nElement %d - [%d]\n",i, room->id_clients[i]);
    }
}

int isRoomFull(WaitingRoom *room){
    int isFull = 0;
    if(room->size == room->max_clients){
        isFull = 1;
    }
    return isFull;
}




