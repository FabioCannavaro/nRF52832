#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "nrf_gpio.h"


#define LED 17

#define Button 13
/**
 * @brief Function for application main entry. 
 */


int main(void)
{
    /* Configure board. */
    printf("Main Application Started \r\n");
    nrf_gpio_cfg_output(LED); //Configure the led pin as OUTPUT pin

    nrf_gpio_cfg_input(Button, NRF_GPIO_PIN_PULLUP); //Configures the Button Pin as input Pin
     
    nrf_gpio_pin_set(LED); //Turns off the LED

    /* Toggle LEDs. */
    while (true)
    {
      if(nrf_gpio_pin_read(Button)==0)
      {
        nrf_gpio_pin_clear(LED); //Turn on the LED
        printf("Button in Pressed state!!\r\n");

        while(nrf_gpio_pin_read(Button)==0); //Stay in this Loop until the button is released

        nrf_gpio_pin_set(LED); //Turn off the LED
        printf("Button in Released state!!\r\n");
      }
    }
}

/**
 *@}
 **/
