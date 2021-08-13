/* 
*/

#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <string>
#include <sstream>
#include <esp_pthread.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>


#include "Task1.h"
#include "Task2.h"
#include "print_thread_info.h"

static bool s_closeApp = false;


using namespace std::chrono;

const auto sleep_time = seconds
{
    5
};






extern "C" void app_main(void)
{


    /* prototypes for mTask1 and mTask2 running in their respective thread */
	AppTask::Task1 mTask1;
	AppTask::Task2 mTask2;

	mTask1.setMilliCycle(sleep_time);
	mTask2.setMilliCycle(sleep_time);

    /* start running Thread1 and Thread2 thread */
	// Create a thread on core 1.
    auto cfg1 = mTask1.create_config("Thread 1", 1, 3 * 1024, 5);
    esp_pthread_set_cfg(&cfg1);
    std::thread mThread1(&AppTask::Task1::run, &mTask1);
    // Create a thread on core 1.
    auto cfg2 = mTask2.create_config("Thread 2", 1, 3 * 1024, 5);
    esp_pthread_set_cfg(&cfg2);
    std::thread mThread2(&AppTask::Task2::run, &mTask2);

    /* wait for core and base being initialized */
    while ((!mTask1.isInitDone()) || (!mTask2.isInitDone()))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }


    /* sample main loop */
    mTask1.startCyclic();
    mTask2.startCyclic();
	
	
    // Let the main task do something too
    while (!s_closeApp)
    {
        print_thread_info("This thread is the main Task.");
        std::this_thread::sleep_for(sleep_time);
    }

    mTask1.exit();
    mTask2.exit();

    mThread1.join();
    mThread2.join();

}
