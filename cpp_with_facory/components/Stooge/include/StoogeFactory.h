/*
 * StoogeFactory.h
 *
 *  Created on: 24.07.2021
 *      Author: FranzHoepfinger
 */

#ifndef COMPONENTS_STOOGE_INCLUDE_STOOGEFACTORY_H_
#define COMPONENTS_STOOGE_INCLUDE_STOOGEFACTORY_H_


class StoogeFactory
{
  public:
    // Factory Method
    static Stooge *make_stooge(int choice);
};


#endif /* COMPONENTS_STOOGE_INCLUDE_STOOGEFACTORY_H_ */
