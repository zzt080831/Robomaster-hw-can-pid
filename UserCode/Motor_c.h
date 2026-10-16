//
// Created by 周再同 on 2026/10/10.
//


#ifndef MOTOR_C_H
#define MOTOR_C_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* MotorHandle;
MotorHandle Motor_Create(const float ratio, uint8_t motor_id);
void SetAngle(MotorHandle motor_handle,float angle);

#ifdef __cplusplus
}
#endif

#endif

