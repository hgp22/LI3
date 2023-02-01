#include "tui.h"
#include "output.h"
#include <ctype.h>
#include <curses.h>
#include <glib.h>
#include <locale.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>

#define BUFFER 128

struct tui {
    WINDOW *console;
    WINDOW *display;
    WINDOW *display_border;
    WINDOW *userhost;
    WINDOW *dataset;
    int display_height;
    int display_width;
};

TUI tui_start(void)
{
    setlocale(LC_ALL, "en_US.UTF-8");
    initscr();
    cbreak();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();

    TUI tui = malloc(sizeof(struct tui));

    tui->console = newwin(1, COLS, LINES - 1, 0);
    keypad(tui->console, TRUE);

    tui->display_border = newwin(LINES - 2, COLS, 1, 0);
    tui->display = newwin(LINES - 4, COLS - 2, 2, 1);
    tui->display_height = LINES - 4;
    tui->display_width = COLS - 2;

    char *user = getlogin();
    char host[BUFFER];
    gethostname(host, BUFFER);
    // char *userhost = malloc(BUFFER * sizeof(*userhost));
    char userhost[BUFFER];
    snprintf(userhost, BUFFER, "%s@%s", user, host);
    int userhost_len = strlen(userhost) + 1;
    tui->userhost = newwin(1, userhost_len, 0, 0);
    waddstr(tui->userhost, userhost);

    tui->dataset = newwin(1, COLS - userhost_len, 0, userhost_len);

    cchar_t VL, HL, TLC, TRC, BLC, BRC;
    setcchar(&VL, L"┃", A_NORMAL, 0, NULL);
    setcchar(&HL, L"━", A_NORMAL, 0, NULL);
    setcchar(&TLC, L"┏", A_NORMAL, 0, NULL);
    setcchar(&TRC, L"┓", A_NORMAL, 0, NULL);
    setcchar(&BLC, L"┗", A_NORMAL, 0, NULL);
    setcchar(&BRC, L"┛", A_NORMAL, 0, NULL);
    wborder_set(tui->display_border, &VL, &VL, &HL, &HL, &TLC, &TRC, &BLC,
                &BRC);

    int greet_lines = 7;
    char *greet[] = {
        "Taxi System",
        "",
        "version 1.0",
        "by Group 59",
        "",
        "type :q<Enter>            to exit ",
        "type :help<Enter> or <F1> for help",
    };

    int greet_top = tui->display_height / 2 - greet_lines / 2;
    int cols_center = tui->display_width / 2;

    for (int i = 0; i < greet_lines; i++) {
        mvwaddstr(tui->display, greet_top + i,
                  cols_center - strlen(greet[i]) / 2, greet[i]);
    }

    wrefresh(tui->console);
    wrefresh(tui->display_border);
    wrefresh(tui->display);
    wrefresh(tui->userhost);

    return tui;
}

void tui_end(TUI tui)
{
    delwin(tui->console);
    delwin(tui->display);
    delwin(tui->display_border);
    delwin(tui->userhost);
    delwin(tui->dataset);
    curs_set(1);
    endwin();
    free(tui);
}

int tui_display_height(TUI tui)
{
    return tui->display_height;
}

int tui_display_width(TUI tui)
{
    return tui->display_width;
}

int tui_get_command(TUI tui)
{
    return wgetch(tui->console);
}

char *tui_input(TUI tui)
{
    werase(tui->console);
    mvwaddstr(tui->console, 0, 0, ":");
    wrefresh(tui->console);
    curs_set(1);
    echo();
    char *str = malloc(BUFFER);
    wgetstr(tui->console, str);
    noecho();
    curs_set(0);
    tui_clear_console(tui);
    return str;
}

void tui_print_display(TUI tui, char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    vw_printw(tui->display, format, ap);
    wrefresh(tui->display);

    va_end(ap);
}

void tui_print_console(TUI tui, char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    tui_clear_console(tui);
    vw_printw(tui->console, format, ap);
    wrefresh(tui->console);

    va_end(ap);
}

void tui_display_output(TUI tui, Output output, int scroll)
{
    if (output == NULL) {
        return;
    }

    werase(tui->display);
    wmove(tui->display, 0, 0);

    if (output_has_header(output)) {
        for (guint i = 0; i < output_header_len(output); i++) {
            waddnwstr(tui->display, output_header_index(output, i),
                      tui_display_width(tui));
        }
    }

    guint bottom = scroll + tui->display_height - output_header_len(output);
    for (guint i = scroll; i < output_lines_len(output) && i < bottom; i++) {
        waddnwstr(tui->display, output_lines_index(output, i),
                  tui_display_width(tui));
    }

    wrefresh(tui->display);
}

void tui_clear_display(TUI tui)
{
    werase(tui->display);
    wmove(tui->display, 0, 0);
    wrefresh(tui->display);
}

void tui_clear_console(TUI tui)
{
    werase(tui->console);
    wmove(tui->console, 0, 0);
    wrefresh(tui->console);
}

void tui_update_dataset(TUI tui, char *dataset)
{
    werase(tui->dataset);
    wmove(tui->dataset, 0, 0);
    char full_path[PATH_MAX];
    realpath(dataset, full_path);
    waddstr(tui->dataset, full_path);
    wrefresh(tui->dataset);
}
