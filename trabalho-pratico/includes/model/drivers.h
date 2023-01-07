#ifndef __DRIVERS_H__
#define __DRIVERS_H__

#include <glib.h>
#include <stdbool.h>

typedef struct driver *Driver;
typedef struct drivers *Drivers;

typedef enum car_class CarClass;

/**
 * @brief Creates a new Driver
 *
 * @return Drivers created
 */
Drivers drivers_new(void);

/**
 * @brief
 *
 * @param inputs_path
 * @return Drivers
 */
Drivers drivers_new_from_file(const char *inputs_path);

/**
 * @brief Adds a Driver to Drivers
 *
 * @param drivers Drivers to add Driver
 * @param d Driver to add to Drivers
 * @return Control boolean
 */
gboolean drivers_add_driver(const Drivers drivers, const Driver d);

/**
 * @brief
 *
 * @param drivers
 * @param driver_line
 * @return gboolean
 */
void drivers_add_record(const Drivers drivers, const char *driver_line);

/**
 * @brief Get Driver from Drivers
 *
 * @param drivers Drivers to get Driver from
 * @param id Id to find Driver
 * @return Driver found
 */
Driver drivers_get_driver(const Drivers drivers, int id);

/**
 * @brief
 *
 * @param drivers
 * @param index
 * @return Driver
 */
Driver drivers_get_nth_driver(const Drivers drivers, guint index);

/**
 * @brief
 *
 * @param drivers
 * @return guint
 */
guint drivers_size(const Drivers drivers);

/**
 * @brief
 *
 * @param drivers
 * @param driver_id
 * @param score
 * @param cost
 * @param tip
 * @param date
 * @param city_name
 */
void drivers_add_driver_ride_data(const Drivers drivers, int driver_id,
                                  guint8 score, double cost, guint16 date,
                                  const char *city_name);

/**
 * @brief
 *
 * @param drivers
 * @param driver_id
 * @return char
 */
char drivers_get_driver_gender(const Drivers drivers, int driver_id);

/**
 * @brief
 *
 * @param drivers
 * @param driver_id
 * @return int
 */
CarClass drivers_get_driver_car_class(const Drivers drivers, int driver_id);

/**
 * @brief
 *
 * @param drivers
 * @param driver_id
 * @return guint16
 */
guint16 drivers_get_driver_account_age(const Drivers drivers, int driver_id);

/**
 * @brief
 *
 * @param drivers
 * @param driver_id
 * @return gboolean
 */
bool drivers_is_driver_active(const Drivers drivers, int driver_id);

/**
 * @brief
 *
 * @param drivers
 * @param driver_id
 * @return int
 */
int drivers_has_driver(const Drivers drivers, int driver_id);

/**
 * @brief Remove inactive driver accounts fromo Drivers
 *
 * @param drivers Drivers to remove innactive accounts
 * @return Control integer
 */
guint drivers_remove_inactive_accounts(const Drivers drivers);

/**
 * @brief
 *
 * @param drivers
 * @return Drivers
 */
Drivers drivers_process(const Drivers drivers);

/**
 * @brief Populates drivers' array
 *
 * @param drivers Drivers to populate
 * @return Drivers with array populated
 */
Drivers drivers_list(const Drivers drivers);

/**
 * @brief Returns the top N drivers in drivers
 *
 * @param Drivers drivers
 * @param N Number of drivers
 * @return Top N drivers
 */
GPtrArray *drivers_top_n_drivers(const Drivers drivers, guint N);

/**
 * @brief
 *
 * @param drivers
 * @return Drivers
 */
Drivers drivers_cities(const Drivers drivers);

/**
 * @brief
 *
 * @param drivers
 * @param city
 * @param N
 * @return GPtrArray*
 */
GPtrArray *drivers_top_n_drivers_in_city(const Drivers drivers,
                                         const char *city, guint N);

/**
 * @brief Frees Drivers
 *
 * @param drivers Drivers to be freed
 */
void drivers_free(const Drivers drivers);

#endif
