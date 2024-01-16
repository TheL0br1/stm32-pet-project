#include "RGB_led.h"
#include "stm32f4xx_it.h"



#define min(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })
#define max(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })


#define ARR_DIV 2.55
#define ARR_1SECOND_VALUE 100
#define CCR_MAX_VALUE 100
#define ADC_NOISE_VALUE 2070
#define ADC_DIV 1


extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim2;
static uint8_t pulseCounter;
static uint8_t currentColor;
static float pulseFrequency;
uint8_t LedMode;
uint8_t displayMode;
int16_t microphoneValue;

//util function to change timer frequency
void update_arr(TIM_HandleTypeDef *htim, uint16_t arr) {
    __HAL_TIM_SET_AUTORELOAD(htim, arr);
    if (__HAL_TIM_GET_COUNTER(htim) >= __HAL_TIM_GET_AUTORELOAD(htim)) {
        htim->Instance->EGR |= TIM_EGR_UG;
    }
}

void parseString(char *input) {

    displayMode = 0;

    char *token;
    switch (input[0]) {
        case 'c':
            LED_setColor(strtoul(&input[1], NULL, 10));
            break;
        case 'm': {
            HAL_TIM_Base_Stop_IT(&htim3);
            HAL_TIM_Base_Stop_IT(&htim2);
            token = strtok(input, ";");
            LedMode = strtoul(&token[1], NULL, 10);
            switch (LedMode) {
                case 0:
                    token = strtok(NULL, ";");
                    currentColor = strtoul(token, NULL, 10);
                    token = strtok(NULL, ";");
                    pulseFrequency = strtof(token, NULL);
                    update_arr(&htim3, pulseFrequency * ARR_1SECOND_VALUE);
                    HAL_TIM_Base_Start_IT(&htim3);
                    break;
                case 1:
                    token = strtok(NULL, ";");
                    pulseFrequency = strtof(token, NULL);
                    update_arr(&htim3, pulseFrequency * ARR_1SECOND_VALUE);
                    HAL_TIM_Base_Start_IT(&htim3);
                    break;
                case 2:
                    token = strtok(NULL, ";");
                    pulseFrequency = strtof(token, NULL);
                    update_arr(&htim3, pulseFrequency * ARR_1SECOND_VALUE);
                    HAL_TIM_Base_Start_IT(&htim3);
                    break;
                case 3:
                    token = strtok(NULL, ";");
                    pulseFrequency = strtof(token, NULL);
                    update_arr(&htim3, pulseFrequency * ARR_1SECOND_VALUE);
                    HAL_TIM_Base_Start_IT(&htim3);
                    break;
                case 4:
                    token = strtok(NULL, ";");
                    currentColor = strtoul(token, NULL, 10);
                    token = strtok(NULL, ";");
                    pulseFrequency = strtof(token, NULL);
                    update_arr(&htim3, pulseFrequency * ARR_1SECOND_VALUE);
                    HAL_TIM_Base_Start_IT(&htim2);
                    HAL_TIM_Base_Start_IT(&htim3);
                    break;
            }
            break;
        }

        case 'd':
            token = strtok(input, ";");
            displayMode = strtoul(&token[1], NULL, 10);
            break;

        default:
            token = strtok(input, ";");
            uint8_t var1 = strtoul(token, NULL, 10);
            token = strtok(NULL, ";");

            uint8_t var2 = strtoul(token, NULL, 10);
            token = strtok(NULL, ";");

            uint8_t var3 = strtoul(token, NULL, 10);
            LED_setColorRGB(var1, var2, var3);
            break;
    }



}

void LED_setColorRGB(uint8_t R, uint8_t G, uint8_t B) {
    TIM1->CCR1 = R;
    TIM1->CCR2 = G;
    TIM1->CCR3 = B;
    prepateLCDMessage();

}

void LED_setColor(enum Color color) {
    TIM1->CCR1 = colorValues[color].red / ARR_DIV;
    TIM1->CCR2 = colorValues[color].green / ARR_DIV;
    TIM1->CCR3 = colorValues[color].blue / ARR_DIV;
    prepateLCDMessage();

}

void LED_pulseMode() {
    TIM1->CCR1 = colorValues[currentColor].red / ARR_DIV - pulseCounter;
    TIM1->CCR2 = colorValues[currentColor].green / ARR_DIV - pulseCounter;
    TIM1->CCR3 = colorValues[currentColor].blue / ARR_DIV - pulseCounter;
    pulseCounter++;
    if (pulseCounter >= CCR_MAX_VALUE) {
        pulseCounter = 0;
        prepateLCDMessage();

    }
}

void LED_continuousTransformationMode() {
    TIM1->CCR1 = colorValues[currentColor].red / ARR_DIV - pulseCounter;
    TIM1->CCR2 = colorValues[currentColor].green / ARR_DIV - pulseCounter;
    TIM1->CCR3 = colorValues[currentColor].blue / ARR_DIV - pulseCounter;
    pulseCounter++;
    if (pulseCounter >= CCR_MAX_VALUE) {
        pulseCounter = 0;
        currentColor++;
        currentColor %= 11;
        prepateLCDMessage();

    }
}

void LED_continuousColorChangeMode() {
    TIM1->CCR1 = colorValues[currentColor].red / ARR_DIV;
    TIM1->CCR2 = colorValues[currentColor].green / ARR_DIV;
    TIM1->CCR3 = colorValues[currentColor].blue / ARR_DIV;
    pulseCounter++;
    if (pulseCounter >= CCR_MAX_VALUE) {
        pulseCounter = 0;
        currentColor++;
        currentColor %= 12;
        prepateLCDMessage();

    }
}

void LED_randomColorMode() {
    pulseCounter++;
    if (pulseCounter >= CCR_MAX_VALUE) {
        pulseCounter = 0;
        TIM1->CCR1 = rand() % 100;
        TIM1->CCR2 = rand() % 100;
        TIM1->CCR3 = rand() % 100;
        prepateLCDMessage();

    }
}

void LED_microphoneMode() {
    pulseCounter++;
    if (pulseCounter >= CCR_MAX_VALUE) {
        pulseCounter = 0;
        TIM1->CCR1 = min(100, max(0, microphoneValue - ADC_NOISE_VALUE)) /
                     ADC_DIV * ((float) colorValues[currentColor].red / (float) UCHAR_MAX);
        TIM1->CCR2 = min(100, max(0, microphoneValue - ADC_NOISE_VALUE)) /
                     ADC_DIV * ((float) colorValues[currentColor].green / (float) UCHAR_MAX);
        TIM1->CCR3 = min(100, max(0, microphoneValue - ADC_NOISE_VALUE)) /
                     ADC_DIV * ((float) colorValues[currentColor].blue / (float) UCHAR_MAX);
        prepateLCDMessage();
    }

}

void prepateLCDMessage() {
    if (!displayMode) return;
    char a[20];
    switch (displayMode) {
        case 1:
            sprintf(a, "%lu;%lu;%lu", TIM1->CCR1, TIM1->CCR2, TIM1->CCR3);
            LCD_clrScr();
            LCD_print(a, 4, 3);
            break;

    }
}
