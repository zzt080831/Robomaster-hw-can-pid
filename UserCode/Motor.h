//
// Created by 周再同 on 2026/10/10.
//

#ifndef CAN_F407_MOTOR_HPP
#define CAN_F407_MOTOR_HPP
#include "stm32f4xx_hal.h"
#include "PID.h"
class Motor{
public:
    uint8_t stop_all = 1;
    explicit Motor(const float ratio, uint8_t motor_id):ratio_(ratio),id_(motor_id) {
        init();
    }

    void canRxMsgCallback(const uint8_t rx_data[8]);

    float angle() const;
    float speedRpm() const;
    float currentAmps() const;
    uint8_t temperatureC() const;

    void setTxCurrent(float amperes, uint8_t motor_id);
    void setAngle(float angle, uint8_t motor_id);
    void setId(uint8_t id);
    uint8_t getId();
    uint8_t* getTxData();
    void init();

    PID ppid_ = PID(15,0.8,140,1.55,90,1,0.25,0);
    PID spid_ = PID(0.15,0,0,0,7,0.96,0.35,0.39);
private:
    const float ratio_;
    uint16_t ecd_angle_ = 0;
    float speedRpm_ = 0;
    float currentA_ = 0;
    uint8_t tempC_ = 0;

    float angle_ = 0;
    uint16_t last_ecd_ = 0;
    bool received_ = false;

    uint8_t tx_data_[8] = {};
    uint8_t id_ = 0;

    const uint16_t kEncoderRange = 8192;
};


#endif