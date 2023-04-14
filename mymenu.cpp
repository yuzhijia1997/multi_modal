#include "mymenu.h"

MyMenu::MyMenu(QWidget *parent):
    QMenu(parent)
{

}

MyMenu::~MyMenu()
{
}

void MyMenu::mouseReleaseEvent(QMouseEvent *e)
{
    QAction *action = this->actionAt(e->position().toPoint());
    if(action)
    {
        action->activate(QAction::Trigger);
    }
    else
    {
        QMenu::mouseReleaseEvent(e);
    }
}
