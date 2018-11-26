#ifndef _FACTORY_H_
#define _FACTORY_H_

typedef enum
{
    VEHICLE_CAR,
    VEHICLE_TRUCK,
    VEHICLE_BUS
}VEHICLE_TYPE_ENUM;

// 这里其实可以只定义一个基类，在定义若干子类型
typedef struct 
{
    unsigned int    ulSitCount;
    unsigned int    ulWheelCount;
}Vehicle;

class VehicleFactory
{
public:
    /************************************************************************/
    /*   根据输入参数生产实例，也可以是静态的               */
    /************************************************************************/
    Vehicle* CreatVehicle(VEHICLE_TYPE_ENUM emType);
};

void FactoryStartFunction();

#endif
