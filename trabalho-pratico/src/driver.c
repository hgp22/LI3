#include "driver.h"
#include <glib.h>
#include <stdlib.h>
#include <string.h>

struct driver {
    char *id;
    char *name;
    char *birth_date;
    char *gender;
    char *car_class;
    char *license_plate;
    char *city;
    char *account_creation;
    char *account_status;
};

Driver init_driver(void) { return g_new(struct driver, 1); }

void free_driver(void *driver)
{
    Driver d = (Driver)driver;
    free(d->id);
    free(d->name);
    free(d->birth_date);
    free(d->gender);
    free(d->car_class);
    free(d->license_plate);
    free(d->city);
    free(d->account_creation);
    free(d->account_status);
    free(driver);
}

void set_driver_id(Driver d, char *id)
{
    d->id = malloc(strlen(id) * sizeof(id));
    strcpy(d->id, id);
}

void set_driver_name(Driver d, char *name)
{
    d->name = malloc(strlen(name) * sizeof(name));
    strcpy(d->name, name);
}

void set_driver_birth_date(Driver d, char *birth_date)
{
    d->birth_date = malloc(strlen(birth_date) * sizeof(birth_date));
    strcpy(d->birth_date, birth_date);
}

void set_driver_gender(Driver d, char *gender)
{
    d->gender = malloc(strlen(gender) * sizeof(gender));
    strcpy(d->gender, gender);
}

void set_driver_car_class(Driver d, char *car_class)
{
    d->car_class = malloc(strlen(car_class) * sizeof(car_class));
    strcpy(d->car_class, car_class);
}

void set_driver_license_plate(Driver d, char *license_plate)
{
    d->license_plate = malloc(strlen(license_plate) * sizeof(license_plate));
    strcpy(d->license_plate, license_plate);
}

void set_driver_city(Driver d, char *city)
{
    d->city = malloc(strlen(city) * sizeof(city));
    strcpy(d->city, city);
}

void set_driver_account_creation(Driver d, char *account_creation)
{
    d->account_creation =
        malloc(strlen(account_creation) * sizeof(account_creation));
    strcpy(d->account_creation, account_creation);
}

void set_driver_account_status(Driver d, char *account_status)
{
    d->account_status = malloc(strlen(account_status) * sizeof(account_status));
    strcpy(d->account_status, account_status);
}

char *get_driver_id(Driver d) { return strdup(d->id); }

char *get_driver_name(Driver d) { return strdup(d->name); }

char *get_driver_birth_date(Driver d) { return strdup(d->birth_date); }

char *get_driver_gender(Driver d) { return strdup(d->gender); }

char *get_driver_car_class(Driver d) { return strdup(d->car_class); }

char *get_driver_license_plate(Driver d) { return strdup(d->license_plate); }

char *get_driver_city(Driver d) { return strdup(d->city); }

char *get_driver_account_creation(Driver d)
{
    return strdup(d->account_creation);
}

char *get_driver_account_status(Driver d) { return strdup(d->account_status); }
