#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "semaforo.h"
#include "trem.h"

int REGIAO2_7 = 1;
int REGIAO2_4 = 1;
int REGIAO6_7 = 1;
int REGIAO5_6 = 1;
int REGIAO3_4 = 1;
int REGIAO3_5 = 1;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    trem1 = new Trem(1,230,200, ui);
    trem2 = new Trem(2,10,280, ui);
    trem3 = new Trem(3,520,350, ui);
    trem4 = new Trem(4,150,250, ui);
    trem5 = new Trem(5,690,150, ui);
    trem6 = new Trem(6,480,50, ui);
    trem7 = new Trem(7,230,50, ui);

    sem2_7 = new Semaforo(1234,1,IPC_CREAT|0600);
    sem2_4 = new Semaforo(1235,1,IPC_CREAT|0600);
    sem5_6 = new Semaforo(1236,1,IPC_CREAT|0600);
    sem5_3 = new Semaforo(1237,1,IPC_CREAT|0600);
    sem1_3 = new Semaforo(1238,1,IPC_CREAT|0600);
    sem4_3 = new Semaforo(1239,1,IPC_CREAT|0600);
    sem1_4 = new Semaforo(1240,1,IPC_CREAT|0600);
    sem7_1 = new Semaforo(1241,1,IPC_CREAT|0600);
    sem1_6 = new Semaforo(1242,1,IPC_CREAT|0600);
    sem7_6 = new Semaforo(1243,1,IPC_CREAT|0600);

    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem6,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem7,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    trem1->start(sem2_7, sem2_4, sem5_6, sem5_3, sem1_3, sem4_3, sem1_4, sem7_1, sem1_6, sem7_6);
    trem2->start(sem2_7, sem2_4, sem5_6, sem5_3, sem1_3, sem4_3, sem1_4, sem7_1, sem1_6, sem7_6);
    trem3->start(sem2_7, sem2_4, sem5_6, sem5_3, sem1_3, sem4_3, sem1_4, sem7_1, sem1_6, sem7_6);
    trem4->start(sem2_7, sem2_4, sem5_6, sem5_3, sem1_3, sem4_3, sem1_4, sem7_1, sem1_6, sem7_6);
    trem5->start(sem2_7, sem2_4, sem5_6, sem5_3, sem1_3, sem4_3, sem1_4, sem7_1, sem1_6, sem7_6);
    trem6->start(sem2_7, sem2_4, sem5_6, sem5_3, sem1_3, sem4_3, sem1_4, sem7_1, sem1_6, sem7_6);
    trem7->start(sem2_7, sem2_4, sem5_6, sem5_3, sem1_3, sem4_3, sem1_4, sem7_1, sem1_6, sem7_6);

}

MainWindow::~MainWindow()
{
    sem1_3->~Semaforo();
    sem1_4->~Semaforo();
    sem1_6->~Semaforo();
    sem2_4->~Semaforo();
    sem2_7->~Semaforo();
    sem4_3->~Semaforo();
    sem5_3->~Semaforo();
    sem5_6->~Semaforo();
    sem7_1->~Semaforo();
    sem7_6->~Semaforo();
    delete ui;
}

void MainWindow::updateInterface(int id, int x, int y)
{
    switch(id){
        case 1:
            ui->labelTrem01->setGeometry(x,y,20,20);
            break;
        case 2:
            ui->labelTrem01_2->setGeometry(x,y,20,20);
            break;
        case 3:
            ui->labelTrem01_3->setGeometry(x,y,20,20);
            break;
        case 4:
            ui->labelTrem01_4->setGeometry(x,y,20,20);
            break;
        case 5:
            ui->labelTrem01_5->setGeometry(x,y,20,20);
            break;
        case 6:
            ui->labelTrem01_6->setGeometry(x,y,20,20);
            break;
        case 7:
            ui->labelTrem01_7->setGeometry(x,y,20,20);
            break;
        default:
            break;
    }
}



