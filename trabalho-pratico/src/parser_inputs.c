#include "user.h"
#include "driver.h"
#include "ride.h"
#include "users.h"
#include "drivers.h"
#include "rides.h"
#include "parser_inputs.h"
#include <glib.h>
#include <stdio.h>
#include <string.h>

Catalog *parse_inputs(Inputs *input)
{
    Catalog *catalog = g_new(Catalog, 1);

    catalog->users = parse_users(input->file_users);
    catalog->drivers = parse_drivers(input->file_drivers);
    catalog->rides = parse_rides(input->file_rides);

    return catalog;
}

Users *parse_users(FILE *fu)
{
    char *record = NULL;
    size_t len = 0;
    char *buff = NULL;
    Users *users = NULL;

    getline(&record, &len, fu); // Remove header

    while (getline(&record, &len, fu) != -1) {
        User *user = init_user();
        for (Field_user field = U_username; field <= U_account_status; field++) {
            buff = strsep(&record, ";");
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
                    set_user_birth_date(user, buff);
                    break;
                case U_account_creation:
                    set_user_account_creation(user, buff);
                    break;
                case U_pay_method:
                    set_user_pay_method(user, buff);
                    break;
                case U_account_status:
                    set_user_account_status(user, buff);
                    break;
                default:
                    break;
            }
        }

        users = insert_user(users, user);
    }

    free(record);

    return users;
}

Drivers *parse_drivers(FILE *fd)
{
    char *record = NULL;
    size_t len = 0;
    char *buff = NULL;
    Drivers *drivers = NULL;

    getline(&record, &len, fd); // Remove header

    while (getline(&record, &len, fd) != -1) {
        Driver *driver = init_driver();
        for (Field_driver field = D_id; field <= D_account_status; field++) {
            buff = strsep(&record, ";");
            switch (field) {
                case D_id:
                    set_driver_id(driver, buff);
                    break;
                case D_name:
                    set_driver_name(driver, buff);
                    break;
                case D_birth_date:
                    set_driver_birth_date(driver, buff);
                    break;
                case D_gender:
                    set_driver_gender(driver, buff);
                    break;
                case D_car_class:
                    set_driver_car_class(driver, buff);
                    break;
                case D_license_plate:
                    set_driver_license_plate(driver, buff);
                    break;
                case D_city:
                    set_driver_city(driver, buff);
                    break;
                case D_account_creation:
                    set_driver_account_creation(driver, buff);
                    break;
                case D_account_status:
                    set_driver_account_status(driver, buff);
                    break;
            }
        }

        drivers = insert_driver(drivers, driver);
    }

    free(record);

    return drivers;
}

Rides *parse_rides(FILE *fr)
{
    char *record = NULL;
    size_t len = 0;
    char *buff = NULL;
    Rides *rides = NULL;

    getline(&record, &len, fr); // Remove header

    while (getline(&record, &len, fr) != -1) {
        Ride *ride = init_ride();
        for (Field_ride field = R_id; field <= R_comment; field++) {
            buff = strsep(&record, ";");
            switch (field) {
                case R_id:
                    set_ride_id(ride, buff);
                    break;
                case R_state:
                    set_ride_state(ride, buff);
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
                    set_ride_comment(ride, buff);
                    break;
            }
        }

        rides = insert_ride(rides, ride);
    }

    free(record);

    return rides;
}
