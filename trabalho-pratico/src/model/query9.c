#include "query9.h"
#include "ride.h"
#include "rides.h"
#include "utils.h"
#include <glib.h>

static gint _ride_comparator_date(gconstpointer a, gconstpointer b);
static gint _ride_comparator_distance(gconstpointer a, gconstpointer b);
static guint g_array_binary_search_safe(GPtrArray *array, gconstpointer target,
                                        GCompareFunc compare_func);

Query9 query9_new(Rides rides)
{
    Query9 q9 = g_ptr_array_sized_new(rides->len);

    for (guint i = 0; i < rides->len; i++) {
        Ride r = rides_get_ride_shallow(rides, i);
        if (ride_get_tip(r) != 0) {
            g_ptr_array_add(q9, r);
        }
    }

    return q9;
}

Query9 query9_rides_with_tips_in_range(Query9 q9, char *dateA, char *dateB)
{
    Ride r_date = ride_new();
    ride_set_date(r_date, dateA);
    guint i = g_array_binary_search_safe(q9, &r_date, _ride_comparator_date);
    unsigned short target = date_to_days(dateB);

    Query9 r_q9 = g_ptr_array_new_with_free_func(ride_free);

    for (Ride r = g_ptr_array_index(q9, i);
         i < q9->len && ride_get_date(r) <= target;
         r = g_ptr_array_index(q9, ++i)) {
        g_ptr_array_add(r_q9, r);
    }

    g_ptr_array_sort(r_q9, _ride_comparator_distance);

    return r_q9;
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
