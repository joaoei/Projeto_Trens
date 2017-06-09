#ifndef TREM_H
#define TREM_H

#include <QObject>
#include <QTime>
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
    void apontar();//modificar o apontador
    int getUltima();//pega tempo da ultima volta
    float desvio();//desvio padrao
    float mean();//media
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
   int apontador;
   int media[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0};
};

#endif // TREM_H



