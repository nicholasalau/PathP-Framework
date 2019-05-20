#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "renderarea.h"
#include "map.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Map *map, Path *path, QWidget *parent = 0);
    ~MainWindow();
    //void setThings(Map *map, Path *path);

private slots:
    void on_runPB_clicked();
    void on_restartPB_clicked();

private:
    Ui::MainWindow *ui;
    RenderArea *area;
};

#endif // MAINWINDOW_H
