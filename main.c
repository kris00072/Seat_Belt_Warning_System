#include "stm32f1xx_hal.h"
#include "sensors.h"
#include "ignition.h"
#include "alerts.h"

void SystemClock_Config(void);

int main(void) {
  HAL_Init();
  SystemClock_Config();
  
  Sensors_Init();
  Ignition_Init();
  Alerts_Init();

  while (1) {
    if (Ignition_IsOn()) {
      for (int seat = SEAT_DRIVER; seat < SEAT_COUNT; seat++) {
        if (!Sensors_IsSeatBeltFastened(seat)) {
          Alerts_Trigger();
        }
      }
    } else {
      current_alert_state = ALERT_OFF; // Turn off alerts when ignition off
      HAL_GPIO_WritePin(ALERT_PORT, ALERT_PIN, GPIO_PIN_RESET);
    }
    
    Alerts_Update();
    HAL_Delay(10); // Minimal delay for power efficiency
  }
}