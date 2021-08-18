

#include <esp_log.h>


class iFunctor
{
public:
	virtual ~iFunctor() {};
    virtual int operator()(int a, int b) = 0;
};



class Functor: virtual public iFunctor
{
public:
    int operator()(int a, int b)
    {
        return a + b;
    }
};




extern "C" void app_main(void)
{
	Functor f;
	int a = 5;
	int b = 7;
	int sum = f(a, b);
	ESP_LOGI("SUM", "%i + %i = %i", a, b, sum);


}

