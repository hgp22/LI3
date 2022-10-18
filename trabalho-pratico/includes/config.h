#ifndef __CONFIG_H__
#define __CONFIG_H__

typedef struct driver {
    char *id;
    char *name;
    char *birth_date;
    char *gender;
    char *car_class;
    char *license_plate;
    char *city;
    char *account_creation;
    char *account_status;
} Driver;

typedef enum field_drivers {
    Id,
    Name,
    Birth_date,
    Gender,
    Car_class,
    License_plate,
    City,
    Account_creation,
    Account_status,
} Field_driver;

#endif
