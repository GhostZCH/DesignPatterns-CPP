#include "AbsractFactory.h"
#include <iostream>

using namespace std;

#define RELEASE_OBJECT(pObj) {delete pObj; pObj = NULL;}

//google
Computer* GoogleFactory::CreateComputer()
{
    ChromeBook* poChromeBook = new ChromeBook();
    poChromeBook->m_strName = "ChromeBook";
    return poChromeBook;
}

Phone* GoogleFactory::CreatePhone()
{
    Nexus* poNexus = new Nexus();
    poNexus->m_strSysName = "android";
    poNexus->m_strName = "Nexus";
    return poNexus;
}

//apple
Computer* AppleFactory::CreateComputer()
{
    Mac* poMac = new Mac();
    poMac->m_strName = "MacBook";
    return poMac;
}

Phone* AppleFactory::CreatePhone()
{
    iPhone* poIPhone = new iPhone();
    poIPhone->m_strAssistName = "siri";
    poIPhone->m_strName = "Nexus";
    return poIPhone;
}

// 记得用虚析构函数哦
Phone::~Phone()
{
    cout << "记得用虚析构函数哦" << endl;
}

iPhone::~iPhone()
{
    cout << "Q: 会是否子类吗？ A: yes" << endl;
}

//使用相同的流程，使用不同的工厂，生产不同的实例，（没检测空指针，不要像我学习 O(∩_∩)O~）
void GetProduct(AbstractFactory* poFactory, Phone*& poPhone, Computer*& poComputer)
{
    poPhone = poFactory->CreatePhone();
    poComputer = poFactory->CreateComputer();
}

void AbstractFactoryStartFunction()
{
    AbstractFactory *poFactory = NULL;
    Phone *poPhone = NULL;
    Computer *poComputer = NULL;

    // for apple
    poFactory = new AppleFactory();// 生成特点类型的工厂用于生成实例
    GetProduct(poFactory, poPhone, poComputer);//生产实例

    cout << " PhoneName :" << poPhone->m_strName << endl;
    cout << " PhoneAssistName :" << ((iPhone*)poPhone)->m_strAssistName << endl; //不同的产品有自己的特性
    cout << " ComputerName :" << poComputer->m_strName << endl;

    RELEASE_OBJECT(poFactory);
    RELEASE_OBJECT(poPhone);
    RELEASE_OBJECT(poComputer);
    
    // for google
    poFactory  = new GoogleFactory(); // 改变的只有这里
    GetProduct(poFactory, poPhone, poComputer);

    cout << " PhoneName :" << poPhone->m_strName << endl;
    cout << " PhoneSysName :" << ((Nexus*)poPhone)->m_strSysName << endl; //不同的产品有自己的特性
    cout << " ComputerName :" << poComputer->m_strName << endl;
    
    RELEASE_OBJECT(poFactory);
    RELEASE_OBJECT(poPhone);
    RELEASE_OBJECT(poComputer);
}

