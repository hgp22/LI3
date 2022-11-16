#include "rides.h"
#include "ride.h"
#include "utils.h"
#include <glib.h>

#define RESERVED_SIZE 1048576 // (2^20)

static gint _ride_comparator(gconstpointer a, gconstpointer b);
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
    g_ptr_array_sort(rides, (GCompareFunc)_ride_comparator);
}

double rides_get_avg_stat_in_range(Rides rides, char *dateA, char *dateB,
                                   double (*get_func)(Ride))
{
    Ride r_date = ride_new();
    ride_set_date(r_date, dateA);
    guint i = g_array_binary_search_safe(rides, &r_date, _ride_comparator);
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

static gint _ride_comparator(gconstpointer a, gconstpointer b)
{
    const Ride r1 = *((Ride *)a);
    const Ride r2 = *((Ride *)b);
    return ride_get_date(r1) - ride_get_date(r2);
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

    while (middle > 0 &&
           compare_func(target, array->pdata + middle - 1) <= 0) {
        middle--;
    }

    while (middle < array->len &&
           compare_func(target, array->pdata + middle) > 0) {
        middle++;
    }

    return middle;
}
