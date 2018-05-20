#include "lift.h"

const int lift::del = 500;

lift::lift(QObject *parent):QObject(parent), floor_array(5)
{
    this->state = wait_state;
    this->max_current_floor = 5;
    this->floor = 1;
    this->max_floor = 5;
    this->min_floor = 1;
    this->current_floor = 1;
    door = new doors(this);
    connect(this, SIGNAL(arrived()), door, SLOT(open()));
    connect(this, SIGNAL(arrived()), this, SLOT(delete_floor()));
    connect(door, SIGNAL(opening_doors()), this, SLOT(wait()));
    connect(this, SIGNAL(closing_doors()), door, SLOT(close()));
    connect(this, SIGNAL(opening_doors()), door, SLOT(open()));
    connect(this, SIGNAL(up()), this, SLOT(go_up())); // сигнал вызывает метод движения лифта вверх объекта лифт
    connect(this, SIGNAL(down()), this, SLOT(go_down())); // сигнал вызывает метод движения лифта вниз объекта лифт
}

void lift::delete_floor()
{
    floor_array.erase(
                std::remove(floor_array.begin(), floor_array.end(), this->max_current_floor),
                floor_array.end()
                );
}

void lift::go_up() // метод движения вверх, порождает событие движения вверх и переводит объект в состояние going_up_state
{
    if(!check_floor())
    {
        this->floor += 1;
        std::cout << "Передвинулся на этаж " << floor << std::endl;
        emit this->up();
    }
    else
        emit this->arrived();
}


void lift::go_down() // метод движения вниз, порождает событие движения вниз и переводит объект в состояние going_down_state
{
    if(!check_floor())
    {
        this->floor -= 1;
        std::cout << "Передвинулся на этаж " << floor << std::endl;
        emit this->down();
    }
    else
        emit this->arrived();
}

void lift::set_state(lift_states status) // метод устанавливает объект лифт в полученное состояние
{
    this->state = status;
}


bool lift::check_floor() // метод проверяет на каком этаже мы находимся и при достижении этажа переводит объект лифт в
                             // состояние ожидания и порождает событие открыть двери
{
    return this->floor == this->current_floor;
}


void lift::handler() // обработчик множества этажей
{
    if(floor_array.empty())
        return;

    this->max_current_floor = *std::max_element(this->floor_array.begin(), this->floor_array.end());

    this->current_floor = this->max_current_floor;
    this->go_to();
}

void lift::go_to()
{
    if(this->floor > this->current_floor)
    {
        open_doors();
        delay(del);
        set_state(going_down_state);
        this->go_down();
    }
    else if(this->floor < this->current_floor)
    {
        open_doors();
        delay(del);
        set_state(going_up_state);
        this->go_up();
    }
    else if(this->floor == this->current_floor)
    {
        open_doors();
    }
}


void lift::add_floor(int floor) // добавляет в множество "этаж"
{
    floor_array.push_back(floor);
}


void lift::wait()
{
    set_state(wait_state);
    std::cout << "Перешел в состояние ожидания..." << std::endl;
    delay(del);
    close_doors();
}

void lift::open_doors()
{
    set_state(opening_doors_state);
    emit this->opening_doors();
}

void lift::close_doors()
{
    set_state(closing_doors_state);
    emit this->closing_doors();
}
