#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "nrf_gpio.h"


#define led 17
#define led2 19
/**
 * @brief Function for application main entry.
 */
int main(void)
{
    nrf_gpio_cfg_output(led); //configures the pin as output pin
    nrf_gpio_cfg_output(led2);

    while(1)
    {
      nrf_gpio_pin_set(led); //Setting logic 1 on pin 17
      nrf_delay_ms(100);
      nrf_gpio_pin_clear(led); //Setting logic 0 on pin 17
      nrf_delay_ms(100);

      nrf_gpio_pin_toggle(led2);

    }
}

/**
 *@}
 **/
