#include "ride.h"
#include "date.h"
#include "validation.h"
#include <glib.h>
#include <string.h>

typedef enum field_ride {
    Id,
    Date,
    Driver_id,
    User_id,
    City_name,
    Distance,
    Score_user,
    Score_driver,
    Tip,
    Comment,
} FieldRide;

struct __attribute__((__packed__)) ride {
    char *user;
    char *city;
    double cost;
    double tip;
    int id;
    int driver;
    guint16 date;
    guint16 user_account_age;
    guint16 driver_account_age;
    guint8 distance;
    guint8 score_driver;
    guint8 score_user;
};

Ride ride_new(void)
{
    Ride ride = g_new(struct ride, 1);

    ride->user = NULL;
    ride->city = NULL;

    return ride;
}

Ride ride_new_from_record(const char *ride_record)
{
    Ride ride = ride_new();

    for (FieldRide field = Id; field <= Comment; field++) {
        char *buff = strsep(&ride_record, ";\n");
        switch (field) {
            case Id:
                ride_set_id(ride, buff);
                break;
            case Date:
                if (!validate_date(buff)) {
                    ride_free(ride);
                    return NULL;
                }
                ride_set_date(ride, buff);
                break;
            case Driver_id:
                ride_set_driver(ride, buff);
                break;
            case User_id:
                ride_set_user(ride, buff);
                break;
            case City_name:
                ride_set_city(ride, buff);
                break;
            case Distance:
                if (!validate_natural(buff)) {
                    ride_free(ride);
                    return NULL;
                }
                ride_set_distance(ride, buff);
                break;
            case Score_user:
                if (!validate_natural(buff)) {
                    ride_free(ride);
                    return NULL;
                }
                ride_set_score_user(ride, buff);
                break;
            case Score_driver:
                if (!validate_natural(buff)) {
                    ride_free(ride);
                    return NULL;
                }
                ride_set_score_driver(ride, buff);
                break;
            case Tip:
                ride_set_tip(ride, buff);
                break;
            case Comment:
                break;
            default:
                break;
        }
    }

    return ride;
}

void ride_set_id(const Ride r, const char *id)
{
    char *endptr;
    r->id = (int)strtol(id, &endptr, 10);
}

void ride_set_date(const Ride r, const char *date)
{
    r->date = date_to_days(date);
}

void ride_set_driver(const Ride r, const char *driver)
{
    char *endptr;
    r->driver = (int)strtol(driver, &endptr, 10);
}

void ride_set_user(const Ride r, const char *user)
{
    r->user = strdup(user);
}

void ride_set_city(const Ride r, const char *city)
{
    r->city = strdup(city);
}

void ride_set_distance(const Ride r, const char *distance)
{
    char *endptr;
    r->distance = (guint8)strtol(distance, &endptr, 10);
}

void ride_set_score_user(const Ride r, const char *score_user)
{
    char *endptr;
    r->score_user = (guint8)strtol(score_user, &endptr, 10);
}

void ride_set_score_driver(const Ride r, const char *score_driver)
{
    char *endptr;
    r->score_driver = (guint8)strtol(score_driver, &endptr, 10);
}

void ride_set_cost(const Ride r, double cost)
{
    r->cost = cost;
}

void ride_set_tip(const Ride r, const char *tip)
{
    char *endptr;
    r->tip = strtof(tip, &endptr);
}

void ride_set_user_account_age(const Ride r, guint16 user_account_age)
{
    r->user_account_age = user_account_age;
}

void ride_set_driver_account_age(const Ride r, guint16 driver_account_age)
{
    r->driver_account_age = driver_account_age;
}

int ride_get_id(const Ride r)
{
    return r->id;
}

guint16 ride_get_date(const Ride r)
{
    return r->date;
}

int ride_get_driver(const Ride r)
{
    return r->driver;
}

char *ride_get_user(const Ride r)
{
    return strdup(r->user);
}

char *ride_get_city(const Ride r)
{
    return strdup(r->city);
}

double ride_get_distance(const Ride r)
{
    return (double)r->distance;
}

guint8 ride_get_score_user(const Ride r)
{
    return r->score_user;
}

guint8 ride_get_score_driver(const Ride r)
{
    return r->score_driver;
}

double ride_get_cost(const Ride r)
{
    return r->cost;
}

double ride_get_tip(const Ride r)
{
    return r->tip;
}

guint16 ride_get_user_account_age(const Ride r)
{
    return r->user_account_age;
}

guint16 ride_get_driver_account_age(const Ride r)
{
    return r->driver_account_age;
}

Ride ride_copy(const Ride old_r)
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
    new_r->user_account_age = old_r->user_account_age;
    new_r->driver_account_age = old_r->driver_account_age;

    return new_r;
}

void ride_free(void *ride)
{
    if (ride != NULL) {
        Ride r = (Ride)ride;
        if (r->user != NULL)
            free(r->user);
        if (r->city != NULL)
            free(r->city);
        free(ride);
    }
}
