# zh_cd74hc4067 - CD74HC4067 16-Channel Analog Multiplexer Component for ESP-IDF

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Pinout Configuration](#pinout-configuration)
- [API Reference](#api-reference)
- [Usage Examples](#usage-examples)
- [Technical Specifications](#technical-specifications)
- [Error Codes](#error-codes)
- [Contributing](#contributing)
- [License](#license)

---

## Overview

`zh_cd74hc4067` is a lightweight ESP-IDF component for controlling the CD74HC4067 16-channel analog multiplexer/demultiplexer. It provides a simple API to connect one of the 16 multiplexer GPIO pins to a single ESP GPIO pin. The component is designed specifically for ESP32 microcontrollers and uses ESP-IDF drivers (GPIO).

The CD74HC4067 is a 16-channel analog multiplexer that allows you to control 16 different signals using only 5 GPIO pins (4 control pins + 1 signal pin) on your ESP32.

---

## Features

1. **16-Channel Multiplexing**: Connect one of 16 GPIO pins to a single control pin
2. **Simple Control Interface**: Use S0-S3 control pins to select channels
3. **Enable Control**: Dedicated EN pin for enabling/disabling the multiplexer
4. **Full GPIO Support**: Supports all standard GPIO operations (digital read/write, interrupt, ADC, PWM, etc.)
5. **Error Handling**: Comprehensive error checking and validation
6. **Thread-Safe**: Uses ESP-IDF drivers (thread-safe)
7. **Low Memory**: Minimal memory footprint
8. **Simple API**: Easy-to-use interface

---

## Installation

1. Navigate to your project's components directory:

```bash
cd ../your_project/components
```

2. Clone the repository:

```bash
git clone https://github.com/aZholtikov/zh_cd74hc4067.git
```

3. In your application, include the header:

```c
#include "zh_cd74hc4067.h"
```

4. The component will be automatically built with your project.

---

## Pinout Configuration

The CD74HC4067 multiplexer requires the following connections:

| CD74HC4067 Pin | Description | ESP32 Connection |
|----------------|-------------|------------------|
| S0, S1, S2, S3 | Address select pins | Any 4 GPIO pins |
| EN | Enable pin (active low) | Any GPIO pin |
| SIG | Signal pin (input/output) | Your control GPIO pin |
| P0-P15 | 16 multiplexer channels | Your 16 GPIO pins to control |

### Pin Configuration Structure

```c
typedef struct
{
    gpio_num_t s0_gpio_number;      // GPIO connected to S0 of CD74HC4067 multiplexer
    gpio_num_t s1_gpio_number;      // GPIO connected to S1 of CD74HC4067 multiplexer
    gpio_num_t s2_gpio_number;      // GPIO connected to S2 of CD74HC4067 multiplexer
    gpio_num_t s3_gpio_number;      // GPIO connected to S3 of CD74HC4067 multiplexer
    gpio_num_t control_gpio_number; // GPIO connected to SIG of CD74HC4067 multiplexer
    gpio_num_t en_gpio_number;      // GPIO connected to EN of CD74HC4067 multiplexer
} zh_cd74hc4067_init_config_t;
```

---

## API Reference

### zh_cd74hc4067_init_config_t Structure

```c
typedef struct
{
    gpio_num_t s0_gpio_number;      // GPIO connected to S0 of CD74HC4067 multiplexer
    gpio_num_t s1_gpio_number;      // GPIO connected to S1 of CD74HC4067 multiplexer
    gpio_num_t s2_gpio_number;      // GPIO connected to S2 of CD74HC4067 multiplexer
    gpio_num_t s3_gpio_number;      // GPIO connected to S3 of CD74HC4067 multiplexer
    gpio_num_t control_gpio_number; // GPIO connected to SIG of CD74HC4067 multiplexer
    gpio_num_t en_gpio_number;      // GPIO connected to EN of CD74HC4067 multiplexer
} zh_cd74hc4067_init_config_t;
```

Use `ZH_CD74HC4067_INIT_CONFIG_DEFAULT()` macro to initialize with default values:

- `s0_gpio_number`: GPIO_NUM_MAX
- `s1_gpio_number`: GPIO_NUM_MAX
- `s2_gpio_number`: GPIO_NUM_MAX
- `s3_gpio_number`: GPIO_NUM_MAX
- `control_gpio_number`: GPIO_NUM_MAX
- `en_gpio_number`: GPIO_NUM_MAX

---

### zh_cd74hc4067_gpio_num_t Enumeration

```c
typedef enum
{
    ZH_CD74HC4067_GPIO_NUM_P0 = 0,
    ZH_CD74HC4067_GPIO_NUM_P1,
    ZH_CD74HC4067_GPIO_NUM_P2,
    ZH_CD74HC4067_GPIO_NUM_P3,
    ZH_CD74HC4067_GPIO_NUM_P4,
    ZH_CD74HC4067_GPIO_NUM_P5,
    ZH_CD74HC4067_GPIO_NUM_P6,
    ZH_CD74HC4067_GPIO_NUM_P7,
    ZH_CD74HC4067_GPIO_NUM_P8,
    ZH_CD74HC4067_GPIO_NUM_P9,
    ZH_CD74HC4067_GPIO_NUM_P10,
    ZH_CD74HC4067_GPIO_NUM_P11,
    ZH_CD74HC4067_GPIO_NUM_P12,
    ZH_CD74HC4067_GPIO_NUM_P13,
    ZH_CD74HC4067_GPIO_NUM_P14,
    ZH_CD74HC4067_GPIO_NUM_P15,
    ZH_CD74HC4067_GPIO_NUM_MAX
} zh_cd74hc4067_gpio_num_t;
```

---

### zh_cd74hc4067_init()

Initializes the CD74HC4067 multiplexer.

**Parameters:**

- `config` - Pointer to CD74HC4067 initialization configuration structure

**Returns:**

- `ESP_OK` - Success
- `ESP_ERR_INVALID_ARG` - Invalid argument (NULL config or invalid GPIO)
- `ESP_ERR_INVALID_STATE` - CD74HC4067 is already initialized
- `ESP_FAIL` - Initialization failed (GPIO initialization)

**Example:**

```c
zh_cd74hc4067_init_config_t config = ZH_CD74HC4067_INIT_CONFIG_DEFAULT();
config.control_gpio_number = GPIO_NUM_4;
config.en_gpio_number = GPIO_NUM_18;
config.s0_gpio_number = GPIO_NUM_19;
config.s1_gpio_number = GPIO_NUM_20;
config.s2_gpio_number = GPIO_NUM_21;
config.s3_gpio_number = GPIO_NUM_22;
zh_cd74hc4067_init(&config);
```

---

### zh_cd74hc4067_set()

Sets the CD74HC4067 GPIO for connection.

**Parameters:**

- `gpio` - GPIO number to connect (ZH_CD74HC4067_GPIO_NUM_P0 to ZH_CD74HC4067_GPIO_NUM_P15)

**Returns:**

- Control GPIO number (success)
- `GPIO_NUM_NC` (error)

**Example:**

```c
zh_cd74hc4067_set(ZH_CD74HC4067_GPIO_NUM_P5);
```

---

### zh_cd74hc4067_get()

Gets the currently connected CD74HC4067 GPIO.

**Returns:**

- GPIO number (success)
- Current connected GPIO number

**Example:**

```c
zh_cd74hc4067_gpio_num_t current = zh_cd74hc4067_get();
printf("Currently connected GPIO: %d\n", current);
```

---

### zh_cd74hc4067_pin()

Gets the CD74HC4067 control GPIO number.

**Returns:**

- Control GPIO number

**Example:**

```c
printf("Control GPIO number: %d\n", zh_cd74hc4067_pin());
```

---

## Usage Examples

### Basic Example: Digital Read and Write

```c
#include "zh_cd74hc4067.h"

void app_main(void)
{
    esp_log_level_set("zh_cd74hc4067", ESP_LOG_ERROR);
    // Configure control GPIO
    gpio_config_t pin_config = {
        .pin_bit_mask = (1ULL << GPIO_NUM_4)};
    gpio_config(&pin_config);
    // Initialize CD74HC4067
    zh_cd74hc4067_init_config_t config = ZH_CD74HC4067_INIT_CONFIG_DEFAULT();
    config.control_gpio_number = GPIO_NUM_4;
    config.en_gpio_number = GPIO_NUM_18;
    config.s0_gpio_number = GPIO_NUM_19;
    config.s1_gpio_number = GPIO_NUM_20;
    config.s2_gpio_number = GPIO_NUM_21;
    config.s3_gpio_number = GPIO_NUM_22;
    zh_cd74hc4067_init(&config);
    // Set GPIO P5 and write low
    gpio_set_direction(zh_cd74hc4067_pin(), GPIO_MODE_OUTPUT);
    zh_cd74hc4067_set(ZH_CD74HC4067_GPIO_NUM_P5);
    printf("Currently connected GPIO number is %d.\n", zh_cd74hc4067_get());
    gpio_set_level(zh_cd74hc4067_pin(), 0);
    // Set GPIO P11 and read level
    gpio_set_direction(zh_cd74hc4067_pin(), GPIO_MODE_INPUT);
    zh_cd74hc4067_set(ZH_CD74HC4067_GPIO_NUM_P11);
    printf("Currently connected GPIO number is %d.\n", zh_cd74hc4067_get());
    printf("GPIO %d level is %d.\n", zh_cd74hc4067_get(), gpio_get_level(zh_cd74hc4067_pin()));
    // Set GPIO P15
    zh_cd74hc4067_set(ZH_CD74HC4067_GPIO_NUM_P15);
    printf("Currently connected GPIO number is %d.\n", zh_cd74hc4067_get());
}
```

---

### Example: Reading Multiple Analog Sensors

```c
#include "zh_cd74hc4067.h"

#define CONTROL_GPIO GPIO_NUM_36
#define EN_GPIO GPIO_NUM_18
#define S0_GPIO GPIO_NUM_19
#define S1_GPIO GPIO_NUM_20
#define S2_GPIO GPIO_NUM_21
#define S3_GPIO GPIO_NUM_22

void app_main(void)
{
    esp_log_level_set("zh_cd74hc4067", ESP_LOG_ERROR);
    // Configure control GPIO
    gpio_config_t pin_config = {
        .pin_bit_mask = (1ULL << CONTROL_GPIO)};
    gpio_config(&pin_config);
    // Initialize CD74HC4067
    zh_cd74hc4067_init_config_t config = ZH_CD74HC4067_INIT_CONFIG_DEFAULT();
    config.control_gpio_number = CONTROL_GPIO;
    config.en_gpio_number = EN_GPIO;
    config.s0_gpio_number = S0_GPIO;
    config.s1_gpio_number = S1_GPIO;
    config.s2_gpio_number = S2_GPIO;
    config.s3_gpio_number = S3_GPIO;
    zh_cd74hc4067_init(&config);
    // Configure ADC
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
    // Read from all 16 channels
    for (int i = 0; i < 16; i++)
    {
        zh_cd74hc4067_set((zh_cd74hc4067_gpio_num_t)i);
        int raw = adc1_get_raw(ADC1_CHANNEL_0);
        printf("Channel P%d: %d\n", i, raw);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
```

---

### Example: Controlling Multiple Relays

```c
#include "zh_cd74hc4067.h"

#define CONTROL_GPIO GPIO_NUM_4
#define EN_GPIO GPIO_NUM_18
#define S0_GPIO GPIO_NUM_19
#define S1_GPIO GPIO_NUM_20
#define S2_GPIO GPIO_NUM_21
#define S3_GPIO GPIO_NUM_22

void app_main(void)
{
    esp_log_level_set("zh_cd74hc4067", ESP_LOG_ERROR);
    // Configure control GPIO
    gpio_config_t pin_config = {
        .pin_bit_mask = (1ULL << CONTROL_GPIO)};
    gpio_config(&pin_config);
    // Initialize CD74HC4067
    zh_cd74hc4067_init_config_t config = ZH_CD74HC4067_INIT_CONFIG_DEFAULT();
    config.control_gpio_number = CONTROL_GPIO;
    config.en_gpio_number = EN_GPIO;
    config.s0_gpio_number = S0_GPIO;
    config.s1_gpio_number = S1_GPIO;
    config.s2_gpio_number = S2_GPIO;
    config.s3_gpio_number = S3_GPIO;
    zh_cd74hc4067_init(&config);
    // Set as output
    gpio_set_direction(zh_cd74hc4067_pin(), GPIO_MODE_OUTPUT);
    // Cycle through all relays
    for (int i = 0; i < 16; i++)
    {
        zh_cd74hc4067_set((zh_cd74hc4067_gpio_num_t)i);
        gpio_set_level(zh_cd74hc4067_pin(), 1);
        printf("Relay P%d ON\n", i);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_set_level(zh_cd74hc4067_pin(), 0);
        printf("Relay P%d OFF\n", i);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
```

---

## Technical Specifications

| Parameter | Value |
|-----------|-------|
| **Channels** | 16 (P0-P15) |
| **Control Pins** | 4 (S0-S3) |
| **Enable Pin** | 1 (EN) |
| **Signal Pin** | 1 (SIG) |
| **GPIO Pins Required** | 6 total |
| **Type** | Analog multiplexer/demultiplexer |
| **ESP-IDF Version** | >= 5.0 |
| **Platform** | ESP32 series |
| **Language** | C (C99) |

---

## Error Codes

| Error Code | Description |
|------------|-------------|
| `ESP_OK` | Operation successful |
| `ESP_ERR_INVALID_ARG` | Invalid argument (NULL pointer, invalid GPIO, or invalid channel number) |
| `ESP_ERR_INVALID_STATE` | CD74HC4067 is not initialized |
| `ESP_FAIL` | General failure (GPIO initialization) |

---

## Contributing

Contributions are welcome! To contribute:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

Please ensure your code follows the existing style and includes appropriate documentation.

---

## License

This project is licensed under the Apache License, Version 2.0 - see the [LICENSE](LICENSE) file for details.

### Apache License, Version 2.0

Copyright (c) 2026 Alexey Zholtikov

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

---

## Additional Notes

- **EN GPIO**: The EN pin on CD74HC4067 must be connected to ESP and configured in the initialization
- **GPIO Operations**: After setting a channel, you can use all standard GPIO operations (digital read/write, interrupt, ADC, PWM, etc.)
- **Channel Selection**: Channels are selected using binary encoding on S0-S3 pins
- **Thread Safety**: The component uses ESP-IDF drivers which are thread-safe
- **Pin Validation**: The library validates that all GPIO numbers are unique and valid during initialization

---

*Generated for zh_cd74hc4067 v1.1.0*
