/*
 * print_thread_info.cpp
 *
 *  Created on: 13.08.2021
 *      Author: FranzHoepfinger
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <string>
#include <sstream>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>




#include "print_thread_info.h"

void print_thread_info(const char *extra)
{
    std::stringstream ss;
    if (extra) {
        ss << extra;
    }
    ss << "Core id: " << xPortGetCoreID()
       << ", prio: " << uxTaskPriorityGet(nullptr)
       << ", minimum free stack: " << uxTaskGetStackHighWaterMark(nullptr) << " bytes.";
    ESP_LOGI(pcTaskGetTaskName(nullptr), "%s", ss.str().c_str());
}
