#ifndef DOORS_H
#define DOORS_H

#include <QObject>
#include <QLabel>
#include <QTimer>


class doors : public QObject
{
    Q_OBJECT
    enum doors_state
    {
        opened_state,
        closed_state,
        opening_state,
        closing_state
    };
private:
    doors_state state; // состояние дверей


public:
    doors();


// работа с переключеним состояния дверей
public slots:
//    void open();    //открыть
//    void close();   //закрыть
//    void start_open();    //начать открывать
//    void start_close();   //начать закрывать

signals:
//    void opening();     //двери открыты
//    void closing();    //двери закрыты

};

#endif // DOORS_H
