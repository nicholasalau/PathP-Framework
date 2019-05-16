#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Map *map, Path *path, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->area->map = map;
    ui->area->path = path;

//    https://stackoverflow.com/questions/34969533/qt-catching-signal-of-checkbox-to-do-an-action
}


MainWindow::~MainWindow()
{
    delete ui;
}
//void MainWindow::setThings(Map *map, Path *path)
//{
//    ui->area->map = map;
//    ui->area->path = path;
//}

void MainWindow::on_runPB_clicked()
{
    ui->status->setText("Status: Iniciou.");
    ui->textEdit->clear();

    //    if(ui->astarCB->isChecked())
//    {
//        // Run Astar
//    }

    // Após executar os algoritmos pegar a informacao de tempo de cada e verificar qual o menor
    // Setar entao o txt da box de resultados : ui->resultBox->setText("Algoritmo X : tempo X");


}

void MainWindow::on_restartPB_clicked()
{
    ui->status->setText("Status: Reiniciou.");
    ui->textEdit->setText("Pressione Run.");
    // Limpar algoritmos
    // Clear path
    // area->update()
    //
}
