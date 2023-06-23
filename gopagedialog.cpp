#include "gopagedialog.h"
#include "ui_gopagedialog.h"

GoPageDialog::GoPageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GoPageDialog)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowMinMaxButtonsHint,false);
    this->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
    this->go_count = -1;
}

GoPageDialog::~GoPageDialog()
{
    delete ui;
}

void GoPageDialog::showEvent(QShowEvent*){
    this->ui->listWidget->clear();
    for(QString str: this->list){
        this->ui->listWidget->addItem(str);
    }
}

void GoPageDialog::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    this->go_count = this->ui->listWidget->currentRow();
    this->close();
}

