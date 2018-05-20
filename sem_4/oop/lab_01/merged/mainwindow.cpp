#include <iostream>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math_part.h"
#include "point.h"
#include "draw.h"
#include "multiply.h"
#include "move.h"
#include "rotate.h"
#include "scale.h"

static const int ok = 0;
static const int memory = 1;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    points = nullptr;
    polygons = nullptr;
    holst = new QGraphicsScene();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int error = ok;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/Users/ivanmorozov",
                                                    tr("Txt file(*.obj)"));

    ui->lineEdit->setText(fileName);

    error = math_part(fileName.toLatin1().data(), &points, &num_points, &polygons, &num_polygons);

    if(error == memory)
        std::cout << "Error of memory allocate" << std::endl;
    else
    {
        draw(holst, points, polygons, num_polygons);
        ui->graphicsView->setScene(holst);
    }
}

// Трансформация перемещения
void MainWindow::on_pushButton_2_clicked()
{
    double dx = ui->lineEdit_2->text().toDouble();
    double dy = ui->lineEdit_3->text().toDouble();
    double dz = ui->lineEdit_4->text().toDouble();

    move_points(dx, dy, dz, points, num_points+1);

    holst->clear();
    draw(holst, points, polygons, num_polygons);

    ui->graphicsView->setScene(holst);
}

// Трансформация вращения
void MainWindow::on_pushButton_3_clicked()
{
    double x_angle = ui->lineEdit_6->text().toDouble();
    double y_angle = ui->lineEdit_5->text().toDouble();
    double z_angle = ui->lineEdit_7->text().toDouble();

    rotate(x_angle, y_angle, z_angle, points, num_points);

    holst->clear();
    draw(holst, points, polygons, num_polygons);

    ui->graphicsView->setScene(holst);

}

// Трансформация масштабирования
void MainWindow::on_pushButton_4_clicked()
{
    double x = ui->lineEdit_9->text().toDouble();
    double y = ui->lineEdit_8->text().toDouble();
    double z = ui->lineEdit_10->text().toDouble();

    scale(x, y, z, points, num_points);

    holst->clear();
    draw(holst, points, polygons, num_polygons);

    ui->graphicsView->setScene(holst);

}
