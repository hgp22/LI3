#include "test.h"
#include "controller/batch.h"
#include "driver.h"
#include "taxi_system.h"
#include "user.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER 128

static int _run_queries(const TaxiSystem ts, const char *queries_path,
                        const char *corrects_path);
static bool _compare_files(FILE *fp1, FILE *fp2);

int main(int argc, char **argv)
{
    if (argc == 4) {
        run_tests(argv[1], argv[2], argv[3]);
    }
    else {
        puts("Wrong number of arguments");
    }

    return 0;
}

int run_tests(const char *inputs_path, const char *queries_path,
              const char *corrects_path)
{
    double cpu_time_used;
    clock_t start, end;
    start = clock();
    TaxiSystem ts = taxi_new(inputs_path);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Parsing executed in: %f sec\n\n", cpu_time_used);

    if (ts == NULL) {
        printf("Invalid inputs path: %s\n", inputs_path);
        exit(1);
    }

    struct stat st = {0};

    if (stat("Resultados", &st) == -1) {
        mkdir("Resultados", 0700);
    }

    int r = _run_queries(ts, queries_path, corrects_path);
    puts("");

    start = clock();
    taxi_free(ts);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Memory freed in: %f sec\n", cpu_time_used);

    return r;
}

static int _run_queries(const TaxiSystem ts, const char *queries_path,
                        const char *corrects_path)
{
    char *query = NULL;
    size_t len = 0;
    char file[BUFFER];
    char correct[BUFFER];
    int n_query = 1;
    clock_t start, end;
    double cpu_time_used;
    double total_queries_time = 0;

    FILE *fp_queries = fopen(queries_path, "r");

    while (getline(&query, &len, fp_queries) != -1) {
        sprintf(file, "./Resultados/command%d_output.txt", n_query);
        sprintf(correct, "%s/command%d_output.txt", corrects_path, n_query++);
        FILE *fp_output = fopen(file, "w+");
        FILE *fp_correct = fopen(correct, "r");
        start = clock();
        run_query(ts, query, fp_output);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        total_queries_time += cpu_time_used;
        query[strcspn(query, "\n")] = '\0';
        rewind(fp_output);
        printf("Query %-*s executed in: %f sec. Correction test %s\n", 34,
               query, cpu_time_used,
               _compare_files(fp_output, fp_correct) ? "passed" : "failed");
        fclose(fp_output);
        fclose(fp_correct);
    }

    printf("\nTotal queries time: %f sec\n", total_queries_time);

    free(query);

    return n_query;
}

static bool _compare_files(FILE *fp1, FILE *fp2)
{
    char ch1 = getc(fp1);
    char ch2 = getc(fp2);

    while (ch1 != EOF && ch2 != EOF) {
        ch1 = getc(fp1);
        ch2 = getc(fp2);
        if (ch1 != ch2) {
            return false;
        }
    }

    return true;
}
