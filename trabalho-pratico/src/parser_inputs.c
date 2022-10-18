#include "parser_inputs.h"
#include "config.h"
#include <glib.h>
#include <stdio.h>
#include <string.h>

Catalog *parse_inputs(Inputs *input)
{
    GSList *users = parse_users(input->file_users);
    GSList *drivers = parse_drivers(input->file_drivers);
    GSList *rides = parse_rides(input->file_rides);

    Catalog *catalog = g_new(Catalog, 1);

    catalog->users = users;
    catalog->drivers = drivers;
    catalog->rides = rides;

    return catalog;
}

GSList *parse_users(FILE *fu)
{
    char *record = NULL;
    size_t len = 0;
    char *buff = NULL;
    GSList *users = NULL;

    getline(&record, &len, fu); // Remove header

    while (getline(&record, &len, fu) != -1) {
        User *user = g_new(User, 1);
        for (Field_user field = U_username; field <= U_account_status;
             field++) {
            buff = strsep(&record, ";");
            size_t size = strlen(buff) * sizeof(buff);
            switch (field) {
                case U_username:
                    user->username = malloc(size);
                    strcpy(user->username, buff);
                    break;
                case U_name:
                    user->name = malloc(size);
                    strcpy(user->name, buff);
                    break;
                case U_gender:
                    user->gender = malloc(size);
                    strcpy(user->gender, buff);
                    break;
                case U_birth_date:
                    user->birth_date = malloc(size);
                    strcpy(user->birth_date, buff);
                    break;
                case U_account_creation:
                    user->account_creation = malloc(size);
                    strcpy(user->account_creation, buff);
                    break;
                case U_pay_method:
                    user->pay_method = malloc(size);
                    strcpy(user->pay_method, buff);
                    break;
                case U_account_status:
                    user->account_status = malloc(size);
                    strcpy(user->account_status, buff);
                    break;
            }
        }

        users = g_slist_prepend(users, user);
    }

    free(record);

    return users;
}

GSList *parse_drivers(FILE *fd)
{
    char *record = NULL;
    size_t len = 0;
    char *buff = NULL;
    GSList *drivers = NULL;

    getline(&record, &len, fd); // Remove header

    while (getline(&record, &len, fd) != -1) {
        Driver *driver = g_new(Driver, 1);
        for (Field_driver field = D_id; field <= D_account_status; field++) {
            buff = strsep(&record, ";");
            size_t size = strlen(buff) * sizeof(buff);
            switch (field) {
                case D_id:
                    driver->id = malloc(size);
                    strcpy(driver->id, buff);
                    break;
                case D_name:
                    driver->name = malloc(size);
                    strcpy(driver->name, buff);
                    break;
                case D_birth_date:
                    driver->birth_date = malloc(size);
                    strcpy(driver->birth_date, buff);
                    break;
                case D_gender:
                    driver->gender = malloc(size);
                    strcpy(driver->gender, buff);
                    break;
                case D_car_class:
                    driver->car_class = malloc(size);
                    strcpy(driver->car_class, buff);
                    break;
                case D_license_plate:
                    driver->license_plate = malloc(size);
                    strcpy(driver->license_plate, buff);
                    break;
                case D_city:
                    driver->city = malloc(size);
                    strcpy(driver->city, buff);
                    break;
                case D_account_creation:
                    driver->account_creation = malloc(size);
                    strcpy(driver->account_creation, buff);
                    break;
                case D_account_status:
                    driver->account_status = malloc(size);
                    strcpy(driver->account_status, buff);
                    break;
            }
        }

        drivers = g_slist_prepend(drivers, driver);
    }

    free(record);

    return drivers;
}

GSList *parse_rides(FILE *fr)
{
    char *record = NULL;
    size_t len = 0;
    char *buff = NULL;
    GSList *rides = NULL;

    getline(&record, &len, fr); // Remove header

    while (getline(&record, &len, fr) != -1) {
        Ride *ride = g_new(Ride, 1);
        for (Field_ride field = R_id; field <= R_comment; field++) {
            buff = strsep(&record, ";");
            size_t size = strlen(buff) * sizeof(buff);
            switch (field) {
                case R_id:
                    ride->id = malloc(size);
                    strcpy(ride->id, buff);
                    break;
                case R_state:
                    ride->state = malloc(size);
                    strcpy(ride->state, buff);
                    break;
                case R_driver:
                    ride->driver = malloc(size);
                    strcpy(ride->driver, buff);
                    break;
                case R_user:
                    ride->user = malloc(size);
                    strcpy(ride->user, buff);
                    break;
                case R_city:
                    ride->city = malloc(size);
                    strcpy(ride->city, buff);
                    break;
                case R_distance:
                    ride->distance = malloc(size);
                    strcpy(ride->distance, buff);
                    break;
                case R_score_user:
                    ride->score_user = malloc(size);
                    strcpy(ride->score_user, buff);
                    break;
                case R_score_driver:
                    ride->score_driver = malloc(size);
                    strcpy(ride->score_driver, buff);
                    break;
                case R_tip:
                    ride->tip = malloc(size);
                    strcpy(ride->tip, buff);
                    break;
                case R_comment:
                    ride->comment = malloc(size);
                    strcpy(ride->comment, buff);
                    break;
            }
        }

        rides = g_slist_prepend(rides, ride);
    }

    free(record);

    return rides;
}
