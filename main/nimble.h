#ifndef NIMBLE_H
#define NIMBLE_H

extern TaskHandle_t xHandle;
extern char *notification;
extern bool notify_state;
void gatt_svr_register_cb(struct ble_gatt_register_ctxt *ctxt, void *arg);
//static int bleprph_gap_event(struct ble_gap_event *event, void *arg);
void sendNotification();
void vTasksendNotification();
void startBLE();
void stopBLE();
void startNVS();

void gpio_isr_init();

#endif

#define INPUT_PIN_D0 2 // GPIO2 Strapping Pin (SPI Boot & Download Boot)
#define INPUT_PIN_D1 3
#define INPUT_PIN_D2 4

#define REED_PIN INPUT_PIN_D0
#define TRG_PIN INPUT_PIN_D1
#define LED_PIN INPUT_PIN_D2
