#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "turinglent.h"
#include "turingmachine.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    TuringMachine* machine;
    TuringLent* lent;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_newMachine_triggered();

    void on_quit_triggered();

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_addStateButton_clicked();

    void on_deleteStateButton_clicked();

    void on_runButton_clicked();

    void on_saveMachine_triggered();

    void on_openMachine_triggered();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
