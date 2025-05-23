#pragma once
#include "stm32f1xx_hal.h"

// Seat Definitions
typedef enum {
  SEAT_DRIVER,
  SEAT_FRONT_PASSENGER,
  SEAT_COUNT // Total seats being monitored
} SeatID;

// Sensor Pins (Customize based on your hardware)
#define SEAT_BELT_SENSOR_PORT    GPIOA
#define DRIVER_SENSOR_PIN        GPIO_PIN_0
#define PASSENGER_SENSOR_PIN     GPIO_PIN_1

// Debounce Config
#define DEBOUNCE_DELAY_MS        50

void Sensors_Init(void);
int Sensors_IsSeatOccupied(SeatID seat);
int Sensors_IsSeatBeltFastened(SeatID seat);