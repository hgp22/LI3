#include "rides.h"
#include "ride.h"
#include "utils.h"
#include <glib.h>

#define RESERVED_SIZE 1048576 // (2^20)

static gint _ride_comparator(gconstpointer a, gconstpointer b);
static guint g_array_binary_search_safe(GPtrArray *array, gconstpointer target,
                                        GCompareFunc compare_func);

Rides new_rides(void)
{
    return g_ptr_array_new_full(RESERVED_SIZE, (GDestroyNotify)free_ride);
}

void free_rides(Rides rides)
{
    g_ptr_array_free(rides, TRUE);
}

void add_rides_ride(Rides rides, Ride ride)
{
    g_ptr_array_add(rides, ride);
}

Ride get_rides_ride(Rides rides, guint index)
{
    return g_ptr_array_index(rides, index);
}

void sort_rides(Rides rides)
{
    g_ptr_array_sort(rides, (GCompareFunc)_ride_comparator);
}

double get_rides_avg_stat_in_range(Rides rides, char *dateA, char *dateB,
                                   double (*get_func)(Ride))
{
    Ride r_date = new_ride();
    set_ride_date(r_date, dateA);
    guint i = g_array_binary_search_safe(rides, &r_date, _ride_comparator);
    free(r_date);

    unsigned short target = date_to_days(dateB);
    double sum_distance = 0;
    int n_rides = 0;

    for (Ride r = g_ptr_array_index(rides, i);
         i < rides->len && get_ride_date(r) <= target;
         r = g_ptr_array_index(rides, ++i)) {
        sum_distance += get_func(r);
        n_rides++;
    }

    return sum_distance / n_rides;
}

static gint _ride_comparator(gconstpointer a, gconstpointer b)
{
    const Ride r1 = *((Ride *)a);
    const Ride r2 = *((Ride *)b);
    return get_ride_date(r1) - get_ride_date(r2);
}

typedef struct _GRealPtrArray GRealPtrArray;

struct _GRealPtrArray {
    gpointer *pdata;
    guint len;
    guint alloc;
    gatomicrefcount ref_count;
    guint8 null_terminated; /* always either 0 or 1, so it can be added to array
                               lengths */
    GDestroyNotify element_free_func;
};

static guint g_array_binary_search_safe(GPtrArray *array, gconstpointer target,
                                        GCompareFunc compare_func)
{
    GRealPtrArray *_array = (GRealPtrArray *)array;
    guint left, middle = 0, right;
    gint val;

    g_return_val_if_fail(_array != NULL, FALSE);
    g_return_val_if_fail(compare_func != NULL, FALSE);

    if (G_LIKELY(_array->len)) {
        left = 0;
        right = _array->len - 1;

        while (left <= right) {
            middle = left + (right - left) / 2;

            val = compare_func(_array->pdata + middle, target);
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
           compare_func(target, _array->pdata + middle - 1) <= 0) {
        middle--;
    }

    while (middle < array->len &&
           compare_func(target, _array->pdata + middle) > 0) {
        middle++;
    }

    return middle;
}
