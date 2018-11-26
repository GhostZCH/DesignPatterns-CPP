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
    m_strResult << ";" << strKey << "\n"    // ��дע�͵��Ǻú���(*^__^*) ��������
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
    m_mapCfg["���ϳ�ɶ"]    = "��Ի������";
    m_mapCfg["���ı�ע"]    = "Ϊɶ������˵��д���벻�����أ�";
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

    poBuidler = new TextSerializationBuilder(); // <--ֻ�������в���
    oConfig.Serialization(*poBuidler); // ��ͬ�Ĳ�����ͬ���
    cout << poBuidler->GetResult() << endl;
    delete poBuidler; poBuidler = NULL;

    poBuidler = new IniSerializationBuilder();// <--ֻ�������в���
    oConfig.Serialization(*poBuidler);// ��ͬ�Ĳ�����ͬ���
    cout << poBuidler->GetResult() << endl;
    delete poBuidler; poBuidler = NULL;

    poBuidler = new XmlSerializationBuilder();// <--ֻ�������в���
    oConfig.Serialization(*poBuidler);// ��ͬ�Ĳ�����ͬ���
    cout << poBuidler->GetResult() << endl;
    delete poBuidler; poBuidler = NULL;

    cout << " ÿ�����µ������ø��ϴ��룬�Ӹ�builder�ͺ��ˣ��ǲ��Ǻ�ˬ��Ҫ��Ҫ˭����һ��json�ģ�" << endl;
}
