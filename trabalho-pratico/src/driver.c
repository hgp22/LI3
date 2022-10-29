#include "driver.h"
#include "ride.h"
#include "utils.h"
#include <glib.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

enum account_status {
    Inactive,
    Active,
};

struct driver {
    long id;
    char *name;
    char gender;
    uint8_t age;
    Car_Class car_class;
    unsigned short account_age;
    Status account_status;
    unsigned short sum_score;
    float total_earned;
    unsigned short n_trips;
    GSList *recent_trips;
};

Driver new_driver(void)
{
    Driver d = g_new(struct driver, 1);

    d->sum_score = 0;
    d->total_earned = 0;
    d->n_trips = 0;
    // ? do we need to initialize the list?

    return d;
}

void free_driver(void *driver)
{
    Driver d = (Driver)driver;
    free(d->name);
    // trips dates list
    free(driver);
}

void set_driver_id(Driver d, char *id)
{
    char *endptr;
    d->id = strtol(id, &endptr, 10);
}

void set_driver_name(Driver d, char *name)
{
    d->name = malloc(strlen(name) * sizeof(name));
    strcpy(d->name, name);
}

void set_driver_gender(Driver d, char *gender)
{
    d->gender = *gender;
}

void set_driver_age(Driver d, char *birth_date)
{
    d->age = date_to_age(birth_date);
}

void set_driver_car_class(Driver d, char *car_class)
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

void set_driver_account_age(Driver d, char *account_creation)
{
    d->account_age = date_to_days(account_creation);
}

void set_driver_account_status(Driver d, char *account_status)
{
    switch (account_status[0]) {
        case 'i':
            d->account_status = Inactive;
            break;
        case 'a':
            d->account_status = Active;
            break;
        default:
            break;
    }
}

long get_driver_id(Driver d)
{
    return d->id;
}

char *get_driver_name(Driver d)
{
    return strdup(d->name);
}

char get_driver_gender(Driver d)
{
    return d->gender;
}

uint8_t get_driver_age(Driver d)
{
    return d->age;
}

Car_Class get_driver_car_class(Driver d)
{
    return d->car_class;
}

unsigned short get_driver_account_age(Driver d)
{
    return d->account_age;
}

Status get_driver_account_status(Driver d)
{
    return d->account_status;
}

float get_driver_avg_score(Driver d)
{
    float avg_score = 0;
    if (d->n_trips != 0) {
        avg_score = (float)d->sum_score / d->n_trips;
    }
    return avg_score;
}

float get_driver_total_earned(Driver d)
{
    return d->total_earned;
}

unsigned short get_driver_n_trips(Driver d)
{
    return d->n_trips;
}

GSList *get_driver_trip_dates(Driver d)
{
    return d->recent_trips;
}

void add_driver_ride_data(Driver d, Ride r)
{
    d->sum_score += get_ride_score_user(r);
    d->total_earned += get_ride_cost(r);
    // ! doubt this works, isn't date lost?
    // unsigned short date = get_ride_date(r);
    // d->recent_trips = g_slist_insert_sorted(d->recent_trips, &date,
    // compare_trips);
    d->n_trips += 1;
}
