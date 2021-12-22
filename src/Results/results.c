#include "results.h"

void _write_e_answer(FILE *fi, e_answer rep)
{
    switch (rep)
    {
    case NONE:
        fprintf(fi, "Aucune réponse");
        break;
    case COLLAB:
        fprintf(fi, "Collaboration");
        break;
    case BETRAY:
        fprintf(fi, "Trahison");
        break;
    }
}

void store_results(char *file_name, GameList al)
{
    FILE *fi = fopen(file_name, "w");

    time_t timestamp = time(NULL);
    struct tm *ptime = localtime(&timestamp);
    char datetime[50];

    // set the file to UTF-8-BOM to make sure Excel read specials characters correctly
    fprintf(fi, "\xef\xbb\xbf");

    // écriture de la date sur le rapport
    strftime(&datetime, sizeof(datetime), "%c", ptime);
    fprintf(fi, "Rapport généré le;%s\n", datetime);

    fprintf(fi, "\n");
    fprintf(fi, "--- INFORMATIONS GÉNÉRALES ---\n");
    fprintf(fi, "Nombre de parties:;%d\n", al.size);
    fprintf(fi, "\n");
    fprintf(fi, "\n");

    for (int gamid = 0; gamid < al.size; gamid++)
    {

        Game *game = &al.gameList[gamid];

        fprintf(fi, "--- GAME #%d ---\n", game->b->gameIndex);
        fprintf(fi, "Tour de jeu:;%d\n", game->currentRound);
        fprintf(fi, "Tour de jeu prévu:;%d\n", game->nbMaxRounds);
        fprintf(fi, "\n");

        fprintf(fi, "- BINOME -\n");
        int idj1, idj2;
        idj1 = game->b->clients_id[0];
        idj2 = game->b->clients_id[1];
        fprintf(fi, "Id joueur 1;%d\n", idj1);
        fprintf(fi, "Id joueur 2;%d\n", idj2);
        fprintf(fi, "\n");

        fprintf(fi, "- RESPONSES -\n");
        fprintf(fi, "Round #;Joueur 1 (id %d); Joueur 2 (id %d)\n", idj1, idj2);

        AnswerList *asl = game->list_of_answers;
        for (int ansid = 0; ansid < asl->size; ansid++)
        {
            fprintf(fi, "%d;", ansid);
            _write_e_answer(fi, asl->answers[ansid].p1);
            fprintf(fi, ";");
            _write_e_answer(fi, asl->answers[ansid].p2);
            fprintf(fi, "\n");
        }

        fprintf(fi, "\n");
    }

    fclose(fi);
}