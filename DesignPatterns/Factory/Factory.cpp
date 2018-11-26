#include "Factory.h"
#include <iostream>

using namespace std;

Vehicle* VehicleFactory::CreatVehicle(VEHICLE_TYPE_ENUM emType)
{
    // Ҳ���Է������࣬����ʵ�����и�Ϊ����
    Vehicle* poVehicle = new Vehicle();

    if (NULL == poVehicle)
    {
        return NULL;
    }

    // ���ݲ�ͬ�������ò�ͬ��ʵ��
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
    VehicleFactory oFactory;  // ���CreatVehicle�Ǿ�̬�Ĳ���Ҫ���������ʹ��VehicleFactory::CreatVehicle

    Vehicle* poTruck = oFactory.CreatVehicle(VEHICLE_TRUCK);
    if (NULL == poTruck)
    {
        return;
    }

    cout << "Truck has " <<  poTruck->ulSitCount << " Seats and " 
            <<  poTruck->ulWheelCount << " Wheels " << endl;

    delete poTruck;
}
