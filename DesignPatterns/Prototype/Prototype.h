#ifndef _PROTOTYPE_H_
#define _PROTOTYPE_H_

#include <string>
#include <map>
#include <iostream>

using namespace std;

class Prototype
{
public:
    unsigned int m_ulPrice;
    string m_strName;

    Prototype(){};//又偷懒，不要学我
    Prototype(Prototype& other);

    virtual Prototype* Clone() = 0;
    virtual void Show() = 0;
};

class YouTiao: public Prototype
{
public:
    YouTiao();
    virtual Prototype* Clone();
    virtual void Show();
};

class DouJiang: public Prototype
{
public:
    DouJiang();
    virtual Prototype* Clone();
    virtual void Show();
};

class Bread: public Prototype
{
public:
    Bread();
    virtual Prototype* Clone();
    virtual void Show();
};

class Milk: public Prototype
{
public:
    Milk();
    virtual Prototype* Clone();
    virtual void Show();
};

class PrototypeManage
{
public:
    void Clear();
    void Init(int iFoodKey, Prototype* poFood, int iDrinkKey, Prototype *poDirnk);
    Prototype* GetCopy(int iKey);

    void InitChineseBreakfirst();
    void InitEnglishBreakfirst();
private:
    map<int, Prototype*> m_mapProtypes;
};


void PrototypeStartFunction();

#endif
