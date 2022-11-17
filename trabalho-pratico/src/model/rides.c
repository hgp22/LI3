#include "rides.h"
#include "ride.h"
#include "utils.h"
#include <glib.h>

#define RESERVED_SIZE 1048576 // (2^20)

static gint _ride_comparator_date(gconstpointer a, gconstpointer b);
static gint _ride_comparator_distance(gconstpointer a, gconstpointer b);
static guint g_array_binary_search_safe(GPtrArray *array, gconstpointer target,
                                        GCompareFunc compare_func);

Rides rides_new(void)
{
    return g_ptr_array_new_full(RESERVED_SIZE, (GDestroyNotify)ride_free);
}

void rides_free(Rides rides)
{
    g_ptr_array_free(rides, TRUE);
}

void rides_add_ride(Rides rides, Ride ride)
{
    g_ptr_array_add(rides, ride_copy(ride));
}

void rides_replace_ride(Rides rides, Ride ride, guint index)
{
    Ride *r = (Ride *)&g_ptr_array_index(rides, index);
    ride_free(*r);
    *r = ride_copy(ride);
}

Ride rides_get_ride(Rides rides, guint index)
{
    return ride_copy(g_ptr_array_index(rides, index));
}

Ride rides_get_ride_shallow(Rides rides, guint index)
{
    return g_ptr_array_index(rides, index);
}

void rides_sort(Rides rides)
{
    g_ptr_array_sort(rides, (GCompareFunc)_ride_comparator_date);
}

double rides_get_avg_stat_in_range(Rides rides, char *dateA, char *dateB,
                                   double (*get_func)(Ride))
{
    Ride r_date = ride_new();
    ride_set_date(r_date, dateA);
    guint i = g_array_binary_search_safe(rides, &r_date, _ride_comparator_date);
    free(r_date);

    unsigned short target = date_to_days(dateB);
    double sum_stat = 0;
    int n_rides = 0;

    for (Ride r = g_ptr_array_index(rides, i);
         i < rides->len && ride_get_date(r) <= target;
         r = g_ptr_array_index(rides, ++i)) {
        sum_stat += get_func(r);
        n_rides++;
    }

    return sum_stat / n_rides;
}

Rides rides_get_rides_with_tip(Rides rides)
{
    Rides rs = g_ptr_array_sized_new(rides->len);

    for (guint i = 0; i < rides->len; i++) {
        Ride r = g_ptr_array_index(rides, i);
        if (ride_get_tip(r) != 0) {
            g_ptr_array_add(rs, r);
        }
    }

    return rs;
}

Rides rides_get_rides_with_tip_in_range(Rides rides, char *dateA, char *dateB)
{
    Ride r_date = ride_new();
    ride_set_date(r_date, dateA);
    guint i = g_array_binary_search_safe(rides, &r_date, _ride_comparator_date);

    unsigned short target = date_to_days(dateB);
    Rides rs = g_ptr_array_new_with_free_func(ride_free);

    for (Ride r = g_ptr_array_index(rides, i);
         i < rides->len && ride_get_date(r) <= target;
         r = g_ptr_array_index(rides, ++i)) {
        g_ptr_array_add(rs, ride_copy(r));
    }

    g_ptr_array_sort(rs, _ride_comparator_distance);

    return rs;
}

static gint _ride_comparator_date(gconstpointer a, gconstpointer b)
{
    const Ride r1 = *((Ride *)a);
    const Ride r2 = *((Ride *)b);
    return ride_get_date(r1) - ride_get_date(r2);
}

static gint _ride_comparator_distance(gconstpointer a, gconstpointer b)
{
    const Ride r1 = *((Ride *)a);
    const Ride r2 = *((Ride *)b);

    uint8_t distance1 = ride_get_distance(r1);
    uint8_t distance2 = ride_get_distance(r2);

    if (distance1 < distance2)
        return 1;
    else if (distance1 > distance2)
        return -1;
    else {
        unsigned short date1 = ride_get_date(r1);
        unsigned short date2 = ride_get_date(r2);

        if (date1 < date2)
            return 1;
        else if (date1 > date2)
            return -1;
        else {
            long id1 = ride_get_id(r1);
            long id2 = ride_get_id(r2);

            if (id1 < id2)
                return 1;
            else if (id1 > id2)
                return -1;
            else
                return 0;
        }
    }
}

static guint g_array_binary_search_safe(GPtrArray *array, gconstpointer target,
                                        GCompareFunc compare_func)
{
    guint left, middle = 0, right;
    gint val;

    left = 0;
    right = array->len - 1;

    while (left <= right) {
        middle = left + (right - left) / 2;

        val = compare_func(array->pdata + middle, target);
        if (val == 0)
            break;
        else if (val < 0)
            left = middle + 1;
        else if (middle > 0)
            right = middle - 1;
        else
            break; // element not found
    }

    while (middle > 0 && compare_func(target, array->pdata + middle - 1) <= 0) {
        middle--;
    }

    while (middle < array->len &&
           compare_func(target, array->pdata + middle) > 0) {
        middle++;
    }

    return middle;
}
