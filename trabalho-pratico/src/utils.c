#include "utils.h"
#include <glib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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
    unsigned short days = (y - 1970) * 365 + months[m - 1] + d + leaps;

    return days;
}

uint8_t date_to_age(char *date)
{
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    local->tm_mon++;

    short d, m, y;
    sscanf(date, "%hd/%hd/%hd", &d, &m, &y);

    uint8_t age = local->tm_year - (y - 1900);

    if (local->tm_mon < m || (local->tm_mon == m && local->tm_mday < d)) {
        age--;
    }

    return age;
}

char *ftoa_no_trailing_z(float f)
{
    char *s = malloc(16 * sizeof(char *));
    sprintf(s, "%.3f", ((int)(f * 1000.0)) / 1000.0);
    size_t len = strlen(s);
    for (int i = len - 1; s[i] == '0' || s[i] == '.'; i--) {
        s[i] = '\0';
    }
    return s;
}
