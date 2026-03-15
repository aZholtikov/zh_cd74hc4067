#include "zh_cd74hc4067.h"

static const char *TAG = "zh_cd74hc4067";

#define ZH_LOGI(msg, ...) ESP_LOGI(TAG, msg, ##__VA_ARGS__)
#define ZH_LOGE(msg, err, ...) ESP_LOGE(TAG, "[%s:%d:%s] " msg, __FILE__, __LINE__, esp_err_to_name(err), ##__VA_ARGS__)

#define ZH_ERROR_CHECK(cond, err, cleanup, msg, ...) \
    if (!(cond))                                     \
    {                                                \
        ZH_LOGE(msg, err, ##__VA_ARGS__);            \
        cleanup;                                     \
        return err;                                  \
    }

static const uint32_t _cd74hc4067_matrix[16][4] = {
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
static zh_cd74hc4067_gpio_num_t _connected_gpio = ZH_CD74HC4067_GPIO_NUM_P0;
static bool _is_initialized = false;

static esp_err_t _zh_cd74hc4067_validate_config(const zh_cd74hc4067_init_config_t *config);
static esp_err_t _zh_cd74hc4067_gpio_init(const zh_cd74hc4067_init_config_t *config);

esp_err_t zh_cd74hc4067_init(const zh_cd74hc4067_init_config_t *config) // -V2008
{
    ZH_LOGI("CD74HC4067 initialization started.");
    ZH_ERROR_CHECK(config != NULL, ESP_ERR_INVALID_ARG, NULL, "CD74HC4067 initialization failed. Invalid argument.");
    ZH_ERROR_CHECK(_is_initialized == false, ESP_ERR_INVALID_STATE, NULL, "CD74HC4067 initialization failed. CD74HC4067 is already initialized.");
    esp_err_t err = _zh_cd74hc4067_validate_config(config);
    ZH_ERROR_CHECK(err == ESP_OK, err, NULL, "CD74HC4067 initialization failed. Invalid GPIO number.");
    err = _zh_cd74hc4067_gpio_init(config);
    ZH_ERROR_CHECK(err == ESP_OK, err, NULL, "CD74HC4067 initialization failed. GPIO initialization failed.");
    _init_config = *config;
    _is_initialized = true;
    ZH_LOGI("CD74HC4067 initialization completed successfully.");
    return ESP_OK;
}

gpio_num_t zh_cd74hc4067_set(zh_cd74hc4067_gpio_num_t gpio) // -V2008
{
    ZH_LOGI("CD74HC4067 connect GPIO started.");
    ZH_ERROR_CHECK(_is_initialized == true, GPIO_NUM_NC, NULL, "CD74HC4067 connect GPIO failed. CD74HC4067 not initialized.");
    ZH_ERROR_CHECK(gpio < ZH_CD74HC4067_GPIO_NUM_MAX, GPIO_NUM_NC, NULL, "CD74HC4067 initialization failed. Invalid argument.");
    esp_err_t err = gpio_set_level((gpio_num_t)_init_config.en_gpio_number, 1);
    ZH_ERROR_CHECK(err == ESP_OK, GPIO_NUM_NC, NULL, "CD74HC4067 connect GPIO failed. GPIO driver internal error.");
    err = gpio_set_level((gpio_num_t)_init_config.s0_gpio_number, _cd74hc4067_matrix[(uint8_t)gpio][0]);
    ZH_ERROR_CHECK(err == ESP_OK, GPIO_NUM_NC, NULL, "CD74HC4067 connect GPIO failed. GPIO driver internal error.");
    err = gpio_set_level((gpio_num_t)_init_config.s1_gpio_number, _cd74hc4067_matrix[(uint8_t)gpio][1]);
    ZH_ERROR_CHECK(err == ESP_OK, GPIO_NUM_NC, NULL, "CD74HC4067 connect GPIO failed. GPIO driver internal error.");
    err = gpio_set_level((gpio_num_t)_init_config.s2_gpio_number, _cd74hc4067_matrix[(uint8_t)gpio][2]);
    ZH_ERROR_CHECK(err == ESP_OK, GPIO_NUM_NC, NULL, "CD74HC4067 connect GPIO failed. GPIO driver internal error.");
    err = gpio_set_level((gpio_num_t)_init_config.s3_gpio_number, _cd74hc4067_matrix[(uint8_t)gpio][3]);
    ZH_ERROR_CHECK(err == ESP_OK, GPIO_NUM_NC, NULL, "CD74HC4067 connect GPIO failed. GPIO driver internal error.");
    err = gpio_set_level((gpio_num_t)_init_config.en_gpio_number, 0);
    ZH_ERROR_CHECK(err == ESP_OK, GPIO_NUM_NC, NULL, "CD74HC4067 connect GPIO failed. GPIO driver internal error.");
    ZH_LOGI("CD74HC4067 connect GPIO completed successfully.");
    _connected_gpio = gpio;
    return (gpio_num_t)_init_config.control_gpio_number;
}

zh_cd74hc4067_gpio_num_t zh_cd74hc4067_get(void)
{
    return _connected_gpio;
}

gpio_num_t zh_cd74hc4067_pin(void)
{
    return (gpio_num_t)_init_config.control_gpio_number;
}

static esp_err_t _zh_cd74hc4067_validate_config(const zh_cd74hc4067_init_config_t *config)
{
    ZH_ERROR_CHECK((config->s0_gpio_number < GPIO_NUM_MAX) && (config->s1_gpio_number < GPIO_NUM_MAX) &&
                       (config->s2_gpio_number < GPIO_NUM_MAX) && (config->s3_gpio_number < GPIO_NUM_MAX) &&
                       (config->en_gpio_number < GPIO_NUM_MAX) && (config->control_gpio_number < GPIO_NUM_MAX),
                   ESP_ERR_INVALID_ARG, NULL, "Invalid GPIO number.");
    uint8_t matrix[] = {config->s0_gpio_number, config->s1_gpio_number, config->s2_gpio_number, config->s3_gpio_number, config->en_gpio_number, config->control_gpio_number};
    for (uint8_t i = 0; i < sizeof(matrix); ++i)
    {
        for (uint8_t j = i + 1; j < sizeof(matrix); ++j)
        {
            ZH_ERROR_CHECK(matrix[i] != matrix[j], ESP_ERR_INVALID_ARG, NULL, "Invalid GPIO number.");
        }
    }
    return ESP_OK;
}

static esp_err_t _zh_cd74hc4067_gpio_init(const zh_cd74hc4067_init_config_t *config)
{
    gpio_config_t pin_config = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << config->s0_gpio_number) | (1ULL << config->s1_gpio_number) | (1ULL << config->s2_gpio_number) |
                        (1ULL << config->s3_gpio_number) | (1ULL << config->en_gpio_number),
    };
    esp_err_t err = gpio_config(&pin_config);
    ZH_ERROR_CHECK(err == ESP_OK, err, NULL, "GPIO initialization failed.");
    return ESP_OK;
}