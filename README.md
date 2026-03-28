# ESP32 ESP-IDF component for CD74HC4067 16-channel analog multiplexer/demultiplexer

## Tested on

1. [ESP32 ESP-IDF v6.0.0](https://docs.espressif.com/projects/esp-idf/en/v6.0/esp32/index.html)

## SAST Tools

[PVS-Studio](https://pvs-studio.com/pvs-studio/?utm_source=website&utm_medium=github&utm_campaign=open_source) - static analyzer for C, C++, C#, and Java code.

## Features

1. Just an electronic galette switch between one of the 16 multiplexer GPIO and one ESP GPIO.
2. Support of all standard operations (digital read/write, interrupt, ADC, PWM, etc).

## Attention

1. EN GPIO on CD74HC4067 must be connected to ESP.

## Using

In an existing project, run the following command to install the components:

```text
cd ../your_project/components
git clone https://github.com/aZholtikov/zh_cd74hc4067
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
    esp_log_level_set("zh_cd74hc4067", ESP_LOG_ERROR);
    gpio_config_t pin_config = {
        .pin_bit_mask = (1ULL << GPIO_NUM_4)};
    gpio_config(&pin_config);
    zh_cd74hc4067_init_config_t config = ZH_CD74HC4067_INIT_CONFIG_DEFAULT();
    config.control_gpio_number = GPIO_NUM_4;
    config.en_gpio_number = GPIO_NUM_18;
    config.s0_gpio_number = GPIO_NUM_19;
    config.s1_gpio_number = GPIO_NUM_20;
    config.s2_gpio_number = GPIO_NUM_21;
    config.s3_gpio_number = GPIO_NUM_22;
    zh_cd74hc4067_init(&config);
    gpio_set_direction(zh_cd74hc4067_pin(), GPIO_MODE_OUTPUT);
    zh_cd74hc4067_set(ZH_CD74HC4067_GPIO_NUM_P5);
    printf("Currently connected GPIO number is %d.\n", zh_cd74hc4067_get());
    gpio_set_level(zh_cd74hc4067_pin(), 0);
    gpio_set_direction(zh_cd74hc4067_pin(), GPIO_MODE_INPUT);
    zh_cd74hc4067_set(ZH_CD74HC4067_GPIO_NUM_P11);
    printf("Currently connected GPIO number is %d.\n", zh_cd74hc4067_get());
    printf("GPIO %d level is %d.\n", zh_cd74hc4067_get(), gpio_get_level(zh_cd74hc4067_pin()));
    zh_cd74hc4067_set(ZH_CD74HC4067_GPIO_NUM_P15);
    printf("Currently connected GPIO number is %d.\n", zh_cd74hc4067_get());
}
```
