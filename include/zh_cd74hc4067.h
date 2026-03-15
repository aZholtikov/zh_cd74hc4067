/**
 * @file zh_cd74hc4067.h
 */

#pragma once

#include "esp_log.h"
#include "driver/gpio.h"

/**
 * @brief CD74HC4067 multiplexer initial default values.
 */
#define ZH_CD74HC4067_INIT_CONFIG_DEFAULT()  \
    {                                        \
        .s0_gpio_number = GPIO_NUM_MAX,      \
        .s1_gpio_number = GPIO_NUM_MAX,      \
        .s2_gpio_number = GPIO_NUM_MAX,      \
        .s3_gpio_number = GPIO_NUM_MAX,      \
        .control_gpio_number = GPIO_NUM_MAX, \
        .en_gpio_number = GPIO_NUM_MAX}

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Enumeration of CD74HC4067 multiplexer GPIO.
     */
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

    /**
     * @brief Sructure for initial initialization of CD74HC4067 multiplexer.
     */
    typedef struct
    {
        uint8_t s0_gpio_number;      /*!< GPIO connected to S0 of CD74HC4067 multiplexer. */
        uint8_t s1_gpio_number;      /*!< GPIO connected to S1 of CD74HC4067 multiplexer. */
        uint8_t s2_gpio_number;      /*!< GPIO connected to S2 of CD74HC4067 multiplexer. */
        uint8_t s3_gpio_number;      /*!< GPIO connected to S3 of CD74HC4067 multiplexer. */
        uint8_t control_gpio_number; /*!< GPIO connected to SIG of CD74HC4067 multiplexer. */
        uint8_t en_gpio_number;      /*!< GPIO connected to EN of CD74HC4067 multiplexer. */
    } zh_cd74hc4067_init_config_t;

    /**
     * @brief Initialize CD74HC4067 multiplexer.
     *
     * @param[in] config Pointer to CD74HC4067 initialized configuration structure. Can point to a temporary variable.
     *
     * @note Before initialize the multiplexer recommend initialize zh_cd74hc4067_init_config_t structure with default values.
     *
     * @code zh_cd74hc4067_init_config_t config = ZH_CD74HC4067_INIT_CONFIG_DEFAULT() @endcode
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