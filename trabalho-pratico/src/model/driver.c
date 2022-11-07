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

Driver driver_new(void)
{
    Driver d = g_new(struct driver, 1);

    d->sum_score = 0;
    d->total_earned = 0;
    d->n_trips = 0;
    d->last_ride_date = 0;

    return d;
}

void driver_free(void *driver)
{
    if (driver != NULL) {
        Driver d = (Driver)driver;
        free(d->name);
        free(driver);
    }
}

void driver_set_id(Driver d, char *id)
{
    char *endptr;
    d->id = strtol(id, &endptr, 10);
}

void driver_set_name(Driver d, char *name)
{
    d->name = strdup(name);
}

void driver_set_gender(Driver d, char *gender)
{
    d->gender = *gender;
}

void driver_set_age(Driver d, char *birth_date)
{
    d->age = date_to_age(birth_date);
}

void driver_set_car_class(Driver d, char *car_class)
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

void driver_set_account_age(Driver d, char *account_creation)
{
    d->account_age = date_to_days(account_creation);
}

void driver_set_account_status(Driver d, char *account_status)
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

long driver_get_id(Driver d)
{
    return d->id;
}

char *driver_get_name(Driver d)
{
    return strdup(d->name);
}

char driver_get_gender(Driver d)
{
    return d->gender;
}

uint8_t driver_get_age(Driver d)
{
    return d->age;
}

Car_Class driver_get_car_class(Driver d)
{
    return d->car_class;
}

unsigned short driver_get_account_age(Driver d)
{
    return d->account_age;
}

D_Status driver_get_account_status(Driver d)
{
    return d->account_status;
}

double driver_get_avg_score(Driver d)
{
    double avg_score = 0;
    if (d->n_trips != 0) {
        avg_score = (double)d->sum_score / d->n_trips;
    }
    return avg_score;
}

double driver_get_total_earned(Driver d)
{
    return d->total_earned;
}

unsigned short driver_get_n_trips(Driver d)
{
    return d->n_trips;
}

unsigned short driver_get_last_ride_date(Driver d)
{
    return d->last_ride_date;
}

void driver_add_ride_data(Driver d, Ride r)
{
    d->sum_score += ride_get_score_driver(r);
    d->total_earned += ride_get_cost(r) + ride_get_tip(r);
    unsigned short ride_date = ride_get_date(r);
    if (ride_date > d->last_ride_date) {
        d->last_ride_date = ride_date;
    }
    d->n_trips += 1;
}

Driver driver_copy(Driver old_d)
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
