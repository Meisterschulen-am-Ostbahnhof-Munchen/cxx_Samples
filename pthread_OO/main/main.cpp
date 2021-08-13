#include "freertos/FreeRTOS.h"
#include "esp_system.h"
#include <chrono>
#include <thread>

#include "Task1.h"
#include "Task2.h"

static bool s_closeApp = false;


extern "C" void app_main(void)
{


    /* prototypes for base and core running in their respective thread */
	AppTask::Task1 mTask1;
	AppTask::Task2 mTask2;

    /* start running core and base thread */
    std::thread mThread1(&AppTask::Task1::run, &mTask1);
    std::thread mThread2(&AppTask::Task2::run, &mTask2);

    /* wait for core and base being initialized */
    while ((!mTask1.isInitDone()) || (!mTask2.isInitDone()))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }


    /* sample main loop */
    mTask1.startCyclic();
    mTask2.startCyclic();

    while (!s_closeApp)
    {
    	std::this_thread::sleep_for(std::chrono::seconds(5));;  // check keyboard every "5ms"

    }

    mTask1.exit();
    mTask2.exit();

    mThread1.join();
    mThread2.join();

}

