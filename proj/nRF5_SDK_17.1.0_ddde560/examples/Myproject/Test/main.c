#include "nrf.h"
#include "nrf_gpio.h"


#define LED_PIN 18


void lfclk_init(void) {
    NRF_CLOCK->LFCLKSRC = CLOCK_LFCLKSRC_SRC_RC;  // 내부 RC 오실레이터 사용
    NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;           // 이벤트 레지스터 초기화
    NRF_CLOCK->TASKS_LFCLKSTART = 1;              // LFCLK 시작

    while (NRF_CLOCK->EVENTS_LFCLKSTARTED == 0);  // LFCLK 시작 대기

    // LFCLK 상태 확인
    if (NRF_CLOCK->LFCLKSTAT & CLOCK_LFCLKSTAT_STATE_Msk) {
        NRF_GPIO->OUTSET = (1 << LED_PIN);  // LFCLK 활성화됨 ->  LED 켜기
    } else {
        NRF_GPIO->OUTCLR = (1 << LED_PIN);  // LFCLK 비활성화됨 ->   LED 끄기
    }
}

void hfclk_init(void) {
    NRF_CLOCK->EVENTS_HFCLKSTARTED = 0; // 이벤트 레지스터 초기화
    NRF_CLOCK->TASKS_HFCLKSTART = 1;    // HFCLK 시작

    while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0); // HFCLK 시작 대기

    // HFCLK 상태 확인
    if (NRF_CLOCK->HFCLKSTAT & CLOCK_HFCLKSTAT_STATE_Msk) {
        NRF_GPIO->OUTSET = (1 << LED_PIN);  // HFCLK 활성화됨 ->  LED 켜기
    } else {
        NRF_GPIO->OUTCLR = (1 << LED_PIN);  // HFCLK 비활성화됨 ->   LED 끄기
    }
}



void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms * 1000; i++) {
        __NOP();
    }
}

int main(void) {
    nrf_gpio_cfg_output(LED_PIN);

    lfclk_init(); 
    hfclk_init();  

    while (1) {

        nrf_gpio_pin_toggle(LED_PIN);
        delay_ms(500);
    }

    return 0;
}
