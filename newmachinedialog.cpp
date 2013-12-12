#include "newmachinedialog.h"
#include "ui_newmachinedialog.h"

NewMachineDialog::NewMachineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMachineDialog)
{
    ui->setupUi(this);
}

NewMachineDialog::~NewMachineDialog()
{
    delete ui;
}

void NewMachineDialog::on_buttonBox_accepted()
{
    if (ui->lineEdit->text() != "")
        *l = ui->lineEdit->text();
    close();
}

void NewMachineDialog::on_buttonBox_rejected()
{
    close();
}
