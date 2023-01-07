#ifndef __VALIDATION_H__
#define __VALIDATION_H__

#include <stdbool.h>

/**
 * @brief
 *
 */
void compile_regex(void);

/**
 * @brief
 *
 */
void free_regex(void);

/**
 * @brief
 *
 * @param date
 * @return true
 * @return false
 */
bool validate_date(const char *date);

/**
 * @brief
 *
 * @param car_class
 * @return true
 * @return false
 */
bool validate_car_class(const char *car_class);

/**
 * @brief
 *
 * @param account_status
 * @return true
 * @return false
 */
bool validate_account_status(const char *account_status);

/**
 * @brief 
 * 
 * @param natural 
 * @return true 
 * @return false 
 */
bool validate_natural(const char *natural);

#endif
