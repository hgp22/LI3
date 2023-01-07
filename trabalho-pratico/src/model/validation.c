#include "validation.h"
#include <glib.h>
#include <regex.h>
#include <stdbool.h>
#include <stdlib.h>

#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

static regex_t r_date;
static regex_t r_car_class;
static regex_t r_account_status;
static regex_t r_natural;
static regex_t r_fractional;

void compile_regex(void)
{
    if (regcomp(&r_date, "[0-9]{2}/[0-9]{2}/[0-9]{4}", REG_EXTENDED))
        exit(EXIT_FAILURE);
    if (regcomp(&r_car_class, "basic|green|premium", REG_EXTENDED | REG_ICASE))
        exit(EXIT_FAILURE);
    if (regcomp(&r_account_status, "active|inactive", REG_EXTENDED | REG_ICASE))
        exit(EXIT_FAILURE);
    if (regcomp(&r_natural, "[0-9]+", REG_EXTENDED))
        exit(EXIT_FAILURE);
    if (regcomp(&r_fractional, "[0-9]+\\.[0-9]+", REG_EXTENDED))
        exit(EXIT_FAILURE);
}

void free_regex(void)
{
    regfree(&r_date);
    regfree(&r_car_class);
    regfree(&r_account_status);
    regfree(&r_natural);
    regfree(&r_fractional);
}

bool validate_date(const char *date)
{
    regmatch_t pmatch[1];

    if (!regexec(&r_date, date, 1, pmatch, 0)) {
        gint8 d = (date[0] - '0') * 10 + (date[1] - '0');
        gint8 m = (date[3] - '0') * 10 + (date[4] - '0');
        return d > 0 && d <= 31 && m > 0 && m <= 12;
    }

    return false;
}

bool validate_car_class(const char *car_class)
{
    regmatch_t pmatch[1];

    return !regexec(&r_car_class, car_class, 1, pmatch, 0);
}
