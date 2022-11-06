#include "query2.h"
#include "driver.h"
#include "drivers.h"
#include <glib.h>

static gint _driver_comparator(gconstpointer driver1, gconstpointer driver2);

Query2 new_query2(Drivers drivers)
{
    Query2 q2 = g_ptr_array_sized_new(g_hash_table_size(drivers));
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, drivers);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        g_ptr_array_add(q2, value);
    }
    return q2;
}

void free_query2(Query2 q2)
{
    g_ptr_array_free(q2, TRUE);
}

void sort_query2(Query2 q2)
{
    g_ptr_array_sort(q2, (GCompareFunc)_driver_comparator);
}

static gint _driver_comparator(gconstpointer a, gconstpointer b)
{
    Driver d1 = *((Driver *)a);
    Driver d2 = *((Driver *)b);

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
