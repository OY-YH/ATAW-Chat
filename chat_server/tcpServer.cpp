#include "tcpServer.h"

#include<QJsonParseError>
#include <QJsonObject>

#include "clientsocket.h"
#include "database.h"
#include"type.h"

TcpServer::TcpServer(QObject *parent) :
    QObject(parent)
{
    m_tcpServer = new QTcpServer(this);

    //newconnect
    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(SltNewConnection()));
}

TcpServer::~TcpServer()
{
    if (m_tcpServer->isListening()) m_tcpServer->close();
}



//void TcpMsgServer::newConnect()
//{
//    QTcpSocket * sock=sockServ->nextPendingConnection();
//    tcpSocket* clnSock=new tcpSocket(this,sock);

    //当用户登陆成功
//    connect(clnSock,&tcpSocket::successLogin,this,[=](){
//          clnMsgList.append(clnSock);
//        qDebug()<<"login sucess";
//          //私发消息
//          connect(clnSock,&tcpSocket::sendMessagetoClient,this,[=](QJsonValue dataval,int ID){

//              foreach (tcpSocket* sock, clnMsgList) {
//                  if(sock->getID()==ID)
//                  {
//                      clnSock->sendMessage(SendMsg,dataval);
//                  }
//              }
//          });
//          //发送全部
//          connect(clnSock,&tcpSocket::sendAllMsg,this,&TcpMsgSever::sendToAll);
//    });

//}

//启动监听
bool TcpServer::StartListen(int port)
{
    if (m_tcpServer->isListening()) m_tcpServer->close();
    bool bOk = m_tcpServer->listen(QHostAddress::Any, port);
    return bOk;
}

void TcpServer::CloseListen()
{
    m_tcpServer->close();
}

TcpMsgServer::TcpMsgServer(QObject *parent)
    : TcpServer{parent}
{
    //    sockServ=new QTcpServer(this);
    //    sockServ->listen(QHostAddress::Any,8888);//消息端口
    //    connect(sockServ,&QTcpServer::newConnection,this,&TcpMsgSever::newConnect);


}

TcpMsgServer::~TcpMsgServer()
{
    qDebug() << "tcp server close";
    foreach (ClientSocket *client, m_clients) {
        m_clients.removeOne(client);
        client->closeSocket();
    }
}
void TcpMsgServer::sendToAll(QJsonValue dataVal)
{
//    foreach (tcpSocket *sock, clnMsgList) {
//        sock->sendMessage(SendMsg,dataVal);
//    }
}

// 有新的客户端连接进来
void TcpMsgServer::SltNewConnection()
{
    ClientSocket *client = new ClientSocket(this, m_tcpServer->nextPendingConnection());
    //check
    connect(client, &ClientSocket::signalConnected, this, &TcpMsgServer::SltConnected);
    connect(client, &ClientSocket::signalDisConnected, this, &TcpMsgServer::SltDisConnected);
}

/**
 * @brief TcpMsgServer::SltConnected
 * 通过验证后，才可以加入容器进行管理(online
 */
void TcpMsgServer::SltConnected()
{
    //sender 如果在由信号激活的插槽中调用该函数 返回指向发送信号的对象的指针 否则返回0
    ClientSocket *client = (ClientSocket *)this->sender();
    if (NULL == client) return;

    //send message 发送全部
    connect(client,&ClientSocket::sendMessagetoClient,this,&TcpMsgServer::SltMsgToClient);
    //signal to signal
    connect(client, &ClientSocket::signalDownloadFile, this, &TcpMsgServer::signalDownloadFile);

    //get name from id
    Q_EMIT signalUserStatus(QString("用户 [%1] 上线").arg(Database::Instance()->getUserName(client->getUserID())));
    m_clients.push_back(client);
}

/**
 * @brief TcpMsgServer::SltDisConnected
 * 有客户端下线
 */
void TcpMsgServer::SltDisConnected()
{
    ClientSocket *client = (ClientSocket *)this->sender();
    if (NULL == client) return;

    for (int i = 0; i < m_clients.size(); i++) {
        if (client == m_clients.at(i))
        {
            m_clients.remove(i);
            Q_EMIT signalUserStatus(QString("用户 [%1] 下线").arg(Database::Instance()->getUserName(client->getUserID())));
            return;
        }
    }

    disconnect(client, &ClientSocket::signalConnected, this, &TcpMsgServer::SltConnected);
    disconnect(client, &ClientSocket::signalDisConnected, this, &TcpMsgServer::SltDisConnected);
    disconnect(client, &ClientSocket::sendMessagetoClient,
               this, &TcpMsgServer::SltMsgToClient);
    disconnect(client, &ClientSocket::signalDownloadFile, this, &TcpMsgServer::signalDownloadFile);
}

/**
 * @brief TcpMsgServer::SltMsgToClient
 * 消息转发控制
 * @param userId
 * @param msg
 */
void TcpMsgServer::SltMsgToClient(const quint8 &type, const int &id, const QJsonValue &json)
{
    // 查找要发送过去的id
    for (int i = 0; i < m_clients.size(); i++) {
        if (id == m_clients.at(i)->getUserID())
        {
            m_clients.at(i)->sendMessage(type, json);
            return;
        }
    }
}

/**
 * @brief TcpMsgServer::SltTransFileToClient
 * @param userId
 * @param fileName
 */
void TcpMsgServer::SltTransFileToClient(const int &userId, const QJsonValue &json)
{
    // 查找要发送过去的id
    for (int i = 0; i < m_clients.size(); i++) {
        if (userId == m_clients.at(i)->getUserID())
        {
            m_clients.at(i)->sendMessage(SendFile, json);
            return;
        }
    }
}



//---------------------------------------------

/// 文件中转服务器，客户端先把待转发的文件发送到服务器，服务器接受完成后，通知
/// 其他客户端来下载
TcpFileServer::TcpFileServer(QObject *parent) :
    TcpServer(parent)
{
}

TcpFileServer::~TcpFileServer()
{
    qDebug() << "tcp server close";
    foreach (ClientFileSocket *client, m_clients) {
        m_clients.removeOne(client);
        client->closeSocket();
    }
}

void TcpFileServer::SltNewConnection()
{
    ClientFileSocket *client = new ClientFileSocket(this, m_tcpServer->nextPendingConnection());

    connect(client, &ClientFileSocket::signalConnected, this, &TcpFileServer::SltConnected);
    connect(client, &ClientFileSocket::signalDisConnected, this, &TcpFileServer::SltDisConnected);
}

/**
 * @brief TcpFileServer::SltConnected
 * socket管理
 */
void TcpFileServer::SltConnected()
{
    ClientFileSocket *client = (ClientFileSocket *)this->sender();
    if (NULL == client) return;

    m_clients.push_back(client);
}

/**
 * @brief TcpFileServer::SltDisConnected
 */
void TcpFileServer::SltDisConnected()
{
    ClientFileSocket *client = (ClientFileSocket *)this->sender();
    if (NULL == client) return;

    for (int i = 0; i < m_clients.size(); i++) {
        if (client == m_clients.at(i))
        {
            m_clients.remove(i);
            return;
        }
    }

    disconnect(client, &ClientFileSocket::signalConnected, this, &TcpFileServer::SltConnected);
    disconnect(client, &ClientFileSocket::signalDisConnected, this, &TcpFileServer::SltDisConnected);
}

/**
 * @brief TcpFileServer::SltClientDownloadFile
 * 客户端请求下载文件
 */
void TcpFileServer::SltClientDownloadFile(const QJsonValue &json)
{
    // 根据ID寻找连接的socket
    if (json.isObject()) {
        QJsonObject jsonObj = json.toObject();
        qint32 nId = jsonObj.value("from").toInt(); //from(me
        qint32 nWid = jsonObj.value("id").toInt(); //to (friend
        QString fileName = jsonObj.value("msg").toString();
        qDebug() << "get file" << jsonObj << m_clients.size();
        for (int i = 0; i < m_clients.size(); i++) {
            if (m_clients.at(i)->CheckUserId(nId, nWid))
            {
                m_clients.at(i)->StartTransferFile(fileName);
                return;
            }
        }
    }
}

//TcpFileServer::TcpFileServer(QObject *parent):TcpServer{parent}
//{
//    sockServ=new QTcpServer(this);
//    sockServ->listen(QHostAddress::Any,9999);//文件端口
//    connect(sockServ,&QTcpServer::newConnection,this,&TcpFileServer::newConnect);


//}

//void TcpFileServer::newConnect()
//{
////    QTcpSocket* sock=sockServ->nextPendingConnection();
//    tcpFileSocket* filesock=new tcpFileSocket(this,sock);
//    clnFileList.append(filesock);
//    connect(filesock,&tcpFileSocket::sendFileToUSer,this,[=](int recvID){
//        foreach (tcpFileSocket* fsock, clnFileList) {
//            if(fsock->getID()==recvID)
//            {
//                filesock->sendFile();
//            }
//        }
//    });
//}
