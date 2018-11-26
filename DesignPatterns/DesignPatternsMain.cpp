#include <iostream>
#include <string>

#include "Factory/Factory.h"
#include "AbsractFactory/AbsractFactory.h"
#include "Builder/Builder.h"
#include "Prototype/Prototype.h"
#include "Singleton/Singleton.h"
#include "Adapter/Adapter.h"
#include "Bridge/Bridge.h"

using namespace std;

typedef void (*PF_StartFunc)();

typedef enum 
{
    DP_FACTORY,
    DP_ABSTRACT_FACTORY,
    DP_BUILDER,
    DP_PROTOTYPE,
    DP_SINGLENTON,
    DP_ADAPTER,
    DP_BRIDGE
}DP_TYPE;

typedef struct
{
    DP_TYPE          emType;
    PF_StartFunc    pfStartFunction;
}DP_START_FUNC;

DP_START_FUNC g_astDesignPatterns[] = {
    {DP_FACTORY,                     FactoryStartFunction             },
    {DP_ABSTRACT_FACTORY,    AbstractFactoryStartFunction},
    {DP_BUILDER,                       BuilderStartFunction             },
    {DP_PROTOTYPE,                 PrototypeStartFunction         },
    {DP_SINGLENTON,               SingletonStartFunction         },
    {DP_ADAPTER,                     AdapterStartFunction            },
    {DP_BRIDGE,                        BridgeStartFuction}
};

PF_StartFunc GetStartFunc(DP_TYPE emType)
{
    size_t uPatternCount = sizeof(g_astDesignPatterns)/sizeof(DP_START_FUNC);

    for (size_t u = 0; u < uPatternCount; u++)
    {
        if (g_astDesignPatterns[u].emType == emType)
        {
            return g_astDesignPatterns[u].pfStartFunction;
        }
    }

    return NULL;
}

int main()
{
    DP_TYPE emType = DP_SINGLENTON; //每次测试修改这里就可以了

    PF_StartFunc pfStartFunc = GetStartFunc(emType);

    if (NULL == pfStartFunc)
    {
        cout << "emType[" << emType <<"]" << "not have start function" << endl;
        return 1;
    }

    (*pfStartFunc)();

    system("pause");

    return 0;
}