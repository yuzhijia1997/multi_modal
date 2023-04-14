#ifndef MYMENU_H
#define MYMENU_H

#include <QMenu>
#include <QMouseEvent>

class MyMenu : public QMenu
{
    Q_OBJECT
public:
    explicit MyMenu(QWidget *parent = nullptr);
    ~MyMenu();
protected:
    void mouseReleaseEvent(QMouseEvent*) override;
};


#endif // MYMENU_H
