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

// �ǵ�������������Ŷ
Phone::~Phone()
{
    cout << "�ǵ�������������Ŷ" << endl;
}

iPhone::~iPhone()
{
    cout << "Q: ���Ƿ������� A: yes" << endl;
}

//ʹ����ͬ�����̣�ʹ�ò�ͬ�Ĺ�����������ͬ��ʵ������û����ָ�룬��Ҫ����ѧϰ O(��_��)O~��
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
    poFactory = new AppleFactory();// �����ص����͵Ĺ�����������ʵ��
    GetProduct(poFactory, poPhone, poComputer);//����ʵ��

    cout << " PhoneName :" << poPhone->m_strName << endl;
    cout << " PhoneAssistName :" << ((iPhone*)poPhone)->m_strAssistName << endl; //��ͬ�Ĳ�Ʒ���Լ�������
    cout << " ComputerName :" << poComputer->m_strName << endl;

    RELEASE_OBJECT(poFactory);
    RELEASE_OBJECT(poPhone);
    RELEASE_OBJECT(poComputer);
    
    // for google
    poFactory  = new GoogleFactory(); // �ı��ֻ������
    GetProduct(poFactory, poPhone, poComputer);

    cout << " PhoneName :" << poPhone->m_strName << endl;
    cout << " PhoneSysName :" << ((Nexus*)poPhone)->m_strSysName << endl; //��ͬ�Ĳ�Ʒ���Լ�������
    cout << " ComputerName :" << poComputer->m_strName << endl;
    
    RELEASE_OBJECT(poFactory);
    RELEASE_OBJECT(poPhone);
    RELEASE_OBJECT(poComputer);
}

