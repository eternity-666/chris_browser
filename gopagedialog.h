#ifndef GOPAGEDIALOG_H
#define GOPAGEDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QWebEngineHistory>
#include <QShowEvent>
#include <QList>

namespace Ui {
class GoPageDialog;
}
#define BACK_TYPE 0
#define FORWARD_TYPE 1
class GoPageDialog : public QDialog
{
    Q_OBJECT

public:
    int type;
    int go_count;
    QList<QString> list;
    explicit GoPageDialog(QWidget *parent = nullptr);
    ~GoPageDialog();
protected:
    void showEvent(QShowEvent*);

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::GoPageDialog *ui;
};

#endif // GOPAGEDIALOG_H
