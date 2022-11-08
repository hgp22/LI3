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

int db_load(Catalog c, char *path_inputs)
{
    FILE *file_users = _get_file_pointer(path_inputs, USERS);
    FILE *file_drivers = _get_file_pointer(path_inputs, DRIVERS);
    FILE *file_rides = _get_file_pointer(path_inputs, RIDES);

    catalog_set_users(c, _load_users(file_users));
    catalog_set_drivers(c, _load_drivers(file_drivers));
    catalog_set_rides(c, _load_rides(file_rides));

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
    Users users = users_new();

    getline(&line, &len, fp); // Remove header

    while (getline(&line, &len, fp) != -1) {
        char *record = line;
        User user = user_new();
        for (Field_user field = U_username; field <= U_account_status;
             field++) {
            char *buff = strsep(&record, ";\n");
            switch (field) {
                case U_username:
                    user_set_username(user, buff);
                    break;
                case U_name:
                    user_set_name(user, buff);
                    break;
                case U_gender:
                    user_set_gender(user, buff);
                    break;
                case U_birth_date:
                    user_set_age(user, buff);
                    break;
                case U_account_creation:
                    user_set_account_age(user, buff);
                    break;
                case U_pay_method:
                    break;
                case U_account_status:
                    user_set_account_status(user, buff);
                    break;
                default:
                    break;
            }
        }

        users_add_user(users, user);
    }

    free(line);

    return users;
}

static Drivers _load_drivers(FILE *fp)
{
    char *line = NULL;
    size_t len = 0;
    Drivers drivers = drivers_new();

    getline(&line, &len, fp); // Remove header

    while (getline(&line, &len, fp) != -1) {
        char *record = line;
        Driver driver = driver_new();
        for (Field_driver field = D_id; field <= D_account_status; field++) {
            char *buff = strsep(&record, ";\n");
            switch (field) {
                case D_id:
                    driver_set_id(driver, buff);
                    break;
                case D_name:
                    driver_set_name(driver, buff);
                    break;
                case D_birth_date:
                    driver_set_age(driver, buff);
                    break;
                case D_gender:
                    driver_set_gender(driver, buff);
                    break;
                case D_car_class:
                    driver_set_car_class(driver, buff);
                    break;
                case D_license_plate:
                    break;
                case D_city:
                    break;
                case D_account_creation:
                    driver_set_account_age(driver, buff);
                    break;
                case D_account_status:
                    driver_set_account_status(driver, buff);
                    break;
                default:
                    break;
            }
        }

        drivers_add_driver(drivers, driver);
    }

    free(line);

    return drivers;
}

static Rides _load_rides(FILE *fp)
{
    char *line = NULL;
    size_t len = 0;
    Rides rides = rides_new();

    getline(&line, &len, fp); // Remove header

    while (getline(&line, &len, fp) != -1) {
        char *record = line;
        Ride ride = ride_new();
        for (Field_ride field = R_id; field <= R_comment; field++) {
            char *buff = strsep(&record, ";\n");
            switch (field) {
                case R_id:
                    ride_set_id(ride, buff);
                    break;
                case R_date:
                    ride_set_date(ride, buff);
                    break;
                case R_driver:
                    ride_set_driver(ride, buff);
                    break;
                case R_user:
                    ride_set_user(ride, buff);
                    break;
                case R_city:
                    ride_set_city(ride, buff);
                    break;
                case R_distance:
                    ride_set_distance(ride, buff);
                    break;
                case R_score_user:
                    ride_set_score_user(ride, buff);
                    break;
                case R_score_driver:
                    ride_set_score_driver(ride, buff);
                    break;
                case R_tip:
                    ride_set_tip(ride, buff);
                    break;
                case R_comment:
                    break;
                default:
                    break;
            }
        }

        rides_add_ride(rides, ride);
    }

    free(line);

    return rides;
}
