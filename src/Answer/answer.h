
typedef struct {
    char *p1_answer;
    char *p2_answer;
} Answer;

typedef struct {
    /**
     * Evolution : faire un tableau static ayant pour taille le nombre de rounds
     * @todo ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    */
    Answer answers[10];
    size;
} AnswerList;

void initialize_answer(Answer *answer);
void initialize_answer_list(AnswerList *list);
void add_to_answer_list(AnswerList *list, Answer *answer);