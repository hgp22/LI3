#ifndef __PARSER_QUERY_H__
#define __PARSER_QUERY_H__

typedef struct catalog *Catalog;

/**
 * @brief
 *
 * @param c
 * @param query
 * @return int
 */
int parse_query(Catalog c, char *query);

#endif
