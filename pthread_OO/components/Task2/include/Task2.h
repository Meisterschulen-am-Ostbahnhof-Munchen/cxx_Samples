/*
 * Task2.h
 *
 *  Created on: 13.08.2021
 *      Author: FranzHoepfinger
 */

#ifndef COMPONENTS_TASK2_INCLUDE_TASK2_H_
#define COMPONENTS_TASK2_INCLUDE_TASK2_H_

#include "AbstractTask.h"

namespace AppTask
{

    class Task2 : virtual public AbstractTask
    {
    public:
        Task2();
        virtual ~Task2();

    protected:

        bool runInit() override;
        bool runAppInit() override;
        bool runCyclic() override;

    private:

    };

} /* namespace AppTask */

#endif /* COMPONENTS_TASK2_INCLUDE_TASK2_H_ */
