#include "terminal2.h"
#include "ui_terminal2.h"
#include "mainwindow.h"
#include "QMessageBox"
#include "globals.h"


Terminal2::Terminal2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Terminal2)
{
    ui->setupUi(this);
// using OpenMP to hide widgets and connect to database in parallel. No actuall reason to do so, but i need to use it somewhere in my program.
#pragma omp sections
    {
    #pragma omp section
    {ui->lblwelcome->hide();
    ui->brnLogout->hide();}
    #pragma omp section
    {MyDB = QSqlDatabase::addDatabase("QSQLITE");
    MyDB.setDatabaseName(QDir::currentPath()+"/db1.sqlite");
    //checking if database file exists
    QFileInfo CheckFile(QDir::currentPath()+"/db1.sqlite");
    if(CheckFile.isFile())
    {
        if (MyDB.open()){
            ui->lblconnect->setText("Connected");
        }
    }else{
        ui->lblconnect->setText("Not Connected");

    }
        }
    }
}

Terminal2::~Terminal2()
{
    delete ui;
}

void Terminal2::on_brnLogout_clicked()
{
#pragma omp sections
    {
     #pragma omp section
        {ui->btnlogin->show();
        ui->txtLogin->show();}
     #pragma omp section
        {ui->txtPass->show();
        ui->lbllogin->show();}
     #pragma omp section
        {ui->lblpassword->show();
        ui->lblwelcome->hide();}
     #pragma omp section
        {ui->brnLogout->hide();
         ui->bankBox->setCurrentIndex(0);}
    }
}

void Terminal2::on_btnlogin_clicked()
{
    QString Login, Pass;
    Login = ui->txtLogin->text();
    Pass = ui->txtPass->text();
    if (!MyDB.isOpen()){
       qDebug() << "no connection";
        return;
    }
        QSqlQuery qry;
        QSqlDatabase MyDB = QSqlDatabase::database();
       if(qry.exec("SELECT * FROM USER_AUTH WHERE LOGIN =\'" + Login + "\' AND PASSWORD =\'" + Pass + "\'"))
        {if(qry.next())
            {
                userid = qry.value(0).toInt();
                ui->btnlogin->hide();
                ui->txtLogin->hide();
                ui->txtPass->hide();
                ui->lbllogin->hide();
                ui->lblpassword->hide();
                ui->lblwelcome->setText("Welcome, " + Login + "!");
                ui->lblwelcome->show();
                ui->brnLogout->show();
                QMessageBox msga;
                msga.setText("Login successful");
                msga.exec();
            }else{
               QMessageBox msgw;
               msgw.setText("Wrong Login information");
               msgw.exec();
           }
       }

}

void Terminal2::on_btnback_clicked()
{
     hide();
}

void Terminal2::on_btnadd_clicked()
{
    int balance;
      if(ui->txtAct->text().toInt()>0)
      {
          QString ID = QString::number(userid);
           QSqlQuery qryaddmoney;
           QSqlQuery qrycheckmoney;
           if(ui->bankBox->currentIndex()==1)
           {

               if(qryaddmoney.exec("SELECT * FROM Bank1 WHERE ID =\'" + ID + "\'"))
                   if(qryaddmoney.next())

                   {
                       balance = qryaddmoney.value(1).toInt();
                       balance = balance + ui->txtAct->text().toInt();
                       QString sbalance = QString::number(balance);
                       qryaddmoney.exec("UPDATE Bank1 SET CURRENT_BALANCE =\'" + sbalance +"\'WHERE ID =\'" + ID + "\'");
                       qrycheckmoney.exec("SELECT * FROM Bank1 WHERE ID =\'" + ID + "\'");
                       if(qrycheckmoney.next())
                       ui->txtBalance->setText(QString::number(qrycheckmoney.value(1).toInt()));
                   }
                   }else if(ui->bankBox->currentIndex()==2)
           { if(qryaddmoney.exec("SELECT * FROM Bank2 WHERE ID =\'" + ID + "\'"))
                   if(qryaddmoney.next())

                   {
                       balance = qryaddmoney.value(1).toInt();
                       balance = balance + ui->txtAct->text().toInt();
                       QString sbalance = QString::number(balance);
                       qryaddmoney.exec("UPDATE Bank2 SET CURRENT_BALANCE =\'" + sbalance +"\'WHERE ID =\'" + ID + "\'");
                       qrycheckmoney.exec("SELECT * FROM Bank2 WHERE ID =\'" + ID + "\'");
                       if(qrycheckmoney.next())
                       ui->txtBalance->setText(QString::number(qrycheckmoney.value(1).toInt()));
           }
                   }else if(ui->bankBox->currentIndex()==0)
               ui->txtBalance->clear();
      }


}

void Terminal2::on_btnwithdraw_clicked()
{
    int balance;
      if(ui->txtAct->text().toInt()>0)
      {
          QString ID = QString::number(userid);
           QSqlQuery qryaddmoney;
           QSqlQuery qrycheckmoney;
           QMessageBox msgw;
           if(ui->bankBox->currentIndex()==1)
           {

               if(qryaddmoney.exec("SELECT * FROM Bank1 WHERE ID =\'" + ID + "\'"))
                   if(qryaddmoney.next())
                   {
                       balance = qryaddmoney.value(1).toInt();
                       if(balance>=0 && balance>ui->txtAct->text().toInt())
                          // #pragma omp parallel for
                       {
                            balance = balance - ui->txtAct->text().toInt();
                            QString sbalance = QString::number(balance);
                            qryaddmoney.exec("UPDATE Bank1 SET CURRENT_BALANCE =\'" + sbalance +"\'WHERE ID =\'" + ID + "\'");
                            qrycheckmoney.exec("SELECT * FROM Bank1 WHERE ID =\'" + ID + "\'");
                            if(qrycheckmoney.next())
                            ui->txtBalance->setText(QString::number(qrycheckmoney.value(1).toInt()));
                            msgw.setText("Money withdrawn = " + ui->txtAct->text() + "");
                            msgw.exec();
                        }else
                       {
                           msgw.setText("Unable to perform action");
                           msgw.exec();
                       }
                   }
                   }else if(ui->bankBox->currentIndex()==2)
           { if(qryaddmoney.exec("SELECT * FROM Bank2 WHERE ID =\'" + ID + "\'"))
                   if(qryaddmoney.next())

                   {
                       balance = qryaddmoney.value(1).toInt();
                       if(balance>=0 && balance>ui->txtAct->text().toInt())
                       {
                           balance = balance - ui->txtAct->text().toInt();
                           QString sbalance = QString::number(balance);
                           qryaddmoney.exec("UPDATE Bank2 SET CURRENT_BALANCE =\'" + sbalance +"\'WHERE ID =\'" + ID + "\'");
                           qrycheckmoney.exec("SELECT * FROM Bank2 WHERE ID =\'" + ID + "\'");
                           if(qrycheckmoney.next())
                           ui->txtBalance->setText(QString::number(qrycheckmoney.value(1).toInt()));
                           msgw.setText("Money withdrawn = " + ui->txtAct->text() + "");
                           msgw.exec();
                        }else
                       {
                           msgw.setText("Unable to perform action");
                           msgw.exec();
                       }
           }
                   }else if(ui->bankBox->currentIndex()==0)
               ui->txtBalance->clear();
      }
}


void Terminal2::on_bankBox_currentIndexChanged(int index)
{
    QString ID = QString::number(userid);
     QSqlQuery qrybankinfo;
     if(ui->bankBox->currentIndex()==1)
     {

         if(qrybankinfo.exec("SELECT * FROM Bank1 WHERE ID =\'" + ID + "\'"))
             if(qrybankinfo.next())
             {
                 ui->txtBalance->setText(QString::number(qrybankinfo.value(1).toInt()));
             }
             }else if(ui->bankBox->currentIndex()==2)
     { if(qrybankinfo.exec("SELECT * FROM Bank2 WHERE ID =\'" + ID + "\'"))
             if(qrybankinfo.next())
             {
                 ui->txtBalance->setText(QString::number(qrybankinfo.value(1).toInt()));
     }
             }else if(ui->bankBox->currentIndex()==0)
         ui->txtBalance->clear();
}
