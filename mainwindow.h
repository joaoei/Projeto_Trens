#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "semaforo.h"
#include <QMainWindow>
#include "trem.h"

#define VERTICAL 2
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateSem();
    void updateTime();

public slots:
    void updateInterface(int,int,int);


private:
    Ui::MainWindow *ui;
    Trem *trem1;
    Trem *trem2;
    Trem *trem3;
    Trem *trem4;
    Trem *trem5;
    Trem *trem6;
    Trem *trem7;
    Semaforo *sem2_7, *sem2_4, *sem5_6, *sem5_3, *sem1_3, *sem4_3, *sem1_4, *sem7_1, *sem1_6, *sem7_6;
};

#endif // MAINWINDOW_H
