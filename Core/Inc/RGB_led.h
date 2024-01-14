//
// Created by User on 1/9/2024.
//
#ifndef LED_PROJECT_RGB_LED_H
#define LED_PROJECT_RGB_LED_H
#include "stm32f4xx_hal.h"
/*structures*/
struct  LED_GPIO{
    GPIO_TypeDef RPort;
    uint16_t RPin;
    GPIO_TypeDef GPort;
    uint16_t GPin;
    GPIO_TypeDef BPort;
    uint16_t BPin;
};

/*LED_GPIO constructor */
struct LED_GPIO Init_LED(GPIO_TypeDef RPort, uint16_t RPin, GPIO_TypeDef GPort,
                         uint16_t GPin, GPIO_TypeDef BPort, uint16_t BPin) {
    struct LED_GPIO a;
    a.RPort = RPort;
    a.RPin = RPin;
    a.GPort = GPort;
    a.GPin = GPin;
    a.BPort = BPort;
    a.BPin = BPin;
    return a;
}
/*Function declaration*/





#endif //LED_PROJECT_RGB_LED_H
