/*
 * AbstractTask.cpp
 *
 *  Created on: 13.08.2021
 *      Author: FranzHoepfinger
 *
 * credits: Andreas Kroop
 */
 
 
#include <thread>
#include <chrono>
#include "AbstractTask.h"
#include "print_thread_info.h"
#include "esp_pthread.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define LOG_LOCAL_LEVEL ESP_LOG_INFO //set this to ESP_LOG_WARN in productive Environment.
#include "esp_log.h"



namespace AppTask
{

	class AbstractTask::Private {
	public:
		esp_pthread_cfg_t cfg;
		Private()
		{
			this->cfg = esp_pthread_get_default_config();
		}

	};


    AbstractTask::AbstractTask()
    : d(new Private),
      milli_cycle(10)
    {

    }

    AbstractTask::~AbstractTask()
    {

    }

    void AbstractTask::create_config(const char *name, int core_id, int stack, int prio)
    {
		this->d->cfg.thread_name = name;
    	this->d->cfg.pin_to_core = core_id;
    	this->d->cfg.stack_size = stack;
    	this->d->cfg.prio = prio;
    	ESP_LOGI(this->d->cfg.thread_name, " **** create_config");
    }

    esp_err_t AbstractTask::esp_pthread_set_config(void) {
    	return esp_pthread_set_cfg(&this->d->cfg);
    	ESP_LOGI(this->d->cfg.thread_name, " **** set_config");
    }

    void AbstractTask::run()
    {
    	ESP_LOGI(this->d->cfg.thread_name, " **** run");

        while (!m_abort.load())
        {
            if (runInit())
            {
            	ESP_LOGI(this->d->cfg.thread_name, " **** initialization is complete");
                m_initDone = true;
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

    	ESP_LOGI(this->d->cfg.thread_name, " **** at this point the task is initialized");

    	ESP_LOGI(this->d->cfg.thread_name, " **** wait for starting cyclic processing");
        while (!m_abort.load())
        {
            if (m_cyclic.load())
            {
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

    	ESP_LOGI(this->d->cfg.thread_name, " **** there is additional initialization of clients and application after core and base are initialized");
        runAppInit();

    	ESP_LOGI(this->d->cfg.thread_name, " **** cyclic processing starts");
        while (!m_abort.load())
        {
            (void)runCyclic();
            print_thread_info("This thread is the AbstractTask Task.");
            std::this_thread::sleep_for(std::chrono::milliseconds(milli_cycle));
        }

    	ESP_LOGI(this->d->cfg.thread_name, " **** any cleanup before terminating");
        while (!runExit())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    bool AbstractTask::runInit()
    {
        return true;
    }

    bool AbstractTask::runAppInit()
    {
        return true;
    }

    bool AbstractTask::runCyclic()
    {
        return true;
    }

    bool AbstractTask::runExit()
    {
        return true;
    }

    void AbstractTask::startCyclic()
    {
        m_cyclic = true;
    }

    void AbstractTask::exit()
    {
        m_abort = true;
    }

    bool AbstractTask::isInitDone()
    {
        return m_initDone.load();
    }

    void AbstractTask::cbWatchdog(void)
    {

    }



    void AbstractTask::cbErrorOutp(uint8_t bFun, uint8_t bLocation, int16_t iCause)
    {
        (void)bFun;
        (void)bLocation;
        (void)iCause;
    }

    std::chrono::milliseconds AbstractTask::getMilliCycle() const {
		return milli_cycle;
	}

	void AbstractTask::setMilliCycle(std::chrono::milliseconds milliCycle) {
		milli_cycle = milliCycle;
	}

	int AbstractTask::getCoreId() const {
		return this->d->cfg.pin_to_core;
	}

	void AbstractTask::setCoreId(int coreId) {
		this->d->cfg.pin_to_core = coreId;
	}

	const char* AbstractTask::getName() const {
		return this->d->cfg.thread_name;
	}

	void AbstractTask::setName(const char *name) {
		this->d->cfg.thread_name = name;
	}

	int AbstractTask::getPrio() const {
		return this->d->cfg.prio;
	}

	void AbstractTask::setPrio(int prio) {
		this->d->cfg.prio = prio;
	}

	int AbstractTask::getStack() const {
		return this->d->cfg.stack_size;
	}

	void AbstractTask::setStack(int stack) {
		this->d->cfg.stack_size = stack;
	}

} /* namespace AppTask */
