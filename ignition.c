#include "ignition.h"

void Ignition_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  __HAL_RCC_GPIOC_CLK_ENABLE();
  
  GPIO_InitStruct.Pin = IGNITION_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(IGNITION_PORT, &GPIO_InitStruct);
}

int Ignition_IsOn(void) {
  return (HAL_GPIO_ReadPin(IGNITION_PORT, IGNITION_PIN) == GPIO_PIN_SET);
}