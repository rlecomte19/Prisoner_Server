#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifndef configuration_h
#define configuration_h

extern char config_serv_ip[20];
extern int config_serv_port;
extern int config_nb_rounds;

void init_configuration();
bool _start_by(char *str1, char *str2);

#endif