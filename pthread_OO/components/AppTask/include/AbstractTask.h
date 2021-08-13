/*
 * AbstractTask.h
 *
 *  Created on: 13.08.2021
 *      Author: FranzHoepfinger
 *
 * credits: Andreas Kroop
 */

#ifndef COMPONENTS_APPTASK_INCLUDE_ABSTRACTTASK_H_
#define COMPONENTS_APPTASK_INCLUDE_ABSTRACTTASK_H_

#include <atomic>

namespace AppTask
{
    /*
    An abstract implementation for a generic task handling.
    This calss is used by CoreTask and BaseTask.
    */
    class AbstractTask
    {
    public:
        AbstractTask();
        virtual ~AbstractTask();

        /*
        The tasks run method .
        It will call the protected runXXX() function as appropriate.
        */
        void run();

        /**
        This method is being called to check if the ECU driver initialization is complete.
        return true  if the init routines are complete
               false otherwise
        */
        bool isInitDone();

        /**
        After ECU driver initializaton is done, this method needs to be called to start aplication init and cyclic execution.
        */
        void startCyclic();

        /**
        This method needs to be called to stop and terminate the task.
        */
        void exit();


        /**
         * get the Cycle Time
         * @return Cycle Time
         */
		int64_t getMilliCycle() const;
		/**
		 * set the Cycle Time
		 * @param milliCycle
		 */
		void setMilliCycle(int64_t milliCycle);

    protected:

        /**
        This method initializes the ECU driver. 
        It needs to be called, before any other function is allowed to call the ISOBUS driver.
        return true  if the init function is complete, 
               false if the initialization is not complete and the function needs to get called again.
        */
        virtual bool runInit();

        /**
        After the Ecu Driver modules are initialized, The application can get initialized. 
        At this time it is allowed to call EcuDriver function.
        return true  if the init function is complete,
               false if the initialization is not complete and the function needs to get called again.
        */
        virtual bool runAppInit();

        /**
        Cyclic execution of all required modules.
        */
        virtual bool runCyclic();

        /**
        This method is called for any required clean up after the cyclic execution has been terminated.
        return true  if the exit function is complete,
               false if the cleanup is not complete and the function needs to get called again.
        */
        virtual bool runExit();

        /**
        An emty dummy function for the watchdog
        */
        static void cbWatchdog(void);


        /**
        A dummy debug callback output function
        */
        static void cbErrorOutp(uint8_t bFun, uint8_t bLocation, int16_t iCause);

    private:

        /** This variable is the cycle Time of the Task.  */
        int64_t milli_cycle;

        /** This variable will get set if the threed needs to get aborted */
        std::atomic_bool m_abort = ATOMIC_VAR_INIT(false);

        /*
        This variable will be set once cyclic execution may start
        */
        std::atomic_bool m_cyclic = ATOMIC_VAR_INIT(false);

        /*
        This variable will be set as the ECU Initialisaton is complete.
        */
        std::atomic_bool m_initDone = ATOMIC_VAR_INIT(false);

    };

} /* namespace AppTask */

#endif /* COMPONENTS_APPTASK_INCLUDE_ABSTRACTTASK_H_ */
