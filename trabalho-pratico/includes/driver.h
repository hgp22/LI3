#ifndef __DRIVER_H__
#define __DRIVER_H__

typedef struct driver *Driver;

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

/**
 * @brief
 *
 * @return Driver
 */
Driver init_driver(void);

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
 * @brief Set the driver birth date object
 *
 * @param d
 * @param birth_date
 */
void set_driver_birth_date(Driver d, char *birth_date);

/**
 * @brief Set the driver gend object
 *
 * @param d
 * @param gender
 */
void set_driver_gender(Driver d, char *gender);

/**
 * @brief Set the driver car class object
 *
 * @param d
 * @param car_class
 */
void set_driver_car_class(Driver d, char *car_class);

/**
 * @brief Set the driver license plate object
 *
 * @param d
 * @param license_plate
 */
void set_driver_license_plate(Driver d, char *license_plate);

/**
 * @brief Set the driver city object
 *
 * @param d
 * @param city
 */
void set_driver_city(Driver d, char *city);

/**
 * @brief Set the driver account creation object
 *
 * @param d
 * @param account_creation
 */
void set_driver_account_creation(Driver d, char *account_creation);

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
 * @return char*
 */
char *get_driver_id(Driver d);

/**
 * @brief Get the driver name object
 *
 * @param d
 * @return char*
 */
char *get_driver_name(Driver d);

/**
 * @brief Get the driver birth date object
 *
 * @param d
 * @return char*
 */
char *get_driver_birth_date(Driver d);

/**
 * @brief Get the driver gender object
 *
 * @param d
 * @return char*
 */
char *get_driver_gender(Driver d);

/**
 * @brief Get the driver car class object
 *
 * @param d
 * @return char*
 */
char *get_driver_car_class(Driver d);

/**
 * @brief Get the driver license plate object
 *
 * @param d
 * @return char*
 */
char *get_driver_license_plate(Driver d);

/**
 * @brief Get the driver city object
 *
 * @param d
 * @return char*
 */
char *get_driver_city(Driver d);

/**
 * @brief Get the driver account creation object
 *
 * @param d
 * @return char*
 */
char *get_driver_account_creation(Driver d);

/**
 * @brief Get the driver account status object
 *
 * @param d
 * @return char*
 */
char *get_driver_account_status(Driver d);

#endif
