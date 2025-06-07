# ESP32 ESP-IDF and ESP8266 RTOS SDK component for CD74HC4067 16-channel analog multiplexer/demultiplexer

## Tested on

1. [ESP8266 RTOS_SDK v3.4](https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/index.html#)
2. [ESP32 ESP-IDF v5.4](https://docs.espressif.com/projects/esp-idf/en/release-v5.4/esp32/index.html)

## Features

1. Just an electronic galette switch between one of the 16 multiplexer GPIO and one ESP GPIO.
2. Support of all standard operations (digital read/write, interrupt, ADC, PWM, etc).

## Attention

1. EN GPIO on CD74HC4067 must be connected to ESP.

## Using

In an existing project, run the following command to install the components:

```text
cd ../your_project/components
git clone http://git.zh.com.ru/alexey.zholtikov/zh_cd74hc4067
```

In the application, add the component:

```c
#include "zh_cd74hc4067.h"
```

## Examples

Digital read and write:

```c
#include "zh_cd74hc4067.h"

void app_main(void)
{
    esp_log_level_set("zh_cd74hc4067", ESP_LOG_NONE); // For ESP8266 first enable "Component config -> Log output -> Enable log set level" via menuconfig.
    gpio_config_t pin_config = {
        .pin_bit_mask = (1ULL << GPIO_NUM_4)}; // Set control GPIO on ESP.
    gpio_config(&pin_config);
    zh_cd74hc4067_init_config_t cd74hc4067_init_config = {
        .control_gpio_number = GPIO_NUM_4,
        .en_gpio_number = GPIO_NUM_18,
        .s0_gpio_number = GPIO_NUM_19,
        .s1_gpio_number = GPIO_NUM_20,
        .s2_gpio_number = GPIO_NUM_21,
        .s3_gpio_number = GPIO_NUM_22,
    };
    zh_cd74hc4067_init(&cd74hc4067_init_config);
    gpio_set_direction(zh_cd74hc4067_pin(), GPIO_MODE_OUTPUT); // Set control GPIO on ESP to output.
    gpio_set_level(zh_cd74hc4067_set(10), 1);                  // Connect 10 GPIO on CD74HC4067 and set it to HIGH.
    zh_cd74hc4067_set(12);                                     // Connect 12 GPIO on CD74HC4067.
    gpio_set_direction(zh_cd74hc4067_pin(), GPIO_MODE_INPUT);  // Set control GPIO on ESP to input.
    bool level = gpio_get_level(zh_cd74hc4067_set(11));        // Connect 11 GPIO on CD74HC4067 and get it status.
    level = gpio_get_level(zh_cd74hc4067_pin());               // Get status of currently connected GPIO on CD74HC4067.
    uint8_t gpio = zh_cd74hc4067_get();                        // Get currently connected GPIO number on CD74HC4067.
}
```
