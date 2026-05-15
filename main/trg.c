#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "pin.h"


static TimerHandle_t pulse_timer;

static void pulse_timer_cb(TimerHandle_t t)
{
    // This function callback did not get called after a delay after xTimerStart was called
    //
    // gpio_set_level(TRG_PIN, 0);
    // printf("trgpulse end\n");
}

void trg_pulse(void)

{
    printf("trgpulse\n");
    gpio_set_level(TRG_PIN, 1);
    vTaskDelay(500 / portTICK_PERIOD_MS); // 500 milliseconds
    gpio_set_level(TRG_PIN, 0);
}

void trg_init() {
    /*
    // xTimerCreate and xTimerStart did not work as expected because
    // pulse_timer_cb did not get called at all
    //
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
    */
}
