#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "terminal1.h"
#include "terminal2.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnterminal1_clicked()
{
    Terminal1 *term1 = new Terminal1(this);
    term1->show();
}

void MainWindow::on_btnexit_clicked()
{
    close();
}

void MainWindow::on_btnterminal2_clicked()
{
    Terminal2 * term2 = new Terminal2(this);
    term2->show();
}
