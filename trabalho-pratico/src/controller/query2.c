#include "query2.h"
#include "catalog.h"
#include "driver.h"

#define ID 12
#define SCORE 5

extern int counter;

void query2(Catalog c, int N)
{
    char *s = malloc(34 * sizeof(char *));
    sprintf(s, "./Resultados/command%d_output.txt", counter++);
    FILE *command_out = fopen(s, "w");
    free(s);

    // find alternative solution to avoid multiple allocs/frees
    for (Query2 itr = get_catalog_query2(c); itr && N; itr = itr->next, N--) {
        char *q2_answer = _driver_to_q2_string(itr->data);
        fprintf(command_out, "%s\n", q2_answer);
        free(q2_answer);
    }

    fclose(command_out);
}

static char *_driver_to_q2_string(Driver d)
{
    char *name = get_driver_name(d);

    char *s = malloc((ID + strlen(name) + SCORE + 1) * sizeof(char *));

    sprintf(s, "%012ld;%s;%.3f", get_driver_id(d), name,
            get_driver_avg_score(d));

    free(name);

    return s;
}
