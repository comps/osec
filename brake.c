/*
 * EGG OpenSource EBike firmware
 *
 * Copyright (C) Casainho, 2015, 2106, 2017.
 *
 * Released under the GPL License, Version 3
 */

#include <stdint.h>
#include "stm8s.h"
#include "stm8s_it.h"
#include "gpio.h"
#include "main.h"
#include "interrupts.h"
#include "brake.h"
#include "motor.h"
#include "pwm.h"
#include "ACAcontrollerState.h"

// Brake signal
void EXTI_PORTA_IRQHandler(void) __interrupt(EXTI_PORTA_IRQHANDLER)
{
#if 0
  if (brake_is_set())
  {
    //brake_coast_enable ();
    //stop_cruise_control ();
  }
  else
  {
    //brake_coast_disable ();
    //pwm_set_duty_cycle (0);
    //stop_cruise_control ();
  }
#endif
}

void brake_init (void)
{
  //hall sensors pins as external input pin interrupt
  GPIO_Init(BRAKE__PORT,
	    BRAKE__PIN,
	    GPIO_MODE_IN_FL_IT); // with external interrupt

  //initialize the Interrupt sensitivity
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOA,
			    EXTI_SENSITIVITY_RISE_FALL);
}

BitStatus brake_is_set (void)
{
  if ((ui16_x4_value >> 2) > (uint16_t)ui8_throttle_min_range)
      return 1;
  return !GPIO_ReadInputPin(BRAKE__PORT, BRAKE__PIN);
}

void brake_coast_enable (void)
{
  TIM1->BKR &= (uint8_t) ~(TIM1_BKR_MOE);
}

void brake_coast_disable (void)
{
  TIM1->BKR |= (uint8_t) (TIM1_BKR_MOE);
}
