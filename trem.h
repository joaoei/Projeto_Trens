#ifndef TREM_H
#define TREM_H

#include <QObject>
#include <thread>
#include <chrono>
#include "semaforo.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
using namespace std;

class Trem : public QObject
{
    Q_OBJECT
public:
    Trem(int,int,int, Ui::MainWindow*);
    ~Trem();
    void start(Semaforo *sem1, Semaforo *sem2, Semaforo *sem3, Semaforo *sem4, Semaforo *sem5, Semaforo *sem6, Semaforo *sem7, Semaforo *sem8, Semaforo *sem9, Semaforo *sem10);
    void run(Semaforo *sem1, Semaforo *sem2, Semaforo *sem3, Semaforo *sem4, Semaforo *sem5, Semaforo *sem6, Semaforo *sem7, Semaforo *sem8, Semaforo *sem9, Semaforo *sem10);
    void setVelocidade(int);
    void setEnable(bool);
    int getX();
    int getY();

signals:
    void updateGUI(int,int,int);

private:
   std::thread threadTrem;
   Ui::MainWindow *ui;
   int id;
   int x;
   int y;
   int velocidade;
   bool enable;
};

#endif // TREM_H



