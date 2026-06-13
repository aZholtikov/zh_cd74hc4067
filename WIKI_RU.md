# zh_cd74hc4067 - Компонент мультиплексора CD74HC4067 для ESP-IDF

## Содержание

- [Обзор](#обзор)
- [Возможности](#возможности)
- [Установка](#установка)
- [Подключение пинов](#подключение-пинов)
- [Справочник API](#справочник-api)
- [Примеры использования](#примеры-использования)
- [Технические характеристики](#технические-характеристики)
- [Коды ошибок](#коды-ошибок)
- [Вклад в проект](#вклад-в-проект)
- [Лицензия](#лицензия)

---

## Обзор

`zh_cd74hc4067` - это легковесный компонент ESP-IDF для управления мультиплексором CD74HC4067 с 16 каналами. Он предоставляет простой API для подключения одного из 16 GPIO пинов мультиплексора к одному GPIO пину ESP. Компонент разработан специально для микроконтроллеров ESP32 и использует драйверы ESP-IDF (GPIO).

CD74HC4067 - это 16-канальный аналоговый мультиплексор, который позволяет управлять 16 различными сигналами, используя только 5 GPIO пинов (4 управляющих пина + 1 сигнальный пин) на вашем ESP32.

---

## Возможности

1. **16-канальный мультиплексинг**: Подключение одного из 16 GPIO пинов к одному управляющему пину
2. **Простой интерфейс управления**: Использование пинов S0-S3 для выбора каналов
3. **Управление включением**: Выделенный пин EN для включения/выключения мультиплексора
4. **Полная поддержка GPIO**: Поддержка всех стандартных операций GPIO (цифровое чтение/запись, прерывание, ADC, PWM и т.д.)
5. **Обработка ошибок**: Комплексная проверка ошибок и валидация
6. **Потокобезопасность**: Использует драйверы ESP-IDF (потокобезопасно)
7. **Минимальный объем памяти**: Низкие накладные расходы на память
8. **Простой API**: Легкое в использовании интерфейс

---

## Установка

1. Перейдите в каталог компонентов вашего проекта:

```bash
cd ../ваш_проект/components
```

2. Клонируйте репозиторий:

```bash
git clone https://github.com/aZholtikov/zh_cd74hc4067.git
```

3. В вашем приложении подключите заголовочный файл:

```c
#include "zh_cd74hc4067.h"
```

4. Компонент будет автоматически собран вместе с вашим проектом.

---

## Подключение пинов

Для мультиплексора CD74HC4067 требуются следующие подключения:

| Пин CD74HC4067 | Описание | Подключение к ESP32 |
|----------------|----------|---------------------|
| S0, S1, S2, S3 | Адресные пины выбора | Любые 4 GPIO пина |
| EN | Пин включения (активный низкий уровень) | Любой GPIO пин |
| SIG | Сигнальный пин (ввод/вывод) | Ваш управляющий GPIO пин |
| P0-P15 | 16 каналов мультиплексора | Ваши 16 GPIO пинов для управления |

### Структура конфигурации пинов

```c
typedef struct
{
    gpio_num_t s0_gpio_number;      // GPIO, подключенный к S0 мультиплексора CD74HC4067
    gpio_num_t s1_gpio_number;      // GPIO, подключенный к S1 мультиплексора CD74HC4067
    gpio_num_t s2_gpio_number;      // GPIO, подключенный к S2 мультиплексора CD74HC4067
    gpio_num_t s3_gpio_number;      // GPIO, подключенный к S3 мультиплексора CD74HC4067
    gpio_num_t control_gpio_number; // GPIO, подключенный к SIG мультиплексора CD74HC4067
    gpio_num_t en_gpio_number;      // GPIO, подключенный к EN мультиплексора CD74HC4067
} zh_cd74hc4067_init_config_t;
```

---

## Справочник API

### Структура zh_cd74hc4067_init_config_t

```c
typedef struct
{
    gpio_num_t s0_gpio_number;      // GPIO, подключенный к S0 мультиплексора CD74HC4067
    gpio_num_t s1_gpio_number;      // GPIO, подключенный к S1 мультиплексора CD74HC4067
    gpio_num_t s2_gpio_number;      // GPIO, подключенный к S2 мультиплексора CD74HC4067
    gpio_num_t s3_gpio_number;      // GPIO, подключенный к S3 мультиплексора CD74HC4067
    gpio_num_t control_gpio_number; // GPIO, подключенный к SIG мультиплексора CD74HC4067
    gpio_num_t en_gpio_number;      // GPIO, подключенный к EN мультиплексора CD74HC4067
} zh_cd74hc4067_init_config_t;
```

Используйте макрос `ZH_CD74HC4067_INIT_CONFIG_DEFAULT()` для инициализации значениями по умолчанию:

- `s0_gpio_number`: GPIO_NUM_MAX
- `s1_gpio_number`: GPIO_NUM_MAX
- `s2_gpio_number`: GPIO_NUM_MAX
- `s3_gpio_number`: GPIO_NUM_MAX
- `control_gpio_number`: GPIO_NUM_MAX
- `en_gpio_number`: GPIO_NUM_MAX

---

### Перечисление zh_cd74hc4067_gpio_num_t

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

Инициализирует мультиплексор CD74HC4067.

**Параметры:**

- `config` - Указатель на структуру конфигурации инициализации CD74HC4067

**Возвращает:**

- `ESP_OK` - Успех
- `ESP_ERR_INVALID_ARG` - Неверный аргумент (NULL config или неверный GPIO)
- `ESP_ERR_INVALID_STATE` - CD74HC4067 уже инициализирован
- `ESP_FAIL` - Ошибка инициализации (GPIO инициализация)

**Пример:**

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

Устанавливает GPIO CD74HC4067 для подключения.

**Параметры:**

- `gpio` - Номер GPIO для подключения (ZH_CD74HC4067_GPIO_NUM_P0 до ZH_CD74HC4067_GPIO_NUM_P15)

**Возвращает:**

- Номер управляющего GPIO (успех)
- `GPIO_NUM_NC` (ошибка)

**Пример:**

```c
zh_cd74hc4067_set(ZH_CD74HC4067_GPIO_NUM_P5);
```

---

### zh_cd74hc4067_get()

Получает текущий подключенный GPIO CD74HC4067.

**Возвращает:**

- Номер GPIO (успех)
- Текущий подключенный GPIO

**Пример:**

```c
zh_cd74hc4067_gpio_num_t current = zh_cd74hc4067_get();
printf("Текущий подключенный GPIO: %d\n", current);
```

---

### zh_cd74hc4067_pin()

Получает номер управляющего GPIO CD74HC4067.

**Возвращает:**

- Номер управляющего GPIO

**Пример:**

```c
printf("Номер управляющего GPIO: %d\n", zh_cd74hc4067_pin());
```

---

## Примеры использования

### Базовый пример: Цифровое чтение и запись

```c
#include "zh_cd74hc4067.h"

void app_main(void)
{
    esp_log_level_set("zh_cd74hc4067", ESP_LOG_ERROR);
    // Настройка управляющего GPIO
    gpio_config_t pin_config = {
        .pin_bit_mask = (1ULL << GPIO_NUM_4)};
    gpio_config(&pin_config);
    // Инициализация CD74HC4067
    zh_cd74hc4067_init_config_t config = ZH_CD74HC4067_INIT_CONFIG_DEFAULT();
    config.control_gpio_number = GPIO_NUM_4;
    config.en_gpio_number = GPIO_NUM_18;
    config.s0_gpio_number = GPIO_NUM_19;
    config.s1_gpio_number = GPIO_NUM_20;
    config.s2_gpio_number = GPIO_NUM_21;
    config.s3_gpio_number = GPIO_NUM_22;
    zh_cd74hc4067_init(&config);
    // Настройка GPIO P5 и запись низкого уровня
    gpio_set_direction(zh_cd74hc4067_pin(), GPIO_MODE_OUTPUT);
    zh_cd74hc4067_set(ZH_CD74HC4067_GPIO_NUM_P5);
    printf("Текущий подключенный номер GPIO: %d.\n", zh_cd74hc4067_get());
    gpio_set_level(zh_cd74hc4067_pin(), 0);
    // Настройка GPIO P11 и чтение уровня
    gpio_set_direction(zh_cd74hc4067_pin(), GPIO_MODE_INPUT);
    zh_cd74hc4067_set(ZH_CD74HC4067_GPIO_NUM_P11);
    printf("Текущий подключенный номер GPIO: %d.\n", zh_cd74hc4067_get());
    printf("Уровень GPIO %d: %d.\n", zh_cd74hc4067_get(), gpio_get_level(zh_cd74hc4067_pin()));
    // Настройка GPIO P15
    zh_cd74hc4067_set(ZH_CD74HC4067_GPIO_NUM_P15);
    printf("Текущий подключенный номер GPIO: %d.\n", zh_cd74hc4067_get());
}
```

---

### Пример: Считывание нескольких аналоговых датчиков

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
    // Настройка управляющего GPIO
    gpio_config_t pin_config = {
        .pin_bit_mask = (1ULL << CONTROL_GPIO)};
    gpio_config(&pin_config);
    // Инициализация CD74HC4067
    zh_cd74hc4067_init_config_t config = ZH_CD74HC4067_INIT_CONFIG_DEFAULT();
    config.control_gpio_number = CONTROL_GPIO;
    config.en_gpio_number = EN_GPIO;
    config.s0_gpio_number = S0_GPIO;
    config.s1_gpio_number = S1_GPIO;
    config.s2_gpio_number = S2_GPIO;
    config.s3_gpio_number = S3_GPIO;
    zh_cd74hc4067_init(&config);
    // Настройка ADC
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
    // Считывание со всех 16 каналов
    for (int i = 0; i < 16; i++)
    {
        zh_cd74hc4067_set((zh_cd74hc4067_gpio_num_t)i);
        int raw = adc1_get_raw(ADC1_CHANNEL_0);
        printf("Канал P%d: %d\n", i, raw);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
```

---

### Пример: Управление несколькими реле

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
    // Настройка управляющего GPIO
    gpio_config_t pin_config = {
        .pin_bit_mask = (1ULL << CONTROL_GPIO)};
    gpio_config(&pin_config);
    // Инициализация CD74HC4067
    zh_cd74hc4067_init_config_t config = ZH_CD74HC4067_INIT_CONFIG_DEFAULT();
    config.control_gpio_number = CONTROL_GPIO;
    config.en_gpio_number = EN_GPIO;
    config.s0_gpio_number = S0_GPIO;
    config.s1_gpio_number = S1_GPIO;
    config.s2_gpio_number = S2_GPIO;
    config.s3_gpio_number = S3_GPIO;
    zh_cd74hc4067_init(&config);
    // Настройка как выход
    gpio_set_direction(zh_cd74hc4067_pin(), GPIO_MODE_OUTPUT);
    // Перебор всех реле
    for (int i = 0; i < 16; i++)
    {
        zh_cd74hc4067_set((zh_cd74hc4067_gpio_num_t)i);
        gpio_set_level(zh_cd74hc4067_pin(), 1);
        printf("Реле P%d ВКЛ\n", i);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        gpio_set_level(zh_cd74hc4067_pin(), 0);
        printf("Реле P%d ВЫКЛ\n", i);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
```

---

## Технические характеристики

| Параметр | Значение |
|----------|----------|
| **Каналы** | 16 (P0-P15) |
| **Управляющие пины** | 4 (S0-S3) |
| **Пин включения** | 1 (EN) |
| **Сигнальный пин** | 1 (SIG) |
| **Требуемые GPIO пины** | 6 всего |
| **Тип** | Аналоговый мультиплексор/демультиплексор |
| **Версия ESP-IDF** | >= 5.0 |
| **Платформа** | Семейство ESP32 |
| **Язык** | C (C99) |

---

## Коды ошибок

| Код ошибки | Описание |
|------------|----------|
| `ESP_OK` | Операция выполнена успешно |
| `ESP_ERR_INVALID_ARG` | Неверный аргумент (NULL указатель, неверный GPIO или неверный номер канала) |
| `ESP_ERR_INVALID_STATE` | CD74HC4067 не инициализирован |
| `ESP_FAIL` | Общая ошибка (GPIO инициализация) |

---

## Вклад в проект

Вклад приветствуется! Чтобы внести свой вклад:

1. Сделайте форк репозитория
2. Создайте ветку функции (`git checkout -b feature/AmazingFeature`)
3. Закоммитьте ваши изменения (`git commit -m 'Add some AmazingFeature'`)
4. Отправьте в ветку (`git push origin feature/AmazingFeature`)
5. Откройте Pull Request

Пожалуйста, убедитесь, что ваш код следует существующему стилю и включает соответствующую документацию.

---

## Лицензия

Этот проект лицензирован по лицензии Apache, версия 2.0 - см. файл [LICENSE](LICENSE) для подробной информации.

### Apache License, Version 2.0

Авторское право (c) 2026 Алексей Жолтиков

Лицензировано по лицензии Apache License, Version 2.0 (далее — "Лицензия");
вы не можете использовать этот файл, кроме случаев, предусмотренных Лицензией.
Копию Лицензии можно получить по адресу:

    http://www.apache.org/licenses/LICENSE-2.0

Если иное не требуется действующим законодательством или не согласовано в письменном виде,
программное обеспечение, распространяемое по Лицензии, распространяется на условиях "КАК ЕСТЬ",
БЕЗ КАКИХ-ЛИБО ГАРАНТИЙ, явных или подразумеваемых, включая, но не ограничиваясь, гарантии
ТОВАРНОГО СОСТОЯНИЯ, ПРИГОДНОСТИ ДЛЯ КОНКРЕТНОЙ ЦЕЛИ И НЕНАРУШЕНИЯ ПРАВ.
Смотрите Лицензию для получения конкретных прав и ограничений.

---

## Дополнительные заметки

- **EN GPIO**: Пин EN на CD74HC4067 должен быть подключен к ESP и настроен в инициализации
- **Операции GPIO**: После настройки канала вы можете использовать все стандартные операции GPIO (цифровое чтение/запись, прерывание, ADC, PWM и т.д.)
- **Выбор канала**: Каналы выбираются с помощью двоичного кодирования на пинах S0-S3
- **Потокобезопасность**: Компонент использует драйверы ESP-IDF, которые являются потокобезопасными
- **Проверка пинов**: Библиотека проверяет, что все номера GPIO уникальны и действительны во время инициализации

---

*Сгенерировано для zh_cd74hc4067 v1.1.0*
