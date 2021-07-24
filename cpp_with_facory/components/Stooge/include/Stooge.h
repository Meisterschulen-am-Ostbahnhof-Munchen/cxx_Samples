/*
 * Stooge.h
 *
 *  Created on: 24.07.2021
 *      Author: FranzHoepfinger
 */

#ifndef COMPONENTS_STOOGE_INCLUDE_STOOGE_H_
#define COMPONENTS_STOOGE_INCLUDE_STOOGE_H_


class Stooge
{
  public:
	// Empty virtual destructor for proper cleanup
	virtual ~Stooge() {}

    virtual void slap_stick() = 0;
};


#endif /* COMPONENTS_STOOGE_INCLUDE_STOOGE_H_ */
