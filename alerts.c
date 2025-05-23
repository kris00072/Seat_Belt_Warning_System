#include "alerts.h"
#include "main.h"  // For system tick

// Alert Timing
#define PHASE1_ON_TIME      200   // ms
#define PHASE1_OFF_TIME     800   // ms
#define PHASE2_ON_TIME      500   // ms
#define PHASE2_OFF_TIME     500   // ms
#define ESCALATION_DELAY    30000 // Time before escalating (30s)

static AlertState current_alert_state = ALERT_OFF;
static uint32_t alert_start_time = 0;
static uint32_t last_toggle_time = 0;

void Alerts_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  __HAL_RCC_GPIOB_CLK_ENABLE();
  
  GPIO_InitStruct.Pin = ALERT_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ALERT_PORT, &GPIO_InitStruct);
}

void Alerts_Trigger(void) {
  if (current_alert_state == ALERT_OFF) {
    current_alert_state = ALERT_PHASE1;
    alert_start_time = HAL_GetTick();
    HAL_GPIO_WritePin(ALERT_PORT, ALERT_PIN, GPIO_PIN_SET);
    last_toggle_time = HAL_GetTick();
  }
}

void Alerts_Update(void) {
  if (current_alert_state == ALERT_OFF) return;

  uint32_t now = HAL_GetTick();
  uint32_t elapsed = now - alert_start_time;

  // Escalate to phase 2 after delay
  if ((current_alert_state == ALERT_PHASE1) && (elapsed > ESCALATION_DELAY)) {
    current_alert_state = ALERT_PHASE2;
    last_toggle_time = now;
  }

  // Handle beep patterns
  uint32_t period = (current_alert_state == ALERT_PHASE1) ? 
                    (PHASE1_ON_TIME + PHASE1_OFF_TIME) : 
                    (PHASE2_ON_TIME + PHASE2_OFF_TIME);

  if ((now - last_toggle_time) > period) {
    HAL_GPIO_TogglePin(ALERT_PORT, ALERT_PIN);
    last_toggle_time = now;
  }
}