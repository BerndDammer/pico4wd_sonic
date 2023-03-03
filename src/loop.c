#include "loop.h"
#include "blinker.h"
#include "ultrasonic.h"

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/watchdog.h"
#include "hardware/clocks.h"

#define CONSOLE_TIMEOUT 1000000

void menu(void)
{
    printf("------------------------------------\n");
    printf("- To Right \n");
    printf("+ To Left \n");
    printf("0 or (space) center\n");
    printf("press key to select\n");
    printf("------------------------------------\n");
}


void loop(void)
{
    volatile int c; // make visible in debugger; avoid optimize out
    int counter = 0;

    ultrasonic_init();

    menu();

    for (;;)
    {
        c = getchar_timeout_us(CONSOLE_TIMEOUT);
        blinker_toggle();

        if (c == PICO_ERROR_TIMEOUT)
        {
            printf("Loop Counter %i\n", counter);
            counter++;
        }
        else
        {
            switch (c)
            {
            case '+':
                break;
            case '-':
                break;
            case ' ':
            case '0':
                break;
            default:
                menu();
                break;
            }
            printf("Angle: %i\n", 12);
        }
    }
}
