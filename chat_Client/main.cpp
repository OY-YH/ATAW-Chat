
//#include"mainwindow.h"
#include <QApplication>
#include"sql_manage.h"
#include "rotatingstackedwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //加载数据库
    sql_manage::Instance()->openUserdb();


    //显示登陆界面
    RotatingStackedWidget launcher;
    launcher.show();
//    MainWindow w;

    return a.exec();
}
