//
// Created by 周再同 on 2026/10/10.
//
#include "Motor_c.h"
#include "Motor.h"
#include "PID.h"
extern "C" {
    MotorHandle Motor_Create(const float ratio, uint8_t motor_id){
        Motor* motor = new Motor(ratio, motor_id);
        motor->init();
        return static_cast<MotorHandle>(motor);
    }
    void SetAngle(MotorHandle motor_handle,float angle){
        Motor* motor = static_cast<Motor*>(motor_handle);
        motor->setAngle(angle, motor->getId());
    }
}