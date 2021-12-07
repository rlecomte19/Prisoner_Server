#include "configuration.h"

char *config_serv_ip;
int config_serv_port;
int config_nb_rounds;

void init_configuration()
{
    FILE *fi = fopen("config.ini", "r");

    // fi will be null if the file doesn't exist
    if (fi == NULL)
    {
        printf("configuration: file not found, creating");
        fi = fopen("config.ini", "w");
        fputs("# server config file\n", fi);
        fputs("# any line starting with a # or are blank will be ignored\n", fi);
        fputs("# the space before and after ':' are mandatory for a correct file reading\n", fi);
        fputs("# if a settings isn't found, default value will be used\n", fi);
        fputs("\n", fi);
        fputs("# define the ip the server should listen to\n", fi);
        fputs("# default: 0.0.0.0 (listen everywhere)\n", fi);
        fputs("server_ip = 0.0.0.0\n", fi);
        config_serv_ip = "0.0.0.0";
        fputs("\n", fi);
        fputs("# define the server port\n", fi);
        fputs("# default: 7799\n", fi);
        fputs("server_port = 7799\n", fi);
        config_serv_port = 7799;
        fputs("\n", fi);
        fputs("# Number of round game\n", fi);
        fputs("# default: 3\n", fi);
        fputs("round_number = 3\n", fi);
        config_nb_rounds = 3;
        fclose(fi);
    }
    else
    {
        
    }
}

// void init()
// {
//     char *ip = NULL;
//     int port = -1;
//     // @todo : parcourir le fichier de paramétrage pour rechercher : IP / PORT&
//     if (ip != NULL && port != -1)
//     {
//         net_server_init(ip, port);
//     }
// }

// void disconnect_client(int id)
// {
//     // for(int i=0;i<size;i++){
//     //     if(connected_clients[i] == id){
//     //         connected_clients[i] = -1;
//     //     }
//     // }
// }
