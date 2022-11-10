#include "ride.h"
#include "driver.h"
#include "utils.h"
#include <glib.h>
#include <stdint.h>
#include <string.h>

struct ride {
    long id;
    unsigned short date;
    long driver;
    char *user;
    char *city;
    uint8_t distance;
    uint8_t score_user;
    uint8_t score_driver;
    double cost;
    double tip;
};

Ride ride_new(void)
{
    return g_new(struct ride, 1);
}

// ? void or proper type
void ride_free(void *ride)
{
    if (ride != NULL) {
        Ride r = (Ride)ride;
        free(r->user);
        free(r->city);
        free(ride);
    }
}

void ride_set_id(Ride r, char *id)
{
    char *endptr;
    r->id = strtol(id, &endptr, 10);
}

void ride_set_date(Ride r, char *date)
{
    r->date = date_to_days(date);
}

void ride_set_driver(Ride r, char *driver)
{
    char *endptr;
    r->driver = strtol(driver, &endptr, 10);
}

void ride_set_user(Ride r, char *user)
{
    r->user = strdup(user);
}

void ride_set_city(Ride r, char *city)
{
    r->city = strdup(city);
}

void ride_set_distance(Ride r, char *distance)
{
    char *endptr;
    r->distance = (uint8_t)strtol(distance, &endptr, 10);
}

void ride_set_score_user(Ride r, char *score_user)
{
    char *endptr;
    r->score_user = (uint8_t)strtol(score_user, &endptr, 10);
}

void ride_set_score_driver(Ride r, char *score_driver)
{
    char *endptr;
    r->score_driver = (uint8_t)strtol(score_driver, &endptr, 10);
}

void ride_set_cost(Ride r, Driver d)
{
    Car_Class class = driver_get_car_class(d);
    double base[] = {3.25, 4.00, 5.20};
    double tax[] = {0.62, 0.79, 0.94};
    double b = base[class];
    double t = tax[class];
    r->cost = b + t * r->distance;
}

void ride_set_tip(Ride r, char *tip)
{
    char *endptr;
    r->tip = (float)strtof(tip, &endptr);
}

long ride_get_id(Ride r)
{
    return r->id;
}

unsigned short ride_get_date(Ride r)
{
    return r->date;
}

long ride_get_driver(Ride r)
{
    return r->driver;
}

char *ride_get_user(Ride r)
{
    return strdup(r->user);
}

char *ride_get_city(Ride r)
{
    return strdup(r->city);
}

double ride_get_distance(Ride r)
{
    return (double)r->distance;
}

uint8_t ride_get_score_user(Ride r)
{
    return r->score_user;
}

uint8_t ride_get_score_driver(Ride r)
{
    return r->score_driver;
}

double ride_get_cost(Ride r)
{
    return r->cost;
}

double ride_get_tip(Ride r)
{
    return r->tip;
}

Ride ride_copy(Ride old_r)
{
    if (old_r == NULL) {
        return NULL;
    }

    Ride new_r = g_new(struct ride, 1);

    new_r->id = old_r->id;
    new_r->date = old_r->date;
    new_r->driver = old_r->driver;
    new_r->user = strdup(old_r->user);
    new_r->city = strdup(old_r->city);
    new_r->distance = old_r->distance;
    new_r->score_user = old_r->score_user;
    new_r->score_driver = old_r->score_driver;
    new_r->cost = old_r->cost;
    new_r->tip = old_r->tip;

    return new_r;
}
