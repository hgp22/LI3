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
    Catalog c = g_new(struct catalog, 1);

    c->users = parse_users(get_inputs_users(i));
    c->drivers = parse_drivers(get_inputs_drivers(i));
    c->rides = parse_rides(get_inputs_rides(i));

    for (Rides iterator = c->rides; iterator; iterator = iterator->next) {
        long d_id = get_ride_driver(iterator->data); // ? use gint
        Driver d = g_hash_table_lookup(c->drivers, &d_id);
        set_ride_cost(iterator->data, d);
        add_driver_ride_data(d, iterator->data);
        char *username = get_ride_user(iterator->data);
        User u = g_hash_table_lookup(c->users, username);
        free(username);
        add_user_ride_data(u, iterator->data);
    }

    return c;
}

void free_catalog(Catalog c)
{
    g_hash_table_destroy(c->users);
    g_hash_table_destroy(c->drivers);
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
