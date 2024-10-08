/**
 * @file control.h
 * @brief Automatically turns on and off a heater based on a thermistor
 * @author Arthur Beck/@ave (averse.abfun@gmail.com)
 * @note Written ad-hoc for Forge by Arthur Beck
 * @version 1.0
 * @copyright 2024
 */

#ifndef PID_CONTROL_H
#define PID_CONTROL_H

#include "../DSP/Include/arm_math.h"
#include "../CMSIS-Core/cmsis_compiler.h"
#include "../HAL/stm32f4xx_hal.h"
#include "therm.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct
    {
        ThermistorConfig *thermistorCfg;
        GPIO_TypeDef *HeaterMOSFETx;
        uint32_t HeaterMOSFET_Pin;
        float32_t K_p;
        float32_t K_i;
        float32_t K_d;
        float32_t target_temp;
        uint32_t _t;
        float32_t _integral;
        float32_t errors[1024];
        uint32_t uhPrescalerValue;
        TIM_HandleTypeDef TimHandle;
        uint32_t timerChannel;

        bool _initialized; // NEVER touch this manually, other then to read it. this is set by initController
        bool _has_autotuned;
    } PIDControlConfig;

    PIDControlConfig createController(
        ThermistorConfig *thermistorCfg,
        GPIO_TypeDef *HeaterMOSFETx,
        uint32_t HeaterMOSFET_Pin,
        float32_t K_p,
        float32_t K_i,
        float32_t K_d);

    void initController(PIDControlConfig *cfg);
    void singleStepController(PIDControlConfig *cfg);

    void PWM_SetDutyCycle(uint32_t channel, float32_t dutyCycle); // Internal use only

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PID_CONTROL_H */