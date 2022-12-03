#ifndef DAELUS_OLEDOUT_H
#define DAELUS_OLEDOUT_H

// Required for uint8_t
#include <stdint.h>


/**
 * @brief Enum describing in which mode to write out date to the OLED
*/
enum daelus_oled_state {
    
    /*! @brief The normal clock view: Time, Second blink, and Sensor data is written to the OLED */
    dae_oled_clock,

    /*! @brief The time synchronization view: Time and Selection (Hour/Minute underline) is written to the OLED */
    dae_oled_tsync
};

/**
 * @brief Structure holding data to send to the OLED screen
*/
struct daelus_oled_data
{
    /*! @brief The hour of the day to display */
    uint8_t hour;
    
    /*! @brief The minute of the day to display */
    uint8_t minute;
    
    /*! @brief The temperature in celsius to display */
    float temp;
    
    /*! @brief The humidity in percent to display */
    float hum;

    /*! @brief The view/state to use when rendering values to display */
    daelus_oled_state state;
    
    /*! @brief Which number is selected when using time synchronization (false for hour; true for minute) */
    bool tsync_val;
    
    /*! @brief Whether or not to hide the colon indicator (xx:xx) in the clock view */
    bool blink;
};

/**
 * @brief Sets up all the necessary stuff to communicate to the OLED screen
 * @return Whether or not the setup succeeded
*/
bool daelus_oled_setup();

/**
 * @brief Sends draw data to the OLED screen
 * @param data The draw data to send to the OLED screen
 * @return Whether or not the draw succeeded, will be false if not initialized
*/
bool daelus_oled_draw(daelus_oled_data data);

#endif