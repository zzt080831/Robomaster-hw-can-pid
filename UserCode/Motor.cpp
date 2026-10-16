//
// Created by 周再同 on 2026/10/10.
//
#include "Motor.h"
float FeedForward = 0;
void Motor::canRxMsgCallback(const uint8_t rx_data[8]){
    last_ecd_ = ecd_angle_;
    ecd_angle_ = rx_data[1]|(rx_data[0]<<8);
    if((last_ecd_-ecd_angle_<0?ecd_angle_-last_ecd_:last_ecd_-ecd_angle_)>4096){
        if(last_ecd_>ecd_angle_){
            angle_+=(ecd_angle_+8192-last_ecd_)*360/8192.0/ratio_;
        }
        else{
            angle_+=(int16_t(ecd_angle_)-int16_t(last_ecd_)-8192)*360/8192.0/ratio_;
        }
    }
    else{
        angle_+=(int16_t(ecd_angle_)-last_ecd_)*360/8192.0/ratio_;
    }
    speedRpm_ = (int16_t)(rx_data[3]|(rx_data[2]<<8))/ratio_;
    currentA_ = (int16_t)(rx_data[5]|(rx_data[4]<<8))*20/16384.0f;
    tempC_ = rx_data[6];
}

float Motor::angle() const{
    return angle_;
}

float Motor::speedRpm() const{
    return speedRpm_;
}

float Motor::currentAmps() const{
    return currentA_;
}

uint8_t Motor::temperatureC() const{
    return tempC_;
}

void Motor::setTxCurrent(float amperes, uint8_t motor_id){
    int16_t currentdata = (int16_t)(amperes*16384.0/20.0);
    tx_data_[2*motor_id-2] = currentdata>>8;
    tx_data_[2*motor_id-1] = currentdata&0b0000000011111111;
}

void Motor::setAngle(float angle, uint8_t motor_id) {
    setTxCurrent(spid_.calc(ppid_.calc(angle,angle_),speedRpm_)+spid_.feedforward(angle_),motor_id);
}

uint8_t* Motor::getTxData(){
    return tx_data_;
}

void Motor::setId(uint8_t id) {
    id_ = id;
}
uint8_t Motor::getId(){
    return id_;
}
void Motor::init() {
    ppid_ = PID(15,0.8,140,1.55,90,1,0.25,0);
    spid_ = PID(0.15,0,0,0,7,0.96,0.35,0.39);
}