# 基于 ESP32-S3 的 HomeKit LED 控制

本项目展示了如何使用 Apple's HomeKit 协议通过 ESP32 微控制器控制 LED。项目使用 [HomeSpan](https://github.com/HomeSpan/HomeSpan) 库，轻松集成 HomeKit 支持，提供一个通过 Apple Home 应用控制的简单 Wi-Fi LED 控制设备。

## 功能

- **Wi-Fi 控制 LED**：可以通过 Apple Home 应用切换 LED 的开/关状态。
- **HomeKit 兼容**：完全兼容 Apple HomeKit，支持安全控制与监控。
- **可自定义 GPIO 控制**：可以修改代码控制 ESP32 上的任何 GPIO 引脚，用于驱动不同的外部设备或传感器。

## 配置 Wi-Fi
```
constexpr char ssid[] = "YOUR_WIFI_SSID";    // 替换为你的 Wi-Fi 名称
constexpr char passwd[] = "YOUR_WIFI_PASSWORD";  // 替换为你的 Wi-Fi 密码
```
## HomeKit 配对
```
constexpr char sn[] = "33877883";  // HomeKit 配对码
constexpr char qr_id[] = "338-77-883";  // HomeKit QR 码
```
1、打开 Apple Home 应用。
2、点击 "+" 按钮并选择“添加配件”。
3、扫描 QR 码或手动输入 HomeKit 配对码。
4、按照屏幕上的指示完成配对。

## LED 控制代码示例
```
class LightControl : public Service::LightBulb {
   SpanCharacteristic *power;

public:
   LightControl() : Service::LightBulb() {
      power = new Characteristic::On(0); 
      pinMode(LED_BUILTIN, OUTPUT);
      digitalWrite(LED_BUILTIN, LOW);
   }

   boolean update() override {
      bool isOn = power->getNewVal();
      digitalWrite(LED_BUILTIN, isOn ? HIGH : LOW);
      return true;
   }
};
```
