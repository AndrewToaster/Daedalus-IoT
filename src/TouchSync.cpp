#include <stdint.h>
#include <Arduino.h>
#include <RTClib.h>
#include "OLedOut.h"

static const uint8_t THRESHOLD = 40;
static const uint8_t EN_PIN = 4;
static const uint8_t INC_PIN = 32;
static const uint8_t DEC_PIN = 33;
static const uint8_t SEL_PIN = 15;
static bool EN_PIN_state[2] = { false, false };
static bool INC_PIN_state[2] = { false, false };
static bool DEC_PIN_state[2] = { false, false };
static bool SEL_PIN_state[2] = { false, false };

// Check if the previous state was 'not touched' and the current one now is 'touched'
static bool nowPressed(bool state[2])
{
    return state[0] && !state[1];
}

// Updates the state of all touch pins
static void updatePins()
{
    EN_PIN_state[1] = EN_PIN_state[0];
    EN_PIN_state[0] = touchRead(EN_PIN) < THRESHOLD;

    INC_PIN_state[1] = INC_PIN_state[0];
    INC_PIN_state[0] = touchRead(INC_PIN) < THRESHOLD;

    DEC_PIN_state[1] = DEC_PIN_state[0];
    DEC_PIN_state[0] = touchRead(DEC_PIN) < THRESHOLD;

    SEL_PIN_state[1] = SEL_PIN_state[0];
    SEL_PIN_state[0] = touchRead(SEL_PIN) < THRESHOLD;

    Serial.printf("PINS: [%i, %i, %i, %i]\n", EN_PIN_state[0], INC_PIN_state[0], DEC_PIN_state[0], SEL_PIN_state[0]);
}

bool daelus_tsync_tick(DateTime* now)
{
    updatePins();
    // If we pressed the enable pin, go into time synchronization
    if (nowPressed(EN_PIN_state))
    {
        Serial.println("Enter TSync");
        bool selection = false;
        byte hour = now->hour();
        byte minute = now->minute();
        while (true)
        {
            updatePins();
            // Pressed enable again, end time sync
            if (nowPressed(EN_PIN_state))
            {
                Serial.println("Closed TSync");
                break;
            }
            // Change hour/minute selection
            else if (nowPressed(SEL_PIN_state))
            {
                selection = !selection;
                Serial.printf("Selection Toggle: %s\n", selection ? "Minute" : "Hour");
            }
            // Increment hour/minute
            else if (nowPressed(INC_PIN_state))
            {
                if (!selection)
                {
                    hour = (hour + 1) % 24;
                    Serial.printf("Incremented Hour: %i\n", hour);
                }
                else
                {
                    minute = (minute + 1) % 60;
                    Serial.printf("Incremented Minute: %i\n", minute);
                }
            }
            // Decrement hour/minute
            else if (nowPressed(DEC_PIN_state))
            {
                if (!selection)
                {
                    // Can't use '(hour - 1) % 24' as C/C++/C# have this operator return the "wrong" value when dealing with negative numbers
                    hour = hour == 0 ? 23 : hour - 1;
                    Serial.printf("Decremented Hour: %i\n", hour);
                }
                else
                {
                    // Can't use '(minute - 1) % 60' as C/C++/C# have this operator return the "wrong" value when dealing with negative numbers
                    minute = minute == 0 ? 59 : minute - 1;
                    Serial.printf("Decremented Minute: %i\n", minute);
                }
            }
            // Set the draw data
            daelus_oled_data data = {
                .hour = hour,
                .minute = minute,
                .state = dae_oled_tsync,
                .tsync_val = selection,
                .blink = false,
            };
            // And yeet it into the OLED
            if (!daelus_oled_draw(data))
            {
                Serial.println("Failed to print to oled!");
            }
            delay(100);
        }
        // We are done, save the new time
        *now = DateTime(now->year(), now->month(), now->day(), hour, minute, 0);
        return true;
    }

    return false;
}