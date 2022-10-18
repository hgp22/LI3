#include "parser.h"
#include "parser_inputs.h"
#include "config.h"
#include <glib.h>

GSList *parse_inputs(Inputs *input) {
    GSList *drivers = NULL;

    drivers = parse_drivers(input->file_drivers, drivers);

    return drivers;
}