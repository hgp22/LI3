#include "catalog.h" 
#include <glib.h>

void free_catalog(Catalog *catalog)
{
    g_slist_free_full(catalog->users, free_user);
    g_slist_free_full(catalog->drivers, free_driver);
    g_slist_free_full(catalog->rides, free_ride);
    free(catalog);
}

void free_user(void *user)
{
    User *u = (User *)user;
    free(u->username);
    free(u->name);
    free(u->gender);
    free(u->birth_date);
    free(u->account_creation);
    free(u->pay_method);
    free(u->account_status);
    free(user);
}

void free_driver(void *driver)
{
    Driver *d = (Driver *)driver;
    free(d->id);
    free(d->name);
    free(d->birth_date);
    free(d->gender);
    free(d->car_class);
    free(d->license_plate);
    free(d->city);
    free(d->account_creation);
    free(d->account_status);
    free(driver);
}

void free_ride(void *ride)
{
    Ride *r = (Ride *)ride;
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
