#ifndef __DRIVER_H__
#define __DRIVER_H__

#include <glib.h>
#include <stdbool.h>

typedef struct driver *Driver;

typedef enum __attribute__((__packed__)) car_class {
    Basic,
    Green,
    Premium,
} CarClass;

/**
 * @brief Create new Driver
 *
 * @return Driver created
 */
Driver driver_new(void);

/**
 * @brief
 *
 * @param driver_record
 * @return Driver
 */
Driver driver_new_from_record(const char *driver_record);

/**
 * @brief Frees GHashTable *
 *
 * @param cs GHashTable * to be freed
 */
void driver_free_cities_score(GHashTable *cs);

/**
 * @brief Set the driver id object
 *
 * @param d
 * @param id
 */
void driver_set_id(const Driver d, const char *id);

/**
 * @brief Set the driver name object
 *
 * @param d
 * @param name
 */
void driver_set_name(const Driver d, const char *name);

/**
 * @brief Set the driver gend object
 *
 * @param d
 * @param gender
 */
void driver_set_gender(const Driver d, const char *gender);

/**
 * @brief Set the driver age object
 *
 * @param d
 * @param birth_date
 */
void driver_set_age(const Driver d, const char *birth_date);

/**
 * @brief Set the driver car class object
 *
 * @param d
 * @param car_class
 */
void driver_set_car_class(const Driver d, const char *car_class);

/**
 * @brief Set the driver account age object
 *
 * @param d
 * @param account_creation
 */
void driver_set_account_age(const Driver d, const char *account_creation);

/**
 * @brief Set the driver account status object
 *
 * @param d
 * @param account_status
 */
void driver_set_account_status(const Driver d, const char *account_status);

/**
 * @brief Get the driver id object
 *
 * @param d
 * @return int
 */
int driver_get_id(const Driver d);

/**
 * @brief Get the driver name object
 *
 * @param d
 * @return char*
 */
char *driver_get_name(const Driver d);

/**
 * @brief Get the driver gender object
 *
 * @param d
 * @return char
 */
char driver_get_gender(const Driver d);

/**
 * @brief Get the driver age object
 *
 * @param d
 * @return guint8
 */
guint8 driver_get_age(const Driver d);

/**
 * @brief Get the driver car class object
 *
 * @param d
 * @return CarClass
 */
CarClass driver_get_car_class(const Driver d);

/**
 * @brief Get the driver account age object
 *
 * @param d
 * @return guint16
 */
guint16 driver_get_account_age(const Driver d);

/**
 * @brief Get the driver account status object
 *
 * @param d
 * @return DStatus
 */
bool driver_is_account_active(const Driver d);

/**
 * @brief Get the driver avg score object
 *
 * @param d
 * @return double
 */
double driver_get_avg_score(const Driver d);

/**
 * @brief Get the driver total earned object
 *
 * @param d
 * @return double
 */
double driver_get_total_earned(const Driver d);

/**
 * @brief Get the driver n trips object
 *
 * @param d
 * @return guint16
 */
guint16 driver_get_n_trips(const Driver d);

/**
 * @brief Get the driver last ride date object
 *
 * @param d
 * @return guint16
 */
guint16 driver_get_last_ride_date(const Driver d);

/**
 * @brief Get cities scores from driver
 *
 * @param d Driver
 * @return Cities Scores
 */
GHashTable *driver_get_cities_score(const Driver d);

/**
 * @brief Get driver city score
 *
 * @param d Driver
 * @param city City
 * @return City score
 */
double driver_get_city_score(const Driver d, const char *city);

/**
 * @brief Add a ride's data in a driver
 *
 * @param d
 * @param score
 * @param cost
 * @param tip
 * @param date
 * @param city_name
 */
void driver_add_ride_data(const Driver d, guint8 score, double cost,
                          guint16 date, const char *city_name);

/**
 * @brief Copy driver
 *
 * @param old_d Driver to be copied
 * @return Driver copy
 */
Driver driver_copy(const Driver old_d);

/**
 * @brief Frees Driver
 *
 * @param driver Driver to be freed
 */
void driver_free(void *driver);

#endif
