#ifndef TURINGLENT_H
#define TURINGLENT_H

#include <QString>

class TuringLent
{
public:
    TuringLent();
    void write(QString a);
    QChar read();
    void moveLeft();
    void moveRight();
    void setLent(QString a);
    QString lent();
    void reset();
    void clean();

private:
    QString mLent;
    int mIterator;
};

#endif // TURINGLENT_H
