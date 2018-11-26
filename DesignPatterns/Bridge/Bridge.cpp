#include "Bridge.h"
#include <iostream>

using namespace std;

/************************************************************************/
/* ʵ�ֲ���                                                                     */
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

    //�ڴ�����ʧ�ܱ�������ʡ��

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
/* �ӿڲ���                                                                                     */
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
*  ����򵥵�ģ����һ�����ݵĴ洢��ʹ�õ�ģ��                              
* IUserDataBase�ǽӿڵ�ԭ�ͣ�AdminDataBase��GuestDataBase����������
* ����ģ�����ݴ洢ϵͳΪ��ͬ��Ӧ�ó����ṩ�Ľӿڣ����Ƕ�����IUserDataBaseImp��ʵ�ֲ���
* IUserDataBaseImp ��ʵϰ���ֵĽӿڣ�����������UserDataBaseImpBySet��UserDataBaseImpByVector
* �����ͽ�ģ��Ľӿں�ʵ�ֲ��ַ��룬�����ֿ��Ե����޸ģ�
* ������µ����󣬿��Ի���IUserDataBase�����µ������ṩ�¶���ӿڣ�
* ����и��õĴ��ڷ�ʽҲ�������IUserDataBaseImp���µ����࣬
* ���罫���ݴ�����xml����mysql�У����ϲ�Ľӿڲ����Ӱ��
*
************************************************************************/
void BridgeStartFuction()
{
    AdminDataBase oAdminDB(VECTOR_IMP);// guest/admin->vector/set��ʵ������������ϾͲ�һһ�о���

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