#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"


/* Inside .cpp file, app_main function must be declared with C linkage */
extern "C" void app_main(void)
{

    while (true) {

        vTaskDelay(300 / portTICK_PERIOD_MS);
    }
}

