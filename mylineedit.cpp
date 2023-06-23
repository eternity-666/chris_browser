#include "mylineedit.h"
#include <QDebug>
MyLineEdit::MyLineEdit(QWidget*parent): QLineEdit(parent)
{

}

MyLineEdit::~MyLineEdit(){}


void MyLineEdit::keyReleaseEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return){
        emit this->keyReleaseSignal();
    }

}
