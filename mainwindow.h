#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "renderarea.h"
#include "map.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Map *map, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    RenderArea *area;
    //Map *map;

};

#endif // MAINWINDOW_H
