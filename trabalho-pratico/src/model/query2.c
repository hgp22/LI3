#include "query2.h"
#include "driver.h"
#include "drivers.h"
#include <glib.h>

static gint _driver_comparator(gconstpointer driver1, gconstpointer driver2);

Query2 new_query2(Drivers drivers)
{
    return (Query2)g_hash_table_get_values(drivers);
}

void free_query2(Query2 q2)
{
    g_slist_free(q2);
}

void free_query2_full(Query2 q2)
{
    g_slist_free_full(q2, free_driver);
}

Query2 sort_query2(Query2 q2)
{
    return g_slist_sort(q2, (GCompareFunc)_driver_comparator);
}

static gint _driver_comparator(gconstpointer driver1, gconstpointer driver2)
{
    Driver d1 = (Driver)driver1;
    Driver d2 = (Driver)driver2;

    float score1 = get_driver_avg_score(d1);
    float score2 = get_driver_avg_score(d2);

    if (score1 < score2)
        return 1;
    else if (score1 > score2)
        return -1;
    else {
        unsigned short ride_date1 = get_driver_last_ride_date(d1);
        unsigned short ride_date2 = get_driver_last_ride_date(d2);

        if (ride_date1 < ride_date2)
            return 1;
        else if (ride_date1 > ride_date2)
            return -1;
        else {
            long id1 = get_driver_id(d1);
            long id2 = get_driver_id(d2);

            if (id1 < id2)
                return 1;
            else if (id1 > id2)
                return -1;
            else
                return 0;
        }
    }
}
