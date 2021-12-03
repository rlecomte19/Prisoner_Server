#include <stdlib.h>
#include <stdio.h>

#include "./create_configuration.h"
#include "../Communication/net_prisoner_server.h"

void create_configuration(){
    char serv_ip[100];
    int port = -1;
    int nb_rounds = -1;
    int sums[3];
    // Asks user for server configurations and put them into variables
    printf("-----------------------------------------------------------\n");
    printf("                       Configuration\n");
    printf("-----------------------------------------------------------\n");

    printf("IP Serveur : ");
    scanf("%s", serv_ip);
    printf("\n");

    printf("Port Serveur : ");
    scanf("%d", &port);
    printf("\n");

    printf("Nombre de tours de jeu : ");
    scanf("%d", &nb_rounds);
    printf("\n");

    for(int i=0;i<3;i++){
        printf("Somme enagagee %d : ", i);
        scanf("%d", &sums[i]);
    }
    printf("\n");

    // Creation of csv file which will contain the server configuration (using the previously initialized variables)
    FILE *file = NULL;

    file = fopen("Server_Setup/setup.csv", "w");
    
    if(file != NULL){
        fputs("IP;PORT;ROUNDS;SUMS\n", file);
        fprintf(file, "%s;%d;%d;", serv_ip, port, nb_rounds);
        for(int i=0;i<3;i++){
            fprintf(file, "%d ", sums[i]);
        }
        fclose(file);
    }

    else{
        // If set up file couldn't load, app is stopped.
        exit(5);
    }
}

void init(){
	char* ip = NULL;
	int port = -1;
	// @todo : parcourir le fichier de paramétrage pour rechercher : IP / PORT&
	if(ip!=NULL && port!=-1){
		net_server_init(ip, port);
	}
}

void disconnect_client(int id){
    // for(int i=0;i<size;i++){
    //     if(connected_clients[i] == id){
    //         connected_clients[i] = -1;
    //     }
    // }
}