#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFileDialog>
#include "math_part.h"
#include "point.h"
#include "draw.h"


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

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/Users/ivanmorozov",
                                                    tr("Txt file(*.obj)"));
    struct Point *points = nullptr;
    struct Polygon *polygons = nullptr;
    int num_polygons = 0;
    QGraphicsScene *holst = new QGraphicsScene();

    ui->lineEdit->setText(fileName);

    math_part(fileName.toLatin1().data(), &points, &polygons, &num_polygons);

    draw(holst, points, polygons, num_polygons);

    ui->graphicsView->setScene(holst);
}
