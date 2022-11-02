#include "driver.h"
#include "ride.h"
#include "utils.h"
#include <glib.h>
#include <stdint.h>
#include <string.h>

struct driver {
    long id;
    char *name;
    char gender;
    uint8_t age;
    Car_Class car_class;
    unsigned short account_age;
    D_Status account_status;
    unsigned short sum_score;
    double total_earned;
    unsigned short n_trips;
    unsigned short last_ride_date;
};

Driver new_driver(void)
{
    Driver d = g_new(struct driver, 1);

    d->sum_score = 0;
    d->total_earned = 0;
    d->n_trips = 0;
    d->last_ride_date = 0;

    return d;
}

void free_driver(void *driver)
{
    Driver d = (Driver)driver;
    free(d->name);
    free(driver);
}

void set_driver_id(Driver d, char *id)
{
    char *endptr;
    d->id = strtol(id, &endptr, 10);
}

void set_driver_name(Driver d, char *name)
{
    d->name = strdup(name);
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
            d->account_status = D_Inactive;
            break;
        case 'a':
            d->account_status = D_Active;
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

D_Status get_driver_account_status(Driver d)
{
    return d->account_status;
}

double get_driver_avg_score(Driver d)
{
    double avg_score = 0;
    if (d->n_trips != 0) {
        avg_score = (double)d->sum_score / d->n_trips;
    }
    return avg_score;
}

double get_driver_total_earned(Driver d)
{
    return d->total_earned;
}

unsigned short get_driver_n_trips(Driver d)
{
    return d->n_trips;
}

unsigned short get_driver_last_ride_date(Driver d)
{
    return d->last_ride_date;
}

void add_driver_ride_data(Driver d, Ride r)
{
    d->sum_score += get_ride_score_driver(r);
    d->total_earned += get_ride_cost(r) + get_ride_tip(r);
    unsigned short ride_date = get_ride_date(r);
    if (ride_date > d->last_ride_date) {
        d->last_ride_date = ride_date;
    }
    d->n_trips += 1;
}

Driver copy_driver(Driver old_d)
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

    return new_d;
}
