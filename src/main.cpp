#include <Arduino.h>
#include "TempSensor.h"
#include "RtcCom.h"
#include "TouchSync.h"
#include "OLedOut.h"

void setup() 
{
    // Watch out, if using PIO you need to specify monitor_speed in platform.io file
    Serial.begin(115200);
    Serial.println("--------- Setup Starting ---------");

    // Setup auxiliary Wire/I2C inteface to free up the main bus
    if (!Wire1.begin(18, 19))
    {
        // Well shit, no project lmao
        Serial.println("Failed to setup Wire1! No OLED!");
    }
    else
    {
        if (!daelus_oled_setup())
        {
            // Well shit, no project lmao
            Serial.println("Failed to setup OLED!");
        }
    }
    daelus_sensor_setup();
    if (!daelus_rtc_setup())
    {
        // We are truly fucked, time is the main part of the display
        Serial.println("Failed to setup RTC!");
    }
    Serial.println("---------   Setup Done   ---------");
}

void loop() 
{
    // Sensor data variables
    float tmp, hum;
    if (daelus_sensor_readTemp(&tmp) && daelus_sensor_readHum(&hum)) 
    {  
        // Heat index calculation is fucked, don't use it
        // UPDATE: Too late lol, at least I didn't write it out to the OLED (not enough space; 1 inch issue kek)
        Serial.printf("%.2f°C - %.2f%% (%.2f°C)\n", tmp, hum, daelus_sensor_computeHI(tmp, hum));
    }
    else
    {
        Serial.println("Temp read failed!");
    }

    // Time variable
    DateTime dtime;
    if (daelus_rtc_getTime(&dtime)) 
    {  
        Serial.printf("%i:%i:%i - %i.%i.%i\n", dtime.hour(), dtime.minute(), dtime.second(), dtime.day(), dtime.month(), dtime.year());

        // True if we entered tsync and changed time
        if (daelus_tsync_tick(&dtime))
        {
            // Synchronize RTC module's time
            daelus_rtc_setTime(dtime);
        }
    }
    else
    {
        Serial.println("Time read failed!");
    }

    // Specify data we want to send to the OLED
    daelus_oled_data data = {
        .hour = dtime.hour(),
        .minute = dtime.minute(),
        .temp = tmp,
        .hum = hum,
        .state = dae_oled_clock,
        // Blink only on odd seconds
        .blink = (dtime.second() % 2) != 0
    };

    // Send the data to the OLED
    if (!daelus_oled_draw(data))
    {
        Serial.println("Failed to print to oled!");
    }

    // Wait half second instead of a second to have better clock seconds accuracy
    delay(500);
}