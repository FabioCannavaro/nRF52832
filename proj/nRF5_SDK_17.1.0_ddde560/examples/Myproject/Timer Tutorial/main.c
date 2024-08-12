#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "nrf_drv_timer.h"
#include "bsp.h"
#include "app_error.h"


const nrfx_timer_t TIMER_LED = NRFX_TIMER_INSTANCE(0); //Timer 0 Enabled

#define LED1 17
#define LED4 20

void timer0_handler(nrf_timer_event_t event_type, void* p_context)
{
  switch(event_type)
  {
    case NRF_TIMER_EVENT_COMPARE0:

    nrf_gpio_pin_toggle(LED1);
    nrf_gpio_pin_toggle(LED4);
    break;


    default:

    break;
  }

}
void timer_init(void)
{
  uint32_t err_code = NRF_SUCCESS;

  uint32_t time_ms = 300;

  uint32_t time_ticks;

  nrfx_timer_config_t timer_cfg = NRFX_TIMER_DEFAULT_CONFIG; //Configure the timer instance to default settings


  err_code = nrfx_timer_init(&TIMER_LED, &timer_cfg, timer0_handler); //Initialize the timer0 with default settings
  APP_ERROR_CHECK(err_code); 

  time_ticks = nrfx_timer_ms_to_ticks(&TIMER_LED, time_ms);

  nrfx_timer_extended_compare(&TIMER_LED, NRF_TIMER_CC_CHANNEL0, time_ticks, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);


}

/**
 * @brief Function for main application entry.
 */
int main(void)
{
    nrf_gpio_cfg_output(LED1);
    nrf_gpio_cfg_output(LED4);

    nrf_gpio_pin_set(LED1);
    nrf_gpio_pin_set(LED4);

    timer_init();

      nrfx_timer_enable(&TIMER_LED);

    while (1)
    {
        __WFI();
    }
}

/** @} */
