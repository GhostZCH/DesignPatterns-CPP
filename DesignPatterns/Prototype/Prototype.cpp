#include "Prototype.h"


//Prototype
Prototype::Prototype( Prototype& other )
{
    m_ulPrice = other.m_ulPrice;
    m_strName = other.m_strName;
}

// YouTiao
YouTiao::YouTiao()
{
    m_strName = "油条";
    m_ulPrice = 1;
}

Prototype* YouTiao::Clone()
{
    return new YouTiao(*this);
}

void YouTiao::Show()
{
    cout << "我是" << m_strName <<"  价格:" << m_ulPrice <<  "元" <<endl;
}



// DouJiang

DouJiang::DouJiang()
{
    m_strName = "豆浆";
    m_ulPrice = 2;
}

Prototype* DouJiang::Clone()
{
    return new DouJiang(*this);
}

void DouJiang::Show()
{
    cout << "我是" << m_strName <<"  价格:" << m_ulPrice <<  "元" <<endl;
}


// Bread
Bread::Bread()
{
    m_strName = "Bread";
    m_ulPrice = 3;
}


Prototype* Bread::Clone()
{
    return new Bread(*this);
}

void Bread::Show()
{
    cout << "This is " << m_strName <<"  price: $" << m_ulPrice <<  endl;
}

//Milk

Milk::Milk()
{
    m_strName = "Milk";
    m_ulPrice = 5; //米国东西就是贵
}

Prototype* Milk::Clone()
{
    return new Milk(*this);
}

void Milk::Show()
{
     cout << "This is " << m_strName <<"  price: $" << m_ulPrice <<  endl;
}

//PrototypeManage
void PrototypeManage::Clear()
{
    map<int, Prototype*>::iterator iter = m_mapProtypes.begin();
    for (;iter != m_mapProtypes.end(); iter++)
    {
        delete iter->second;
    }
    m_mapProtypes.clear();
}

void PrototypeManage::Init( int iFoodKey, Prototype* poFood, int iDrinkKey, Prototype *poDirnk )
{
    Clear();
    m_mapProtypes[iFoodKey]   = poFood;
    m_mapProtypes[iDrinkKey]  = poDirnk;
}

Prototype* PrototypeManage::GetCopy( int iKey )
{
    if (m_mapProtypes.find(iKey) == m_mapProtypes.end())
    {
        return NULL;
    }

    return m_mapProtypes[iKey]->Clone();
}

void PrototypeManage::InitChineseBreakfirst()
{
    Init(0 , new YouTiao(), 1 ,new DouJiang());
}

void PrototypeManage::InitEnglishBreakfirst()
{
    Init(0 , new Bread(), 1 ,new Milk());
}

void Sell(int aiSellList[], int iListLen,PrototypeManage& oPrototypeManage)
{
    for (int i = 0; i < iListLen; i++)
    {
        Prototype* poItem = oPrototypeManage.GetCopy(aiSellList[i]);
        poItem->Show();
        delete poItem;
    }
}

//PrototypeStartFunction
void PrototypeStartFunction()
{
    int aiSellList[] = {0, 1, 1, 0, 1, 0 }; // 我们需要很多的实例，但是不用每次都创建他们，配置他们，只要从原型中复制一下就好
    PrototypeManage oPrototypeManage;

    oPrototypeManage.InitChineseBreakfirst();
    Sell(aiSellList, sizeof(aiSellList)/sizeof(int), oPrototypeManage);

    oPrototypeManage.InitEnglishBreakfirst(); // 重新设置原型
    Sell(aiSellList, sizeof(aiSellList)/sizeof(int), oPrototypeManage);//同样的操作产生了很不相同的结果，这是原先的好处之一：动态更换原型
}
