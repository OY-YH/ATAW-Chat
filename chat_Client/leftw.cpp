#include "leftw.h"
#include "ui_leftw.h"

leftw::leftw(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::leftw)
{
    ui->setupUi(this);

    m_btnGroup = new QButtonGroup(this);
    m_btnGroup->setExclusive(true);
    m_btnGroup->addButton(ui->btn_chat, 0);
    m_btnGroup->addButton(ui->btn_contact, 1);
    m_btnGroup->addButton(ui->btn_settings, 2);

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
