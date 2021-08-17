/*
 * CurlyLarry.h
 *
 *  Created on: 17.08.2021
 *      Author: FranzHoepfinger
 */

#ifndef COMPONENTS_STOOGE_INCLUDE_CURLYLARRY_H_
#define COMPONENTS_STOOGE_INCLUDE_CURLYLARRY_H_


class CurlyLarry: public Larry, public Curly, public Stooge
{
  public:
    void slap_stick();
};


#endif /* COMPONENTS_STOOGE_INCLUDE_CURLYLARRY_H_ */
