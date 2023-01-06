#include "date.h"
#include <glib.h>
#include <stdio.h>
#include <string.h>

#define D 9
#define M 10
#define Y 2022
#define DATE_STR_SIZE 11

guint16 date_to_days(const char *date)
{
    guint8 d = (date[0] - '0') * 10 + (date[1] - '0');
    guint8 m = (date[3] - '0') * 10 + (date[4] - '0');
    guint16 y = (date[6] - '0') * 1000 + (date[7] - '0') * 100 +
                (date[8] - '0') * 10 + (date[9] - '0');

    y -= m <= 2;
    const int era = y / 400;
    const unsigned yoe = y - era * 400; // [0, 399]
    const unsigned doy =
        (153 * (m > 2 ? m - 3 : m + 9) + 2) / 5 + d - 1;        // [0, 365]
    const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy; // [0, 146096]

    return era * 146097 + doe - 719468;
}

char *days_to_date(guint16 days)
{
    const int z = days + 719468;
    const int era = (z >= 0 ? z : z - 146096) / 146097;
    const unsigned doe = (unsigned)(z - era * 146097); // [0, 146096]
    const unsigned yoe =
        (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;    // [0, 399]
    const unsigned doy = doe - (365 * yoe + yoe / 4 - yoe / 100); // [0, 365]
    const unsigned mp = (5 * doy + 2) / 153;                      // [0, 11]
    const unsigned char d = doy - (153 * mp + 2) / 5 + 1;         // [1, 31]
    const unsigned char m = mp < 10 ? mp + 3 : mp - 9;            // [1, 12]
    const unsigned short y = (int)(yoe) + era * 400 + (m <= 2);

    char *date_str = malloc(DATE_STR_SIZE);
    sprintf(date_str, "%02hhu/%02hhu/%hu", d, m, y);

    return date_str;
}

guint8 date_to_age(const char *date)
{
    guint8 d = (date[0] - '0') * 10 + (date[1] - '0');
    guint8 m = (date[3] - '0') * 10 + (date[4] - '0');
    guint8 y = (date[6] - '0') * 1000 + (date[7] - '0') * 100 +
               (date[8] - '0') * 10 + (date[9] - '0');

    guint8 age = Y - y;

    if (M < m || (M == m && D < d)) {
        age--;
    }

    return age;
}
