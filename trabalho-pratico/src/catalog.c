#include "catalog.h"
#include "driver.h"
#include "drivers.h"
#include "ride.h"
#include "rides.h"
#include "user.h"
#include "users.h"
#include <glib.h>

struct catalog {
    Users users;
    Drivers drivers;
    Rides rides;
};

Catalog init_catalog(void)
{
    return g_new(struct catalog, 1);
}

void free_catalog(Catalog c)
{
    g_slist_free_full(c->users, free_user);
    g_slist_free_full(c->drivers, free_driver);
    g_slist_free_full(c->rides, free_ride);
    free(c);
}

void set_catalog_users(Catalog c, Users users)
{
    c->users = users;
}

void set_catalog_drivers(Catalog c, Drivers drivers)
{
    c->drivers = drivers;
}

void set_catalog_rides(Catalog c, Rides rides)
{
    c->rides = rides;
}

Users get_catalog_users(Catalog c)
{
    return c->users;
}

Drivers get_catalog_drivers(Catalog c)
{
    return c->drivers;
}

Rides get_catalog_rides(Catalog c)
{
    return c->rides;
}
