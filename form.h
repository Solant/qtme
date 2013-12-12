#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "turingmachine.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT
private:
    TuringMachine* tm;

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    void setTuringMachine(TuringMachine* t);
private slots:
    void on_addButton_clicked();

private:
    Ui::Form *ui;
};

#endif // FORM_H
