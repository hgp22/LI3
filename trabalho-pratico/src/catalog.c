#include "catalog.h"
#include "user.h"
#include "driver.h"
#include "ride.h"
#include <glib.h>

void free_catalog(Catalog *catalog)
{
    g_slist_free_full(catalog->users, free_user);
    g_slist_free_full(catalog->drivers, free_driver);
    g_slist_free_full(catalog->rides, free_ride);
    free(catalog);
}
