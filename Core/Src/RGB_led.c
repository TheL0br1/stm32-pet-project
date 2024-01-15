#include "RGB_led.h"
#include "stm32f4xx_it.h"
#include <stdlib.h>
#include <string.h>

void parse_string(char *input) {
    if (input[0] == 'c') {
        LED_setColor(strtoul(&input[1], NULL, 10));
        return;
    }
    char *token = strtok(input, ";");
    uint8_t var1 = strtoul(token, NULL, 10);
    token = strtok(NULL, ";");

    uint8_t var2 = strtoul(token, NULL, 10);
    token = strtok(NULL, ";");

    uint8_t var3 = strtoul(token, NULL, 10);
    LED_setColorRGB(var1, var2, var3);

}

void LED_setColorRGB(uint8_t R, uint8_t G, uint8_t B) {
    TIM1->CCR1 = R;
    TIM1->CCR2 = G;
    TIM1->CCR3 = B;
}

void LED_setColor(enum Color color) {
    TIM1->CCR1 = colorValues[color].red / 2.55;
    TIM1->CCR2 = colorValues[color].green / 2.55;
    TIM1->CCR3 = colorValues[color].blue / 2.55;
}
