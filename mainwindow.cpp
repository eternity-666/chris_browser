#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gopagedialog.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this->web_view = new QWebEngineView(this);
    this->connect(this->web_view,SIGNAL(loadFinished(bool)),this,SLOT(webViewLoadFinished(bool)));
    this->connect(this->web_view,SIGNAL(loadStarted()),this,SLOT(webViewLoadStarted()));
    this->connect(this->web_view,SIGNAL(loadProgress(int)),this,SLOT(webViewLoadProgress(bool)));
    this->connect(this->ui->url_line_edit,SIGNAL(keyReleaseSignal()),this,SLOT(urlKeyReleaseSlot));


    this->web_view->setGeometry(0,30,this->width(),this->height());
    QString url = "about:blank";
    this->web_view->load(QUrl(url));

    this->web_view->show();

    this->current_url = url;
    this->ui->progress_line_edit->setText("100%");
    this->ui->back_button->setEnabled(false);
     this->ui->forward_button->setEnabled(false);
      this->ui->back_list_button->setEnabled(false);
       this->ui->forward_list_button->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_goto_button_clicked()
{
    QString url = this->ui->url_line_edit->text();

    if(url.left(7)!= "http://"&& url.left(8) !="https://"){
        url = "http://" + url;
    }
    this->back.push_front(this->current_url);
    this->current_url = url;
    this->ui->goto_button->setEnabled(false);
    this->forward.clear();

    this->web_view->load(QUrl(url));
}


void MainWindow::webViewLoadFinished(bool){
    this->ui->goto_button->setEnabled(true);
    this->ui->refresh_button->setText("R");


    QString url = this->web_view->url().toString();
     this->ui->url_line_edit->setText(url);

    if(web_view->history()->canGoBack()){
        this->ui->back_button->setEnabled(true);
        this->ui->back_list_button->setEnabled(true);
    }else{
        this->ui->back_button->setEnabled(false);
         this->ui->back_list_button->setEnabled(false);
    }
    if(web_view->history()->canGoForward()){
        this->ui->forward_button->setEnabled(true);
          this->ui->forward_list_button->setEnabled(true);
    }else{
        this->ui->forward_button->setEnabled(false);
           this->ui->forward_list_button->setEnabled(false);
    }



}


void MainWindow::urlKeyReleaseSlot(){
    this->on_goto_button_clicked();

}

void MainWindow::webViewLoadStarted(){
    this->ui->refresh_button->setText("S");
    this->ui->goto_button->setEnabled(false);

}

void MainWindow::webViewLoadProgress(int progress){
    this->ui->progress_line_edit->setText(QVariant(progress).toString()+"%");
}

void MainWindow::on_back_button_clicked()
{
    if(web_view->history()->canGoBack()){
        this->web_view->back();
           this->forward.push_front(this->current_url);
        if(this->back.length()>0){
               this->current_url = this->back.first();
            this->back.removeFirst();
           }
        if(web_view->history()->canGoBack()){
            this->ui->back_button->setEnabled(true);

        }else{
             this->ui->back_button->setEnabled(false);

        }
        if(web_view->history()->canGoForward()){
             this->ui->forward_button->setEnabled(true);

        }else{
             this->ui->forward_button->setEnabled(false);

        }
    }
}


void MainWindow::on_forward_button_clicked()
{
    if(web_view->history()->canGoForward()){
        this->web_view->forward();
        this->back.push_front(this->current_url);
        this->current_url = this->forward.first();
        this->forward.removeFirst();
        if(web_view->history()->canGoForward()){
             this->ui->forward_button->setEnabled(true);
            this->ui->forward_list_button->setEnabled(true);
        }else{
             this->ui->forward_button->setEnabled(false);
             this->ui->forward_list_button->setEnabled(false);
        }
    }
}


void MainWindow::on_forward_list_button_clicked()
{
    GoPageDialog dlg;
    dlg.list = this->forward;
    dlg.exec();
    int go_count = dlg.go_count;
    for(int i = 0;i<=go_count;++i){
        if(this->web_view->history()->canGoForward()){
            this->web_view->forward();
             this->back.push_front(this->current_url);
            if(this->forward.length() >0){
                 this->current_url = this->forward.first();
                this->forward.removeFirst();
             }
        }
    }
}


void MainWindow::on_back_list_button_clicked()
{
    GoPageDialog dlg;
    dlg.list = this->back;
    dlg.exec();
    int go_count = dlg.go_count;
    for(int i = 0;i<=go_count;++i){
        if(this->web_view->history()->canGoBack()){
            this->web_view->back();
             this->forward.push_front(this->current_url);
            if(this->back.length() >0){
                 this->current_url = this->back.first();
                this->back.removeFirst();
             }
        }
    }
}


void MainWindow::on_refresh_button_clicked()
{
    QString refresh_type = this->ui->refresh_button->text();
    if(refresh_type == "R"){
        this->web_view->reload();
        this->ui->refresh_button->setText("S");
    }else if(refresh_type == "S"){
        this->web_view->stop();

        this->ui->refresh_button->setText("R");
    }
}

