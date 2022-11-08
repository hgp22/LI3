#include "rides.h"
#include "ride.h"
#include "utils.h"
#include <glib.h>

#define RESERVED_SIZE 1048576 // (2^20)

static gint _ride_comparator(gconstpointer a, gconstpointer b);
static guint g_array_binary_search_safe(GArray *array, gconstpointer target,
                                        GCompareFunc compare_func);

Rides rides_new(void)
{
    Rides r = g_array_sized_new(FALSE, FALSE, sizeof(Ride), RESERVED_SIZE);
    g_array_set_clear_func(r, (GDestroyNotify)ride_free);
    return r;
}

void rides_free(Rides rides)
{
    g_array_free(rides, TRUE);
}

void rides_add_ride(Rides rides, Ride ride)
{
    g_array_append_val(rides, ride);
}

Ride rides_get_ride(Rides rides, guint index)
{
    return g_array_index(rides, Ride, index);
}

void rides_sort(Rides rides)
{
    g_array_sort(rides, (GCompareFunc)_ride_comparator);
}

double rides_get_avg_stat_in_range(Rides rides, char *dateA, char *dateB,
                                   double (*get_func)(Ride))
{
    Ride r_date = ride_new();
    ride_set_date(r_date, dateA);
    guint i = g_array_binary_search_safe(rides, &r_date, _ride_comparator);
    free(r_date);

    unsigned short target = date_to_days(dateB);
    double sum_distance = 0;
    int n_rides = 0;

    for (Ride r = g_array_index(rides, Ride, i);
         i < rides->len && ride_get_date(r) <= target;
         r = g_array_index(rides, Ride, ++i)) {
        sum_distance += (double)get_func(r);
        n_rides++;
    }

    return sum_distance / n_rides;
}

static gint _ride_comparator(gconstpointer a, gconstpointer b)
{
    const Ride r1 = *((Ride *)a);
    const Ride r2 = *((Ride *)b);
    return ride_get_date(r1) - ride_get_date(r2);
}

typedef struct _GRealArray GRealArray;

struct _GRealArray {
    guint8 *data;
    guint len;
    guint elt_capacity;
    guint elt_size;
    guint zero_terminated : 1;
    guint clear : 1;
    gatomicrefcount ref_count;
    GDestroyNotify clear_func;
};

static guint g_array_binary_search_safe(GArray *array, gconstpointer target,
                                        GCompareFunc compare_func)
{
    GRealArray *_array = (GRealArray *)array;
    guint left, middle = 0, right;
    gint val;

    g_return_val_if_fail(_array != NULL, FALSE);
    g_return_val_if_fail(compare_func != NULL, FALSE);

    if (G_LIKELY(_array->len)) {
        left = 0;
        right = _array->len - 1;

        while (left <= right) {
            middle = left + (right - left) / 2;

            val = compare_func(_array->data + (_array->elt_size * middle),
                               target);
            if (val == 0)
                break;
            else if (val < 0)
                left = middle + 1;
            else if (middle > 0)
                right = middle - 1;
            else
                break; /* element not found */
        }
    }

    while (middle > 0 &&
           compare_func(target, _array->data +
                                    (_array->elt_size * (middle - 1))) <= 0) {
        middle--;
    }

    while (middle < array->len &&
           compare_func(target, _array->data + (_array->elt_size * middle)) >
               0) {
        middle++;
    }

    return middle;
}
