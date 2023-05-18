#include "database.h"
#include"type.h"
#include<QDebug>
#include <QJsonObject>
#include <QSqlQuery>

#define DATE_TME_FORMAT     QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")

Database *Database::self = nullptr;

Database::Database(QObject *parent)
    : QObject{parent}
{

}

Database::~Database()
{
    if (userdb.isOpen()) {
        userdb.close();
    }
}

bool Database::openDb(const QString &dataName)
{
    userdb = QSqlDatabase::addDatabase("QSQLITE");
    userdb.setDatabaseName(dataName);
    if (!userdb.open()) {
        qDebug() << "Open database failed";
        return false;
    }

    // 添加数据表
    QSqlQuery query;

    //创建用户信息表(id,name,passwd,head,status,lasttime),
    query.exec("CREATE TABLE UserInfo( id INT PRIMARY KEY, "
               "name varchar(20), passwd varchar(20), "
               "head varchar(20), status INT, lasttime DATETIME )");
//    query.exec("CREATE TABLE USERINFO (id INT PRIMARY KEY, name varchar(20), "
//               "passwd varchar(20), head varchar(20), status INT, groupId INT, lasttime DATETIME);");

    //创建群信息表(id,name,head,adminID,memberCnt,createTime)
    query.exec("CREATE TABLE GroupInfo( id INT PRIMARY KEY, "
               "name varchar(20), head varchar(20), "
               "adminID INT, memberCnt INT,createTime DATETIME )");

    //创建好友关系信息表
    query.exec("CREATE TABLE Friendship( userID1 INT,userID2 INT, "
               "createTime DATETIME, PRIMARY KEY(userID1,userID2), "
               "constraint id_fk1 foreign key (userID1) references UserInfo(id), "
               "constraint id_fk2 foreign key (userID2) references UserInfo(id) )");

    //创建群组成员信息表
    query.exec("CREATE TABLE GroupUser( groupID INT,userID INT, "
               "joinTime DATETIME,PRIMARY KEY(groupID,userID), "
               "constraint id_fk1 foreign key (groupID) references GroupInfo(id), "
               "constraint id_fk2 foreign key (userID) references UserInfo(id) )");

    //创建用户发送文件信息表
    // tag用于表示该文件是否被用户接收(0表示未接收,1表示已接收)
    // type表示该文件是私聊文件还是群聊文件(0表示私聊文件,1表示群聊文件)
    // filename 表示文件的名字，注意是指单纯的文件名字，不包含文件路径
    // filepath 表示文件在服务器上的路径，注意，路径长度最长100个字符
    // (senderID,receiverID,time)可唯一地标注一条文件信息，time用户发送该文件的时间
    query.exec("CREATE TABLE FileSent( senderID int,receiverID int,GroupID int,"
               "filename varchar(50),filesize bigint,filepath varchar(100),"
               "time DATETIME,tag bit,type bit,PRIMARY KEY(senderID,receiverID,time),"
               "constraint id_fk1 foreign key (senderID) references UserInfo(id),"
               "constraint id_fk2 foreign key (receiverID) references UserInfo(id),"
               "constraint id_fk3 foreign key (GroupID) references GroupInfo(id) )");

    //消息缓存表，把未发给用户的消息缓存在此张表中
    //如果是普通的文本消息，则在msg字段写入文本，如果是文件或者图片，则写入该文件在服务器上的存储地址
    //tag = 0表示私聊消息，tag = 1表示群聊消息
    query.exec("CREATE TABLE UnreadMsg( senderID int,receiverID int,"
               "groupID int,type int,time bigint,"
               "msg varchar(200),tag bit,fileSize bigint,"
               "PRIMARY KEY(senderID,receiverID,time),"
               "constraint id_fk1 foreign key (senderID) references UserInfo(id),"
               "constraint id_fk2 foreign key (receiverID) references UserInfo(id),"
               "constraint id_fk3 foreign key (groupID) references GroupInfo(id) )");

    //往用户信息表中插入一条管理员记录
    query.exec("INSERT INTO UserInfo VALUES(100000, 'admin', '123456', '', 0, '');");

    qDebug() << "初始化数据库完毕";

    // 更新状态,避免有些客户端异常退出没有更新下线状态
//    changeAllUserStatus();
    //queryAll();
    return true;
}



// 用户校验
//QJsonObject Database::checkUserLogin(const int &id, const QString &passwd)
QJsonObject Database::CheckUserLogin(const QString &name, const QString &passwd)
{
//    int code;
//    QString head = "";
//    QString name = "";
//    QString strQuery = "SELECT * FROM UserInfo ";
//    strQuery.append("WHERE id=");
//    strQuery.append(QString::number(id));

//    QSqlQuery query(strQuery);
//    if (query.next()) {//id存在
//        strQuery.append(" AND passwd= '");
//        strQuery.append(passwd);
//        strQuery.append("'");
//        QSqlQuery query2(strQuery);
//        qDebug()<<"password:"<<passwd;
//        if(query2.next()){
//            strQuery.append(" AND status=");
//            strQuery.append(QString::number(OnLine));
//            QSqlQuery query3(strQuery);
//            if(query3.next()){//重复登陆
//                code = -3;
//            }else{//登陆成功
//                code = 0;
//                head = query2.value("head").toString();
//                name = query2.value("name").toString();
//                updateUserStatus(id, OnLine);
//            }
//        }else{//密码错误
//            code = -1;
//        }
//    }else{//id不存在
//        code = -2;
//    }

//    QJsonObject json;
//    json.insert("id",id);
//    json.insert("code",code);
//    json.insert("head",head);
//    json.insert("name",name);

//    return json;

    QString strQuery = "SELECT [id],[head],[status] FROM USERINFO ";
    strQuery.append("WHERE name='");
    strQuery.append(name);
    strQuery.append("' AND passwd='");
    strQuery.append(passwd);
    strQuery.append("';");

    QJsonObject jsonObj;
    int nId = 1;
    int code = -1;
    QString strHead = "0.bmp";

    QSqlQuery query(strQuery);
    if (query.next()) {
        nId = query.value("id").toInt();
        int nStatus = query.value("status").toInt();
        if (OnLine == nStatus)
        {
            nId = -2;
            code = -2;
        }
        else
        {
            // 更新在线信息
//            UpdateUserStatus(nId, OnLine);
            code = 0;
        }
        strHead = query.value("head").toString();
    }

    // 组织返回
    jsonObj.insert("id", nId);
    jsonObj.insert("msg", nId < 0 ? "error" : "ok");
    jsonObj.insert("head", strHead);
    jsonObj.insert("code", code);

    return jsonObj;
}

int Database::registerUser(QString name, QString pwd)
{
    QString strQuery = "SELECT * FROM UserInfo";
    strQuery.append(" order by id desc");

    int id;
    QSqlQuery query(strQuery);
    if (query.next()) {
        id = query.value(0).toInt();
        id++;//分配给该注册用户的id
    }

    // 根据新ID重新创建用户
    query.prepare("INSERT INTO UserInfo (id, name, passwd, head, status, lasttime) "
                  "VALUES (?, ?, ?, ?, ?, ?);");
    query.bindValue(0, id);
    query.bindValue(1, name);
    query.bindValue(2, pwd);
    query.bindValue(3, QString::number(id) + ".png");
    query.bindValue(4, 0);
    query.bindValue(5, DATE_TME_FORMAT);

    query.exec();


    //为用户分配存放头像的目录
//    MyApp::createDir(MyApp::m_strHeadPath + QString::number(id) + "/");
//    myHelper::CopyFile(MyApp::m_strHeadPath + "system/default.png",
//                       MyApp::m_strHeadPath + QString::number(id) + "/" + QString::number(id) + ".png");

    return id;
}

QString Database::getUserName(const int &id) const
{
    QString strQuery = "SELECT [name] FROM USERINFO ";
    strQuery.append("WHERE id=");
    strQuery.append(QString::number(id));

    QSqlQuery query(strQuery);
    if (query.next()) {
        return query.value(0).toString();
    }

    return "";
}
