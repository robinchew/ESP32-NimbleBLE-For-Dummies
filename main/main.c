#include "esp_log.h"
#include "esp_pm.h"
#include "esp_sleep.h"
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

    while(1) {
        ESP_LOGI(tag, "wait...");
        vTaskDelay(10000 / portTICK_PERIOD_MS);

        esp_sleep_enable_bt_wakeup();
        ESP_LOGI(tag, "light sleeping...");
        // esp_bt_controller_disable();
        esp_light_sleep_start();
        ESP_LOGI(tag, "continue from light sleep");
    }
}
