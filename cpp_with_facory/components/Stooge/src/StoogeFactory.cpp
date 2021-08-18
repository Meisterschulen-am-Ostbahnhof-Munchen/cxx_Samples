/*
 * StoogeFactory.cpp
 *
 *  Created on: 24.07.2021
 *      Author: FranzHoepfinger
 */



#include <memory>
#include "Stooge.h"
#include "StoogeFactory.h"
#include "Larry.h"
#include "Moe.h"
#include "Curly.h"



using namespace std;



std::shared_ptr<Stooge> StoogeFactory::make_stooge(t_choice choice)
{


    static shared_ptr<Larry> 	sp_Larry = make_shared<Larry>();
    static shared_ptr<Moe>		sp_Moe   = make_shared<Moe>();
    static shared_ptr<Curly> 	sp_Curly = make_shared<Curly>();





    //give the Object
	switch (choice) {
		case cLarry:
		    return sp_Larry;
		case cMoe:
		    return sp_Moe;
		case cCurly:
		default: //needed to statisfy the Compiler.
		    return sp_Curly;
	}
}
