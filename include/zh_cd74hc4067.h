#pragma once

#include "esp_log.h"
#include "driver/gpio.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct // Structure for initial initialization of CD74HC4067 multiplexer.
    {
        uint8_t s0_gpio_number;      // GPIO connected to S0 of CD74HC4067 multiplexer.
        uint8_t s1_gpio_number;      // GPIO connected to S1 of CD74HC4067 multiplexer.
        uint8_t s2_gpio_number;      // GPIO connected to S2 of CD74HC4067 multiplexer.
        uint8_t s3_gpio_number;      // GPIO connected to S3 of CD74HC4067 multiplexer.
        uint8_t control_gpio_number; // GPIO connected to SIG of CD74HC4067 multiplexer.
        uint8_t en_gpio_number;      // GPIO connected to EN of CD74HC4067 multiplexer.
    } zh_cd74hc4067_init_config_t;

    /**
     * @brief Initialize CD74HC4067 multiplexer.
     *
     * @param[in] config Pointer to CD74HC4067 initialized configuration structure. Can point to a temporary variable.
     *
     * @return ESP_OK if success or an error code otherwise.
     */
    esp_err_t zh_cd74hc4067_init(const zh_cd74hc4067_init_config_t *config);

    /**
     * @brief Set CD74HC4067 GPIO for connect.
     *
     * @param[in] gpio GPIO for connect.
     *
     * @return Control GPIO number or -1 otherwise.
     */
    gpio_num_t zh_cd74hc4067_set(uint8_t gpio);

    /**
     * @brief Get CD74HC4067 connected GPIO.
     *
     * @return GPIO number.
     */
    uint8_t zh_cd74hc4067_get(void);

    /**
     * @brief Get CD74HC4067 control GPIO number.
     *
     * @return Control GPIO number.
     */
    gpio_num_t zh_cd74hc4067_pin(void);

#ifdef __cplusplus
}
#endif