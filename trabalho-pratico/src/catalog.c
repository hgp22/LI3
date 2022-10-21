#include "catalog.h"
#include "driver.h"
#include "drivers.h"
#include "ride.h"
#include "rides.h"
#include "user.h"
#include "users.h"
#include <glib.h>

struct catalog {
    GSList *users;
    GSList *drivers;
    GSList *rides;
};

Catalog *init_catalog(void) { return g_new(Catalog, 1); }

void free_catalog(Catalog *catalog)
{
    g_slist_free_full(catalog->users, free_user);
    g_slist_free_full(catalog->drivers, free_driver);
    g_slist_free_full(catalog->rides, free_ride);
    free(catalog);
}

void set_catalog_users(Catalog *c, Users *users) { c->users = users; }

void set_catalog_drivers(Catalog *c, Drivers *drivers) { c->drivers = drivers; }

void set_catalog_rides(Catalog *c, Rides *rides) { c->rides = rides; }

Users *get_catalog_users(Catalog *c) { return c->users; }

Drivers *get_catalog_drivers(Catalog *c) { return c->drivers; }

Rides *get_catalog_rides(Catalog *c) { return c->rides; }
