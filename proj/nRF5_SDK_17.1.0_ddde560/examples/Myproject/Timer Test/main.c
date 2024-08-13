#include "nrf.h"
#include "nrf_gpio.h"

// LED 핀 설정
#define LED_PIN 17

volatile uint32_t counter = 0; // 상태 변화 감지 카운터 변수
volatile bool led_on = false;  // LED 상태 변수

// HFCLK 초기화 함수

void hfclk_init(void) {
    NRF_CLOCK->EVENTS_HFCLKSTARTED = 0; // 이벤트 레지스터 초기화
    NRF_CLOCK->TASKS_HFCLKSTART = 1;    // HFCLK 시작

    while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0);  // HFCLK 시작 대기
}


// GPIO 초기화 함수
void gpio_init(void) {
    nrf_gpio_cfg_output(LED_PIN); // GPIO 핀을 출력으로 설정
    nrf_gpio_pin_clear(LED_PIN);  // LED를 초기화 시   OFF 상태로 설정
}

// HFCLK 상태 변화 감지 함수
void check_hfclk_state_change(void) {
    // HFCLK 상태 확인
    bool current_state = (NRF_CLOCK->HFCLKSTAT & CLOCK_HFCLKSTAT_STATE_Msk) != 0;

    // 상태 변화 감지
    counter++; // 상태 변화마다 카운터 증가

    // 일정 시간마다   LED 토글
    if (counter >= 1000000) { // 1000000번 상태 변화 시    LED 토글
        counter = 0;
        if (led_on) {
            nrf_gpio_pin_clear(LED_PIN); // LED OFF
            led_on = false;
        } else {
            nrf_gpio_pin_set(LED_PIN);   // LED ON
            led_on = true;
        }
    }
}

int main(void) {
    gpio_init();   // GPIO 초기화
    hfclk_init();  // HFCLK 초기화

    // 메인 루프
    while (1) {
        check_hfclk_state_change(); // HFCLK 상태 변화 체크 및    LED 토글
    }

    return 0;
}
