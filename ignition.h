#pragma once
#include "stm32f1xx_hal.h"

#define IGNITION_PORT       GPIOC
#define IGNITION_PIN        GPIO_PIN_13

void Ignition_Init(void);
int Ignition_IsOn(void);