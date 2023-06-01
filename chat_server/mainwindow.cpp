#include "mainwindow.h"
#include "qabstractitemmodel.h"
#include "qlabel.h"
#include "qmessagebox.h"
#include "qstatusbar.h"
#include "qtableview.h"
#include "tcpServer.h"
#include "ui_mainwindow.h"
#include "database.h"
#include "myapp.h"

#include<QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonObject>
#include <QMessageBox>
#include <QModelIndex>

#include<tcpServer.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isFile=false;

//    sockSer=new QTcpServer(this);
//    sockSer->listen(QHostAddress::Any,quint16(8888));
//    connect(sockSer,&QTcpServer::newConnection,this,&MainWindow::newConnect);
//    connect(&timer,&QTimer::timeout,this,[=](){
//        qDebug()<<"开始发送文件";
//        timer.stop();
//        sendfile(curScok);
//    });
//    msgServer=new TcpMsgSever(this);
//    fileServer=new TcpFileSever(this);


//    ui->treeWidget->setColumnCount(1);

    //隐藏表头
    ui->treeWidget->setHeaderHidden(true);

    QStringList l;
    l<<"ATAW Server";
    QTreeWidgetItem *qf=new QTreeWidgetItem(ui->treeWidget,l);
    ui->treeWidget->addTopLevelItem(qf);

    l.clear();
    l<<"用户信息";
    QTreeWidgetItem *q1=new QTreeWidgetItem(qf,l);
    qf->addChild(q1);
    //    ui->treeWidget->setItemWidget(q1,0,ui->tableWidget);

    l.clear();
    l<<"服务配置";
    QTreeWidgetItem *q2=new QTreeWidgetItem(qf,l);
    qf->addChild(q2);

    l.clear();
    l<<"用户管理";
    QTreeWidgetItem *q3=new QTreeWidgetItem(qf,l);
    qf->addChild(q3);

    l.clear();
    l<<"密码修改";
    QTreeWidgetItem *q4=new QTreeWidgetItem(qf,l);
    qf->addChild(q4);

    l.clear();
    l<<"数据备份";
    QTreeWidgetItem *q5=new QTreeWidgetItem(qf,l);
    qf->addChild(q5);

    ui->treeWidget->expandAll();
    ui->stackedWidget->setCurrentIndex(0);

    ui->stackedWidgetMain->setCurrentIndex(0);  //

    m_model = new QStandardItemModel(this); //保存数据

    ui->tableViewUsers->setModel(m_model);  //显示数据

    // 设置几张表格的属性不可编辑
    ui->tableViewUsers->setEditTriggers(QTableView::NoEditTriggers);
    // 设置几张表格的属性选择整行
    ui->tableViewUsers->setSelectionBehavior(QTableView::SelectRows);
    connect(ui->tableViewUsers, SIGNAL(clicked(QModelIndex)), this, SLOT(SltTableClicked(QModelIndex)));

    ui->lineEditBackup->setText(MyApp::m_strBackupPath);

    // 初始化网络
    InitNetwork();

    //tool
    QStatusBar *bar=this->statusBar();
//    QLabel *lb_ip=new QLabel(QString("本机IP：") + myHelper::GetIP());
// 显示系统时间
    QLabel *lb_time=new QLabel(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss ddd"));
    bar->addWidget(lb_time);        //left
//    bar->addPermanentWidget(lb_ip); //right

    m_nTimerId = startTimer(1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readMsg()
{
}

// 初始化网络
void MainWindow::InitNetwork()
{
    msgServer = new TcpMsgServer(this);     //connect
    bool bOk = msgServer->StartListen(60100);
    ui->textBrowser->setText(tr("服务器通知消息:"));
    ui->textBrowser->append(bOk ? tr("消息服务器监听成功,端口: 60100") : tr("消息服务器监听失败"));

    fileServer = new TcpFileServer(this);       //connect
    bOk = fileServer->StartListen(60101);
    ui->textBrowser->append(bOk ? tr("文件服务器监听成功,端口: 60101") : tr("文件服务器监听失败"));

    connect(msgServer, &TcpMsgServer::signalDownloadFile, fileServer, &TcpFileServer::SltClientDownloadFile);
    connect(msgServer, &TcpMsgServer::signalUserStatus, this, &MainWindow::ShowUserStatus);
    connect(fileServer, &TcpFileServer::signalUserStatus, this, &MainWindow::ShowUserStatus);

    systemTrayIcon = new QSystemTrayIcon(this);
    systemTrayIcon->setIcon(QIcon(":/res/images/ic_app.png"));

    //系统托盘(在应用程序图标那显示
    QMenu *m_trayMenu = new QMenu(this);
    m_trayMenu->addAction("显示主面板");
    m_trayMenu->addSeparator();
    m_trayMenu->addAction("退出");

    systemTrayIcon->setContextMenu(m_trayMenu);
    systemTrayIcon->show();

    connect(systemTrayIcon, &QSystemTrayIcon::activated,this, &MainWindow::SltTrayIcoClicked);
    connect(m_trayMenu, &QMenu::triggered, this, &MainWindow::SltTrayIconMenuClicked);
}

//void MainWindow::newConnect()
//{
//        QTcpSocket* sockCln=nullptr;;
//        sockCln=sockSer->nextPendingConnection();
//        QString ip=sockCln->peerAddress().toString();
//        int port=sockCln->peerPort();
//        QString showClint=QString("ip:%1 port:%2").arg(ip).arg(port);
//        ui->textEdit->append(showClint);

//        sockLists.append(sockCln);
//        connect(sockCln,&QTcpSocket::readyRead,[=](){

//                QByteArray readmsg=sockCln->readAll();

//                  qDebug()<<"recv from client"<<readmsg<<sockCln->peerPort();
//                ui->textEdit->append(readmsg);



//        });
//                QString message=readmsg;
//                if(message.section("##",0,0)=="sendfile")
//                {
//                        fileName=message.section("##",1,1);
//                        fileSize=message.section("##",2,2).toUInt();
//                        file.setFileName(fileName);
//                        if(!file.open(QIODevice::WriteOnly))
//                            qDebug()<<"文件打开失败";

//                       isFile=true;
//                       fileport=sockCln->peerPort();
//                }
//                else if(isFile)
//                {
//                    qDebug()<<"开始写文件";

//                    recvSize=0;
//                    int len=file.write(readmsg);
//                    recvSize+=len;
//                    if(recvSize==fileSize)//接受完文件
//                    {
//                        qDebug()<<"接受文件完成";
//                        isFile=false;
//                        file.close();
//                        //发送文件给其他客户端
//                        foreach (QTcpSocket* sock, sockLists) {
//                            if(sock->peerPort()!=fileport)
//                            {
//                                curScok=sock;
//                                sendhead(sock);
//                            }

//                        }
//                    }

//                }
//                else//读取文本信息
//                {
//                    qDebug()<<"发送文本消息";
//                    foreach (QTcpSocket* sock, sockLists) {
//                        QString sendmsg=QString("sendmsg##%1").arg(message);
//                        sock->write(sendmsg.toUtf8());
//                    }


//                }
//            }

//        );




//        connect(sockCln,&QTcpSocket::disconnected,this,&MainWindow::removeSocket);

//}

void MainWindow::removeSocket()
{
    int i=0;
    foreach(QTcpSocket* soc, sockLists)
        {
            if(soc->state() == QTcpSocket::UnconnectedState)
            {
                qDebug()<<soc->peerAddress().toString()<<"closed";
                soc->deleteLater();
                sockLists.removeAt(i); //tcpSockets.removeOne(soc);
            }
            i++;

        }

}

void MainWindow::sendfile(QTcpSocket *&sock)
{
     qDebug()<<"send";
    if(!file.open(QIODevice::ReadOnly))
        qDebug()<<"文件打开失败";
    int len;
    do{

        char buf[4*1024]={0};
        len=0;
        len=file.read(buf,sizeof(buf));
        len=sock->write(buf,len);
        sendSize+=len;
    }while(len>0);
    if(sendSize==fileSize)
    {
        curScok=nullptr;
        file.close();
        sendSize=0;
        qDebug()<<"文件发送成功";
    }

}

void MainWindow::sendhead(QTcpSocket *&sock)
{
    //封装头部信息
    QString head=QString("sendfile##%1##%2").arg(fileName).arg(fileSize);
    sock->write(head.toUtf8());
    timer.start(20);

}

//exit
void MainWindow::on_btn_Exit_clicked()
{
    this->close();
}

//login
void MainWindow::on_btn_Login_clicked()
{
    QString name = ui->lineEditUser->text();
    QString passwd = ui->lineEditPasswd->text();
    //
    QJsonObject jsonObje = Database::Instance()->CheckUserLogin(name,passwd);
    int nId = jsonObje.value("id").toInt();
    int identity = jsonObje.value("identity").toInt();

    if (-1 == nId) {
        QMessageBox::information(this, tr("提示"), tr("用户名或密码错误！"));
        return;
    }

//    MyApp::m_nId = nId;
//    MyApp::m_nIdentyfi = identity;
    //    // 设置权限
    //    SetUserIdentity(identity);

    ui->stackedWidgetMain->setCurrentIndex(1);
}


void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    if(item->text(column)=="用户信息"){
//        qDebug()<<item->text(column);
        ui->stackedWidget->setCurrentWidget(ui->page);
    }
    else if(item->text(column)=="服务配置"){
        ui->stackedWidget->setCurrentWidget(ui->page_2);
    }else if(item->text(column)=="用户管理"){
        ui->stackedWidget->setCurrentWidget(ui->page_3);
    }    else if(item->text(column)=="密码修改"){
        ui->stackedWidget->setCurrentWidget(ui->page_4);
    }    else if(item->text(column)=="数据备份"){
        ui->stackedWidget->setCurrentWidget(ui->page_5);
    }
}

void MainWindow::SltTableClicked(const QModelIndex &index)
{
    qDebug() << index.row();
}

void MainWindow::ShowUserStatus(const QString &text)
{

}

// 托盘菜单
void MainWindow::SltTrayIcoClicked(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:      //单击系统托盘
    {
    }
        break;
    case QSystemTrayIcon::DoubleClick:  //双击系统托盘
    {
        if (!this->isVisible())
            this->show();
    }
        break;
    default:
        break;
    }
}

void MainWindow::SltTrayIconMenuClicked(QAction *action)
{
    if ("退出" == action->text()) {
        msgServer->CloseListen();
        fileServer->CloseListen();
        qApp->quit();
    }
    else if ("显示主面板" == action->text()) {
        this->show();
    }
}
