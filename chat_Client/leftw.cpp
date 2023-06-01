#include "leftw.h"
#include "ui_leftw.h"

leftw::leftw(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::leftw)
{
    ui->setupUi(this);

//    QStringList tmp;
//    tmp << ":/res/pic/Chat.png"
//        << ":/Icons/MainWindow/chat2.png"
//        << ":/res/pic/Chat.png";
//    ui->btn_chat = new MyButton(nullptr,tmp,QSize(63,41));
//    qDebug()<<"errorrr1";

//    tmp.clear();
//    tmp << ":/res/pic/\347\224\250\346\210\267.png"
//        << ":/Icons/MainWindow/chat2.png"
//        << ":/res/pic/\347\224\250\346\210\267.png";
//    ui->btn_contact = new MyButton(nullptr,tmp,QSize(63,41));

//    tmp.clear();
//    tmp << ":/res/pic/3.1 \350\256\276\347\275\256.png"
//        << ":/Icons/MainWindow/chat2.png"
//        << ":/res/pic/3.1 \350\256\276\347\275\256.png";
//    ui->btn_settings = new MyButton(nullptr,tmp,QSize(63,41));

    m_btnGroup = new QButtonGroup(this);
    m_btnGroup->setExclusive(true);
    m_btnGroup->addButton(ui->btn_chat, 0);
    m_btnGroup->addButton(ui->btn_contact, 1);
    m_btnGroup->addButton(ui->btn_settings, 2);

    ui->btn_chat->onBtnClicked();//默认选中会话列表按钮

//    QPalette palette;
//    palette.setColor(QPalette::Window, QColor(40, 41, 45));//110, 123, 139
//    setAutoFillBackground(true);  //一定要这句，否则不行
//    setPalette(palette);

//    setFocusPolicy(Qt::StrongFocus);

}

leftw::~leftw()
{
    delete ui;
}

void leftw::mousePressEvent(QMouseEvent *event)
{
#ifdef Q_OS_WIN
        if (ReleaseCapture()){
            QWidget *pWindow = this->window();
            if (pWindow->isTopLevel()){
                SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
            }
        }
        event->ignore();
#endif
}
