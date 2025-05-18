#include "zh_cd74hc4067.h"

static const char *TAG = "zh_cd74hc4067";

#define ZH_CD74HC4067_LOGI(msg, ...) ESP_LOGI(TAG, msg, ##__VA_ARGS__)
#define ZH_CD74HC4067_LOGW(msg, ...) ESP_LOGW(TAG, msg, ##__VA_ARGS__)
#define ZH_CD74HC4067_LOGE(msg, ...) ESP_LOGE(TAG, msg, ##__VA_ARGS__)
#define ZH_CD74HC4067_LOGE_ERR(msg, err, ...) ESP_LOGE(TAG, "[%s:%d:%s] " msg, __FILE__, __LINE__, esp_err_to_name(err), ##__VA_ARGS__)

#define ZH_CD74HC4067_CHECK(cond, err, msg, ...) \
    if (!(cond))                                 \
    {                                            \
        ZH_CD74HC4067_LOGE_ERR(msg, err);        \
        return err;                              \
    }

static const uint8_t _cd74hc4067_matrix[16][4] = {
    {0, 0, 0, 0},
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 1, 0},
    {1, 0, 1, 0},
    {0, 1, 1, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 1},
    {1, 0, 0, 1},
    {0, 1, 0, 1},
    {1, 1, 0, 1},
    {0, 0, 1, 1},
    {1, 0, 1, 1},
    {0, 1, 1, 1},
    {1, 1, 1, 1}};

static zh_cd74hc4067_init_config_t _init_config = {0};
static uint8_t _connected_gpio = 0;
static bool _is_initialized = false;

static bool _zh_cd74hc4067_gpio_check(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t en, uint8_t control);

esp_err_t zh_cd74hc4067_init(const zh_cd74hc4067_init_config_t *config)
{
    ZH_CD74HC4067_LOGI("CD74HC4067 initialization started.");
    ZH_CD74HC4067_CHECK(config != NULL, ESP_ERR_INVALID_ARG, "CD74HC4067 initialization failed. Invalid argument.");
    if (_is_initialized == true)
    {
        ZH_CD74HC4067_LOGW("CD74HC4067 initialization failed. CD74HC4067 is already initialized.");
        return ESP_OK;
    }
    ZH_CD74HC4067_CHECK((config->s0_gpio_number < GPIO_NUM_MAX) && (config->s1_gpio_number < GPIO_NUM_MAX) &&
                            (config->s2_gpio_number < GPIO_NUM_MAX) && (config->s3_gpio_number < GPIO_NUM_MAX) &&
                            (config->en_gpio_number < GPIO_NUM_MAX) && (config->control_gpio_number < GPIO_NUM_MAX),
                        ESP_FAIL, "CD74HC4067 initialization failed. Invalid GPIO number.");
    bool gpio_check = _zh_cd74hc4067_gpio_check(config->s0_gpio_number, config->s1_gpio_number, config->s2_gpio_number, config->s3_gpio_number, config->en_gpio_number, config->control_gpio_number);
    ZH_CD74HC4067_CHECK(gpio_check == true, ESP_FAIL, "CD74HC4067 initialization failed. Invalid GPIO number.");
    gpio_config_t pin_config = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << config->s0_gpio_number) | (1ULL << config->s1_gpio_number) | (1ULL << config->s2_gpio_number) |
                        (1ULL << config->s3_gpio_number) | (1ULL << config->en_gpio_number),
    };
    esp_err_t err = gpio_config(&pin_config);
    ZH_CD74HC4067_CHECK(err == ESP_OK, err, "CD74HC4067 initialization failed. GPIO initialization failed.")
    _init_config = *config;
    _is_initialized = true;
    ZH_CD74HC4067_LOGI("CD74HC4067 initialization completed successfully.");
    return ESP_OK;
}

gpio_num_t zh_cd74hc4067_set(uint8_t gpio)
{
    ZH_CD74HC4067_LOGI("CD74HC4067 connect GPIO started.");
    ZH_CD74HC4067_CHECK(_is_initialized == true, ESP_FAIL, "CD74HC4067 connect GPIO failed. CD74HC4067 not initialized.");
    ZH_CD74HC4067_CHECK(gpio <= 15, ESP_FAIL, "CD74HC4067 initialization failed. Invalid argument.");
    esp_err_t err = gpio_set_level(_init_config.en_gpio_number, 1);
    ZH_CD74HC4067_CHECK(err == ESP_OK, ESP_FAIL, "CD74HC4067 connect GPIO failed. GPIO driver internal error.");
    err = gpio_set_level(_init_config.s0_gpio_number, _cd74hc4067_matrix[gpio][0]);
    ZH_CD74HC4067_CHECK(err == ESP_OK, ESP_FAIL, "CD74HC4067 connect GPIO failed. GPIO driver internal error.");
    err = gpio_set_level(_init_config.s1_gpio_number, _cd74hc4067_matrix[gpio][1]);
    ZH_CD74HC4067_CHECK(err == ESP_OK, ESP_FAIL, "CD74HC4067 connect GPIO failed. GPIO driver internal error.");
    err = gpio_set_level(_init_config.s2_gpio_number, _cd74hc4067_matrix[gpio][2]);
    ZH_CD74HC4067_CHECK(err == ESP_OK, ESP_FAIL, "CD74HC4067 connect GPIO failed. GPIO driver internal error.");
    err = gpio_set_level(_init_config.s3_gpio_number, _cd74hc4067_matrix[gpio][3]);
    ZH_CD74HC4067_CHECK(err == ESP_OK, ESP_FAIL, "CD74HC4067 connect GPIO failed. GPIO driver internal error.");
    err = gpio_set_level(_init_config.en_gpio_number, 0);
    ZH_CD74HC4067_CHECK(err == ESP_OK, ESP_FAIL, "CD74HC4067 connect GPIO failed. GPIO driver internal error.");
    ZH_CD74HC4067_LOGI("CD74HC4067 connect GPIO completed successfully.");
    _connected_gpio = gpio;
    return (gpio_num_t)_init_config.control_gpio_number;
}

uint8_t zh_cd74hc4067_get(void)
{
    return _connected_gpio;
}

gpio_num_t zh_cd74hc4067_pin(void)
{
    return (gpio_num_t)_init_config.control_gpio_number;
}

static bool _zh_cd74hc4067_gpio_check(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t en, uint8_t control)
{
    uint8_t matrix[] = {s0, s1, s2, s3, en, control};
    for (uint8_t i = 0; i < sizeof(matrix); ++i)
    {
        for (uint8_t j = i + 1; j < sizeof(matrix); ++j)
        {
            if (matrix[i] == matrix[j])
            {
                return false;
            }
        }
    }
    return true;
}