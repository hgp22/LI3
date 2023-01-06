#include "validation.h"
#include <regex.h>
#include <stdlib.h>

static regex_t date;
static regex_t car_class;
static regex_t account_status;
static regex_t natural;
static regex_t fractional;

void compile_regex(void)
{
    if (regcomp(&date, "(\\d{2})/(\\d{2})/\\d{4}", REG_NEWLINE))
        exit(EXIT_FAILURE);
    if (regcomp(&car_class, "(?i)(?:basic|green|premium)", REG_NEWLINE))
        exit(EXIT_FAILURE);
    if (regcomp(&account_status, "(?i)(?:active|inactive)", REG_NEWLINE))
        exit(EXIT_FAILURE);
    if (regcomp(&natural, "[1-9]\\d*", REG_NEWLINE))
        exit(EXIT_FAILURE);
    if (regcomp(&fractional, "\\d+(?:.\\d+)?", REG_NEWLINE))
        exit(EXIT_FAILURE);
}
