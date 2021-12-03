#include "game.h"
#include "../Communication/net_prisoner_server.h"

BinomeList *binomes;

void game(){
    binomes = malloc(sizeof(Binome));
    
}
void betray(int id, ulong answerTime) {
    
    Binome *usedBinome = get_client_binome(id);
    int playerIdIndex = -1;
    for(int i=0; i<2;i++){
        if(usedBinome->clients_id[i] == id){
            playerIdIndex = i;
        }
    }
	if(areAnswersWritten(usedBinome)){
        usedBinome->answer[playerIdIndex] = 0;
        end_round(usedBinome);
	}
	else{
		net_server_send_screen_waiting(id);
	}

}

void collaborate(int id, ulong answerTime) {
    Binome *usedBinome = get_client_binome(id);
    int playerIdIndex = -1;
    for(int i=0; i<2;i++){
        if(usedBinome->clients_id[i] == id){
            playerIdIndex = i;
        }
    }
	if(areAnswersWritten(usedBinome)){
        usedBinome->answer[playerIdIndex] = 1;
        end_round(usedBinome);
	}
	else{ 
		net_server_send_screen_waiting(id);
	}
}

Binome* get_client_binome(int id){
    Binome *usedBinome = malloc(sizeof(Binome));
    for(int i=0;i<binomes->size;i++){
        for(int j=0;j<2;j++){
            if(binomes->list[i].clients_id[j] == id){
                // asigns address of right binome to a temporary variable
                usedBinome = &(binomes->list[i]); 
            }
        }
    }
    return usedBinome;
}

int are_answers_written(Binome *b){
    int answersWritten = 0;
    if(b->answer[0] != -1 && b->answer[1] != -1){
        answersWritten = 1;
    }
    return answersWritten;
}

void end_round(Binome *b){
    reinitializeAnswer(b);
    // AFFICHER RESULTATS ROUNDS : net_server_send_end_round ?
    // tester si le nombre max de rounds n'a pas été atteint
    // renvoyer fin de partie si c'est le cas
}

void reinitializeAnswer(Binome *b){
    b->answer[0] = -1;
    b->answer[0] = -1;
}