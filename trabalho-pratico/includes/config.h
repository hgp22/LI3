#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <glib.h>

typedef struct user {
    char *username;
    char *name;
    char *gender;
    char *birth_date;
    char *account_creation;
    char *pay_method;
    char *account_status;
} User;

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

typedef struct ride {
    char *id;
    char *state;
    char *driver;
    char *user;
    char *city;
    char *distance;
    char *score_user;
    char *score_driver;
    char *tip;
    char *comment;
} Ride;

typedef enum field_user {
    U_username,
    U_name,
    U_gender,
    U_birth_date,
    U_account_creation,
    U_pay_method,
    U_account_status,
} Field_user;

typedef enum field_driver {
    D_id,
    D_name,
    D_birth_date,
    D_gender,
    D_car_class,
    D_license_plate,
    D_city,
    D_account_creation,
    D_account_status,
} Field_driver;

typedef enum field_ride {
    R_id,
    R_state,
    R_driver,
    R_user,
    R_city,
    R_distance,
    R_score_user,
    R_score_driver,
    R_tip,
    R_comment,
} Field_ride;

typedef struct catalog {
    GSList *users;
    GSList *drivers;
    GSList *rides;
} Catalog;

#endif
