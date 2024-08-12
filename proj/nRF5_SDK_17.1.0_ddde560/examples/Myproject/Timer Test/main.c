#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "nrf_drv_timer.h"
#include "boards.h"
#include "app_error.h"

// LED 핀 설정
#define LED_PIN 19


const nrf_drv_timer_t TIMER_LED = NRF_DRV_TIMER_INSTANCE(0);

void timer_handler(nrf_timer_event_t event_type, void* p_context) {
    nrf_gpio_pin_toggle(LED_PIN);
}

void lfclk_init(void) {
    NRF_CLOCK->LFCLKSRC = CLOCK_LFCLKSRC_SRC_RC; //NRF_CLOCK은 nRF52832에 접근할 수 있는 구조체,     LFCLK가 내부  RC 오실레이터로부터 클럭 신호를 받아 동작하도록 설정         

    NRF_CLOCK->EVENTS_LFCLKSTARTED = 0; //LFCLK가 시작되었음을 나타내는 이벤트 플래그를 초기화
    NRF_CLOCK->TASKS_LFCLKSTART = 1;    // LFCLK 시작 

    while (NRF_CLOCK->EVENTS_LFCLKSTARTED == 0); // LFCLK가 완전히 시작될 때까지 대기하는 역할

}

void hfclk_init(void) {
    NRF_CLOCK->EVENTS_HFCLKSTARTED = 0; // HFCLK가 시작되었음을 나타내는 이벤트 플래그를 초기화
    NRF_CLOCK->TASKS_HFCLKSTART = 1;    // HFCLK 시작 

    while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0);//HFCLK가 완전히 시작할 때까지 대기하는 역할

}

void timer_init(void) {
    uint32_t time_ms = 300; // LED 토글 주기 (1초)
    uint32_t time_ticks;

    // 타이머 초기화
    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
    APP_ERROR_CHECK(nrf_drv_timer_init(&TIMER_LED, &timer_cfg, timer_handler));

    time_ticks = nrf_drv_timer_ms_to_ticks(&TIMER_LED, time_ms);

    nrf_drv_timer_extended_compare(
         &TIMER_LED, NRF_TIMER_CC_CHANNEL0, time_ticks, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);

    // 타이머 시작
    nrf_drv_timer_enable(&TIMER_LED);
}

int main(void) {
    lfclk_init();  // LFCLK 초기화
    hfclk_init();  // HFCLK 초기화

    // LED 핀 초기화
    nrf_gpio_cfg_output(LED_PIN);

    timer_init();  // 타이머 초기화

    while (1) {
        __WFE();  // 이벤트 대기 (저전력 모드)
    }
}

/** @} */
