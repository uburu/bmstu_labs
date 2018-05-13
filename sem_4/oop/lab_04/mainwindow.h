#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool ventState = false;

private slots:
    void on_ventButton_clicked();

    void on_closeDoorsInLift_clicked();

    void on_openDoorsInLift_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
