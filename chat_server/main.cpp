#include "mainwindow.h"

#include<database.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 加载数据库
    Database::Instance()->openDb("server.db");

    MainWindow w;
    w.show();

    return a.exec();
}
