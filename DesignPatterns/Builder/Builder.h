#ifndef _BUILDER_H_
#define _BUILDER_H_

#include <string>
#include <map>
#include <sstream>

using namespace std;

// 这个类不能，也不需要实例化
class SerializationBuilder
{
public:
    virtual void  Start() = 0;
    virtual void AddCfg(string strKey, string strValue) = 0;
    virtual void End() = 0;

    virtual string GetResult();

protected:
    stringstream m_strResult;
};

// *.text
class TextSerializationBuilder: public SerializationBuilder
{
public:
    virtual void  Start();
    virtual void AddCfg(string strKey, string strValue);
    virtual void End();
};

// *.ini
class IniSerializationBuilder: public SerializationBuilder
{
public:
    virtual void  Start();
    virtual void AddCfg(string strKey, string strValue);
    virtual void End();
};

// *.xml
class XmlSerializationBuilder: public SerializationBuilder
{
public:
    virtual void  Start();
    virtual void AddCfg(string strKey, string strValue);
    virtual void End();
};

// *.*
// 其实你还可以创建更多的builder而不需要修改老代码，比如json...

class Config
{
public:
    Config();
    void Serialization(SerializationBuilder& oBuilder);

private:
    map<string, string> m_mapCfg;
};


void BuilderStartFunction();

#endif
