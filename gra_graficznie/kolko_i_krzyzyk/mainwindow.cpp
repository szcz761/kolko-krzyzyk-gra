#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
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

void MainWindow::wyswietl(QString s)
{

    ui->textBrowser->append(s);
}



void MainWindow::print(computer_game& gra)
{
    char cos [4*gra.get_size()];
    int k=1;
    for (int i = 0; i < gra.get_size(); i++)
    {
        for (int j = 0; j < gra.get_size(); j++)
        {
           k=4*j;
           cos[k]={gra.get_tab()[i][j]};
           cos[k+1]={' '};
           cos[k+2]={' '};
           cos[k+3]={' '};
        }
        cos[k+1]=0;
        wyswietl(cos);
    }
}



void MainWindow::on_pushButton_clicked()
{
    QString s_r=ui->textEdit_rozmiar->toPlainText();
    QString s_w=ui->textEdit_wygrana->toPlainText();
    QString s_p=ui->textEdit_poziom->toPlainText();

    int r = s_r.toInt();
    int w = s_w.toInt();
    int p = s_p.toInt();

    computer_game gra(r,w,p);



   while (!(gra.czywygrany() || gra.czyremis()))
   {
       ui->textBrowser->clear();
       print(gra);
       gra.rusz_sie();
       if (!(gra.czywygrany() || gra.czyremis()))
       {
           ui->textBrowser->clear();
           print(gra);
           ruchX(gra);
       }
   }
   ui->textBrowser->clear();
   print(gra);
   if (gra.czyremis())
       QMessageBox::information(this,"KONIEC GRY","Remis!");
   if (gra.wsp_gry()==2)
       QMessageBox::information(this,"KONIEC GRY","Niestety przegrałes!");
   if (gra.wsp_gry()==-2)
       QMessageBox::information(this,"KONIEC GRY","Brawo wygrałeś!");
}


void MainWindow::ruchX(computer_game& gra)
{

    QEventLoop loop;
    QObject::connect(ui->zatwierdz_button, SIGNAL(clicked()), &loop, SLOT(quit()));
    loop.exec();


    QString s_j=ui->textEdit_X->toPlainText();
    QString s_i=ui->textEdit_Y->toPlainText();

    int j = s_j.toInt();
    int i = s_i.toInt();

    if (i >= gra.get_size() || j >= gra.get_size()) //w razie wyjscia po za zakres tablicy
    {
        ui->label->setText("Złe współrzędne! Podaj inne!");
        ruchX(gra);
        return;
    }
    if (gra.get_tab()[i][j] == '*')
    {
        gra.get_tab()[i][j] = 'X';
        gra.set_ruchy(gra.get_ruchy()+1);
    }
    else
    {
        ui->label->setText( "To pole już zajętę! Podaj inne!");
        ruchX(gra);
        return;
    }
}


void MainWindow::on_zatwierdz_button_clicked()
{

}



