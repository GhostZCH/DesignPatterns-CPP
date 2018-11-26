#include "Bridge.h"
#include <iostream>

using namespace std;

/************************************************************************/
/* 实现部分                                                                     */
/************************************************************************/

void UserDataBaseImpByVector::GetByFilter( UserInfoFilter stFilter, UserInfo** ppstUserList, unsigned int *pulCount )
{
    if (NULL == ppstUserList || NULL == pulCount)
    {
        return;
    }

    *pulCount = 0;
    *ppstUserList = NULL;

    vector<UserInfo> vecRlst;
    for (size_t u = 0; u < m_vecData.size(); u++)
    {
        if (stFilter.bIsUserTypeAct && m_vecData[u].bIsAdmin != stFilter.bIsAdmin)
        {
            continue;
        }

        if (stFilter.bIsUserIDAct && m_vecData[u].ulUserID != stFilter.ulUserID)
        {
            continue;
        }
        vecRlst.push_back(m_vecData[u]);
    }

    if(vecRlst.size() == 0)
    {
        return;
    }

    *pulCount = vecRlst.size();
    *ppstUserList = new UserInfo[*pulCount];

    //内存申请失败保护，先省掉

    for (size_t u = 0; u < vecRlst.size(); u++)
    {
        (*ppstUserList)[u] = vecRlst[u];
    }
}

void UserDataBaseImpByVector::AddUserInfo( UserInfo stInfo )
{
    m_vecData.push_back(stInfo);
}

void UserDataBaseImpBySet::GetFromSetByUserID( const set<unsigned int>& setUserID,
                                                                               UserInfoFilter stFilter, bool bIsAdmin,
                                                                               vector<UserInfo>& vecRlstList )
{
    UserInfo stInfo;
    if (stFilter.bIsUserIDAct && setUserID.count(stFilter.ulUserID))
    {
        stInfo.bIsAdmin = bIsAdmin;
        stInfo.ulUserID = stFilter.ulUserID;
        vecRlstList.push_back(stInfo);
        return;
    }

    set<unsigned int>::iterator iter = setUserID.begin();
    for ( ; iter != setUserID.end(); iter++)
    {
        stInfo.bIsAdmin = bIsAdmin;
        stInfo.ulUserID = *iter;
        vecRlstList.push_back(stInfo);
    }
}

void UserDataBaseImpBySet::GetRlstFromVector( const vector<UserInfo>& vecRlstList,
                                                                            UserInfo** ppstUserList,
                                                                            unsigned int *pulCount )
{
    if (vecRlstList.size() == 0)
    {
        *ppstUserList = NULL;
        *pulCount = 0;
        return;
    }

    *pulCount = vecRlstList.size();
    *ppstUserList = new UserInfo[*pulCount];

    for (size_t u = 0; u < vecRlstList.size(); u++)
    {
        (*ppstUserList)[u] = vecRlstList[u];
    }
}

void UserDataBaseImpBySet::GetByFilter( UserInfoFilter stFilter,
                                                               UserInfo** ppstUserList,
                                                               unsigned int *pulCount )
{
    if (NULL == ppstUserList || NULL == pulCount)
    {
        return;
    }

    *pulCount = 0;
    *ppstUserList = NULL;

    vector<UserInfo> vecRlst;
    if (!stFilter.bIsUserIDAct || (stFilter.bIsUserIDAct && stFilter.bIsAdmin))
    {
        GetFromSetByUserID(m_setAdmin, stFilter, true, vecRlst);
    }

    if (!stFilter.bIsUserIDAct || (stFilter.bIsUserIDAct && !(stFilter.bIsAdmin)))
    {
        GetFromSetByUserID(m_setGuest, stFilter, false, vecRlst);
    }

    GetRlstFromVector(vecRlst, ppstUserList, pulCount);
}

void UserDataBaseImpBySet::AddUserInfo( UserInfo stInfo )
{
    if (stInfo.bIsAdmin)
    {
        m_setAdmin.insert(stInfo.ulUserID);
    }
    else
    {
        m_setGuest.insert(stInfo.ulUserID);
    }
}

/************************************************************************/
/* 接口部分                                                                                     */
/************************************************************************/
IUserDataBase::IUserDataBase( IMP_TYPE_ENUM emType )
{
    switch(emType)
    {
        case VECTOR_IMP: 
        {
            m_poIUserDataBaseImp = new UserDataBaseImpByVector();
            break;
        }
        case  SET_IMP:
        {
            m_poIUserDataBaseImp = new UserDataBaseImpBySet();
            break;
        }
        default:
           //throw ""
            break;
    }
}

void IUserDataBase::GetByType( bool bIsAdmin, UserInfo** ppstUserList, unsigned int *pulCount )
{
    UserInfoFilter stFilter;

    stFilter.bIsUserTypeAct = true;
    stFilter.bIsAdmin = true;

    stFilter.bIsUserIDAct = false;

    return m_poIUserDataBaseImp->GetByFilter(stFilter, ppstUserList, pulCount);
}

void IUserDataBase::AddUser( bool bIsAdmin, unsigned int ulUserID )
{
    UserInfo stInfo = {bIsAdmin, ulUserID};
    m_poIUserDataBaseImp->AddUserInfo(stInfo);
}

AdminDataBase::AdminDataBase(IMP_TYPE_ENUM emType):IUserDataBase(emType)
{

}

void AdminDataBase::GetAdmin(UserInfo** ppstUserList, unsigned int *pulCount)
{
    GetByType(true, ppstUserList, pulCount);
}

void AdminDataBase::AddAdmin(unsigned int ulUserID)
{
    AddUser(true, ulUserID);
}

GuestDataBase::GuestDataBase( IMP_TYPE_ENUM emType ):IUserDataBase(emType)
{
}

void GuestDataBase::GetGuest( UserInfo** ppstUserList, unsigned int *pulCount )
{
    GetByType(false, ppstUserList, pulCount);
}

void GuestDataBase::AddGuest( unsigned int ulUserID )
{
    AddUser(false, ulUserID);
}


/************************************************************************
*  这里简单的模拟了一个数据的存储与使用的模型                              
* IUserDataBase是接口的原型，AdminDataBase和GuestDataBase是两个子类
* 用来模拟数据存储系统为不同的应用场景提供的接口，他们都基于IUserDataBaseImp的实现部分
* IUserDataBaseImp 是实习部分的接口，有两个子类UserDataBaseImpBySet和UserDataBaseImpByVector
* 这样就将模块的接口和实现部分分离，两部分可以单独修改：
* 如果有新的需求，可以基于IUserDataBase增加新的子类提供新对外接口，
* 如果有更好的存在方式也可以添加IUserDataBaseImp的新的子类，
* 比如将数据存在在xml或者mysql中，对上层的接口不造成影响
*
************************************************************************/
void BridgeStartFuction()
{
    AdminDataBase oAdminDB(VECTOR_IMP);// guest/admin->vector/set其实可以有四种组合就不一一列举了

    oAdminDB.AddAdmin(1);
    oAdminDB.AddAdmin(2);

    UserInfo *pstUserInfo = NULL;
    unsigned int ulCount = 0;
    oAdminDB.GetAdmin(&pstUserInfo, &ulCount);

    for (unsigned int u = 0; u < ulCount; u++)
    {
        cout << "admin id " << pstUserInfo[u].ulUserID << endl;
    }
}