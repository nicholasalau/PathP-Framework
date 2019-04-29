#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Map *map, Path *path, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setThings(Map *map, Path *path)
{
    ui->area->map = map;
    ui->area->path = path;
}
