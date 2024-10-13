# 基于 ESP32-S3 的 HomeKit LED 控制

本项目展示了如何使用 Apple's HomeKit 协议通过 ESP32 微控制器控制 LED。项目使用 [HomeSpan](https://github.com/HomeSpan/HomeSpan) 库，轻松集成 HomeKit 支持，提供一个通过 Apple Home 应用控制的简单 Wi-Fi LED 控制设备。

## 功能

- **Wi-Fi 控制 LED**：可以通过 Apple Home 应用切换 LED 的开/关状态。
- **HomeKit 兼容**：完全兼容 Apple HomeKit，支持安全控制与监控。
- **可自定义 GPIO 控制**：可以修改代码控制 ESP32 上的任何 GPIO 引脚，用于驱动不同的外部设备或传感器。

## 硬件连接

| LED驱动器引脚 | ESP32 引脚 |
|---------|------------|
| LIGHT_PIN    | 3          |

## 使用方法

1. **下载项目**：将代码克隆或下载到本地。
2. **打开 CLion IDE**：在 IDE 中打开 `main.cpp` 文件。
4. **上传代码**：点击“上传”按钮，将代码上传到 ESP32-S3。
6. **运行程序**：打开串口监视器，您将看到LED灯状态的反馈。

## 代码结构

```
esp32_homekit_light/
├── .gitignore                # Git 忽略文件
├── platformio.ini           # PlatformIO 项目配置文件
├── src/
│   ├── main.cpp             # 主程序文件
│   └── light_control.cpp    # Led控制类实现
├── include/
│   └── light_control.h      # Led控制类头文件
└── lib/
    └── HomeSpan/        # HomeKit 库文件
```

- .gitignore: 指定 Git 忽略的文件和文件夹，例如编译生成的文件。
- platformio.ini: PlatformIO 的项目配置文件，用于指定开发板、库和其他设置。
- src/: 源代码目录，包含所有的源文件和头文件。
    - main.cpp: 主程序文件，包含 setup() 和 loop() 函数。
    - light_control.cpp 和 light_control.h: 用于实现和定义LED控制的逻辑。
- lib/: 库目录，用于存放项目所需的第三方库。
  - HomeSpan/: HomeKit 库文件夹，包含库的实现和头文件。

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
