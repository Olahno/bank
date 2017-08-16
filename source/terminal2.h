#ifndef TERMINAL2_H
#define TERMINAL2_H

#include <QDialog>
#include <QDebug>
#include <QtSql>
#include <QFileInfo>
#include <omp.h>

namespace Ui {
class Terminal2;
}

class Terminal2 : public QDialog
{
    Q_OBJECT

public:
    explicit Terminal2(QWidget *parent = 0);
    ~Terminal2();

private slots:
    void on_brnLogout_clicked();

    void on_btnlogin_clicked();

    void on_btnback_clicked();

    void on_btnadd_clicked();

    void on_btnwithdraw_clicked();

    void on_bankBox_currentIndexChanged(int index);

private:
    Ui::Terminal2 *ui;
     QSqlDatabase MyDB;
};

#endif // TERMINAL2_H
