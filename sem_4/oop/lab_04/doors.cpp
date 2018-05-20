#include "doors.h"

const int doors::del = 500;

doors::doors(QObject *parent):QObject(parent)
{
    this->state = close_state;
}


void doors::open()
{
    std::cout << "Двери открываются..." << std::endl;
    delay(del);
    this->state = open_state;
    std::cout << "Двери открыты..." << std::endl;
    emit this->opening_doors();
}


void doors::close()
{
    this->state = close_state;
    std::cout << "Двери закрыты" << std::endl;
    emit this->closing_doors();
}
