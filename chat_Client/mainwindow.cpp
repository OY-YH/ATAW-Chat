#include "mainwindow.h"
#include "leftw.h"
#include "midw.h"
#include "qabstractbutton.h"
#include "qbuttongroup.h"
#include "rightw/rightw.h"
#include "tcp_manage.h"
#include "type.h"
#include "ui_mainwindow.h"
#include"chatlist.h"
#include<QFileInfo>
#include<QDateTime>
#include <QJsonValue>
#include <QSqlQuery>
#include <QHBoxLayout>
#include"frienddlg.h"
#include"myapp.h"
#include "sql_manage.h"
#include "cell.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //resize(1600, 800);
    this->setWindowFlags(Qt::FramelessWindowHint);
    fileInfo=nullptr;
//    login.show();
//    connect(&login,&Page_login::sendLoginSuccess,this,[=](){
//        this->show();
//    });

    qDebug()<<"errorrr";
    QHBoxLayout *layout = new QHBoxLayout(ui->centralwidget);
    leftBar = new leftw;
    midBar = new midw;
    rightBar = new rightw;

    layout->addWidget(leftBar);
    layout->addWidget(midBar);
    layout->addWidget(rightBar);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

//    connect(rightBar,SIGNAL(stayOnTop(bool)),this,SLOT(stayOnTop(bool)));
    connect(rightBar,&rightw::updateMidBarTime,
            midBar,&midw::updateTime);
    //    connect(leftBar->m_btnGroup, &QButtonGroup::buttonClicked,
    //            this, &MainWindow::onleftBtnClicked);
    connect(leftBar->m_btnGroup, &QButtonGroup::idClicked,
            this, &MainWindow::onleftBtnClicked);

    connect(midBar,&midw::openDialog,[&](Cell *cell){
        if(cell == nullptr){
            rightBar->resetPage();
            rightBar->setCurrentPage(0);
        }else{
            qDebug() << cell->id << "is opening...";
            rightBar->switchPage(cell); //点击中栏的聊天对话列表，切换右栏中的聊天界面
            onleftBtnClicked(0);
        }
    });

    connect(midBar,&midw::resetRightPage,[&](){
        rightBar->resetPage();
        rightBar->setCurrentPage(0);
    });

    connect(midBar,&midw::contactBtnClicked,[&](){
        onleftBtnClicked(1);
    });


//    settings = new SettingsWnd;
//    settings->setVisible(false);


    //聊天信息列表
//    chatList *list1=new chatList();
//    QListWidgetItem *item1=new QListWidgetItem();
//    item1->setSizeHint(QSize(300,60));
//    ui->listWidget_message->addItem(item1);
//    ui->listWidget_message->setItemWidget(item1,list1);
//    connect(&login,&Page_login::sendSokets,this,[=](clientSock *sock,clientFileSock *filesock){

//        setMainSocket(sock,filesock);//设置主窗口的sockets

//        // QDateTime time=QDateTime::currentDateTime();
//        connect(m_tcp,&clientSock::recvFormServre,this,[=](QString data){
//        QString time = QString::number(QDateTime::currentDateTime().toSecsSinceEpoch()); //时间戳

//        //ui->textBrowser->append(showData);
//        dealMessageTime(time);

////        QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
////        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
////        dealMessage(messageW, item, data, time, QNChatMessage::User_She);
//    });

//        connect(m_fileTcp,&clientFileSock::sendFileSucess,[=]()
//                {

//                    ui->textEdit->clear();
//                });
//        connect(m_fileTcp,&clientFileSock::sucessRecvfile,[=](QString data){
//            QString time = QString::number(QDateTime::currentDateTime().toSecsSinceEpoch()); //时间戳
//            //QDateTime time=QDateTime::currentDateTime();
//            QString showData=data+"\t"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
//            //ui->textBrowser->append(showData);
//            dealMessageTime(time);

//            QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
//            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
//            dealMessage(messageW, item, showData, time, QNChatMessage::User_She);
//            //ui->textBrowser->append(showData);

//        });


//        //添加好友信息
//        connect(&addFriWin,&AddFriendWin::signalFind,this,[=](QJsonObject json){
//            m_tcp->sendMsg(FindFriend,json);
//        });

//        connect(m_tcp,&clientSock::findFrindReply,&addFriWin,&AddFriendWin::SltfindFrindReply);

//        connect(&addFriWin,&AddFriendWin::signalSendMessage,m_tcp,&clientSock::sendMsg);

//        connect(m_tcp,&clientSock::signalMessage,this,&MainWindow::sltTcpReply);

//    });



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setMainSocket(clientSock *socket, clientFileSock *filesocket)
{

//        this->m_tcp=m_tcp;
//        this->m_fileTcp=m_fileTcp;
//        qDebug()<<this->m_tcp<<this->m_fileTcp;

    if(socket != nullptr && filesocket != nullptr){
        m_tcp = socket;

        connect(m_tcp, &clientSock::signalMessage,
                this, &MainWindow::sltTcpReply);
        connect(m_tcp, &clientSock::signalStatus,
                this, &MainWindow::sltTcpStatus);

        connect(rightBar, &rightw::signalSendMessage,
                m_tcp, &clientSock::sendMsg);

        connect(midBar,&midw::signalSendMessage,
                m_tcp, &clientSock::sendMsg);
        connect(midBar,&midw::signalAddChat,this,&MainWindow::sltAddChat);
        connect(m_tcp,&clientSock::signalFindFriendReply,
                midBar,&midw::signalFindFriendReply);

        m_fileTcp = filesocket;
        connect(m_fileTcp,&clientFileSock::signalFileRecvOk,
                this,&MainWindow::sltFileRecvFinished);

        initUI();
    }
}

void MainWindow::initUI()
{
    //加载左栏的头像 ok
    midBar->InitContactList();//加载好友列表和群列表
    midBar->InitChatList();//加载中栏的历史聊天记录框
}


//void MainWindow::on_sendBut_clicked()
//{
//   QString msg= ui->textEdit->toPlainText();
//   ui->textEdit->setText("");
//   QJsonValue data=msg;
//   //
//   QString time = QString::number(QDateTime::currentDateTime().toSecsSinceEpoch()); //时间戳

//   if(msg.isEmpty())
//   {
//    QMessageBox::warning(this,"warning","输入有空");
//   }
//   else  //发送信息或者文件
//   {
//   //    bool isSending = true; // 发送中

//       qDebug()<<"addMessage" << msg << time << ui->listWidget->count();
//       //if(ui->listWidget->count()%2) {
////           if(isSending) {
////               dealMessageTime(time);

////               QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
////               QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
////               dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
////           } else {
////               bool isOver = true;
////               for(int i = ui->listWidget->count() - 1; i > 0; i--) {
////                   QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(ui->listWidget->item(i));
////                   if(messageW->text() == msg) {
////                       isOver = false;
////                       messageW->setTextSuccess();
////                   }
////               }
////               if(isOver) {
////                   dealMessageTime(time);

////                   QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
////                   QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
////                   dealMessage(messageW, item, msg, time, QNChatMessage::User_She);
////                   messageW->setTextSuccess();
////               }
////           }
////       }else {
//           if(fileInfo!=nullptr)
//           {
//               //发送文件
//               qDebug()<<"sendfile";
//               qint64 curTime = QDateTime::currentSecsSinceEpoch();//时间戳

//                m_fileTcp->sendFile(fileName,curTime,SendFile);//发送文件

//                delete fileInfo;
//                fileInfo=nullptr;
//                //QDateTime time=QDateTime::currentDateTime();
//                QString showData=fileName+"\t"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
//                //ui->textBrowser->append(showData);
//                dealMessageTime(time);

//                QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
//                QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
//                dealMessage(messageW, item, showData, time, QNChatMessage::User_Me);
//                messageW->setTextSuccess();
//           }
//         else if(msg != "") {
//               qDebug()<<"sendmsg";
//               m_tcp->sendMsg(SendGroupMsg,data);
//               dealMessageTime(time);

//               QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
//               QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
//               dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
//               messageW->setTextSuccess();

//               ui->textEdit->clear();
//           }
//       }
//           //ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
//  // }

//}


//void MainWindow::on_fileButton_clicked()
//{

//    QFileDialog dialog(this);
//    dialog.setFileMode(QFileDialog::AnyFile);

//    fileName=dialog.getOpenFileName(this,"选择要发送文件");
//    if(!fileName.isEmpty())
//    {
//        fileInfo=new QFileInfo(fileName);
//        ui->textEdit->setText(fileInfo->fileName());
//    }
//}




//void MainWindow::on_btn_user_clicked()
//{
//  friendlg.show();

//}

//void MainWindow::dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time,  QNChatMessage::User_Type type)
//{
//    messageW->setFixedWidth(this->width()/1.57);
//    QSize size = messageW->fontRect(text+" ");
//    item->setSizeHint(size);
//    messageW->setText(text, time, size, type);
//    ui->listWidget->setItemWidget(item, messageW);
//}

//void MainWindow::dealMessageTime(QString curMsgTime)
//{
//    bool isShowTime = false;
//    if(ui->listWidget->count() > 0) {
//        QListWidgetItem* lastItem = ui->listWidget->item(ui->listWidget->count() - 1);
//        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(lastItem);
//        int lastTime = messageW->time().toInt();
//        int curTime = curMsgTime.toInt();
//        qDebug() << "curTime lastTime:" << curTime - lastTime;
//        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差一分钟
////        isShowTime = true;
//    } else {
//        isShowTime = true;
//    }
//    if(isShowTime) {
//        QNChatMessage* messageTime = new QNChatMessage(ui->listWidget->parentWidget());
//        QListWidgetItem* itemTime = new QListWidgetItem(ui->listWidget);

//        QSize size = QSize(this->width()/2, 30);
//        messageTime->resize(size);
//        itemTime->setSizeHint(size);
//        messageTime->setText(curMsgTime, curMsgTime, size, QNChatMessage::User_Time);
//        ui->listWidget->setItemWidget(itemTime, messageTime);
//    }
//}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);


//    ui->textEdit->resize(this->width() - 20, ui->widget->height() - 20);
//    ui->textEdit->move(10, 10);

//    ui->sendBut->move(ui->textEdit->width()+ui->textEdit->x() - ui->sendBut->width() - 10,
//                         ui->textEdit->height()+ui->textEdit->y() - ui->sendBut->height() - 10);


//    for(int i = 0; i < ui->listWidget->count(); i++) {
//        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(ui->listWidget->item(i));
//        QListWidgetItem* item = ui->listWidget->item(i);

//        dealMessage(messageW, item, messageW->text(), messageW->time(), messageW->userType());
//    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //获得部件当前位置
    this->windowPos=this->pos();
    //获得鼠标位置
    this->mousePos=event->globalPos();
    //移动后部件所在的位置
    this->dPos=mousePos-windowPos;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos()-this->dPos);
}

//void MainWindow::on_btn_add_clicked()
//{
//    addFriWin.show();
//}

void MainWindow::sltTcpReply(quint8 type, QJsonValue dataVal)
{
    switch (type) {
    case UserOnLine:
    {
//        UpdateFriendStatus(OnLine, dataVal);
    }
    break;
    case UserOffLine:
    {
//        UpdateFriendStatus(OffLine, dataVal);
    }
    break;
    case UpdateHeadPic:
    {
        // 你的好友更新了头像
        //ParseUpFriendHead(dataVal);
    }
    break;
    case AddFriend:
    {
        parseAddFriendReply(dataVal);
    }
    break;
    case AddGroup:
    {
//        parseAddGroupReply(dataVal);
    }
    break;

    case AddFriendRequist:
    {
        parseAddFriendRequestConfirmed(dataVal);
    }
    break;
    case AddGroupRequist:
    {
//        parseAddGroupRequestConfirmed(dataVal);
    }
    break;

    case CreateGroup:
    {
        //ParseCreateGroupReply(dataVal);
    }
    break;
    case GetMyFriends:
    {
        //ParseGetFriendsReply(dataVal);
    }
    break;
    case GetMyGroups:
    {
        //ParseGetGroupFriendsReply(dataVal);
    }
    break;
    case GetGroupMembers:
    {
//        parseGetGroupMembersReply(dataVal);
    }
    break;
    case RefreshFriends:
    {
        //ParseRefreshFriendsReply(dataVal);
    }
    break;
    case RefreshGroups:
    {
        //ParseRefreshGroupFriendsReply(dataVal);
    }
    break;
    case SendMsg:
    {
//        parseFriendMessageReply(dataVal);//收到私聊消息
    }
    break;
    case SendGroupMsg:
    {
//        parseGroupMessageReply(dataVal);//收到群聊消息
    }
    break;
    case SendFile:
    case SendPicture:
    {
//        parseSendFileReply(dataVal);//收到服务器文件下载通知
    }
    break;
    case MsgReceived:
    {
//        rightBar->msgconfirmed(dataVal);
    }
    break;
    case DeleteFriend:
    {
//        parseDeleteFriendReply(dataVal);
    }
    break;
    case DeleteGroup:
    {
//        parseDeleteGroupReply(dataVal);
    }
    break;
    default:
        break;
    }
}

void MainWindow::sltTcpStatus(quint8)
{

}

void MainWindow::sltAddChat(Cell *cell)
{
    if(cell->type == Cell_FriendChat){
        //切换左栏按钮
        onleftBtnClicked(0);

        //中栏插入聊天格子
        midBar->insertCell(cell);
        midBar->switchToChatList();

        //右栏聊天窗口增加一条消息
        QJsonObject jsonObj;
        jsonObj.insert("type",Notice);
        jsonObj.insert("noticeType",NewFriend);
        jsonObj.insert("id",cell->id);
        jsonObj.insert("msg","你和" + QString::number(cell->id) + "已经成为好友了，开始聊天吧！");

        rightBar->allowSendMsg(cell->id);//允许和此用户聊天
        rightBar->msgReceived(cell,jsonObj);

        //更新联系人列表
        Cell* c = new Cell;
        c->type = Cell_FriendContact;
        c->groupName = "默认分组";
        c->id = cell->id;
        c->iconPath = cell->iconPath;
        c->name = cell->name;
        c->isClicked = false;
        c->status = OnLine;
        midBar->addCellToContact(c);//更新联系人列表
    }else if(cell->type == Cell_GroupChat){
        //切换左栏按钮
        onleftBtnClicked(0);

        Cell* c = midBar->isIDExist(cell->id);
        if(c == nullptr){
            //说明中栏目前没有此聊天格子
            //中栏插入聊天格子
            midBar->insertCell(cell);
            midBar->switchToChatList();

            //右栏聊天窗口增加一条消息
            QJsonObject jsonObj;
            jsonObj.insert("type",Notice);
            jsonObj.insert("noticeType",NewMember);
            jsonObj.insert("id",cell->newUserID);
            jsonObj.insert("msg",cell->msg);

            rightBar->msgReceived(cell,jsonObj);
        }else{
            c->msg = cell->msg;
            c->subTitle = cell->subTitle;

            //刷新聊天窗口的群成员列表
            Cell* newUser = new Cell;
            newUser->type = Cell_FriendChat;
            newUser->id = cell->newUserID;
            newUser->name = cell->newUserName;
            newUser->iconPath = cell->newUserHead;
            newUser->status = OnLine;
            rightBar->addNewUserToGroupList(cell->id,newUser);

            //右栏聊天窗口增加一条消息
            QJsonObject jsonObj;
            jsonObj.insert("type",Notice);
            jsonObj.insert("noticeType",NewMember);
            jsonObj.insert("id",cell->newUserID);
            jsonObj.insert("msg",c->msg);
            rightBar->msgReceived(c,jsonObj);
        }
    }
}

void MainWindow::parseAddFriendReply(QJsonValue dataVal)
{
    //好友接受端

//    if(dataVal.isObject()){
//        QJsonObject json = dataVal.toObject();

//        int id = json.value("id").toInt();//  请求端Id
//        QString head = json.value("head").toString();
//        QString name = json.value("name").toString();

//        msgDlg=new MessageDlg(nullptr,id,name);
//        msgDlg->setTitle(QDateTime::currentDateTime().toString("hh:mm:ss"));
//        msgDlg->setMsg( QString::number(id) + "请求添加好友");

//        msgDlg->show();
//        connect(msgDlg,&MessageDlg::signalAddFriend,m_tcp,&clientSock::sendMsg);
//    }

    if(dataVal.isObject()){
        QJsonObject json = dataVal.toObject();

        int id = json.value("id").toInt();
        QString head = json.value("head").toString();
        QString name = json.value("name").toString();

        Cell *cell = new Cell;
        cell->id = id;
        cell->iconPath = MyApp::m_strHeadPath + head;
        cell->name = name;
        cell->subTitle = QDateTime::currentDateTime().toString("hh:mm:ss");
        cell->msg = QString::number(id) + "请求添加好友";
        cell->type = Cell_AddFriend;

        midBar->insertCell(cell);
        midBar->switchToChatList();
    }
}

void MainWindow::parseAddGroupRequestConfirmed(const QJsonValue &dataVal)
{
    if(dataVal.isObject()){
        QJsonObject json = dataVal.toObject();
        int id = json.value("id").toInt();
        QString name = json.value("name").toString();
        QString head = json.value("head").toString();
        int adminID = json.value("adminID").toInt();

        //更新本地数据库
        QSqlQuery query;
        query.prepare("INSERT INTO MyGroup (id, name, admin, head, tag, lastMsg, lastTime) "
                      "VALUES (?, ?, ?, ?, ?, ?, ?);");
        query.bindValue(0, id);
        query.bindValue(1, name);
        query.bindValue(2, adminID);
//        query.bindValue(3, MyApp::m_strHeadPath + head);
        query.bindValue(4, 0);
        query.bindValue(5, 0);
        query.bindValue(6, 0);

        query.exec();

//        Cell *cell = new Cell;
//        cell->id = id;
//        cell->name = name;
//        cell->iconPath = MyApp::m_strHeadPath + head;
//        cell->type = Cell_GroupChat;
//        cell->status = OnLine;
//        cell->msg = "你已加入该群";
//        cell->subTitle = QDateTime::currentDateTime().toString("hh:mm:ss");

//        midBar->insertCell(cell);
//        midBar->switchToChatList();

//        QJsonObject jsonObj;
//        jsonObj.insert("type",Notice);
//        jsonObj.insert("noticeType",NewMember);
//        jsonObj.insert("group",cell->id);
//        jsonObj.insert("id",MyApp::m_nId);
//        jsonObj.insert("msg",QString("你已经加入该群，") + "开始聊天吧！");

//        rightBar->msgReceived(cell,jsonObj);
//        onBtnClicked(0);

//        Cell* c = new Cell;
//        c->type = Cell_GroupContact;
//        c->groupName = "我的群组";
//        c->id = cell->id;
//        c->name = cell->name;
//        c->iconPath = cell->iconPath;
//        c->isClicked = false;
//        c->status = OnLine;

//        midBar->addCellToContact(c);
    }
}

void MainWindow::parseAddFriendRequestConfirmed(const QJsonValue &dataVal)
{
    if(dataVal.isObject()){
        QJsonObject json = dataVal.toObject();
        int id = json.value("id").toInt();
        QString name = json.value("name").toString();
        QString head = json.value("head").toString();

        //更新本地数据库
        QSqlQuery query;
        query.prepare("INSERT INTO MyFriend (id, name, head, subgroup, tag, lastMsg, lastTime) "
                      "VALUES (?, ?, ?, ?, ?, ?, ?);");
        query.bindValue(0, id);
        query.bindValue(1, name);
        query.bindValue(2, MyApp::m_strHeadPath + head);
        query.bindValue(3, "默认分组");
        query.bindValue(4, 0);
        query.bindValue(5, "");
        query.bindValue(6, "");

        query.exec();

//        //通知服务器，已同意
//        QJsonObject jsonObj;
//        json.insert("userID1",cell->id);
//        json.insert("userID2",MyApp::m_nId);
//        json.insert("time",QDateTime::currentDateTime().toString("yyyy-MM-dd  hh:mm:ss"));
//        emit signalAddFriend(AddFriendRequist,json);
        // 判断我是否已经添加该好友
//        if (!sql_manage::Instance()->isMyFriend(MyApp::m_nId)) {
//               Cell *cell = new Cell;
//               cell->groupName = QString(tr("我的好友"));
//               cell->iconPath  = MyApp::m_strHeadPath + json.value("head").toString();
//               cell->type      = CellType_Child;
//               cell->name     = name;
//               cell->subTitle  = QString("当前用户状态：在线 ");
//               cell->id        = nId;
//               cell->status    = OnLine;

//               ui->frindListWidget->insertQQCell(cell);

//               // 更新至数据库
//               DataBaseMagr::Instance()->AddFriend(cell->id, MyApp::m_nId, cell->name);
//        }

//        // 播放系统提示音
//        myHelper::PlaySound("system");
//        // 询问
//        CMessageBox::Question(this, tr("[%1] 请求加你为好友，是否接受？\n %2").arg(name).arg(strMsg));

        Cell *cell = new Cell;
        cell->id = id;
        cell->name = name;
        cell->iconPath = MyApp::m_strHeadPath + head;
        cell->type = Cell_FriendChat;
        cell->status = OnLine;
        cell->msg = "你和" + QString::number(id) + "已经成为好友了！";
        cell->subTitle = QDateTime::currentDateTime().toString("hh:mm:ss");

//        midBar->insertCell(cell);
//        midBar->switchToChatList();

//        QJsonObject jsonObj;
//        jsonObj.insert("type",Notice);
//        jsonObj.insert("noticeType",NewFriend);
//        jsonObj.insert("id",id);
//        jsonObj.insert("msg","你和" + QString::number(id) + "已经成为好友了，开始聊天吧！");

//        rightBar->allowSendMsg(id);
//        rightBar->msgReceived(cell,jsonObj);
//        onBtnClicked(0);

//        Cell* c = new Cell;
//        c->type = Cell_FriendContact;
//        c->groupName = "默认分组";
//        c->id = cell->id;
//        c->name = cell->name;
//        c->iconPath = cell->iconPath;
//        c->isClicked = false;
//        c->status = OnLine;
//        midBar->addCellToContact(c);
    }
}

void MainWindow::sltFileRecvFinished(quint8, QString, int)
{

}

//void MainWindow::on_btn_min_clicked()
//{
//    //
//    this->hide();
//}


//void MainWindow::on_btn_max_clicked()
//{

//}

void MainWindow::onleftBtnClicked(int page)
//void MainWindow::onleftBtnClicked(QAbstractButton* button)
{
    midBar->MainPageChanged(page);

    if(page == 0){
        rightBar->restorePage();
    }else if(page == 1){
        rightBar->resetPage();
    }else if(page == 2){
        //        leftBar->chatList->restoreBtn();
        //        leftBar->contacts->restoreBtn();
        //        leftBar->settings->onBtnClicked();
        //        rightBar->resetPage();

        qDebug() << "显示设置面板";
//        settings->show();
    }
}

