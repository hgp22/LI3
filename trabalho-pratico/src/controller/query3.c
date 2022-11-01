#include "query3.h"
#include "catalog.h"
#include "user.h"

#define DISTANCE 5

extern int counter;

void query3(Catalog c, int N)
{
    char *s = malloc(34 * sizeof(char *));
    sprintf(s, "./Resultados/command%d_output.txt", counter++);
    FILE *command_out = fopen(s, "w");
    free(s);

    // find alternative solution to avoid multiple allocs/frees
    for (Query3 itr = get_catalog_query3(c); itr && N; itr = itr->next, N--) {
        char *q3_answer = _user_to_q3_string(itr->data);
        fprintf(command_out, "%s\n", q3_answer);
        free(q3_answer);
    }

    fclose(command_out);
}

static char *_user_to_q3_string(User u)
{
    char *username = get_user_username(u);
    char *name = get_user_name(u);

    char *s = malloc((strlen(username) + strlen(name) + DISTANCE + 1) *
                     sizeof(char *));

    sprintf(s, "%s;%s;%d", username, name, get_user_total_distance(u));

    free(username);
    free(name);

    return s;
}
