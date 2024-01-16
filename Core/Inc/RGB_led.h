//
// Created by User on 1/9/2024.
//
#ifndef LED_PROJECT_RGB_LED_H
#define LED_PROJECT_RGB_LED_H

#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "colors.h"
/*structures*/
/*Function declaration*/
void parseString(char *input);

void LED_setColorRGB(uint8_t R, uint8_t G, uint8_t B);

void LED_setColor(enum Color color);

void LED_continuousTransformationMode();

void LED_pulseMode();

#endif //LED_PROJECT_RGB_LED_H
