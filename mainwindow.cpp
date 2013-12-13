#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include "form.h"
#include "newmachinedialog.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->addStateButton->setVisible(false);
    ui->runButton->setVisible(false);
    ui->deleteStateButton->setVisible(false);
    machine = NULL;
}

MainWindow::~MainWindow()
{
    if (machine){

        delete machine;
        delete lent;
    }
    delete ui;
}

void MainWindow::on_newMachine_triggered()
{
    NewMachineDialog* d = new NewMachineDialog();
    QString* tmp = new QString("");
    d->setString(tmp);
    d->exec();
    if (tmp->isEmpty())
        return;
    // Don't create new machine if alphabet is empty

    machine = new TuringMachine();
    lent = new TuringLent();
    machine->setAlphabet(*tmp);
    machine->addState();
    machine->loadTable(ui->tableWidget);
    ui->addStateButton->setVisible(true);
    ui->runButton->setVisible(true);
    ui->deleteStateButton->setVisible(true);
    setWindowTitle("Turing Machine Emulator (new)");
    delete tmp;
}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    if (machine->isTableLoading())
        return;
    // itemChanged slot calls even when we redraw table, that we don't need

    Node addingNode;
    addingNode.value = item->text()[0];
    addingNode.action = item->text()[1];
    addingNode.nextState = item->text().mid(3).toInt();
    machine->setNode(item->column(), item->row(), addingNode);
    machine->loadTable(ui->tableWidget);
}

void MainWindow::on_addStateButton_clicked()
{
    machine->addState();
    machine->loadTable(ui->tableWidget);
}

void MainWindow::on_deleteStateButton_clicked()
{
    if (machine->statesNumber() == 1)
        return;

    machine->deleteState();
    machine->loadTable(ui->tableWidget);
}

void MainWindow::on_runButton_clicked()
{
    lent->reset();
    if (ui->inputLineEdit->text() == "")
        lent->setLent("#");
    else
        lent->setLent(ui->inputLineEdit->text());

    int success = machine->exec(lent);
    if (success == -1)
        ui->outputLabel->setText("Конечный результат не может быть получен");
    else{
        lent->clean();
        ui->outputLabel->setText(lent->lent());
    }
}

void MainWindow::on_quit_triggered()
{
    if (machine){
        delete machine;
        delete lent;
    }
    close();
}

void MainWindow::on_saveMachine_triggered()
{
    if (!machine)
        return;

    QString fileName = QFileDialog::getSaveFileName(this, tr("OpenFile"), "", tr("Turing Machine (*.tm)"));
    if (fileName != "")
    {
        if (!fileName.endsWith(".tm"))
            fileName += ".tm";

        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                return;

        QTextStream out (&file);
        out << machine->getAlphabet() << endl;
        out << ui->inputLineEdit->text() << endl;
        out << machine->statesNumber() << endl;
        for (int i = 0; i < machine->statesNumber(); i++)
            for (int i2 = 0; i2 < machine->getAlphabet().size(); i2++){
                Node v = machine->getNode(i+1, machine->getAlphabet()[i2]+"");
                out << v.value << " " << v.action << " " << v.nextState << endl;
            }

        file.close();
        setWindowTitle("Turing Machine Emulator (" + fileName + ")");
    }
}

void MainWindow::on_openMachine_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("OpenFile"), "", tr("Turing Machine (*.tm)"));
    if (fileName != "")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return;

        if (!machine){
            machine = new TuringMachine();
            lent = new TuringLent();
        }else{
            delete machine;
            delete lent;
            machine = new TuringMachine();
            lent = new TuringLent();
        }

        QTextStream  in (&file);
        machine->setAlphabet(in.readLine());
        ui->inputLineEdit->setText(in.readLine());
        int t;
        in >> t;
        for (int i = 0; i < t; i++)
            machine->addState();

        for (int i = 0; i < machine->statesNumber(); i++)
            for (int i2 = 0; i2 < machine->getAlphabet().size(); i2++){
                Node v;
                in >> v.value >> v.action >> v.nextState;
                machine->setNode(i, i2, v);
            }

        machine->loadTable(ui->tableWidget);
        ui->addStateButton->setVisible(true);
        ui->deleteStateButton->setVisible(true);
        ui->runButton->setVisible(true);
        setWindowTitle("Turing Machine Emulator (" + fileName + ")");
        file.close();
    }
}
