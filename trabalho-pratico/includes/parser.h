#ifndef __PARSER_H__
#define __PARSER_H__

#include <glib.h>
#include <stdio.h>

GSList *parse_drivers(FILE *fd, GSList *drivers);

#endif

