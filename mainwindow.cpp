#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Map *map, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    area = ui->area;
    area->map = map;
    //map->setMap();
}


MainWindow::~MainWindow()
{
    delete ui;
}
