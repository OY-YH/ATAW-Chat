#include "clientsocket.h"
#include "type.h"
#include "myapp.h"

#include<database.h>
#include <QJsonDocument>
#include <QJsonObject>
#include<QJsonValue>

ClientSocket::ClientSocket(QObject *parent,QTcpSocket* tcpSocket)
    : QObject{parent}
{
    m_id = -1;

    if (tcpSocket == NULL) m_tcpSocket = new QTcpSocket(this);
    m_tcpSocket = tcpSocket;
    connect(tcpSocket,&QTcpSocket::readyRead,this,&ClientSocket::readMsg);
//    connect(tcpSocket,&QTcpSocket::disconnected,this,[=](){tcpSocket->deleteLater();});


//    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(SltReadyRead()));
    connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(SltConnected()));
    connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(SltDisconnected()));
}

void ClientSocket::closeSocket()
{
    //终止当前连接并重置套接字 丢弃写缓冲区中的任何挂起数据
    m_tcpSocket->abort();

}

int ClientSocket::getUserID()
{
    return m_id;
}

void ClientSocket::readMsg()
{
    QByteArray byteArray=m_tcpSocket->readAll();
    //解析数据
    QJsonParseError jsonError;
    QJsonDocument document=QJsonDocument::fromJson(byteArray,&jsonError);

    if((!document.isNull())&&(QJsonParseError::NoError==jsonError.error))
    {
        if(document.isObject())
        {
            QJsonObject jsonObj=document.object();
            int sendID=jsonObj.value("from").toInt();
            int type=jsonObj.value("type").toInt();
            QJsonValue data=jsonObj.value("data");
            qDebug()<<"recv from client"<<sendID<<jsonObj;
            switch (type) {
            case SendMsg://私发消息
//                emit sendMessagetoClient(data,1);//由tcpServer查找发送的目标主机
                break;
            case SendGroupMsg:
                emit sendAllMsg(data);
                break;
            case Login:
                UserLogin(data);
                break;
            case Register:
                parseReister(data);
                break;
            default:
                break;
            }

        }

    }
}

void ClientSocket::sendMessage(const quint8 &type, const QJsonValue &jsonVal)
{
    if (!m_tcpSocket->isOpen())
        return;

    // 构建 Json 对象
    QJsonObject jsonObj;
    jsonObj.insert("type", type);
    jsonObj.insert("from", m_id);
    jsonObj.insert("data", jsonVal);

    // 构建 Json 文档
    QJsonDocument document;
    document.setObject(jsonObj);
    m_tcpSocket->write(document.toJson(QJsonDocument::Indented));
}


void ClientSocket::UserLogin(QJsonValue dataVal)
{
    // data 的 value 是对象
    if (dataVal.isObject()) {
        QJsonObject dataObj = dataVal.toObject();
        int id = dataObj.value("id").toInt();
        QString name = dataObj.value("name").toString();
        QString strPwd = dataObj.value("password").toString();
        //查询数据库验证用户的ID和密码是否匹配
        QJsonObject json = Database::Instance()->CheckUserLogin(name, strPwd);
        qDebug()<<"验证完毕"<<json.value("code").toInt();
        int code = json.value("code").toInt();

        //登陆成功
        if(code == 0){
            m_id = id;
            emit successLogin();
        }
        //把登陆消息返回给客户端
        sendMessage(Login,json);
    }
}

void ClientSocket::parseReister(const QJsonValue &dataVal)
{
    if(dataVal.isObject())
    {
        QJsonObject dataObj=dataVal.toObject();
        QString name=dataObj.value("name").toString();
        QString password=dataObj.value("pwd").toString();

        int id=Database::Instance()->registerUser(name,password);
        //封装数据 将数据结果发送至客户端
        QJsonObject json;
        json.insert("id",id);
        json.insert("pwd",password);
        json.insert("name",name);
        sendMessage(Register,json);
    }

}




ClientFileSocket::ClientFileSocket(QObject *parent, QTcpSocket *tcpSocket):QObject{parent}
{
//    ID=-1;
//    connect(fileSock,&QTcpSocket::readyRead,this,&ClientFileSocket::readFileMsg);
//    connect(fileSock,&QTcpSocket::disconnected,[=](){
//        fileSock->deleteLater();
//    });
//    connect(this,&ClientFileSocket::headmsg,this,&ClientFileSocket::handleHeadmsg);
//    connect(&timer,&QTimer::timeout,this,[=](){

//        qDebug()<<"send";
//       if(!file.open(QIODevice::ReadOnly))
//           qDebug()<<"文件打开失败";
//       int len;
//       do{

//           char buf[4*1024]={0};
//           len=0;
//           len=file.read(buf,sizeof(buf));
//           len=fileSock->write(buf,len);
//           sendSize+=len;
//       }while(len>0);
//       if(sendSize==fileSize)
//       {
//           file.close();
//           sendSize=0;
//           qDebug()<<"文件发送成功";
//       }
//    });

    // 将整个大的文件分成很多小的部分进行发送，每部分为4字节
    loadSize            = 50 * 1024;
    ullSendTotalBytes   = 0;
    ullRecvTotalBytes   = 0;
    bytesWritten        = 0;
    bytesToWrite        = 0;
    bytesReceived       = 0;

    fileNameSize        = 0;
    m_bBusy             = false;

    m_UserId           = -1;
    m_WindowId         = -1;

    // 本地文件存储
    fileToSend = new QFile(this);
    fileToRecv = new QFile(this);

    // 客户端
    if (tcpSocket == NULL) m_tcpSocket = new QTcpSocket(this);
    m_tcpSocket = tcpSocket;

    // 我们更新进度条
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(SltReadyRead()));
    connect(m_tcpSocket, SIGNAL(disconnected()), this, SIGNAL(signalDisConnected()));
    // 当有数据发送成功时，我们更新进度条
    connect(m_tcpSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(SltUpdateClientProgress(qint64)));
}

void ClientFileSocket::closeSocket()
{
    m_fileSocket->abort();
}

//用户socket检测，通过此函数进行判断连接的socket
bool ClientFileSocket::CheckUserId(const qint32 fromId,const qint32 toId)
{
    return ((m_UserId == fromId) && (m_WindowId == toId));
}

int ClientFileSocket::getID() const
{
    return m_UserId;
}

 /**
 * @brief ClientFileSocket::startTransferFile
 * 下发文件
 * @param type 0 表示单纯的语音文件，1表示文字+语音，客户端只收不显示
 * @param fileName  文件名
 */
void ClientFileSocket::StartTransferFile(QString fileName)
{
    if (m_bBusy) return;

    if (!m_tcpSocket->isOpen()) {       //未连接
        return;
    }

    // 要发送的文件
    fileToSend = new QFile((-2 == m_WindowId ? MyApp::m_strHeadPath : MyApp::m_strRecvPath) + fileName);

    if (!fileToSend->open(QFile::ReadOnly))
    {
        qDebug() << "open file error!";
        return;
    }

    ullSendTotalBytes = fileToSend->size(); // 文件总大小

    QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_6_4);

    QString currentFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);

    // 依次写入总大小信息空间，文件名大小信息空间，文件名
    sendOut << qint64(0) << qint64(0) << currentFileName;

    // 这里的总大小是文件名大小等信息和实际文件大小的总和
    ullSendTotalBytes += outBlock.size();

    // 返回outBolock的开始，用实际的大小信息代替两个qint64(0)空间
    sendOut.device()->seek(0);
    sendOut << ullSendTotalBytes << qint64((outBlock.size() - sizeof(qint64)*2));

    // 发送完头数据后剩余数据的大小
    bytesToWrite = ullSendTotalBytes - m_tcpSocket->write(outBlock);

    outBlock.resize(0);
    m_bBusy = true;
    qDebug() << "Begin to send file" << fileName << m_UserId << m_WindowId;

}

void ClientFileSocket::readFileMsg()
{
    QByteArray msg=m_fileSocket->readAll();
    qDebug()<<"recv from client"<<msg;
   //解析发送的消息 是否为文件的头部信息
    QJsonParseError parseError;
    QJsonDocument docuemnt=QJsonDocument::fromJson(msg,&parseError);
    if((!docuemnt.isNull())&&(parseError.error==QJsonParseError::NoError))
    {
        if(docuemnt.isObject())
        {
           QJsonObject JsonObj=docuemnt.object();
           int type=JsonObj.value("type").toInt();
           m_UserId=JsonObj.value("from").toInt();
           m_WindowId=JsonObj.value("to").toInt();
           QString data=JsonObj.value("data").toString();
           switch (type) {
           case SendFileHead:
//               emit headmsg(data);//文件头部信息
               break;
           default:

               break;
           }


        }
       return;
    }
    handleFileMsg(msg);

}

void ClientFileSocket::handleHeadmsg(QString data)
{
    fileName=data.section("##",0,0);
    fileSize=data.section("##",1,1).toInt();
    file.setFileName(fileName);
   if(!file.open(QIODevice::WriteOnly))
   {
       qDebug()<<"打开文件失败";
   }


}

void ClientFileSocket::handleFileMsg(QByteArray data)
{

    qDebug()<<"开始写文件";

    recvSize=0;
    int len=file.write(data);
    recvSize+=len;

    if(recvSize==fileSize)//接受完文件
    {
        qDebug()<<"接受文件完成";
        isFile=false;
        file.close();
        //发送文件给用户
//        sendFileToUSer(recvID);
    }
}

void ClientFileSocket::sendFile()
{
    //封装发送的头部信息
    QString data=QString("%0##%1").arg(fileName).arg(fileSize);
    QJsonObject JsonObj;
    JsonObj.insert("from",m_UserId);
    JsonObj.insert("type",SendFileHead);
    JsonObj.insert("data",data);
    QJsonDocument document;
    document.setObject(JsonObj);
    int len=m_fileSocket->write(document.toJson(QJsonDocument::Indented));
    if(len>0)
   {
        qDebug()<<"文件的头部的信息发送完成";
        timer.start(20);
    }

}


