#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <string>
#include <map>
#include <iostream>

using namespace std;

typedef enum
{
    CAR_FACTORY,
}FACTORTY_TYPE;

class Singleton
{
public:
    static Singleton* GetInstance(FACTORTY_TYPE emType); 

protected:
    Singleton();

private:
    static Singleton* s_poInstance;
};


class CarFactory: public Singleton
{
public:
    void GetNewCar();
};

void SingletonStartFunction();

#endif
