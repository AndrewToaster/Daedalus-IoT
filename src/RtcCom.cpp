#include "RtcCom.h"

// Variable to hold whether or not we setup the I2C interface
static bool is_setup = false; 

// RTC module I2C interface
static RTC_DS3231 rtc = RTC_DS3231();

bool daelus_rtc_setup()
{
    if (!is_setup)
    {
        if (!rtc.begin())
        {
            return false;
        }
        is_setup = true;
    }

    return true;
}

bool daelus_rtc_getTime(DateTime* result)
{
    if (!is_setup) { return false; }
    // This shit coulnd't get easier I swear
    *result = rtc.now();
    return true;
}

bool daelus_rtc_setTime(DateTime time)
{
    if (!is_setup) { return false; }
    // This shit coulnd't get easier I swear
    rtc.adjust(time);
    return true;
}