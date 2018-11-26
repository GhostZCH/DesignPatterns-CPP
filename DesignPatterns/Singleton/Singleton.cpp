#include "Singleton.h"

Singleton* Singleton::s_poInstance = NULL; //C++ �ľ�̬�������ƱȽ����

Singleton* Singleton::GetInstance(FACTORTY_TYPE emType)
{
    switch (emType)
    {
        case  CAR_FACTORY:
            if (NULL == s_poInstance)
            {
                s_poInstance = new CarFactory();
            }
            break;
        default:
            cout << "unknow type :" << emType << endl;
            break;
    }

    return s_poInstance;
}

Singleton::Singleton()
{

}

void CarFactory::GetNewCar()
{
    cout << "build a new cat" << endl;
}

void SingletonStartFunction()
{
   CarFactory *poFactory =  (CarFactory*)Singleton::GetInstance(CAR_FACTORY);

   poFactory->GetNewCar();
}
