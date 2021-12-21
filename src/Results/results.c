#include "results.h"

void store_results(char* file_name, GameList al)
{
    FILE *fi = fopen(file_name, "w");
    
    fprintf(fi, "Rapport généré le ");
    char datetime[50];
    strftime(&datetime, sizeof(datetime), "%c", localtime(time(NULL)));
    fprintf(fi, "%s\n", datetime);
}