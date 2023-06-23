#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QWebEngineHistory>
#include <QMouseEvent>
#include <QList>
#include "gopagedialog.h"
#include "mylineedit.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void webViewLoadStarted();
    void webViewLoadProgress(int progress);
    void urlKeyReleaseSlot();
    void webViewLoadFinished(bool ok);

    void on_goto_button_clicked();

    void on_back_button_clicked();

    void on_forward_button_clicked();

    void on_forward_list_button_clicked();

    void on_back_list_button_clicked();

    void on_refresh_button_clicked();

private:
    Ui::MainWindow *ui;
    QWebEngineView * web_view;
    QList<QString> back;
    QList<QString> forward;
    QString current_url;
};
#endif // MAINWINDOW_H
