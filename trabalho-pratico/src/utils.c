#include "utils.h"
#include <glib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define D 9
#define M 10
#define Y 2022
#define DATE_STR 11

// ? substitute with pre-defined glib function
// doesn't seem to exist
// this is copyed from the IBM tutorial where
// they used a different function signature
// gint compare_trips(gconstpointer a, gconstpointer b)
gint compare_trips(gpointer a, gpointer b)
{
    return GPOINTER_TO_INT(b) - GPOINTER_TO_INT(a);
}

unsigned short date_to_days(char *date)
{
    short d, m, y;
    sscanf(date, "%hd/%hd/%hd", &d, &m, &y);

    int months[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    int leaps = (y - 1970 + 2) / 4; // works until 2100
    unsigned short days = (y - 1970) * 365 + months[m - 1] + d + leaps - 1;

    return days;
}

char *days_to_date(unsigned short date)
{
    char *date_str = malloc(DATE_STR * sizeof(date_str));

    int y = 1970 + date / 365;
    int m = (date % 365) / 12;
    int d = (date % 365) % 12;

    sprintf(date_str, "%02d/%02d/%d", d, m, y);

    return date_str;
}

uint8_t date_to_age(char *date)
{
    short d, m, y;
    sscanf(date, "%hd/%hd/%hd", &d, &m, &y);

    uint8_t age = Y - y;

    if (M < m || (M == m && D < d)) {
        age--;
    }

    return age;
}
