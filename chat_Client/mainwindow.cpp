#include "mainwindow.h"
#include "type.h"
#include "ui_mainwindow.h"
#include"chatlist.h"
#include<QFileInfo>
#include<QDateTime>
#include <QJsonValue>
#include"frienddlg.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileInfo=nullptr;
    login.show();
    connect(&login,&Page_login::sendLoginSuccess,this,[=](){
        this->show();
    });


    //聊天信息列表
    chatList *list1=new chatList();
    QListWidgetItem *item1=new QListWidgetItem();
    item1->setSizeHint(QSize(320,60));
    ui->listWidget->addItem(item1);
    ui->listWidget->setItemWidget(item1,list1);
    connect(&login,&Page_login::sendSokets,this,[=](clientSock *sock,clientFileSock *filesock){

        setMainSocket(sock,filesock);

         QDateTime time=QDateTime::currentDateTime();
        connect(m_tcp,&clientSock::recvFormServre,this,[=](QString data){
            qDebug()<<"data";
            QString showData=data+"\t"+time.toString("yyyy-MM-dd hh:mm:ss");
            ui->textBrowser->append(showData);

        });

        connect(m_fileTcp,&clientFileSock::sendFileSucess,[=]()
                {

                    ui->textEdit->clear();
                });
        connect(m_fileTcp,&clientFileSock::sucessRecvfile,[=](QString data){
            QDateTime time=QDateTime::currentDateTime();

            QString showData=data+"\t"+time.toString("yyyy-MM-dd hh:mm:ss");
            ui->textBrowser->append(showData);

        });
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setMainSocket(clientSock *m_tcp, clientFileSock *m_fileTcp)
{

        this->m_tcp=m_tcp;
        this->m_fileTcp=m_fileTcp;
        qDebug()<<this->m_tcp<<this->m_fileTcp;
}


void MainWindow::on_sendBut_clicked()
{
   QString msg= ui->textEdit->toPlainText();
   QJsonValue data=msg;
   if(msg.isEmpty())
   {
    QMessageBox::warning(this,"warning","输入有空");

   }
   else
   {
       //判断是发送文件还是文字

       if(fileInfo!=nullptr)
       {
           qDebug()<<"sendfile";
            m_fileTcp->sendFile(fileName);
            delete fileInfo;
            fileInfo=nullptr;
            QDateTime time=QDateTime::currentDateTime();
            QString showData=fileName+"\t"+time.toString("yyyy-MM-dd hh:mm:ss");
            ui->textBrowser->append(showData);

       }
       else
       {
            qDebug()<<"sendmsg";
            m_tcp->sendMsg(SendGroupMsg,data);
            ui->textEdit->clear();

       }

   }
}


void MainWindow::on_fileButton_clicked()
{

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    fileName=dialog.getOpenFileName(this,"选择要发送文件");
    if(!fileName.isEmpty())
    {
        fileInfo=new QFileInfo(fileName);
        ui->textEdit->setText(fileInfo->fileName());
    }
}




void MainWindow::on_btn_user_clicked()
{
  friendlg.show();

}


void MainWindow::on_btn_add_clicked()
{

}

