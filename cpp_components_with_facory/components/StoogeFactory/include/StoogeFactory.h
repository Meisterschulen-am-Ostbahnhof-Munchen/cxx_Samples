/*
 * StoogeFactory.h
 *
 *  Created on: 24.07.2021
 *      Author: FranzHoepfinger
 */

#ifndef COMPONENTS_STOOGE_INCLUDE_STOOGEFACTORY_H_
#define COMPONENTS_STOOGE_INCLUDE_STOOGEFACTORY_H_


typedef enum e_coice
{
	cLarry, cMoe, cCurly
} t_choice;

class StoogeFactory
{
  public:
    // Factory Method
    static Stooge *make_stooge(t_choice choice);
};


#endif /* COMPONENTS_STOOGE_INCLUDE_STOOGEFACTORY_H_ */
