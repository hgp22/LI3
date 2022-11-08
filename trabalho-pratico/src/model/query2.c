#include "query2.h"
#include "driver.h"
#include "drivers.h"
#include <glib.h>

static gint _driver_comparator(gconstpointer driver1, gconstpointer driver2);

Query2 query2_new(Drivers drivers)
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

Query2 query2_new_sized(int N)
{
    return g_ptr_array_new_full(N, driver_free);
}

void query2_free(Query2 q2)
{
    g_ptr_array_free(q2, TRUE);
}

void query2_add_driver(Query2 q2, Driver d)
{
    g_ptr_array_add(q2, d);
}

Driver query2_index(Query2 q2, int index)
{
    return g_ptr_array_index(q2, index);
}

void query2_sort(Query2 q2)
{
    g_ptr_array_sort(q2, (GCompareFunc)_driver_comparator);
}

static gint _driver_comparator(gconstpointer a, gconstpointer b)
{
    Driver d1 = *((Driver *)a);
    Driver d2 = *((Driver *)b);

    float score1 = driver_get_avg_score(d1);
    float score2 = driver_get_avg_score(d2);

    if (score1 < score2)
        return 1;
    else if (score1 > score2)
        return -1;
    else {
        unsigned short ride_date1 = driver_get_last_ride_date(d1);
        unsigned short ride_date2 = driver_get_last_ride_date(d2);

        if (ride_date1 < ride_date2)
            return 1;
        else if (ride_date1 > ride_date2)
            return -1;
        else {
            long id1 = driver_get_id(d1);
            long id2 = driver_get_id(d2);

            if (id1 < id2)
                return 1;
            else if (id1 > id2)
                return -1;
            else
                return 0;
        }
    }
}
