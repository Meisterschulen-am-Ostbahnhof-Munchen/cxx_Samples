/*
 * Task1.h
 *
 *  Created on: 13.08.2021
 *      Author: FranzHoepfinger
 */

#ifndef COMPONENTS_TASK1_INCLUDE_TASK1_H_
#define COMPONENTS_TASK1_INCLUDE_TASK1_H_

#include "AbstractTask.h"

namespace AppTask
{

    class Task1 : public AbstractTask
    {
    public:
        Task1();
        virtual ~Task1();

    protected:

        bool runInit() override;
        bool runAppInit() override;
        bool runCyclic() override;

    private:

    };

} /* namespace AppTask */

#endif /* COMPONENTS_TASK1_INCLUDE_TASK1_H_ */
