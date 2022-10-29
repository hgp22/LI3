#include "catalog.h"
#include "driver.h"
#include "drivers.h"
#include "inputs.h"
#include "parser_inputs.h"
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

Catalog init_catalog(Inputs i)
{
    Catalog catalog = g_new(struct catalog, 1);

    catalog->users = parse_users(get_inputs_users(i));
    catalog->drivers = parse_drivers(get_inputs_drivers(i));
    catalog->rides = parse_rides(get_inputs_rides(i));

    return catalog;
}

void free_catalog(Catalog c)
{
    g_hash_table_destroy(c->users);
    g_slist_free_full(c->drivers, free_driver);
    g_slist_free_full(c->rides, free_ride);
    free(c);
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
