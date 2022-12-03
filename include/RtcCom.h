#ifndef DAEDALUS_RTCCOM_H
#define DAEDALUS_RTCCOM_H

// Included here just for the DateTime struct
#include <RTClib.h>

/**
 * @brief Sets up all the necessary stuff to interface with the RTC module
*/
bool daelus_rtc_setup();

/**
 * @brief Read the time from the RTC module
 * @note The day, month, and year are not synchronized directly, so don't be surprised when you see 1.1.2000
 * @param result Pointer to where the time read is saved
 * @return Whether or not the read was successful
*/
bool daelus_rtc_getTime(DateTime* result);

/**
 * @brief Write new time to the RTC module
 * @param time The new time to be written/sychronized to the RTC module
 * @return Whether or not the write was successful
*/
bool daelus_rtc_setTime(DateTime time);

#endif