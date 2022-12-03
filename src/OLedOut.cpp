#include "OLedOut.h"
#include "SSD1306Wire.h"

// I2C oled interface
static SSD1306Wire oled = SSD1306Wire(0x3c, SDA, SCL, GEOMETRY_128_32, I2C_TWO);

// Wheter or not the I2C inteface was setup
static bool is_setup = false;

// Extremely stupid, but works
static String padNumber(uint8_t val)
{
    if (val >= 10)
    {
        return String(val);
    }

    return String("0") + String(val);
}

bool daelus_oled_setup()
{
    if (!is_setup)
    {
        if (!oled.init())
        {
            return false;
        }
        // Turn on pixels when drawing
        oled.setColor(WHITE);
        is_setup = true;
        return true;
    }

    return false;
}

bool daelus_oled_draw(daelus_oled_data data)
{
    if (!is_setup) { return false; }
    oled.clear();

    // Diplay the clock view
    if (data.state == dae_oled_clock)
    {
        // Clock graphic
        oled.setFont(ArialMT_Plain_24);
        oled.setTextAlignment(TEXT_ALIGN_LEFT);
        oled.drawString(0, 2, padNumber(data.hour) + (!data.blink ? ":" : " ") + padNumber(data.minute));

        // Vertical separator
        oled.drawRect(70, 0, 2, 32);
        
        // Temperature and humidity graphic
        oled.setFont(ArialMT_Plain_16);
        oled.setTextAlignment(TEXT_ALIGN_RIGHT);
        oled.drawString(127, 0, String(data.temp, 1U) + "°C");
        oled.drawString(127, 16, String(data.hum, 1U) + "%");
    }
    // Time synchronization view
    else if (data.state == dae_oled_tsync)
    {
        // Clock graphic
        oled.setFont(ArialMT_Plain_24);
        oled.setTextAlignment(TEXT_ALIGN_LEFT);
        oled.drawString(16, 2, padNumber(data.hour) + "   :   " + padNumber(data.minute));

        if (!data.tsync_val)
        {
            // Underline Hour
            oled.drawHorizontalLine(8, 31, 38);
        }
        else
        {
            // Underline Minute
            oled.drawHorizontalLine(84, 31, 38);
        }
        
    }
    
    // Send data through I2C interface
    oled.display();

    return true;
}