


#include <vector>
#include <algorithm>
#include <iostream>


using namespace std;


class MyLess
{
public:
   bool operator()(int a, int b)
   {
	   return a < b;
   }
};

/* Inside .cpp file, app_main function must be declared with C linkage */
extern "C" void app_main(void)
{
    cout << "app_main starting" << endl;



   vector<int> v{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};

   sort(begin(v), end(v), MyLess());

   cout << " Hi ";

   for (auto a : v) {
       cout << a << ' ';
   }





   cout << "app_main done" << endl;
}
