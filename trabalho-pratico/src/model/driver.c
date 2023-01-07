#include "driver.h"
#include "date.h"
#include "validation.h"
#include <glib.h>
#include <stdbool.h>
#include <string.h>

typedef enum field_driver {
    Id,
    Name,
    Birth_date,
    Gender,
    Car_class,
    License_plate,
    City,
    Account_creation,
    Account_status,
} FieldDriver;

struct __attribute__((__packed__)) driver {
    char *name;
    double total_earned;
    GHashTable *cities_score;
    int id;
    guint16 account_age;
    guint16 sum_score;
    guint16 n_trips;
    guint16 last_ride_date;
    char gender;
    guint8 age;
    CarClass car_class;
    bool account_status;
};

typedef struct city_score {
    int sum_score;
    int n_cities;
} * CityScore;

static void _key_destroyed(gpointer data);
static void _value_destroyed(gpointer data);

Driver driver_new(void)
{
    Driver d = g_new(struct driver, 1);

    d->name = NULL;
    d->cities_score = NULL;
    d->sum_score = 0;
    d->total_earned = 0;
    d->n_trips = 0;
    d->last_ride_date = 0;
    d->cities_score = g_hash_table_new_full(g_str_hash, g_str_equal,
                                            (GDestroyNotify)_key_destroyed,
                                            (GDestroyNotify)_value_destroyed);

    return d;
}

Driver driver_new_from_record(const char *driver_record)
{
    Driver driver = driver_new();

    for (FieldDriver field = Id; field <= Account_status; field++) {
        char *buff = strsep(&driver_record, ";\n");
        switch (field) {
            case Id:
                driver_set_id(driver, buff);
                break;
            case Name:
                driver_set_name(driver, buff);
                break;
            case Birth_date:
                if (!validate_date(buff)) {
                    driver_free(driver);
                    return NULL;
                }
                driver_set_age(driver, buff);
                break;
            case Gender:
                driver_set_gender(driver, buff);
                break;
            case Car_class:
                if (!validate_car_class(buff)) {
                    driver_free(driver);
                    return NULL;
                }
                driver_set_car_class(driver, buff);
                break;
            case License_plate:
                break;
            case City:
                break;
            case Account_creation:
                if (!validate_date(buff)) {
                    driver_free(driver);
                    return NULL;
                }
                driver_set_account_age(driver, buff);
                break;
            case Account_status:
                driver_set_account_status(driver, buff);
                break;
            default:
                break;
        }
    }

    return driver;
}

void driver_free_cities_score(GHashTable *cs)
{
    g_hash_table_destroy(cs);
}

void driver_set_id(const Driver d, const char *id)
{
    char *endptr;
    d->id = (int)strtol(id, &endptr, 10);
}

void driver_set_name(const Driver d, const char *name)
{
    d->name = strdup(name);
}

void driver_set_gender(const Driver d, const char *gender)
{
    d->gender = *gender;
}

void driver_set_age(const Driver d, const char *birth_date)
{
    d->age = date_to_age(birth_date);
}

void driver_set_car_class(const Driver d, const char *car_class)
{
    switch (car_class[0]) {
        case 'b':
            d->car_class = Basic;
            break;
        case 'g':
            d->car_class = Green;
            break;
        case 'p':
            d->car_class = Premium;
            break;
        default:
            break;
    }
}

void driver_set_account_age(const Driver d, const char *account_creation)
{
    d->account_age = date_to_days(account_creation);
}

void driver_set_account_status(const Driver d, const char *account_status)
{
    d->account_status = *account_status == 'a';
}

int driver_get_id(const Driver d)
{
    return d->id;
}

char *driver_get_name(const Driver d)
{
    return strdup(d->name);
}

char driver_get_gender(const Driver d)
{
    return d->gender;
}

guint8 driver_get_age(const Driver d)
{
    return d->age;
}

CarClass driver_get_car_class(const Driver d)
{
    return d->car_class;
}

guint16 driver_get_account_age(const Driver d)
{
    return d->account_age;
}

bool driver_is_account_active(const Driver d)
{
    return d->account_status;
}

double driver_get_avg_score(const Driver d)
{
    double avg_score = 0;
    if (d->n_trips != 0) {
        avg_score = (double)d->sum_score / d->n_trips;
    }
    return avg_score;
}

double driver_get_total_earned(const Driver d)
{
    return d->total_earned;
}

guint16 driver_get_n_trips(const Driver d)
{
    return d->n_trips;
}

guint16 driver_get_last_ride_date(const Driver d)
{
    return d->last_ride_date;
}

GHashTable *driver_get_cities_score(const Driver d)
{
    GHashTable *cities_score = g_hash_table_new_similar(d->cities_score);

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, d->cities_score);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        char *k = strdup(key);
        CityScore tmp = (CityScore)value;
        CityScore v = g_new(struct city_score, 1);
        v->sum_score = tmp->sum_score;
        v->n_cities = tmp->n_cities;
        g_hash_table_insert(cities_score, k, v);
    }

    return cities_score;
}

double driver_get_city_score(const Driver d, const char *city)
{
    CityScore c_s = g_hash_table_lookup(d->cities_score, city);
    return (double)c_s->sum_score / c_s->n_cities;
}

void driver_add_ride_data(const Driver d, guint8 score, double cost,
                          guint16 date, const char *city_name)
{
    d->sum_score += score;
    d->total_earned += cost;
    d->last_ride_date = date;
    CityScore city = g_hash_table_lookup(d->cities_score, city_name);
    if (city == NULL) {
        city = g_new(struct city_score, 1);
        city->sum_score = 0;
        city->n_cities = 0;
        g_hash_table_insert(d->cities_score, strdup(city_name), city);
    }
    city->sum_score += score;
    city->n_cities++;
    d->n_trips += 1;
}

Driver driver_copy(const Driver old_d)
{
    if (old_d == NULL) {
        return NULL;
    }

    Driver new_d = g_new(struct driver, 1);

    new_d->id = old_d->id;
    new_d->name = strdup(old_d->name);
    new_d->gender = old_d->gender;
    new_d->age = old_d->age;
    new_d->car_class = old_d->car_class;
    new_d->account_age = old_d->account_age;
    new_d->account_status = old_d->account_status;
    new_d->sum_score = old_d->sum_score;
    new_d->total_earned = old_d->total_earned;
    new_d->n_trips = old_d->n_trips;
    new_d->last_ride_date = old_d->last_ride_date;
    new_d->cities_score = g_hash_table_new_similar(old_d->cities_score);

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, old_d->cities_score);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        char *k = strdup(key);
        CityScore tmp = (CityScore)value;
        CityScore v = g_new(struct city_score, 1);
        v->sum_score = tmp->sum_score;
        v->n_cities = tmp->n_cities;
        g_hash_table_insert(new_d->cities_score, k, v);
    }

    return new_d;
}

static void _key_destroyed(gpointer data)
{
    g_free(data);
}

static void _value_destroyed(gpointer data)
{
    g_free(data);
}

void driver_free(void *driver)
{
    if (driver != NULL) {
        Driver d = (Driver)driver;
        if (d->name != NULL)
            free(d->name);
        if (d->cities_score != NULL)
            driver_free_cities_score(d->cities_score);
        free(driver);
    }
}
