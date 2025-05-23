#include "sensors.h"

// Sensor Pin Map (Add more seats here)
static const uint16_t SEAT_BELT_PINS[SEAT_COUNT] = {
  [SEAT_DRIVER] = DRIVER_SENSOR_PIN,
  [SEAT_FRONT_PASSENGER] = PASSENGER_SENSOR_PIN
};

// Debounce States
typedef struct {
  uint32_t last_debounce_time;
  int last_state;
} DebounceState;

static DebounceState belt_debounce[SEAT_COUNT];

void Sensors_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // Enable GPIO Clocks
  __HAL_RCC_GPIOA_CLK_ENABLE();

  // Configure all seat belt sensors as inputs
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  for (int i = 0; i < SEAT_COUNT; i++) {
    GPIO_InitStruct.Pin = SEAT_BELT_PINS[i];
    HAL_GPIO_Init(SEAT_BELT_SENSOR_PORT, &GPIO_InitStruct);
  }
}

int Sensors_IsSeatBeltFastened(SeatID seat) {
  int current_state = HAL_GPIO_ReadPin(SEAT_BELT_SENSOR_PORT, SEAT_BELT_PINS[seat]);
  
  // Debounce logic
  if (current_state != belt_debounce[seat].last_state) {
    belt_debounce[seat].last_debounce_time = HAL_GetTick();
  }
  
  if ((HAL_GetTick() - belt_debounce[seat].last_debounce_time) > DEBOUNCE_DELAY_MS) {
    belt_debounce[seat].last_state = current_state;
  }
  
  return (belt_debounce[seat].last_state == GPIO_PIN_SET);
}