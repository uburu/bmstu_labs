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


double scan_field (QLineEdit *obj)
{
    QString input = obj->text();
    return input.toDouble();
}


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
    double dx = scan_field(ui->lineEdit_2); // ui->lineEdit_2->text().toDouble();
    double dy = scan_field(ui->lineEdit_3);
    double dz = scan_field(ui->lineEdit_4);

    move_points(dx, dy, dz, points, num_points+1);

    holst->clear();
    draw(holst, points, polygons, num_polygons);

    ui->graphicsView->setScene(holst);
}

// Трансформация вращения
void MainWindow::on_pushButton_3_clicked()
{
    double x_angle = scan_field(ui->lineEdit_2); // ui->lineEdit_6->text().toDouble();
    double y_angle = scan_field(ui->lineEdit_5);
    double z_angle = scan_field(ui->lineEdit_7);

    rotate(x_angle, y_angle, z_angle, points, num_points);

    holst->clear();
    draw(holst, points, polygons, num_polygons);

    ui->graphicsView->setScene(holst);

}

// Трансформация масштабирования
void MainWindow::on_pushButton_4_clicked()
{
    double x = scan_field(ui->lineEdit_9); // ui->lineEdit_9->text().toDouble();
    double y =scan_field(ui->lineEdit_8);
    double z = scan_field(ui->lineEdit_10);

    scale(x, y, z, points, num_points);

    holst->clear();
    draw(holst, points, polygons, num_polygons);

    ui->graphicsView->setScene(holst);

}
