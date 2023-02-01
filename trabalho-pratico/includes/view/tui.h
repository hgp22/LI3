#ifndef __TUI_H__
#define __TUI_H__

#include "output.h"
#include <glib.h>

typedef struct tui *TUI;

/**
 * @brief
 *
 * @return TUI
 */
TUI tui_start(void);

/**
 * @brief
 *
 * @param tui
 */
void tui_end(TUI tui);

/**
 * @brief
 *
 * @param tui
 * @return int
 */
int tui_display_height(TUI tui);

/**
 * @brief
 *
 * @param tui
 * @return int
 */
int tui_display_width(TUI tui);

/**
 * @brief
 *
 * @param tui
 * @return int
 */
int tui_get_command(TUI tui);

/**
 * @brief
 *
 * @param tui
 * @return char*
 */
char *tui_input(TUI tui);

/**
 * @brief
 *
 * @param tui
 * @param format
 * @param ...
 */
void tui_print_display(TUI tui, char *format, ...);

/**
 * @brief
 *
 * @param tui
 * @param format
 * @param ...
 */
void tui_print_console(TUI tui, char *format, ...);

/**
 * @brief
 *
 * @param tui
 * @param output
 * @param scroll
 */
void tui_display_output(TUI tui, Output output, int scroll);

/**
 * @brief
 *
 * @param tui
 */
void tui_clear_display(TUI tui);

/**
 * @brief
 *
 * @param tui
 */
void tui_clear_console(TUI tui);

/**
 * @brief
 *
 * @param tui
 * @param dataset
 */
void tui_update_dataset(TUI tui, char *dataset);

#endif
