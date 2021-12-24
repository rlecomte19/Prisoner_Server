#include "configuration.h"

char config_serv_ip[20];
int config_serv_port;
int config_nb_rounds;
struct_config_games config_games;

void init_configuration()
{
    FILE *fi = fopen("config.ini", "r");

    //config_serv_ip = "0.0.0.0";
    memcpy(&config_serv_ip, "0.0.0.0", 9);
    config_serv_port = 7799;
    config_nb_rounds = 3;
    memset(config_games.pairs, -1, sizeof(config_games.pairs));
    config_games.pairs[0] = 1;
    config_games.pairs[1] = 2;
    config_games.size = 2;

    // fi will be null if the file doesn't exist
    if (fi == NULL)
    {
        printf("configuration: file not found, creating");
        fi = fopen("config.ini", "w");
        fputs("# server config file\n", fi);
        fputs("# any line starting with a # or are blank will be ignored\n", fi);
        fputs("# the space before and after '=' are mandatory for a correct file reading\n", fi);
        fputs("# if a settings isn't found, default value will be used\n", fi);
        fputs("\n", fi);
        fputs("# define the ip the server should listen to\n", fi);
        fputs("# default: 0.0.0.0 (listen everywhere)\n", fi);
        fputs("server_ip = 0.0.0.0\n", fi);
        fputs("\n", fi);
        fputs("# define the server port\n", fi);
        fputs("# default: 7799\n", fi);
        fputs("server_port = 7799\n", fi);
        fputs("\n", fi);
        fputs("# Number of round game\n", fi);
        fputs("# default: 3\n", fi);
        fputs("round_number = 3\n", fi);
        fputs("\n", fi);
        fputs("# Define prisoner's pair\n", fi);
        fputs("# default: 1,2|3,4\n", fi);
        fputs("games = 1,2|3,4\n", fi);
        fclose(fi);
    }
    else
    {
        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        while ((read = getline(&line, &len, fi)) != -1)
        {
            if (len > 0)
            {
                //saute les lignes qui sont juste un retour à la ligne
                //ou les lignes qui commencent par un #
                if (line[0] == '\n' || line[0] == '#')
                {
                    continue;
                }

                if (_start_by(line, "server_ip"))
                {
                    sscanf(line, "%*s = %s", config_serv_ip);
                }
                else if (_start_by(line, "server_port"))
                {
                    sscanf(line, "%*s = %i", &config_serv_port);
                }
                else if (_start_by(line, "round_number"))
                {
                    sscanf(line, "%*s = %i", &config_nb_rounds);
                }
                else if (_start_by(line, "games"))
                {
                    //clearing array before hand
                    memset(config_games.pairs, -1, sizeof(config_games.pairs));
                    config_games.size = 0;

                    char text[255];
                    sscanf(line, "%*s = %s", text);

                    //heavily inspired from here: https://www.cplusplus.com/reference/cstring/strtok/
                    int i1, i2;
                    int index = 0;
                    char *ret;
                    ret = strtok(text, "|");
                    while (ret != NULL)
                    {
                        sscanf(ret, "%i,%i", &i1, &i2);
                        config_games.pairs[index] = i1;
                        index++;
                        config_games.pairs[index] = i2;
                        index++;
                        config_games.size += 2;

                        ret = strtok(NULL, "|");
                    }
                }
            }
        }
    }
    // printf("server_ip = %s\n", config_serv_ip);
    // printf("server_port = %i\n", config_serv_port);
    // printf("round_number = %i\n", config_nb_rounds);
}

/**
 * @brief Check if str1 start with str2
 * This function is case sensitive
 * Examples:
 * - str1 = "abcdefg"
 * - str2 = "abc"
 * -> return true
 * 
 * - str1 = "apple juice"
 * - str2 = "orange"
 * -> return false
 * 
 * @param str1 tested text
 * @param str2 text to test
 * @return true if str1 start is equals to str2 text
 * @return false if str1 != str2 or one of the two contains nothing
 */
bool _start_by(char *str1, char *str2)
{
    // determine who is the smallest between str1 and str2
    int min_size = strlen(str1);
    int snd_size = strlen(str2);
    if (snd_size < min_size)
    {
        min_size = snd_size;
    }

    // we substract 1 because we don't want to check the end of string character (\0)
    min_size--;

    // check if the size is valid before we continue
    if (min_size < 0)
    {
        return false;
    }

    // check if str1 start with str2
    for (int i = 0; i < min_size; i++)
    {
        if (str1[i] != str2[i])
        {
            return false;
        }
    }
    return true;
}