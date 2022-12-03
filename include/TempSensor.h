#ifndef DAEDALUS_SENSOR_H
#define DAEDALUS_SENSOR_H

/**
 * @brief Sets up all the necessary stuff to enable reading from the sensor
*/
void daelus_sensor_setup();

/**
 * @brief Reads temperature from the sensor
 * @param result Pointer to where the read temperature is saved (NaN value read in case of faulty connection)
 * @return Whether or not the read was successful
*/
bool daelus_sensor_readTemp(float* result);

/**
 * @brief Reads humidity from the sensor
 * @param result Pointer to where the read humidity is saved (NaN value read in case of faulty connection)
 * @return Whether or not the read was successful
*/
bool daelus_sensor_readHum(float* result);

/**
 * @brief Calculates the Heat Index from temperature and humidity
 * @param tmp Temperature to be used in the calculation
 * @param hum Humidity to be used in the calculation
 * @return The calculated Heat Index value (i.e perceived temperature in celsius)
 * @deprecated Heat Index calculation is fucked at the moment
*/
float daelus_sensor_computeHI(float tmp, float hum);

#endif