#include "turingmachine.h"

TuringMachine::TuringMachine()
{
    states = NULL;
}

TuringMachine::~TuringMachine()
{
    delete states;
}

void TuringMachine::setAlphabet(QString a)
{
    for (int i = 0; i < a.size()-1; i++)
        if (a[i] > a[i+1]){
            QString tmp = a[i] + "";
            a[i] = a[i+1];
            a[i+1] = tmp[0];
            i = -1;
        }

    if(a[0] != '#')
        a = "#" + a;

    mAlphabet = a;
}

void TuringMachine::addState()
{
    State addingState;
    if (!states)
        states = new QList<State>();

    for (int i = 0; i < mAlphabet.size(); i++){
        Node v;
        v.nextState = 0;
        v.action = "S";
        v.value = mAlphabet[i];
        addingState.nodes.push_back(v);
    }

    states->push_back(addingState);
}

QString TuringMachine::getAlphabet()
{
    return mAlphabet;
}

void TuringMachine::loadTable(QTableWidget *widget)
{
    mTableLoading = true;
    widget->clear();
    widget->setRowCount(0);
    widget->setColumnCount(0);
    for (int i = 0; i < states->size(); i++){
        widget->insertColumn(i);
        widget->setHorizontalHeaderItem(i, new QTableWidgetItem("q"+QString::number(i+1)));
    }

    for (int i = 0; i < mAlphabet.size(); i++){
        widget->insertRow(i);
        widget->setVerticalHeaderItem(i, new QTableWidgetItem(mAlphabet[i]+""));  //исправить QCharRef -> QString
    }

    for (int i = 0; i < states->size(); i++){
        for (int i2 = 0; i2 < states->value(i).nodes.size(); i2++){
            widget->setItem(i2,i, new QTableWidgetItem(states->value(i).nodes.value(i2).value + states->value(i).nodes.value(i2).action + "q" + QString::number(states->value(i).nodes.value(i2).nextState)));
        }
    }

    mTableLoading = false;
}

void TuringMachine::setNode(int s, int v, Node n)
{
    State addingState;
    addingState = states->at(s);
    addingState.nodes.replace(v, n);
    states->replace(s, addingState);
}

bool TuringMachine::isTableLoading()
{
    return mTableLoading;
}

void TuringMachine::deleteState()
{
     states->removeLast();
}

int TuringMachine::exec(TuringLent *lent)
{
    int state = 1;
    int iterations = 0;
    while(true){
        QString read = lent->read();
        Node current = getNode(state, read);
        lent->write(current.value);
        if (current.action == "L")
            lent->moveLeft();

        if (current.action == "R")
            lent->moveRight();

        if (current.nextState == 0)
            return 0;
        else
            state = current.nextState;

        if (iterations > 15000)
            return -1;
        iterations++;
    }
}

Node TuringMachine::getNode(int state, QString value)
{
    State s = states->value(state-1);
    int i = 0;
    for (; i < mAlphabet.size(); i++){
        if (mAlphabet[i] == value[0])
            break;
    }

    return s.nodes.value(i);
}

int TuringMachine::statesNumber()
{
    return states->size();
}

bool TuringMachine::isEmpty() //ниработает:(
{
    if (states->isEmpty())
        return true;
    else
        return false;
}
