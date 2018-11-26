#ifndef _FACTORY_H_
#define _FACTORY_H_

typedef enum
{
    VEHICLE_CAR,
    VEHICLE_TRUCK,
    VEHICLE_BUS
}VEHICLE_TYPE_ENUM;

// ������ʵ����ֻ����һ�����࣬�ڶ�������������
typedef struct 
{
    unsigned int    ulSitCount;
    unsigned int    ulWheelCount;
}Vehicle;

class VehicleFactory
{
public:
    /************************************************************************/
    /*   ���������������ʵ����Ҳ�����Ǿ�̬��               */
    /************************************************************************/
    Vehicle* CreatVehicle(VEHICLE_TYPE_ENUM emType);
};

void FactoryStartFunction();

#endif
