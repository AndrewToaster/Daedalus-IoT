#include "TempSensor.h"
#include "DHT.h"
#include <math.h>

// Interface with the sensor
static DHT tmp_sensor = DHT(23, DHT22);

// Whether or not we setup the interface
static bool is_setup = false;

void daelus_sensor_setup() 
{
    if (!is_setup)
    {
        is_setup = true;
        tmp_sensor.begin();
    }
}

bool daelus_sensor_readTemp(float* result)
{
    if (!is_setup) { return false; }
    *result = tmp_sensor.readTemperature();
    return true;
}

bool daelus_sensor_readHum(float* result)
{
    if (!is_setup) { return false; }
    *result = tmp_sensor.readHumidity();
    return true;
}

float daelus_sensor_computeHI(float tmp, float hum)
{
    // Meterologists we wildin' on that funny temperature math
    return (-8.78469475556) + 
           (1.61139411 * tmp) + 
           (2.33854883889 * hum) + 
           (-0.14611605 * tmp * hum) + 
           (-0.0012308094 * pow(tmp, 2)) + 
           (-0.0164248277778 * pow(hum, 2)) + 
           (0.002211732 * pow(tmp, 2) * hum) +
           (0.00072546 * tmp * pow(hum, 2)) +
           (-0.000003582 * pow(tmp * hum, 2));  
}