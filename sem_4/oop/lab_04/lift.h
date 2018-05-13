#ifndef LIFT_H
#define LIFT_H

#include <QObject>
#include <QTextEdit>
#include <QLCDNumber>
#include <QTimer>
#include <QSet>
#include <QQueue>
#include <QLabel>

#include "doors.h"

class lift: public QObject
{
    Q_OBJECT
    enum lift_state //состояния лифта
    {
        going_up,
        going_down,
        opening_state,
        closing_state,
        wait
    };
public:
    lift();

private:
    doors* doors_lift;
};

#endif // LIFT_H
