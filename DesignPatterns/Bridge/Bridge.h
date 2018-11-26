#ifndef _BRIDGE_H_
#define _BRIDGE_H_

#include <set>
#include <vector>

using namespace std;

typedef enum
{
    VECTOR_IMP,
    SET_IMP
}IMP_TYPE_ENUM;

typedef struct
{
    bool  bIsAdmin;
    unsigned int ulUserID;
}UserInfo;

typedef struct
{
    bool bIsUserIDAct;
    bool bIsUserTypeAct;

    unsigned int ulUserID;
    bool  bIsAdmin;
}UserInfoFilter;

/************************************************************************/
/* 实现部分                                                                     */
/************************************************************************/
// 实现的原型
class IUserDataBaseImp
{
public:
    virtual void GetByFilter(UserInfoFilter stFilter, UserInfo** ppstUserList, unsigned int *pulCount) = 0;
    virtual void AddUserInfo(UserInfo stInfo) = 0;
};

// 两种不同的实现
class UserDataBaseImpByVector: public IUserDataBaseImp
{
public:    
    virtual void GetByFilter(UserInfoFilter stFilter, UserInfo** ppstUserList, unsigned int *pulCount);
    virtual void AddUserInfo(UserInfo stInfo);
private:
    vector<UserInfo> m_vecData;
};

class UserDataBaseImpBySet: public IUserDataBaseImp
{
public:    
    virtual void GetByFilter(UserInfoFilter stFilter, UserInfo** ppstUserList, unsigned int *pulCount);
    virtual void AddUserInfo(UserInfo stInfo);

    void GetFromSetByUserID(const set<unsigned int>& setUserID,
                                            UserInfoFilter stFilter, bool bIsAdmin,
                                            vector<UserInfo>& vecRlstList);

    void GetRlstFromVector(const vector<UserInfo>& vecRlstList,
                                          UserInfo** ppstUserList,
                                          unsigned int *pulCount);
        
private:
    set<unsigned int> m_setAdmin;
    set<unsigned int> m_setGuest;
};

/************************************************************************/
/* 接口部分                                                                                     */
/************************************************************************/
// 接口的原型
class IUserDataBase
{
public:
    IUserDataBase(IMP_TYPE_ENUM emType);
    void GetByType(bool bIsAdmin, UserInfo** ppstUserList, unsigned int *pulCount);
    void AddUser(bool bIsAdmin, unsigned int ulUserID);

protected:
    IUserDataBaseImp* m_poIUserDataBaseImp;
};

// 基于原型的新接口，不改变实现部分可以适应不断变化的需求，
// 只要IUserDataBase不变，接口层感知不到底层实现方式的变化
class AdminDataBase: public IUserDataBase
{
public:
    AdminDataBase(IMP_TYPE_ENUM emType);
    void GetAdmin(UserInfo** ppstUserList, unsigned int *pulCount);
    void AddAdmin(unsigned int ulUserID);
};

// 基于原型的新接口，不改变实现部分可以适应不断变化的需求，
// 只要IUserDataBase不变，接口层感知不到底层实现方式的变化
class GuestDataBase: public IUserDataBase
{
public:
    GuestDataBase(IMP_TYPE_ENUM emType);
    void GetGuest(UserInfo** ppstUserList, unsigned int *pulCount);
    void AddGuest(unsigned int ulUserID);
};

//////////////////////////////////////////////////////////////////////////
// start funciton
//////////////////////////////////////////////////////////////////////////
void BridgeStartFuction();

#endif