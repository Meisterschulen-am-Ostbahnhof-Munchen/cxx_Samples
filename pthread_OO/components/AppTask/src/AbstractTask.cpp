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

namespace AppTask
{
    AbstractTask::AbstractTask()
    : milli_cycle(10)
    {
    }

    AbstractTask::~AbstractTask()
    {
    }

    esp_pthread_cfg_t AbstractTask::create_config(const char *name, int core_id, int stack, int prio)
    {
        auto cfg = esp_pthread_get_default_config();
        cfg.thread_name = name;
        cfg.pin_to_core = core_id;
        cfg.stack_size = stack;
        cfg.prio = prio;
        return cfg;
    }

    esp_err_t AbstractTask::esp_pthread_set_cfg(const esp_pthread_cfg_t *cfg) {
    	return esp_pthread_set_cfg(cfg);
    }

    void AbstractTask::run()
    {

        while (!m_abort.load())
        {
            if (runInit())
            {
                // initialization is complete
                m_initDone = true;
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        /* at this point the task is initialized */

        /* wait for starting cyclic processing */
        while (!m_abort.load())
        {
            if (m_cyclic.load())
            {
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        /* there is additional initialization of clients and application after core and base are initialized */
        runAppInit();

        /* cyclic processing starts */
        while (!m_abort.load())
        {
            (void)runCyclic();
            print_thread_info("This thread is the AbstractTask Task.");
            std::this_thread::sleep_for(std::chrono::milliseconds(milli_cycle));
        }

        /* any cleanup before terminating */
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

} /* namespace AppTask */
