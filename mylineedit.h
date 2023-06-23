#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>


#include <QKeyEvent>


class MyLineEdit : public QLineEdit
{
    Q_OBJECT

public:

    MyLineEdit(QWidget*parent = nullptr);
    ~MyLineEdit();
signals:
    void keyReleaseSignal();

protected:
    void keyReleaseEvent(QKeyEvent *e);
};


#endif // MYLINEEDIT_H
