#include "utils.h"
#include <glib.h>

// substitute with pre-defined glib function
static gint compare_trips(gconstpointer a, gconstpointer b)
{
    // unsigned short date_a = (unsigned short)a;
    // unsigned short date_b = (unsigned short)b;
    // return date_b - date_a;
    return b - a;
}