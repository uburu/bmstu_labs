#ifndef LIFT_H
#define LIFT_H

#include <QObject>
#include <algorithm>
#include <iostream>

#include "delay.h"
#include "doors.h"

class lift : public QObject
{
    Q_OBJECT
    enum lift_states
    {
        wait_state, // ждущее состояние
        going_up_state, // состояние движение вверх
        going_down_state, // состояние движения вниз
        closing_doors_state, // двери закрыты
        opening_doors_state // двери открыты
    };

public:
    lift(QObject *parent = nullptr);

private:
    lift_states state; // состояние
    int floor; // текущий этаж
    int current_floor; // выбранный этаж
    int max_current_floor;
    int max_floor; // максимальное количество этажей
    int min_floor; // минимальное количество этажей
    std::vector<int> floor_array; // множество этажей
    static const int del;
    void go_to(); // запускает процесс движения лифта на полученный этаж
    doors *door; // двери

public slots:
    void go_up(); // метод движения вверх, порождает событие движения вверх и переводит объект в состояние going_up_state
                  // так же вызывает метод проверки этажа
    void go_down(); // метод движения вниз, порождает событие движения вниз и переводит объект в состояние going_down_state
    void set_state(lift_states status); // метод устанавливает объект лифт в полученное состояние
    bool check_floor(); // метод проверяет на каком этаже мы находимся и при достижении этажа переводит объект лифт в
                        // состояние ожидания и порождает событие открыть двери
    void open_doors();
    void close_doors();
    void wait(); // метод переводит объект лифт в состояние "ждуна")0)(death time 1:03)
    void handler(); // обработчик множества этажей
    void add_floor(int floor); // добавляет в множество "этаж"

private slots:
    void delete_floor();

signals:
    void up(); // событие движения вверх
    void down(); // событие движения вниз
    void opening_doors();
    void closing_doors();
    void arrived(); // событие прибытия лифта на нужный этаж
};

#endif // LIFT_H
