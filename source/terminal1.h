#ifndef TERMINAL1_H
#define TERMINAL1_H

#include <QDialog>
#include <QDebug>
#include <QtSql>
#include <QFileInfo>
#include <omp.h>

namespace Ui {
class Terminal1;
}

class Terminal1 : public QDialog
{
    Q_OBJECT

public:
    explicit Terminal1(QWidget *parent = 0);
    ~Terminal1();

private slots:
    void on_btnback_clicked();

    void on_btnlogin_clicked();

    void on_brnLogout_clicked();

    void on_btnadd_clicked();

    void on_bankBox_currentIndexChanged(int index);

    void on_btnwithdraw_clicked();

private:
    Ui::Terminal1 *ui;
    QSqlDatabase MyDB;
};


#endif // TERMINAL1_H
