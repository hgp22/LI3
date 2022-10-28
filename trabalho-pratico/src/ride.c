#include "ride.h"
#include <glib.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct ride {
    char *id;
    char *date;
    char *driver;
    char *user;
    char *city;
    uint8_t distance;
    uint8_t score_user;
    uint8_t score_driver;
    char *tip;
    char *comment;
};

Ride init_ride(void)
{
    return g_new(struct ride, 1);
}

void free_ride(void *ride)
{
    Ride r = (Ride)ride;
    free(r->id);
    free(r->date);
    free(r->driver);
    free(r->user);
    free(r->city);
    free(r->tip);
    free(r->comment);
    free(ride);
}

void set_ride_id(Ride r, char *id)
{
    r->id = malloc(strlen(id) * sizeof(id));
    strcpy(r->id, id);
}

void set_ride_date(Ride r, char *date)
{
    r->date = malloc(strlen(date) * sizeof(date));
    strcpy(r->date, date);
}

void set_ride_driver(Ride r, char *driver)
{
    r->driver = malloc(strlen(driver) * sizeof(driver));
    strcpy(r->driver, driver);
}

void set_ride_user(Ride r, char *user)
{
    r->user = malloc(strlen(user) * sizeof(user));
    strcpy(r->user, user);
}

void set_ride_city(Ride r, char *city)
{
    r->city = malloc(strlen(city) * sizeof(city));
    strcpy(r->city, city);
}

void set_ride_distance(Ride r, char *distance)
{
    char *endptr;
    r->distance = (uint8_t)strtol(distance, &endptr, 10);
}

void set_ride_score_user(Ride r, char *score_user)
{
    char *endptr;
    r->score_user = (uint8_t)strtol(score_user, &endptr, 10);
}

void set_ride_score_driver(Ride r, char *score_driver)
{
    char *endptr;
    r->score_driver= (uint8_t)strtol(score_driver, &endptr, 10);
}

void set_ride_tip(Ride r, char *tip)
{
    r->tip = malloc(strlen(tip) * sizeof(tip));
    strcpy(r->tip, tip);
}

void set_ride_comment(Ride r, char *comment)
{
    r->comment = malloc(strlen(comment) * sizeof(comment));
    strcpy(r->comment, comment);
}

char *get_ride_id(Ride r)
{
    return strdup(r->id);
}

char *get_ride_date(Ride r)
{
    return strdup(r->date);
}

char *get_ride_driver(Ride r)
{
    return strdup(r->driver);
}

char *get_ride_user(Ride r)
{
    return strdup(r->user);
}

char *get_ride_city(Ride r)
{
    return strdup(r->city);
}

uint8_t get_ride_distance(Ride r)
{
    return r->distance;
}

uint8_t get_ride_score_user(Ride r)
{
    return r->score_user;
}

uint8_t get_ride_score_driver(Ride r)
{
    return r->score_driver;
}

char *get_ride_tip(Ride r)
{
    return strdup(r->tip);
}

char *get_ride_comment(Ride r)
{
    return strdup(r->comment);
}
