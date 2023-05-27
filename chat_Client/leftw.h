#ifndef LEFTW_H
#define LEFTW_H

#include <QWidget>
#include <QButtonGroup>

namespace Ui {
class leftw;
}

class leftw : public QWidget
{
    Q_OBJECT

public:
    explicit leftw(QWidget *parent = nullptr);
    ~leftw();

    QButtonGroup *m_btnGroup;
protected:
    // 重写鼠标操作以实现移动窗口
    virtual void mousePressEvent(QMouseEvent *event) override;
private:
    Ui::leftw *ui;
};

#endif // LEFTW_H
