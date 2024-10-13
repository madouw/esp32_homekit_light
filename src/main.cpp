#include <Arduino.h>
#include <HomeSpan.h>
#include <WiFi.h>

#include "light_control.h"

// 定义 HomeKit 配对码和QR码ID
constexpr char sn[] = "33877883"; // HomeKit配对码
constexpr char qr_id[] = "338-77-883"; // HomeKit设备的QR码ID

// 定义 Wi-Fi 参数
constexpr char ssid[] = "Your Wi_Fi"; // Wi-Fi名称
constexpr char passwd[] = "Your Wi_Fi Password"; // Wi-Fi密码

void connectToWiFi() {
    Serial.print("Connecting to WiFi: ");
    Serial.println(ssid);
    WiFi.begin(ssid, passwd);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.printf("\nWiFi connected. IP Address: %s\n", WiFi.localIP().toString().c_str());
}

void setup() {
    Serial.begin(115200);

    // 设置 HomeKit 配对码和 QR 码 ID
    homeSpan.setPairingCode(sn);
    homeSpan.setQRID(qr_id);

    // 启动 HomeSpan 设备
    homeSpan.begin(Category::Lighting, "MY Home LED");
    // 配置 HomeKit 配件和服务
    new SpanAccessory();
    new Service::AccessoryInformation();
    new Characteristic::Identify();
    new Characteristic::Name("Simple LED");

    // 初始化灯光控制类
    new LightControl();

    // 连接 Wi-Fi
    connectToWiFi();
}

void loop() {
    // HomeKit 循环处理
    homeSpan.poll();
}
