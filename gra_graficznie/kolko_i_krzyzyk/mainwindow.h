#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "computer_game.h"

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

    void on_pushButton_clicked();

    void on_zatwierdz_button_clicked();

private:
    void wyswietl(QString s);
    void print(computer_game& gra);
    void ruchX(computer_game& gra);
    bool x;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
