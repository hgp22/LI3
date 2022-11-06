#include "db.h"
#include "catalog.h"
#include "driver.h"
#include "drivers.h"
#include "ride.h"
#include "rides.h"
#include "user.h"
#include "users.h"
#include <stdio.h>
#include <string.h>

#define USERS "/users.csv"
#define DRIVERS "/drivers.csv"
#define RIDES "/rides.csv"

static FILE *_get_file_pointer(char *path_inputs, char *input_file);
static Users _load_users(FILE *fp);
static Drivers _load_drivers(FILE *fp);
static Rides _load_rides(FILE *fp);

int load_db(Catalog c, char *path_inputs)
{
    FILE *file_users = _get_file_pointer(path_inputs, USERS);
    FILE *file_drivers = _get_file_pointer(path_inputs, DRIVERS);
    FILE *file_rides = _get_file_pointer(path_inputs, RIDES);

    set_catalog_users(c, _load_users(file_users));
    set_catalog_drivers(c, _load_drivers(file_drivers));
    set_catalog_rides(c, _load_rides(file_rides));

    fclose(file_users);
    fclose(file_drivers);
    fclose(file_rides);

    return 0;
}

// ! move fopen out of this funtion and only use to create full path?
static FILE *_get_file_pointer(char *path_inputs, char *input_file)
{
    char *path_file = malloc((strlen(path_inputs) + strlen(input_file) + 1) *
                             sizeof(path_file));
    strcpy(path_file, path_inputs);
    strcat(path_file, input_file);

    FILE *fp = fopen(path_file, "r");
    if (fp == NULL) {
        perror(path_file);
        exit(1);
    }

    free(path_file);

    return fp;
}

static Users _load_users(FILE *fp)
{
    char *line = NULL;
    size_t len = 0;
    Users users = new_users();

    getline(&line, &len, fp); // Remove header

    while (getline(&line, &len, fp) != -1) {
        char *record = line;
        User user = new_user();
        for (Field_user field = U_username; field <= U_account_status;
             field++) {
            char *buff = strsep(&record, ";\n");
            switch (field) {
                case U_username:
                    set_user_username(user, buff);
                    break;
                case U_name:
                    set_user_name(user, buff);
                    break;
                case U_gender:
                    set_user_gender(user, buff);
                    break;
                case U_birth_date:
                    set_user_age(user, buff);
                    break;
                case U_account_creation:
                    set_user_account_age(user, buff);
                    break;
                case U_pay_method:
                    break;
                case U_account_status:
                    set_user_account_status(user, buff);
                    break;
                default:
                    break;
            }
        }

        add_users_user(users, user);
    }

    free(line);

    return users;
}

static Drivers _load_drivers(FILE *fp)
{
    char *line = NULL;
    size_t len = 0;
    Drivers drivers = new_drivers();

    getline(&line, &len, fp); // Remove header

    while (getline(&line, &len, fp) != -1) {
        char *record = line;
        Driver driver = new_driver();
        for (Field_driver field = D_id; field <= D_account_status; field++) {
            char *buff = strsep(&record, ";\n");
            switch (field) {
                case D_id:
                    set_driver_id(driver, buff);
                    break;
                case D_name:
                    set_driver_name(driver, buff);
                    break;
                case D_birth_date:
                    set_driver_age(driver, buff);
                    break;
                case D_gender:
                    set_driver_gender(driver, buff);
                    break;
                case D_car_class:
                    set_driver_car_class(driver, buff);
                    break;
                case D_license_plate:
                    break;
                case D_city:
                    break;
                case D_account_creation:
                    set_driver_account_age(driver, buff);
                    break;
                case D_account_status:
                    set_driver_account_status(driver, buff);
                    break;
                default:
                    break;
            }
        }

        add_drivers_driver(drivers, driver);
    }

    free(line);

    return drivers;
}

static Rides _load_rides(FILE *fp)
{
    char *line = NULL;
    size_t len = 0;
    Rides rides = new_rides();

    getline(&line, &len, fp); // Remove header

    while (getline(&line, &len, fp) != -1) {
        char *record = line;
        Ride ride = new_ride();
        for (Field_ride field = R_id; field <= R_comment; field++) {
            char *buff = strsep(&record, ";\n");
            switch (field) {
                case R_id:
                    set_ride_id(ride, buff);
                    break;
                case R_date:
                    set_ride_date(ride, buff);
                    break;
                case R_driver:
                    set_ride_driver(ride, buff);
                    break;
                case R_user:
                    set_ride_user(ride, buff);
                    break;
                case R_city:
                    set_ride_city(ride, buff);
                    break;
                case R_distance:
                    set_ride_distance(ride, buff);
                    break;
                case R_score_user:
                    set_ride_score_user(ride, buff);
                    break;
                case R_score_driver:
                    set_ride_score_driver(ride, buff);
                    break;
                case R_tip:
                    set_ride_tip(ride, buff);
                    break;
                case R_comment:
                    break;
                default:
                    break;
            }
        }

        add_rides_ride(rides, ride);
    }

    free(line);

    return rides;
}
