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
/* ʵ�ֲ���                                                                     */
/************************************************************************/
// ʵ�ֵ�ԭ��
class IUserDataBaseImp
{
public:
    virtual void GetByFilter(UserInfoFilter stFilter, UserInfo** ppstUserList, unsigned int *pulCount) = 0;
    virtual void AddUserInfo(UserInfo stInfo) = 0;
};

// ���ֲ�ͬ��ʵ��
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
/* �ӿڲ���                                                                                     */
/************************************************************************/
// �ӿڵ�ԭ��
class IUserDataBase
{
public:
    IUserDataBase(IMP_TYPE_ENUM emType);
    void GetByType(bool bIsAdmin, UserInfo** ppstUserList, unsigned int *pulCount);
    void AddUser(bool bIsAdmin, unsigned int ulUserID);

protected:
    IUserDataBaseImp* m_poIUserDataBaseImp;
};

// ����ԭ�͵��½ӿڣ����ı�ʵ�ֲ��ֿ�����Ӧ���ϱ仯������
// ֻҪIUserDataBase���䣬�ӿڲ��֪�����ײ�ʵ�ַ�ʽ�ı仯
class AdminDataBase: public IUserDataBase
{
public:
    AdminDataBase(IMP_TYPE_ENUM emType);
    void GetAdmin(UserInfo** ppstUserList, unsigned int *pulCount);
    void AddAdmin(unsigned int ulUserID);
};

// ����ԭ�͵��½ӿڣ����ı�ʵ�ֲ��ֿ�����Ӧ���ϱ仯������
// ֻҪIUserDataBase���䣬�ӿڲ��֪�����ײ�ʵ�ַ�ʽ�ı仯
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