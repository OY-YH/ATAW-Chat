#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include<QFileDialog>
#include<QMessageBox>
//#include <QListWidgetItem>

#include "leftw.h"
#include "midw/midw.h"
//#include "qabstractbutton.h"
#include "rightw/rightw.h"

#include"tcp_manage.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setMainSocket(clientSock *socket,clientFileSock *filesocket);
    void initUI();
//    void dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage::User_Type type);
//    void dealMessageTime(QString curMsgTime);
protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void signalFind(QJsonObject);

private slots:

    void sltTcpReply(quint8 type, QJsonValue dataVal);
    void sltTcpStatus(quint8);
    void sltAddChat(Cell*);

    void parseAddFriendReply(QJsonValue dataVal);
    void parseAddGroupRequestConfirmed(const QJsonValue &dataVal);
    void parseAddFriendRequestConfirmed(const QJsonValue &dataVal);

    void parseFriendMessageReply(const QJsonValue &dataVal);

    void parseSendFileReply(const QJsonValue &dataVal);

    void sltFileRecvFinished(quint8,QString,int);

//    void on_btn_min_clicked();

//    void on_btn_max_clicked();

    void onleftBtnClicked(int page);
//    void onleftBtnClicked(QAbstractButton* button);

private:
    leftw *leftBar;
    midw *midBar;
    rightw *rightBar;

    //记录鼠标，窗口位置
    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;
    Ui::MainWindow *ui;
    clientSock *m_tcp;
    clientFileSock *m_fileTcp;
    QFileInfo *fileInfo;
    QString fileName;
//    FriendDlg friendlg;
//    Page_login login;
//    AddFriendWin addFriWin;
//    MessageDlg *msgDlg;
};
#endif // MAINWINDOW_H
