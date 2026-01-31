#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "pin.h"


static TimerHandle_t pulse_timer;

// Timer callback to turn output off
static void pulse_timer_cb(TimerHandle_t t)
{
    gpio_set_level(TRG_PIN, 0);
}

void trg_pulse(void)

{
    gpio_set_level(TRG_PIN, 1);
    xTimerStart(pulse_timer, 0);
}

void trg_init() {
    // Create timer (10 seconds)
    pulse_timer = xTimerCreate(
        "pulse_timer",
        // 10ms, DO NOT USE any lower or else you will get boot loop with:
        // assert failed: prvInitialiseNewTimer timers.c:428 (( xTimerPeriodInTicks > 0 ))
        // https://www.reddit.com/r/esp32/comments/pa47q9/assert_failed_prvinitialisenewtimer_timersc365/
        pdMS_TO_TICKS(10),
        pdFALSE,                // one-shot timer
        NULL,
        pulse_timer_cb
    );
}
