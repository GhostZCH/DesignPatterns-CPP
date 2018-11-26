#include "Builder.h"
#include <iostream>

using namespace std;

string SerializationBuilder::GetResult()
{
    return m_strResult.str();
}

//TextSerializationBuilder
void TextSerializationBuilder::Start()
{
    m_strResult << "=============[ApplictionConfig BEG]============ " <<endl;
}

void TextSerializationBuilder::AddCfg( string strKey, string strValue )
{
    m_strResult <<"[" << strKey << "]: " << strValue << endl;
}

void TextSerializationBuilder::End()
{
     m_strResult << "=============[ApplictionConfig END]============ " <<endl;
}

//IniSerializationBuilder
void IniSerializationBuilder::Start()
{
    m_strResult << "[ApplictionConfig] " <<endl;
}

void IniSerializationBuilder::AddCfg( string strKey, string strValue )
{
    m_strResult << ";" << strKey << "\n"    // 爱写注释的是好孩子(*^__^*) 嘻嘻……
                       << strKey << "=" << strValue << endl;
}

void IniSerializationBuilder::End()
{
    m_strResult << endl;
}

//XmlSerializationBuilder

void XmlSerializationBuilder::Start()
{
    m_strResult << "<ApplictionConfig> " <<endl;
}

void XmlSerializationBuilder::AddCfg( string strKey, string strValue )
{
    m_strResult << "    <"    << strKey   << ">\n"   
                       << "        " << strValue << "\n" 
                       << "    </"  << strKey    << ">" << endl;
}

void XmlSerializationBuilder::End()
{
    m_strResult << "</ApplictionConfig> " <<endl;
}


//Config
Config::Config()
{
    m_mapCfg.clear();

    m_mapCfg["AppName"]  = "builder test";
    m_mapCfg["IpAddress"]  = "127.0.0.1";
    m_mapCfg["TcpPort"]     = "8888";
    m_mapCfg["晚上吃啥"]    = "想吃火锅啊！";
    m_mapCfg["无聊备注"]    = "为啥总有人说我写代码不正经呢？";
}

void Config::Serialization( SerializationBuilder& oBuilder )
{
    oBuilder.Start();

    map<string, string>::iterator iter = m_mapCfg.begin();
    for (; iter != m_mapCfg.end(); iter++)
    {
        oBuilder.AddCfg(iter->first, iter->second);
    }

    oBuilder.End();
}

//BuilderStartFunction
void BuilderStartFunction()
{
    Config oConfig;

    SerializationBuilder* poBuidler = NULL;

    poBuidler = new TextSerializationBuilder(); // <--只有这里有差异
    oConfig.Serialization(*poBuidler); // 相同的操作不同结果
    cout << poBuidler->GetResult() << endl;
    delete poBuidler; poBuidler = NULL;

    poBuidler = new IniSerializationBuilder();// <--只有这里有差异
    oConfig.Serialization(*poBuidler);// 相同的操作不同结果
    cout << poBuidler->GetResult() << endl;
    delete poBuidler; poBuidler = NULL;

    poBuidler = new XmlSerializationBuilder();// <--只有这里有差异
    oConfig.Serialization(*poBuidler);// 相同的操作不同结果
    cout << poBuidler->GetResult() << endl;
    delete poBuidler; poBuidler = NULL;

    cout << " 每次有新的需求不用改老代码，加个builder就好了，是不是很爽，要不要谁来加一个json的？" << endl;
}
