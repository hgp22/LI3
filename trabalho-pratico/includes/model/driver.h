#ifndef __DRIVER_H__
#define __DRIVER_H__

#include <glib.h>
#include <stdint.h>

typedef struct ride *Ride;
typedef struct driver *Driver;
typedef GHashTable *CitiesScore;
typedef struct city_score *CityScore;

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

typedef enum d_account_status {
    D_Inactive,
    D_Active,
} D_Status;

/**
 * @brief Create new Driver
 *
 * @return Driver created
 */
Driver driver_new(void);

/**
 * @brief Frees Driver
 *
 * @param driver Driver to be freed
 */
void driver_free(void *driver);

/**
 * @brief Frees CitiesScore
 *
 * @param cs CitiesScore to be freed
 */
void driver_free_cities_score(CitiesScore cs);

/**
 * @brief Set the driver id object
 *
 * @param d
 * @param id
 */
void driver_set_id(Driver d, char *id);

/**
 * @brief Set the driver name object
 *
 * @param d
 * @param name
 */
void driver_set_name(Driver d, char *name);

/**
 * @brief Set the driver gend object
 *
 * @param d
 * @param gender
 */
void driver_set_gender(Driver d, char *gender);

/**
 * @brief Set the driver age object
 *
 * @param d
 * @param birth_date
 */
void driver_set_age(Driver d, char *birth_date);

/**
 * @brief Set the driver car class object
 *
 * @param d
 * @param car_class
 */
void driver_set_car_class(Driver d, char *car_class);

/**
 * @brief Set the driver account age object
 *
 * @param d
 * @param account_creation
 */
void driver_set_account_age(Driver d, char *account_creation);

/**
 * @brief Set the driver account status object
 *
 * @param d
 * @param account_status
 */
void driver_set_account_status(Driver d, char *account_status);

/**
 * @brief Get the driver id object
 *
 * @param d
 * @return long
 */
long driver_get_id(Driver d);

/**
 * @brief Get the driver name object
 *
 * @param d
 * @return char*
 */
char *driver_get_name(Driver d);

/**
 * @brief Get the driver gender object
 *
 * @param d
 * @return char
 */
char driver_get_gender(Driver d);

/**
 * @brief Get the driver age object
 *
 * @param d
 * @return uint8_t
 */
uint8_t driver_get_age(Driver d);

/**
 * @brief Get the driver car class object
 *
 * @param d
 * @return Car_Class
 */
Car_Class driver_get_car_class(Driver d);

/**
 * @brief Get the driver account age object
 *
 * @param d
 * @return uint8_t
 */
uint8_t driver_get_account_age(Driver d);

/**
 * @brief Get the driver account status object
 *
 * @param d
 * @return D_Status
 */
D_Status driver_get_account_status(Driver d);

/**
 * @brief Get the driver avg score object
 *
 * @param d
 * @return double
 */
double driver_get_avg_score(Driver d);

/**
 * @brief Get the driver total earned object
 *
 * @param d
 * @return double
 */
double driver_get_total_earned(Driver d);

/**
 * @brief Get the driver n trips object
 *
 * @param d
 * @return unsigned short
 */
unsigned short driver_get_n_trips(Driver d);

/**
 * @brief Get the driver last ride date object
 *
 * @param d
 * @return unsigned short
 */
unsigned short driver_get_last_ride_date(Driver d);

/**
 * @brief Get cities scores from driver
 *
 * @param d Driver
 * @return Cities Scores
 */
CitiesScore driver_get_cities_score(Driver d);

/**
 * @brief Get driver city score
 *
 * @param d Driver
 * @param city City
 * @return City score
 */
double driver_get_city_score(Driver d, char *city);

/**
 * @brief Get data in a drivers' ride
 *
 * @param d Driver
 * @param r Ride
 */
void driver_add_ride_data(Driver d, Ride r);

/**
 * @brief Copy driver
 *
 * @param old_d Driver to be copied
 * @return Driver copy
 */
Driver driver_copy(Driver old_d);

#endif
