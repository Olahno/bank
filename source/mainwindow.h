#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <omp.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnterminal1_clicked();

    void on_btnexit_clicked();

    void on_btnterminal2_clicked();

private:
    Ui::MainWindow *ui;
 };

#endif // MAINWINDOW_H
