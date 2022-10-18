#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "config.h"
#include "parser.h"

// id;name;birth_day;gender;car_class;license_plate;city;account_creation;account_status
// 000000000001;Luísa Almeida;19/09/1990;F;green;EV-54-07;Setúbal;05/07/2021;active

GSList *parse_drivers(FILE *fd, GSList *drivers) {
    char *record = NULL;
    size_t len = 0;
    char *buff;

    getline(&record, &len, fd); // Remove header

    while (getline(&record, &len, fd) != -1) {
        //Driver *driver = (Driver*)malloc(sizeof(Driver));
        Driver *driver = g_new(Driver, 1);
        for (Field_driver field = D_id; field <= D_account_status; field++) {
            buff = strsep(&record, ";");
            switch (field) {
                case D_id:
                    driver->id = buff;
                    break;
                case D_name:
                    driver->name = buff;
                    break;
                case D_birth_date:
                    driver->birth_date = buff;
                    break;
                case D_gender:
                    driver->gender = buff;
                    break;
                case D_car_class:
                    driver->car_class = buff;
                    break;
                case D_license_plate:
                    driver->license_plate = buff;
                    break;
                case D_city:
                    driver->city = buff;
                    break;
                case D_account_creation:
                    driver->account_creation = buff;
                    break;
                case D_account_status:
                    driver->account_status = buff;
                    break;
            }
        }

        drivers = g_slist_append(drivers, driver);
    }

    free(record);

    return drivers;
}

