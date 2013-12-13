#include "turinglent.h"

TuringLent::TuringLent()
{
    mLent = "";
    mIterator = 0;
}

void TuringLent::moveRight()
{
    if (mIterator == mLent.size()-1)
        mLent += "#";
    mIterator++;
}

void TuringLent::moveLeft()
{
    if (mIterator == 0)
        mLent = "#" + mLent;
    else
        mIterator--;
}

void TuringLent::write(QString a)
{
    mLent[mIterator] = a[0];
}

QChar TuringLent::read()
{
    return mLent[mIterator];
}

void TuringLent::setLent(QString a)
{
    mLent = a;
}

QString TuringLent::lent()
{
    return mLent;
}

void TuringLent::reset()
{
    mIterator = 0;
}

void TuringLent::clean()
{
    while (true && mLent.size()){
        if (mLent[0] == '#')
            mLent.remove(0,1);
        else
            break;
    }
    while(true && mLent.size()){
        if (mLent[mLent.size()-1] == '#')
            mLent.remove(mLent.size()-1, 1);
        else
            break;
    }
}
