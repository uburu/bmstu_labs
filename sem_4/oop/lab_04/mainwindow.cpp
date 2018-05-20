#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    lft = new lift(this);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    lft->add_floor(1);
    std::cout << "Лифт вызвали на этаж 1..." << std::endl;
    lft->handler();
}

void MainWindow::on_pushButton_2_clicked()
{
    lft->add_floor(2);
    std::cout << "Лифт вызвали на этаж 2..." << std::endl;
    lft->handler();
}

void MainWindow::on_pushButton_3_clicked()
{
    lft->add_floor(3);
    std::cout << "Лифт вызвали на этаж 3..." << std::endl;
    lft->handler();
}

void MainWindow::on_pushButton_4_clicked()
{
    lft->add_floor(4);
    std::cout << "Лифт вызвали на этаж 4..." << std::endl;
    lft->handler();
}

void MainWindow::on_pushButton_5_clicked()
{
    lft->add_floor(5);
    std::cout << "Лифт вызвали на этаж 5..." << std::endl;
    lft->handler();
}

