#ifndef __OUTPUT_H__
#define __OUTOUT_H__

#include <glib.h>
#include <stdbool.h>

typedef struct output *Output;

/**
 * @brief
 *
 * @return Output
 */
Output output_new(void);

/**
 * @brief
 *
 * @param entries
 * @return Output
 */
Output output_build_lines(GPtrArray *entries);

/**
 * @brief
 *
 * @param entries
 * @param sizes
 * @param headers
 * @return Output
 */
Output output_build_table(const GPtrArray *entries, int sizes[],
                          char *headers[]);

/**
 * @brief
 *
 * @param output
 * @return guint
 */
guint output_lines_len(Output output);

/**
 * @brief
 *
 * @param output
 * @return guint
 */
guint output_header_len(Output output);

/**
 * @brief
 *
 * @param output
 * @return true
 * @return false
 */
bool output_has_header(Output output);

/**
 * @brief
 *
 * @param output
 * @param index
 * @return wchar_t*
 */
wchar_t *output_header_index(Output output, guint index);

/**
 * @brief
 *
 * @param output
 * @param index
 * @return wchar_t*
 */
wchar_t *output_lines_index(Output output, guint index);

/**
 * @brief
 *
 * @param output
 */
void output_free(Output output);

#endif
