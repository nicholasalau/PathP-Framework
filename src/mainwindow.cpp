#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Map *map, Path *path, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    area = ui->area;
    area->map = map;
    area->path = path;
}


MainWindow::~MainWindow()
{
    delete ui;
}
