#ifndef _ABS_FACTORY_H_
#define _ABS_FACTORY_H_

#include <string>

using namespace std;

//////////////////////////////////////////////////////////////////////////
// base
class Phone
{
public:
    string m_strName;

    virtual ~Phone();
};

class Computer
{
public:
    string m_strName;
};

class AbstractFactory
{
public:
    virtual  Phone* CreatePhone() = 0;
    virtual  Computer* CreateComputer() = 0;
};

//////////////////////////////////////////////////////////////////////////
// apple
class iPhone:public Phone
{
public:
    string m_strAssistName;

    ~iPhone();
};

class Mac:public Computer
{
     // Íµ¸öÀÁ
};

class AppleFactory: public AbstractFactory
{
public:
    virtual  Phone* CreatePhone();
    virtual  Computer* CreateComputer();
};

//////////////////////////////////////////////////////////////////////////
//google
class Nexus:public Phone
{
public:
    string m_strSysName;
};
class ChromeBook: public Computer
{
    // Íµ¸öÀÁ
};

class GoogleFactory : public AbstractFactory
{
public:
    virtual  Phone* CreatePhone();
    virtual  Computer* CreateComputer();
};

void AbstractFactoryStartFunction();

#endif
