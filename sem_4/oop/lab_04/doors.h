#ifndef DOORS_H
#define DOORS_H

#include <QObject>
#include <iostream>

#include "delay.h"

class doors : public QObject
{
    Q_OBJECT
    enum doors_states
    {
        open_state, //  состояние открыта
        close_state // состояние закрыта
    };

public:
    doors(QObject *parent = nullptr);

private:
    doors_states state; // состояние
    static const int del;

public slots:
    void open(); // метод открывает двери и порождает событие откывающиеся двери и переводит объект двери в состояние открыты
    void close(); // метод закрывает двери и порождает событие закрывающихся дверей и переводит объект двери в состояние закрыты

signals:
    void opening_doors(); // событие открывающихся дверей
    void closing_doors(); // событие закрывающихся дверей

};

#endif // DOORS_H
