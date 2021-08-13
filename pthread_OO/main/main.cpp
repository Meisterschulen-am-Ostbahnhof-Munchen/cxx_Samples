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



void thread_func_inherited()
{
    while (true) {
        print_thread_info("This is the INHERITING thread with the same parameters as our parent, including name. ");
        std::this_thread::sleep_for(sleep_time);
    }
}

void spawn_another_thread()
{
    // Create a new thread, it will inherit our configuration
    std::thread inherits(thread_func_inherited);

    while (true) {
        print_thread_info();
        std::this_thread::sleep_for(sleep_time);
    }
}

void thread_func_any_core()
{
    while (true) {
        print_thread_info("This thread (with the default name) may run on any core.");
        std::this_thread::sleep_for(sleep_time);
    }
}

void thread_func()
{
    while (true) {
        print_thread_info();
        std::this_thread::sleep_for(sleep_time);
    }
}

esp_pthread_cfg_t create_config(const char *name, int core_id, int stack, int prio)
{
    auto cfg = esp_pthread_get_default_config();
    cfg.thread_name = name;
    cfg.pin_to_core = core_id;
    cfg.stack_size = stack;
    cfg.prio = prio;
    return cfg;
}

extern "C" void app_main(void)
{


    /* prototypes for mTask1 and mTask2 running in their respective thread */
	AppTask::Task1 mTask1;
	AppTask::Task2 mTask2;

	mTask1.setMilliCycle(sleep_time);
	mTask2.setMilliCycle(sleep_time);

    /* start running Thread1 and Thread2 thread */
	// Create a thread on core 1.
    auto cfg1 = create_config("Thread 1", 1, 3 * 1024, 5);
    esp_pthread_set_cfg(&cfg1);
    std::thread mThread1(&AppTask::Task1::run, &mTask1);
    // Create a thread on core 1.
    auto cfg2 = create_config("Thread 2", 1, 3 * 1024, 5);
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
