#ifndef NEWMACHINEDIALOG_H
#define NEWMACHINEDIALOG_H

#include <QDialog>

namespace Ui {
class NewMachineDialog;
}

class NewMachineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewMachineDialog(QWidget *parent = 0);
    ~NewMachineDialog();
    void setString(QString* s){ l = s; }

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::NewMachineDialog *ui;
    QString *l;
};

#endif // NEWMACHINEDIALOG_H
