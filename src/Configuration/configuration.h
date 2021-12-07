#include <stdlib.h>
#include <stdio.h>

#ifndef configuration_h
#define configuration_h

extern char* config_serv_ip;
extern int config_serv_port;
extern int config_nb_rounds;

void init_configuration();

#endif