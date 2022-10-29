#ifndef __DRIVER_H__
#define __DRIVER_H__

#include <glib.h>
#include <stdint.h>

typedef struct driver *Driver;

typedef struct ride *Ride;

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

typedef enum car_class {
    Basic,
    Green,
    Premium,
} Car_Class;

typedef enum account_status Status;

/**
 * @brief
 *
 * @return Driver
 */
Driver new_driver(void);

/**
 * @brief
 *
 * @param driver
 */
void free_driver(void *driver);

/**
 * @brief Set the driver id object
 *
 * @param d
 * @param id
 */
void set_driver_id(Driver d, char *id);

/**
 * @brief Set the driver name object
 *
 * @param d
 * @param name
 */
void set_driver_name(Driver d, char *name);

/**
 * @brief Set the driver gend object
 *
 * @param d
 * @param gender
 */
void set_driver_gender(Driver d, char *gender);

/**
 * @brief Set the driver age object
 *
 * @param d
 * @param birth_date
 */
void set_driver_age(Driver d, char *birth_date);

/**
 * @brief Set the driver car class object
 *
 * @param d
 * @param car_class
 */
void set_driver_car_class(Driver d, char *car_class);

/**
 * @brief Set the driver account age object
 *
 * @param d
 * @param account_creation
 */
void set_driver_account_age(Driver d, char *account_creation);

/**
 * @brief Set the driver account status object
 *
 * @param d
 * @param account_status
 */
void set_driver_account_status(Driver d, char *account_status);

/**
 * @brief Get the driver id object
 *
 * @param d
 * @return long
 */
long get_driver_id(Driver d);

/**
 * @brief Get the driver name object
 *
 * @param d
 * @return char*
 */
char *get_driver_name(Driver d);

/**
 * @brief Get the driver gender object
 *
 * @param d
 * @return char
 */
char get_driver_gender(Driver d);

/**
 * @brief Get the driver age object
 *
 * @param d
 * @return uint8_t
 */
uint8_t get_driver_age(Driver d);

/**
 * @brief Get the driver car class object
 *
 * @param d
 * @return Car_Class
 */
Car_Class get_driver_car_class(Driver d);

/**
 * @brief Get the driver account age object
 *
 * @param d
 * @return unsigned short
 */
unsigned short get_driver_account_age(Driver d);

/**
 * @brief Get the driver account status object
 *
 * @param d
 * @return Status
 */
Status get_driver_account_status(Driver d);

/**
 * @brief Get the driver avg score object
 *
 * @param d
 * @return float
 */
float get_driver_avg_score(Driver d);

/**
 * @brief Get the driver total earned object
 *
 * @param d
 * @return float
 */
float get_driver_total_earned(Driver d);

/**
 * @brief Get the driver n trips object
 *
 * @param d
 * @return unsigned short
 */
unsigned short get_driver_n_trips(Driver d);

/**
 * @brief Get the driver trip dates object
 *
 * @param d
 * @return GSList*
 */
GSList *get_driver_trip_dates(Driver d);

/**
 * @brief
 *
 * @param d
 * @param r
 */
void add_driver_ride_data(Driver d, Ride r);

#endif
