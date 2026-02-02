#include "esp_log.h"
#include "esp_pm.h"
#include "esp_sleep.h"
#include "driver/gpio.h"
#include "nvs_flash.h"
#include "esp_nimble_hci.h"
#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"
#include "host/ble_hs.h"
#include "host/util/util.h"
#include "console/console.h"
#include "services/gap/ble_svc_gap.h"
#include "bleprph.h"
#include "nimble.h"
#include "trg.h"

static const char *tag = "Main";

void app_main(void)
{
    esp_pm_config_t pm_config = {
            .max_freq_mhz = 80,
            .min_freq_mhz = 40,
            .light_sleep_enable = true
    };
    // CANNOT USE ESP_ERROR_CHECK OR ELSE STACK DUMP BOOT LOOP
    // ESP_ERROR_CHECK( esp_pm_configure(&pm_config) );
    esp_pm_configure(&pm_config);

    ESP_LOGI(tag, "start");

    startNVS();
    startBLE();

    ESP_LOGI(tag, "startble");

    //!! Start the FreeRTOS task to notify the client
    notification="Hello There";
    xTaskCreate(vTasksendNotification, "vTasksendNotification", 4096, NULL, 1, &xHandle);

    gpio_config_t output_conf = {
        // Set pull down resistor
        // for simple output
        .pin_bit_mask = 1ULL << TRG_PIN,
        .mode = GPIO_MODE_OUTPUT,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&output_conf);

    gpio_config_t reed_input_conf = {
        // Set pull down resistor
        // for simple read
        .pin_bit_mask = 1ULL << REED_PIN,
        .mode = GPIO_MODE_INPUT,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&reed_input_conf);

    gpio_isr_init();
    trg_init();

    /*
    while(1) {
        ESP_LOGI(tag, "wait...");
        vTaskDelay(10000 / portTICK_PERIOD_MS);

        esp_sleep_enable_bt_wakeup();
        ESP_LOGI(tag, "light sleeping...");
        // esp_bt_controller_disable();
        esp_light_sleep_start();
        ESP_LOGI(tag, "continue from light sleep");
    }
    */
}
