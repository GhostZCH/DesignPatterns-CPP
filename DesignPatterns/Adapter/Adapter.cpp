#include "Adapter.h"

#include <string.h>

// 新系统的C++接口
bool UserSystem::Add( UINT ulUserID, string strName )
{
    if (IsExist(ulUserID))
    {
        return false;
    }

    m_mapUser[ulUserID] = strName;// map 的机制访问不存在的键会自动添加
    return true;
}

bool UserSystem::AddFriend( UINT ulUserID, const set<UINT>& setFrdUserIDList )
{
    if (!IsExist(ulUserID))
    {
        return false;
    }

    set<UINT>::iterator iter = setFrdUserIDList.begin();
    for ( ; iter != setFrdUserIDList.end(); iter++)
    {
        if (!IsExist(*iter))
        {
            return false;
        }
    }

    m_mapFirend[ulUserID]= setFrdUserIDList; // map 的机制访问不存在的键会自动添加
    return true;
}

bool UserSystem::GetFirends(UINT ulUserID, set<string>& setFirend)
{
    if (!IsExist(ulUserID))
    {
        return false;
    }

   set<UINT> setFrdId = m_mapFirend[ulUserID]; // 会复制

   set<UINT>::iterator iter;
   for (iter = setFrdId.begin(); iter != setFrdId.end(); iter++)
   {
       setFirend.insert(m_mapUser[*iter]);
   }
   return true;
}

bool UserSystem::IsExist( UINT ulUserId )
{
    return m_mapUser.find(ulUserId) != m_mapUser.end();
}

UserSystem g_oUserSystem;

// adapter

Adapter::Adapter( UserSystem* poNewSys )
{
    if (IsNullPtr(poNewSys))
    {
        throw "poNewSys is NULL";
    }
    m_poNewSys = poNewSys;
}

int Adapter::AddUser(UINT ulUserNum, const char* pcUsername)
{
    if (IsNullString(pcUsername))
    {
        return ERR;
    }

    // 在新老接口中周旋，数据转换，调用
    return BoolToInt(m_poNewSys->Add(ulUserNum, string(pcUsername)));
}

int Adapter::AddFirend(UINT ulUserNum, UINT ulFrdUserNum)
{
    // 新老接口总有些不同 /(ㄒoㄒ)/~~
    // 总是需要转换下，这是常事
    set<UINT> setFriend;
    setFriend.insert(ulFrdUserNum);

    return BoolToInt(m_poNewSys->AddFriend(ulUserNum, setFriend)); 
}

int Adapter::ListFirend(UINT ulUserNum, char* apcFirendNames[],  const UINT ulMaxNameLen, const UINT ulMaxFrCount, UINT *pulFrdCount)
{
    set<string> setFriend;

    if (IsNullPtr(pulFrdCount))
    {
        return ERR;
    }

    if (!m_poNewSys->GetFirends(ulUserNum, setFriend))
    {
        return ERR;
    }

    set<string>::iterator iter = setFriend.begin();
    for ((*pulFrdCount) = 0; *pulFrdCount < setFriend.size() && (*pulFrdCount) < ulMaxFrCount; (*pulFrdCount)++, iter++)
    {
        if (IsNullPtr(apcFirendNames[*pulFrdCount]))
        {
            return ERR;
        }
        CpyString(apcFirendNames[*pulFrdCount], *iter, ulMaxNameLen);
    }
    return OK;
}


bool Adapter::IsNullString(const char* pcUsername)
{
    return (NULL == pcUsername) || ('\0' == pcUsername[0]); 
}

bool Adapter::IsNullPtr(const void* pPtr)
{
    return NULL == pPtr;
}

void Adapter::CpyString(char* pcUsername, const string& strString, const UINT ulMaxNameLen)
{
    if (ulMaxNameLen <= strString.length() )//strString.length() 不包括\0
    {
        strcpy(pcUsername, strString.substr(0, ulMaxNameLen - 1).c_str());
        // substr(a,b) 取[a,b), c_str 自动补上 \0 
        return;
    }
   strcpy(pcUsername, strString.c_str());
}

inline int Adapter::BoolToInt( bool bValue )
{
    return bValue? OK : ERR;
}


Adapter g_oAdapter(&g_oUserSystem);

// 典型的C语言接口，用来模仿老接口
int USER_AddUser( UINT ulUserNum, const char* pcUsername )
{
    return g_oAdapter.AddUser(ulUserNum, pcUsername); //利用adapter在新老接口中转换
}

int USER_AddFirend( UINT ulUserNum, UINT ulFrdUserNum )
{
    return g_oAdapter.AddFirend(ulUserNum, ulFrdUserNum);
}

int USER_ListFirend( UINT ulUserNum, char * apcFirendNames[], const UINT ulMaxNameLen, const UINT ulMaxFrCount, UINT *pulFrdCount )
{
    return g_oAdapter.ListFirend(ulUserNum, apcFirendNames,  ulMaxNameLen, ulMaxFrCount, pulFrdCount);
}

void AdapterStartFunction()
{
    USER_AddUser(1,"tom xxxx");
    USER_AddUser(2,"li lei");
    USER_AddUser(3, "han meimei");

    USER_AddFirend(3, 1);

    char* apcRslt[10]; // 指针的数组
    char  aacRslt[10][10];
    for (int i = 0; i < 10 ; i++)
    {
        apcRslt[i] = &(aacRslt[i][0]);
    }

    UINT ulFrdCnt;
    USER_ListFirend(3, apcRslt, 6, 10, &ulFrdCnt);

    for (UINT u = 0; u < ulFrdCnt; u++)
    {
        printf("%s\n", apcRslt[u]);
    }
}
