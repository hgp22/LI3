#include "ride.h"
#include <glib.h>
#include <stdlib.h>
#include <string.h>

struct ride {
    char *id;
    char *state;
    char *driver;
    char *user;
    char *city;
    char *distance;
    char *score_user;
    char *score_driver;
    char *tip;
    char *comment;
};

Ride init_ride(void) { return g_new(struct ride, 1); }

void free_ride(void *ride)
{
    Ride r = (Ride)ride;
    free(r->id);
    free(r->state);
    free(r->driver);
    free(r->user);
    free(r->city);
    free(r->distance);
    free(r->score_user);
    free(r->score_driver);
    free(r->tip);
    free(r->comment);
    free(ride);
}

void set_ride_id(Ride r, char *id)
{
    r->id = malloc(strlen(id) * sizeof(id));
    strcpy(r->id, id);
}

void set_ride_state(Ride r, char *state)
{
    r->state = malloc(strlen(state) * sizeof(state));
    strcpy(r->state, state);
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
    r->distance = malloc(strlen(distance) * sizeof(distance));
    strcpy(r->distance, distance);
}

void set_ride_score_user(Ride r, char *score_user)
{
    r->score_user = malloc(strlen(score_user) * sizeof(score_user));
    strcpy(r->score_user, score_user);
}

void set_ride_score_driver(Ride r, char *score_driver)
{
    r->score_driver = malloc(strlen(score_driver) * sizeof(score_driver));
    strcpy(r->score_driver, score_driver);
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

char *get_ride_id(Ride r) { return strdup(r->id); }

char *get_ride_state(Ride r) { return strdup(r->state); }

char *get_ride_driver(Ride r) { return strdup(r->driver); }

char *get_ride_user(Ride r) { return strdup(r->user); }

char *get_ride_city(Ride r) { return strdup(r->city); }

char *get_ride_distance(Ride r) { return strdup(r->distance); }

char *get_ride_score_user(Ride r) { return strdup(r->score_user); }

char *get_ride_score_driver(Ride r) { return strdup(r->score_driver); }

char *get_ride_tip(Ride r) { return strdup(r->tip); }

char *get_ride_comment(Ride r) { return strdup(r->comment); }
