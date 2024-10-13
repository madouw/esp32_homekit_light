//
// Created by wangxx on 2024/10/11.
// 灯控制头文件
//

#ifndef LIGHT_CONTROL_H
#define LIGHT_CONTROL_H

#define LIGHT_PIN 3

#include <HomeSpan.h>

// 常量定义，增加可读性
constexpr int LIGHT_ON = HIGH;
constexpr int LIGHT_OFF = LOW;

class LightControl : public Service::LightBulb {
    // 存储灯的状态（开/关）
    SpanCharacteristic *power;

public:
    LightControl() : Service::LightBulb() {
        power = new Characteristic::On(false);
        pinMode(LIGHT_PIN,OUTPUT);
        digitalWrite(LED_BUILTIN, LIGHT_OFF);
    }

    boolean update() override;
};

#endif //LIGHT_CONTROL_H
