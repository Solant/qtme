#include "form.h"
#include "ui_form.h"
#include <QLabel>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::setTuringMachine(TuringMachine *t)
{
    tm = t;
    //QPushButton* but = new QPushButton("One");
    //ui->gridLayout_2->addWidget(but);
    for (int i = 0; i < tm->getAlphabet().size(); i++){
        QLabel* q = new QLabel(tm->getAlphabet()[i] + "");
        ui->verticalLayout->addWidget(q);
    }
}

void Form::on_addButton_clicked()
{
    //tm->addState();
    //this->setTuringMachine(tm);
    QLabel* l = new QLabel("q1");
    ui->horizontalLayout->addWidget(l);
}
