#include "drivers.h"
#include "driver.h"
#include "loader.h"
#include <glib.h>
#include <stdbool.h>

#define INPUT_FILE "/drivers.csv"
#define ORDER_ASCENDING 1
#define ORDER_DESCENDING -1
#define ORDER_EQUAL 0

struct drivers {
    GHashTable *hash_table;
    GPtrArray *array;
    GHashTable *cities;
};

static gboolean _clean(gpointer key, gpointer value, gpointer user_data);
static gint _driver_comparator(gconstpointer driver1, gconstpointer driver2);
static gint _driver_comparator_by_city(gconstpointer a, gconstpointer b,
                                       gpointer user_data);
static void _key_destroyed_city(gpointer data);
static void _value_destroyed_city(gpointer data);

Drivers drivers_new(void)
{
    Drivers drivers = g_new(struct drivers, 1);

    drivers->hash_table =
        g_hash_table_new_full(g_int_hash, g_int_equal, (GDestroyNotify)g_free,
                              (GDestroyNotify)driver_free);
    drivers->array = NULL;
    drivers->cities = NULL;

    return drivers;
}

Drivers drivers_new_from_file(const char *inputs_path)
{
    return load_file(inputs_path, INPUT_FILE, drivers_new(),
                     drivers_add_record);
}

gboolean drivers_add_driver(const Drivers drivers, const Driver d)
{
    gint *k_id = g_new(gint, 1);
    *k_id = driver_get_id(d);
    return g_hash_table_insert(drivers->hash_table, k_id, driver_copy(d));
}

void drivers_add_record(const Drivers drivers, const char *driver_record)
{
    Driver driver = driver_new_from_record(driver_record);
    if (driver != NULL) {
        gint *driver_id = g_new(gint, 1);
        *driver_id = driver_get_id(driver);
        g_hash_table_insert(drivers->hash_table, driver_id, driver);
    }
}

Driver drivers_get_driver(const Drivers drivers, int id)
{
    return driver_copy(g_hash_table_lookup(drivers->hash_table, &id));
}

Driver drivers_get_nth_driver(const Drivers drivers, guint index)
{
    return driver_copy(g_ptr_array_index(drivers->array, index));
}

guint drivers_size(const Drivers drivers)
{
    return drivers->array->len;
}

void drivers_add_driver_ride_data(const Drivers drivers, int driver_id,
                                  guint8 score, double cost, guint16 date,
                                  const char *city_name)
{
    driver_add_ride_data(g_hash_table_lookup(drivers->hash_table, &driver_id),
                         score, cost, date, city_name);
}

char drivers_get_driver_gender(const Drivers drivers, int driver_id)
{
    return driver_get_gender(
        g_hash_table_lookup(drivers->hash_table, &driver_id));
}

CarClass drivers_get_driver_car_class(const Drivers drivers, int driver_id)
{
    return driver_get_car_class(
        g_hash_table_lookup(drivers->hash_table, &driver_id));
}

guint16 drivers_get_driver_account_age(const Drivers drivers, int driver_id)
{
    return driver_get_account_age(
        g_hash_table_lookup(drivers->hash_table, &driver_id));
}

bool drivers_is_driver_active(const Drivers drivers, int driver_id)
{
    return driver_is_account_active(
        g_hash_table_lookup(drivers->hash_table, &driver_id));
}

int drivers_has_driver(const Drivers drivers, int driver_id)
{
    return g_hash_table_lookup(drivers->hash_table, &driver_id) != NULL;
}

guint drivers_remove_inactive_accounts(const Drivers drivers)
{
    return g_hash_table_foreach_remove(drivers->hash_table, (GHRFunc)_clean,
                                       NULL);
}

// ? return something different ?
Drivers drivers_process(const Drivers drivers)
{
    drivers->array =
        g_ptr_array_sized_new(g_hash_table_size(drivers->hash_table));

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, drivers->hash_table);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        if (driver_is_account_active(value)) {
            g_ptr_array_add(drivers->array, value);
        }
        else {
            g_hash_table_iter_remove(&iter);
        }
    }

    g_ptr_array_sort(drivers->array, (GCompareFunc)_driver_comparator);

    return drivers;
}

Drivers drivers_list(const Drivers drivers)
{
    drivers->array =
        g_ptr_array_sized_new(g_hash_table_size(drivers->hash_table));

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, drivers->hash_table);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        g_ptr_array_add(drivers->array, value);
    }

    g_ptr_array_sort(drivers->array, (GCompareFunc)_driver_comparator);
    return drivers;
}

Drivers drivers_cities(const Drivers drivers)
{
    drivers->cities = g_hash_table_new_full(
        g_str_hash, g_str_equal, (GDestroyNotify)_key_destroyed_city,
        (GDestroyNotify)_value_destroyed_city);

    // add drivers to cities
    for (guint i = 0; i < drivers_size(drivers); i++) {
        Driver d = g_ptr_array_index(drivers->array, i);
        GHashTable *cities_score = driver_get_cities_score(d);
        GHashTableIter iter;
        gpointer key, value;
        g_hash_table_iter_init(&iter, cities_score);
        while (g_hash_table_iter_next(&iter, &key, &value)) {
            GPtrArray *ds = g_hash_table_lookup(drivers->cities, key);
            if (ds == NULL) {
                ds = g_ptr_array_sized_new(drivers_size(drivers));
                g_hash_table_insert(drivers->cities, strdup(key), ds);
            }
            g_ptr_array_add(ds, d);
        }
        driver_free_cities_score(cities_score);
    }

    // sort drivers in cities by driver score in city
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, drivers->cities);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        GPtrArray *ds = (GPtrArray *)value;
        g_ptr_array_sort_with_data(ds, _driver_comparator_by_city, key);
    }

    return drivers;
}

// query 2
GPtrArray *drivers_top_n_drivers(const Drivers drivers, int N)
{
    GPtrArray *r = g_ptr_array_new_full(N, driver_free);

    for (int i = 0; i < N; i++) {
        g_ptr_array_add(r, driver_copy(g_ptr_array_index(drivers->array, i)));
    }

    return r;
}

// query 7
GPtrArray *drivers_top_n_drivers_in_city(const Drivers drivers,
                                         const char *city, guint N)
{
    const GPtrArray *ds = g_hash_table_lookup(drivers->cities, city);
    GPtrArray *r = g_ptr_array_new_full(N, driver_free);

    for (guint i = 0; i < ds->len && i < N; i++) {
        g_ptr_array_add(r, driver_copy(g_ptr_array_index(ds, i)));
    }

    return r;
}

static gboolean _clean(gpointer key, gpointer value, gpointer user_data)
{
    return !driver_is_account_active(value);
}

static gint _driver_comparator(gconstpointer a, gconstpointer b)
{
    const Driver d1 = *((Driver *)a);
    const Driver d2 = *((Driver *)b);

    const float score1 = driver_get_avg_score(d1);
    const float score2 = driver_get_avg_score(d2);

    if (score1 < score2)
        return ORDER_ASCENDING;
    else if (score1 > score2)
        return ORDER_DESCENDING;

    const guint16 ride_date1 = driver_get_last_ride_date(d1);
    const guint16 ride_date2 = driver_get_last_ride_date(d2);

    if (ride_date1 < ride_date2)
        return ORDER_ASCENDING;
    else if (ride_date1 > ride_date2)
        return ORDER_DESCENDING;

    const int id1 = driver_get_id(d1);
    const int id2 = driver_get_id(d2);

    if (id1 < id2)
        return ORDER_ASCENDING;
    else if (id1 > id2)
        return ORDER_DESCENDING;
    else
        return ORDER_EQUAL;
}

static gint _driver_comparator_by_city(gconstpointer a, gconstpointer b,
                                       gpointer user_data)
{
    const Driver d1 = *((Driver *)a);
    const Driver d2 = *((Driver *)b);
    const char *city = (char *)user_data;

    const double avg_score1 = driver_get_city_score(d1, city);
    const double avg_score2 = driver_get_city_score(d2, city);

    if (avg_score1 < avg_score2)
        return ORDER_ASCENDING;
    else if (avg_score1 > avg_score2)
        return ORDER_DESCENDING;
    else
        return driver_get_id(d2) - driver_get_id(d1);
}

static void _key_destroyed_city(gpointer data)
{
    g_free(data);
}

static void _value_destroyed_city(gpointer data)
{
    g_ptr_array_free(data, TRUE);
}

void drivers_free(const Drivers drivers)
{
    if (drivers != NULL) {
        if (drivers->hash_table != NULL) {
            g_hash_table_destroy(drivers->hash_table);
        }
        if (drivers->array != NULL) {
            g_ptr_array_free(drivers->array, TRUE);
        }
        if (drivers->cities != NULL) {
            g_hash_table_destroy(drivers->cities);
        }
        g_free(drivers);
    }
}
