#include "Factory.h"
#include <iostream>

using namespace std;

Vehicle* VehicleFactory::CreatVehicle(VEHICLE_TYPE_ENUM emType)
{
    // 也可以返回子类，在真实环境中更为常见
    Vehicle* poVehicle = new Vehicle();

    if (NULL == poVehicle)
    {
        return NULL;
    }

    // 根据不同参数配置不同的实例
    switch(emType)
    {
        case VEHICLE_CAR:
            poVehicle->ulSitCount = 4;
            poVehicle->ulWheelCount = 4;
            break;

        case VEHICLE_TRUCK:
            poVehicle->ulSitCount = 2;
            poVehicle->ulWheelCount = 6;
            break;

        case VEHICLE_BUS:
            poVehicle->ulSitCount = 20;
            poVehicle->ulWheelCount = 6;
            break;

        default:
            delete poVehicle;
            poVehicle = NULL;
    }

    return poVehicle;
}

void FactoryStartFunction()
{
    VehicleFactory oFactory;  // 如果CreatVehicle是静态的不需要这个，后面使用VehicleFactory::CreatVehicle

    Vehicle* poTruck = oFactory.CreatVehicle(VEHICLE_TRUCK);
    if (NULL == poTruck)
    {
        return;
    }

    cout << "Truck has " <<  poTruck->ulSitCount << " Seats and " 
            <<  poTruck->ulWheelCount << " Wheels " << endl;

    delete poTruck;
}
