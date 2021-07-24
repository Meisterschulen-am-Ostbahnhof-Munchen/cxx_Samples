/*
 * StoogeFactory.cpp
 *
 *  Created on: 24.07.2021
 *      Author: FranzHoepfinger
 */




#include "Stooge.h"
#include "StoogeFactory.h"
#include "Larry.h"
#include "Moe.h"
#include "Curly.h"

Stooge *StoogeFactory::make_stooge(int choice)
{
  if (choice == 1)
    return new Larry;
  else if (choice == 2)
    return new Moe;
  else
    return new Curly;
}
