#include "rides.h"
#include "date.h"
#include "loader.h"
#include "ride.h"
#include <glib.h>
#include <stdio.h>

#define INPUT_FILE "/rides.csv"
#define RESERVED_RIDES 1048576 // (2^20)
#define RESERVED_CITY 262144   // (2^18)
#define ORDER_ASCENDING 1
#define ORDER_DESCENDING -1
#define ORDER_EQUAL 0

struct rides {
    GPtrArray *all;
    GPtrArray *tips;
    GHashTable *cities;
    GPtrArray *females;
    GPtrArray *males;
};

typedef struct city {
    GPtrArray *rides;
    double sum_costs;
    int n_rides;
} * City;

static gint _ride_comparator_date(gconstpointer a, gconstpointer b);
static gint _ride_comparator_distance(gconstpointer a, gconstpointer b);
static gint _ride_comparator_accounts_age(gconstpointer a, gconstpointer b);
static guint _ptr_array_binary_search(const GPtrArray *array,
                                      gconstpointer target,
                                      GCompareFunc compare_func);
static void _key_destroyed_city(gpointer data);
static void _value_destroyed_city(gpointer data);

Rides rides_new(void)
{
    Rides rides = g_new(struct rides, 1);

    rides->all =
        g_ptr_array_new_full(RESERVED_RIDES, (GDestroyNotify)ride_free);
    rides->tips = NULL;
    rides->cities = NULL;
    rides->females = NULL;
    rides->males = NULL;

    return rides;
}

Rides rides_new_from_file(const char *inputs_path)
{
    return load_file(inputs_path, INPUT_FILE, rides_new(), rides_add_record);
}

void rides_new_genders(const Rides rides)
{
    guint size = rides->all->len / 4;
    rides->females = g_ptr_array_sized_new(size);
    rides->males = g_ptr_array_sized_new(size);
}

void rides_add_ride(const Rides rides, const Ride ride)
{
    g_ptr_array_add(rides->all, ride_copy(ride));
}

void rides_add_record(const Rides rides, const char *ride_record)
{
    Ride ride = ride_new_from_record(ride_record);
    g_ptr_array_add(rides->all, ride);
}

void rides_replace_ride(const Rides rides, const Ride ride, guint index)
{
    Ride *r = (Ride *)&g_ptr_array_index(rides->all, index);
    ride_free(*r);
    *r = ride_copy(ride);
}

Ride rides_get_ride(const Rides rides, guint index)
{
    return ride_copy(g_ptr_array_index(rides->all, index));
}

guint rides_size(const Rides rides)
{
    return rides->all->len;
}

void rides_set_ride_cost(const Rides rides, guint index, double cost)
{
    ride_set_cost(g_ptr_array_index(rides->all, index), cost);
}

void rides_set_ride_user_account_age(const Rides rides, guint index,
                                     guint16 user_account_age)
{
    ride_set_user_account_age(g_ptr_array_index(rides->all, index),
                              user_account_age);
}

void rides_set_ride_driver_account_age(const Rides rides, guint index,
                                       guint16 driver_account_age)
{
    ride_set_driver_account_age(g_ptr_array_index(rides->all, index),
                                driver_account_age);
}

guint16 rides_get_ride_date(const Rides rides, guint index)
{
    return ride_get_date(g_ptr_array_index(rides->all, index));
}

char *rides_get_ride_user(const Rides rides, guint index)
{
    return ride_get_user(g_ptr_array_index(rides->all, index));
}

int rides_get_ride_driver(const Rides rides, guint index)
{
    return ride_get_driver(g_ptr_array_index(rides->all, index));
}

char *rides_get_ride_city(const Rides rides, guint index)
{
    return ride_get_city(g_ptr_array_index(rides->all, index));
}

guint8 rides_get_ride_distance(const Rides rides, guint index)
{
    return ride_get_distance(g_ptr_array_index(rides->all, index));
}

guint8 rides_get_ride_score_user(const Rides rides, guint index)
{
    return ride_get_score_user(g_ptr_array_index(rides->all, index));
}

guint8 rides_get_ride_score_driver(const Rides rides, guint index)
{
    return ride_get_score_driver(g_ptr_array_index(rides->all, index));
}

double rides_get_ride_tip(const Rides rides, guint index)
{
    return ride_get_tip(g_ptr_array_index(rides->all, index));
}

void rides_add_females_ride_index(const Rides rides, guint index)
{
    g_ptr_array_add(rides->females, g_ptr_array_index(rides->all, index));
}

void rides_add_males_ride_index(const Rides rides, guint index)
{
    g_ptr_array_add(rides->males, g_ptr_array_index(rides->all, index));
}

Rides rides_sort_date(const Rides rides)
{
    g_ptr_array_sort(rides->all, (GCompareFunc)_ride_comparator_date);
    return rides;
}

Rides rides_sort_accounts_age(const Rides rides)
{
    g_ptr_array_sort(rides->females,
                     (GCompareFunc)_ride_comparator_accounts_age);
    g_ptr_array_sort(rides->males, (GCompareFunc)_ride_comparator_accounts_age);
    return rides;
}

Rides rides_with_tip(const Rides rides)
{
    rides->tips = g_ptr_array_sized_new(rides->all->len);

    for (guint i = 0; i < rides->all->len; i++) {
        Ride r = g_ptr_array_index(rides->all, i);
        if (ride_get_tip(r) != 0) {
            g_ptr_array_add(rides->tips, r);
        }
    }

    return rides;
}

Rides rides_cities(const Rides rides)
{
    rides->cities = g_hash_table_new_full(
        g_str_hash, g_str_equal, (GDestroyNotify)_key_destroyed_city,
        (GDestroyNotify)_value_destroyed_city);

    // add rides to cities
    for (guint i = 0; i < rides_size(rides); i++) {
        Ride r = g_ptr_array_index(rides->all, i);
        double cost = ride_get_cost(r);
        char *city_name = ride_get_city(r);
        City city = g_hash_table_lookup(rides->cities, city_name);
        if (city == NULL) {
            city = g_new(struct city, 1);
            city->rides = g_ptr_array_sized_new(RESERVED_CITY);
            city->sum_costs = 0;
            city->n_rides = 0;
            char *key = strdup(city_name);
            g_hash_table_insert(rides->cities, key, city);
        }
        free(city_name);
        city->sum_costs += cost;
        city->n_rides++;
        g_ptr_array_add(city->rides, r);
    }

    return rides;
}

double rides_get_avg_stat_in_range(const GPtrArray *rides, const char *dateA,
                                   const char *dateB, double (*get_func)(Ride))
{
    Ride r_date = ride_new();
    ride_set_date(r_date, dateA);
    guint i = _ptr_array_binary_search(rides, &r_date, _ride_comparator_date);
    free(r_date);

    guint16 target = date_to_days(dateB);
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

// query 4
double rides_city_avg_cost(const Rides rides, const char *city_name)
{
    City city = g_hash_table_lookup(rides->cities, city_name);
    return city->sum_costs / city->n_rides;
}

// query 5
double rides_get_avg_cost_in_range(const Rides rides, const char *dateA,
                                   const char *dateB)
{
    return rides_get_avg_stat_in_range(rides->all, dateA, dateB, ride_get_cost);
}

// query 6
double rides_city_avg_dist_in_range(const Rides rides, const char *city_name,
                                    const char *dateA, const char *dateB)
{
    City city = g_hash_table_lookup(rides->cities, city_name);
    return rides_get_avg_stat_in_range(city->rides, dateA, dateB,
                                       ride_get_distance);
}

// query 8
GPtrArray *rides_by_gender_by_age(const Rides rides, char gender,
                                  int account_age)
{
    char date[18];
    snprintf(date, 18, "09/10/%d", 2022 - account_age);
    guint16 age_days = date_to_days(date);

    GPtrArray *rs;

    switch (gender) {
        case 'F':
            rs = rides->females;
            break;
        case 'M':
            rs = rides->males;
            break;
        default:
            return NULL;
    }

    GPtrArray *answer =
        g_ptr_array_new_with_free_func((GDestroyNotify)ride_free);

    guint i = 0;
    for (Ride r = g_ptr_array_index(rs, i);
         i < rs->len && ride_get_driver_account_age(r) <= age_days;
         r = g_ptr_array_index(rs, ++i)) {
        if (ride_get_user_account_age(r) <= age_days) {
            g_ptr_array_add(answer, ride_copy(r));
        }
    }

    return answer;
}

// query 9
GPtrArray *rides_get_rides_with_tip_in_range(const Rides rides,
                                             const char *dateA,
                                             const char *dateB)
{
    Ride r_date = ride_new();
    ride_set_date(r_date, dateA);
    guint i =
        _ptr_array_binary_search(rides->tips, &r_date, _ride_comparator_date);
    free(r_date);

    guint16 target = date_to_days(dateB);
    GPtrArray *rs = g_ptr_array_new_with_free_func(ride_free);

    for (Ride r = g_ptr_array_index(rides->all, i);
         i < rides->all->len && ride_get_date(r) <= target;
         r = g_ptr_array_index(rides->all, ++i)) {
        g_ptr_array_add(rs, ride_copy(r));
    }

    g_ptr_array_sort(rs, _ride_comparator_distance);

    return rs;
}

static guint _ptr_array_binary_search(const GPtrArray *array,
                                      gconstpointer target,
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

    const guint8 distance1 = ride_get_distance(r1);
    const guint8 distance2 = ride_get_distance(r2);

    if (distance1 < distance2)
        return ORDER_ASCENDING;
    else if (distance1 > distance2)
        return ORDER_DESCENDING;

    const guint16 date1 = ride_get_date(r1);
    const guint16 date2 = ride_get_date(r2);

    if (date1 < date2)
        return ORDER_ASCENDING;
    else if (date1 > date2)
        return ORDER_DESCENDING;

    const int id1 = ride_get_id(r1);
    const int id2 = ride_get_id(r2);

    if (id1 < id2)
        return ORDER_ASCENDING;
    else if (id1 > id2)
        return ORDER_DESCENDING;
    else
        return ORDER_EQUAL;
}

static gint _ride_comparator_accounts_age(gconstpointer a, gconstpointer b)
{
    const Ride r1 = *((Ride *)a);
    const Ride r2 = *((Ride *)b);

    const guint16 d_account_age1 = ride_get_driver_account_age(r1);
    const guint16 d_account_age2 = ride_get_driver_account_age(r2);

    if (d_account_age1 < d_account_age2)
        return ORDER_DESCENDING;
    else if (d_account_age1 > d_account_age2)
        return ORDER_ASCENDING;

    const guint16 u_account_age1 = ride_get_user_account_age(r1);
    const guint16 u_account_age2 = ride_get_user_account_age(r2);

    if (u_account_age1 < u_account_age2)
        return ORDER_DESCENDING;
    else if (u_account_age1 > u_account_age2)
        return ORDER_ASCENDING;

    const int id1 = ride_get_id(r1);
    const int id2 = ride_get_id(r2);

    if (id1 < id2)
        return ORDER_DESCENDING;
    else if (id1 > id2)
        return ORDER_ASCENDING;
    else
        return ORDER_EQUAL;
}

static void _key_destroyed_city(gpointer data)
{
    g_free(data);
}

static void _value_destroyed_city(gpointer data)
{
    City city = (City)data;
    g_ptr_array_free(city->rides, TRUE);
    g_free(data);
}

void rides_free(const Rides rides)
{
    if (rides != NULL) {
        if (rides->all != NULL) {
            g_ptr_array_free(rides->all, TRUE);
        }
        if (rides->tips != NULL) {
            g_ptr_array_free(rides->tips, TRUE);
        }
        if (rides->cities != NULL) {
            g_hash_table_destroy(rides->cities);
        }
        if (rides->females != NULL) {
            g_ptr_array_free(rides->females, TRUE);
        }
        if (rides->males != NULL) {
            g_ptr_array_free(rides->males, TRUE);
        }
        g_free(rides);
    }
}
