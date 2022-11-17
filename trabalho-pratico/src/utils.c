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

    y -= m <= 2;
    const int era = (y >= 0 ? y : y - 399) / 400;
    const unsigned yoe = (unsigned)(y - era * 400); // [0, 399]
    const unsigned doy =
        (153 * (m > 2 ? m - 3 : m + 9) + 2) / 5 + d - 1;        // [0, 365]
    const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy; // [0, 146096]

    return era * 146097 + (int)(doe)-719468;
}

char *days_to_date(unsigned short days)
{
    char *date_str = malloc(DATE_STR * sizeof(date_str));

    const int z = days + 719468;
    const int era = (z >= 0 ? z : z - 146096) / 146097;
    const unsigned doe = (unsigned)(z - era * 146097); // [0, 146096]
    const unsigned yoe =
        (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;    // [0, 399]
    const unsigned doy = doe - (365 * yoe + yoe / 4 - yoe / 100); // [0, 365]
    const unsigned mp = (5 * doy + 2) / 153;                      // [0, 11]
    const unsigned d = doy - (153 * mp + 2) / 5 + 1;              // [1, 31]
    const unsigned m = mp < 10 ? mp + 3 : mp - 9;                 // [1, 12]
    const int y = (int)(yoe) + era * 400 + (m <= 2);

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
