#ifndef NIMBLE_H
#define NIMBLE_H

extern TaskHandle_t xHandle;
extern char *notification;
extern bool notify_state;
void gatt_svr_register_cb(struct ble_gatt_register_ctxt *ctxt, void *arg);
//static int bleprph_gap_event(struct ble_gap_event *event, void *arg);
void vTasksendNotification();
void startBLE();
void stopBLE();
void startNVS();

void gpio_isr_led_init();
void gpio_isr_reed_init();
void queue_init();

#endif
