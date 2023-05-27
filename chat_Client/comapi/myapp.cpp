#include "myapp.h"

#include <QSettings>

// 应用程序配置目录
QString MyApp::m_strAppPath         = "./";
QString MyApp::m_strDataPath        = "";
QString MyApp::m_strRecvPath        = "";
QString MyApp::m_strDatabasePath    = "";
QString MyApp::m_strConfPath        = "";
QString MyApp::m_strFacePath        = "";
QString MyApp::m_strHeadPath        = "";
QString MyApp::m_strSoundPath       = "";
QString MyApp::m_strRecordPath      = "";
// 配置文件
QString MyApp::m_strIniFile         = "config.ini";
QString MyApp::m_debugFile          = "debug.log";

// 服务器相关配置
QString MyApp::m_strHostAddr        = "";
int     MyApp::m_nMsgPort           = 0;
int     MyApp::m_nFilePort          = 0;
int     MyApp::m_nGroupPort         = 0;

//用户信息配置
int     MyApp::m_nId                = -1;
QString MyApp::m_strUserName        = "";
QString MyApp::m_strPassword        = "";
QString MyApp::m_strHeadFile        = "";

//应用程序设置
bool    MyApp::checked              = false;
bool    MyApp::autoLogin            = false;
bool    MyApp::sendWay              = false;
int     MyApp::m_nWinX              = 0;
int     MyApp::m_nWinY              = 0;


MyApp::MyApp(QObject *parent)
    : QObject{parent}
{

}

void MyApp::saveConfig()
{
    QSettings settings(m_strIniFile, QSettings::IniFormat);

    /*系统设置*/
    settings.beginGroup("User");
    settings.setValue("ID", m_nId);
    settings.setValue("Name", m_strUserName);
    settings.setValue("Passwd", m_strPassword);
    settings.endGroup();

    /*其他配置*/
    settings.beginGroup("Server");
    settings.setValue("HostAddr", m_strHostAddr);
    settings.setValue("MsgPort",  m_nMsgPort);
    settings.setValue("FilePort",  m_nFilePort);
    settings.setValue("GroupPort",  m_nGroupPort);
    settings.endGroup();

    /*应用程序设置*/
    settings.beginGroup("Application");
    settings.setValue("checked", checked);
    settings.setValue("autoLogin", autoLogin);
    settings.setValue("sendWay", sendWay);
    settings.endGroup();

    settings.sync();
}
