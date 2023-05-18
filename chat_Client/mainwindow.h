#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QFileDialog>
#include<QMessageBox>

#include"tcp_manage.h"
#include"page_login.h"
#include "frienddlg.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setMainSocket(clientSock *m_tcp,clientFileSock *m_fileTcp);

private slots:

    void on_sendBut_clicked();

    void on_fileButton_clicked();

    void on_btn_user_clicked();

    void on_btn_add_clicked();

private:
    Ui::MainWindow *ui;
    clientSock *m_tcp;
    clientFileSock *m_fileTcp;
    QFileInfo *fileInfo;
    QString fileName;
    FriendDlg friendlg;
    Page_login login;
};
#endif // MAINWINDOW_H
