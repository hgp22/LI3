#include "controller/interactive.h"
#include "driver.h"
#include "output.h"
#include "rides.h"
#include "taxi_system.h"
#include "tui.h"
#include "user.h"
#include "view/interactive.h"
#include <ctype.h>
#include <curses.h>
#include <glib.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define BUFFER 64

static TaxiSystem _load_dataset(TUI tui, TaxiSystem ts, const char *command);
static Output _query1(const TaxiSystem ts, const char *query);
static Output _query2(const TaxiSystem ts, const char *query);
static Output _query3(const TaxiSystem ts, const char *query);
static Output _query4(const TaxiSystem ts, const char *query);
static Output _query5(const TaxiSystem ts, const char *query);
static Output _query6(const TaxiSystem ts, const char *query);
static Output _query7(const TaxiSystem ts, const char *query);
static Output _query8(const TaxiSystem ts, const char *query);
static Output _query9(const TaxiSystem ts, const char *query);

int run_interactive(void)
{
    TUI tui = tui_start();

    TaxiSystem ts = NULL;
    Output output = NULL;

    guint delta = 0;
    guint scroll = 0;
    guint display_height = tui_display_height(tui);

    while (1) {
        switch (tui_get_command(tui)) {
            case ':':
                char *input = tui_input(tui);
                if (isdigit(input[0])) {
                    if (ts == NULL) {
                        tui_print_console(tui, "No dataset loaded");
                        break;
                    }
                    scroll = 0;
                    output_free(output);
                }
                switch (input[0]) {
                    case '\0':
                        // no input, do nothing
                        break;
                    case 'q':
                        free(input);
                        output_free(output);
                        taxi_free(ts);
                        tui_end(tui);
                        return 0;
                    case 'l':
                        ts = _load_dataset(tui, ts, input);
                        break;
                    case 'h':
                        output = interactive_help();
                        break;
                    case '1':
                        output = _query1(ts, input);
                        break;
                    case '2':
                        output = _query2(ts, input);
                        break;
                    case '3':
                        output = _query3(ts, input);
                        break;
                    case '4':
                        output = _query4(ts, input);
                        break;
                    case '5':
                        output = _query5(ts, input);
                        break;
                    case '6':
                        output = _query6(ts, input);
                        break;
                    case '7':
                        output = _query7(ts, input);
                        break;
                    case '8':
                        output = _query8(ts, input);
                        break;
                    case '9':
                        output = _query9(ts, input);
                        break;
                    default:
                        tui_print_console(tui, "Invalid command");
                        break;
                }
                free(input);
                break;
            case 'J':
                guint last_page = output_lines_len(output) +
                                  output_header_len(output) - display_height;
                delta = display_height - output_header_len(output);
                if ((scroll + delta) > last_page) {
                    scroll = last_page;
                }
                else {
                    scroll += delta;
                }
                break;
            case 'K':
                delta = display_height - output_header_len(output);
                if (scroll < delta) {
                    scroll = 0;
                }
                else {
                    scroll -= delta;
                }
                break;
            case 'j':
            case KEY_DOWN:
                if ((scroll + display_height) <
                    output_lines_len(output) + output_header_len(output)) {
                    scroll++;
                }
                break;
            case 'k':
            case KEY_UP:
                if (scroll > 0) {
                    scroll--;
                }
                break;
            case 'g':
                scroll = 0;
                break;
            case 'G':
                scroll = output_lines_len(output) + output_header_len(output) -
                         display_height;
                break;
            default:
                tui_print_console(tui, "Invalid command");
                break;
        }
        tui_display_output(tui, output, scroll);
    }
}

static TaxiSystem _load_dataset(TUI tui, TaxiSystem ts, const char *command)
{
    taxi_free(ts);
    char inputs_path[BUFFER];
    sscanf(command, "%*c %s\n", inputs_path);
    tui_print_console(tui, "Loading dataset from %s", inputs_path);
    ts = taxi_new(inputs_path);
    if (ts != NULL) {
        tui_print_console(tui, "Dataset loaded from %s", inputs_path);
        tui_update_dataset(tui, inputs_path);
    }
    else {
        tui_print_console(tui, "Failed loading dataset from %s", inputs_path);
    }
    return ts;
}

static Output _query1(const TaxiSystem ts, const char *query)
{
    char id[BUFFER];
    sscanf(query, "%*d %s\n", id);
    char *endptr;
    int driver_id = strtol(id, &endptr, 10);
    Output output = NULL;
    if (*endptr != '\0') {
        User user = taxi_get_user(ts, id);
        if (user != NULL) {
            output = interactive_query1_user(user);
        }
        user_free(user);
    }
    else {
        Driver driver = taxi_get_driver(ts, driver_id);
        if (driver != NULL) {
            output = interactive_query1_driver(driver);
        }
        driver_free(driver);
    }
    return output;
}

static Output _query2(const TaxiSystem ts, const char *query)
{
    int N;
    sscanf(query, "%*d %d", &N);
    GPtrArray *drivers = taxi_top_n_drivers_by_score(ts, N);
    Output output = interactive_query2(drivers);
    g_ptr_array_free(drivers, TRUE);
    return output;
}

static Output _query3(const TaxiSystem ts, const char *query)
{
    int N;
    sscanf(query, "%*d %d", &N);
    GPtrArray *users = taxi_top_n_users_by_distance(ts, N);
    Output output = interactive_query3(users);
    g_ptr_array_free(users, TRUE);
    return output;
}

static Output _query4(const TaxiSystem ts, const char *query)
{
    char city[BUFFER];
    sscanf(query, "%*d %s", city);
    double avg_cost = taxi_city_avg_cost(ts, city);
    if (avg_cost > 0) {
        return interactive_query4(avg_cost);
    }
    return NULL;
}

static Output _query5(const TaxiSystem ts, const char *query)
{
    char dateA[BUFFER], dateB[BUFFER];
    sscanf(query, "%*d %s %s", dateA, dateB);
    double avg_cost = taxi_avg_cost_in_range(ts, dateA, dateB);
    if (avg_cost == avg_cost) { // check if avg_cost is NaN
        return interactive_query5(avg_cost);
    }
    return NULL;
}

static Output _query6(const TaxiSystem ts, const char *query)
{
    char city[BUFFER], dateA[BUFFER], dateB[BUFFER];
    sscanf(query, "%*d %s %s %s", city, dateA, dateB);
    double avg_dist = taxi_city_avg_dist_in_range(ts, city, dateA, dateB);
    if (avg_dist > 0) {
        return interactive_query6(avg_dist);
    }
    return NULL;
}

static Output _query7(const TaxiSystem ts, const char *query)
{
    int N;
    char city[BUFFER];
    sscanf(query, "%*d %d %s", &N, city);
    GPtrArray *drivers = taxi_top_n_drivers_in_city(ts, city, N);
    if (drivers != NULL) {
        Output output = interactive_query7(drivers, city);
        g_ptr_array_free(drivers, TRUE);
        return output;
    }
    return NULL;
}

static Output _query8(const TaxiSystem ts, const char *query)
{
    char gender;
    int account_age;
    sscanf(query, "%*d %c %d", &gender, &account_age);
    GPtrArray *rides = taxi_rides_by_gender_by_age(ts, gender, account_age);
    Output output = interactive_query8(rides, ts);
    return output;
    g_ptr_array_free(rides, TRUE);
}

static Output _query9(const TaxiSystem ts, const char *query)
{
    char dateA2[BUFFER];
    char dateB2[BUFFER];
    sscanf(query, "%*d %s %s", dateA2, dateB2);
    GPtrArray *rides = taxi_rides_with_tip_in_range(ts, dateA2, dateB2);
    Output output = interactive_query9(rides);
    g_ptr_array_free(rides, TRUE);
    return output;
}
