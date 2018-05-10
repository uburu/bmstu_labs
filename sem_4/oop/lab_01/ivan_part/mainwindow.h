#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    struct Point *points;
    struct Polygon *polygons;
    int num_polygons = 0;
    int num_points = 0;
    QGraphicsScene *holst;
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

public:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
