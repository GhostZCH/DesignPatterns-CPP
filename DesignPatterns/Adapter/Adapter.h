#ifndef _ADAPTER_H_
#define _ADAPTER_H_

#include <string>
#include <map>
#include <set>
#include <vector>
#include <iostream>

using namespace std;

// 典型的C语言接口，用来模仿老接口

#define OK 0
#define ERR -1

typedef unsigned int UINT;

int USER_AddUser(UINT ulUserNum, const char* pcUsername);
int USER_AddFirend(UINT ulUserNum, UINT ulFrdUserNum);
int USER_ListFirend(UINT ulUserNum, char * apcFirendNames[],  const UINT ulMaxNameLen, const UINT ulMaxFrCount, UINT *pulFrdCount);


// 新系统的C++接口

class UserSystem
{
public:
    bool Add(UINT ulUserID, string strName);
    bool AddFriend(UINT ulUserID, const set<UINT>& setFrdUserIDList);
    bool GetFirends(UINT ulUserID, set<string>& setFirend);

private:
    bool IsExist(UINT ulUserId);

private:
    map<UINT, string> m_mapUser;
    map<UINT, set<UINT>> m_mapFirend; 
};


// adapter
class Adapter
{
public:
    Adapter(UserSystem* poNewSys);

    int AddUser(UINT ulUserNum, const char* pcUsername);
    int AddFirend(UINT ulUserNum, UINT ulFrdUserNum);
    int ListFirend(UINT ulUserNum, char* apcFirendNames[],  const UINT ulMaxNameLen, const UINT ulMaxFrCount, UINT *pulFrdCount);

private:
    bool IsNullString(const char* pcUsername);
    bool IsNullPtr(const void* pPtr);
    void CpyString(char* pcUsername, const string& strString, const UINT ulMaxNameLen);
    inline int BoolToInt(bool bValue);

private:
    UserSystem* m_poNewSys;
};

void AdapterStartFunction();

#endif
