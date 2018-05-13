#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ventButton_clicked()
{
    ventState = !ventState; // состояние вентилятора должно быть типа bool (вкл/выкл)
    ui->ventsProgress->setValue(100 * ventState);
}

void MainWindow::on_closeDoorsInLift_clicked()
{
    // взаимодействие с логикой
    ui->doorsProgress->setValue(0);
}

void MainWindow::on_openDoorsInLift_clicked()
{
    // взаимодействие с логикой
    ui->doorsProgress->setValue(100);
}
