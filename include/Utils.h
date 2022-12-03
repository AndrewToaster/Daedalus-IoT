#ifndef DAEDALUS_UTILS_H
#define DAEDALUS_UTILS_H

/**
 * @brief Disables unwanted peripherals and other stuff
 * @param enable Whether or not to enable/disable this configuration option
 * @note Even though it says 'bool enable' setting it to true will DISABLE as it enables the configuration option, not enables the peripherals
 * @deprecated Not implemented, will error with symbol not found
*/
void daelus_util_disableUnwanted(bool enable);

/**
 * @brief Reduces the CPU's clock speed to reduce power draw
 * @param enable Whether or not to enable/disable this configuration option
 * @deprecated Not implemented, will error with symbol not found
*/
void daelus_util_reduceClockRate(bool enable);

#endif