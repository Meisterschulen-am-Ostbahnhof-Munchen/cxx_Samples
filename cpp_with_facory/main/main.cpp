#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <cxxabi.h>

using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;
using std::make_shared;
using std::vector;


#include "Stooge.h"
#include "StoogeFactory.h"

/* these 3 Includes are no more needed. !! and THIS is the Advantage !*/
/* because they are now in "priv_include" they would not be ABLE to be included !
//NOT #include "Larry.h"
//NOT #include "Moe.h"
//NOT #include "Curly.h"


/* Inside .cpp file, app_main function must be declared with C linkage */
extern "C" void app_main(void)
{


	 vector<Stooge*> roles;


     cout << "Example cpp_with_facory." << endl;


     roles.push_back(StoogeFactory::make_stooge(1));
     roles.push_back(StoogeFactory::make_stooge(2));
     roles.push_back(StoogeFactory::make_stooge(3));

     for (int i = 0; i < roles.size(); i++)
       roles[i]->slap_stick();
     for (int i = 0; i < roles.size(); i++)
       delete roles[i];


     cout << "Example finished." << endl;
}

