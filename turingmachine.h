#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include <QList>
#include <QString>
#include <QTableWidget>
#include "turinglent.h"

struct Node
{
    QString value;
    QString action;
    int nextState;
};

struct State
{
    QList<Node> nodes;
};

class TuringMachine
{
public:
    TuringMachine();
    ~TuringMachine();
    void addState();
    void deleteState();
    void setAlphabet(QString a);
    QString getAlphabet();
    void loadTable(QTableWidget* widget);
    void setNode(int s, int v, Node n);
    bool isTableLoading();
    int exec(TuringLent* lent);
    Node getNode(int state, QString value);
    bool isEmpty();
    int statesNumber();

private:
    QList<State>* states;
    QString mAlphabet;
    bool mTableLoading;
};

#endif // TURINGMACHINE_H
