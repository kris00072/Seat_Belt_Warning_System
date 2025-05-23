#pragma once
#include "stm32f1xx_hal.h"

#define ALERT_PORT          GPIOB
#define ALERT_PIN           GPIO_PIN_13

// Alert Phases
typedef enum {
  ALERT_OFF,
  ALERT_PHASE1,  // Slow beep
  ALERT_PHASE2   // Fast beep
} AlertState;

void Alerts_Init(void);
void Alerts_Trigger(void);
void Alerts_Update(void);