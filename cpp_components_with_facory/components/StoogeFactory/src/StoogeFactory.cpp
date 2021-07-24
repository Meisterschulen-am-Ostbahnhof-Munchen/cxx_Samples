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







Stooge *StoogeFactory::make_stooge(t_choice choice)
{
	switch (choice) {
		case cLarry:
		    return new Larry;
		case cMoe:
		    return new Moe;
		case cCurly:
		default: //needed to statisfy the Compiler.
		    return new Curly;
	}
}
