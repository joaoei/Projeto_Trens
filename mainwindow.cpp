#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "semaforo.h"
#include "trem.h"
#include <thread>
#include <string>
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
    s = std::thread(&MainWindow::soc, this);
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
    updateSem();
    updateTime();
}

void MainWindow::updateSem() {

    if (sem2_7->getContador() == 0) {
        ui->v_sem1->setStyleSheet("background-color: red;");
        if (sem2_7->getTremId() != 0) {
            std::string s = "Semáforo 1: P() dado por " + std::to_string(sem2_7->getTremId());
            ui->sem1->setText(s.c_str());
        }
    } else {
        ui->v_sem1->setStyleSheet("background-color: green;");
        if (sem2_7->getTremId() != 0) {
            std::string s = "Semáforo 1: V() dado por " + std::to_string(sem2_7->getTremId());
            ui->sem1->setText(s.c_str());
        }

    }

    if (sem2_4->getContador() == 0) {
        ui->v_sem2->setStyleSheet("background-color: red;");
        if (sem2_4->getTremId() != 0) {
            std::string s = "Semáforo 2: P() dado por " + std::to_string(sem2_4->getTremId());
            ui->sem2->setText(s.c_str());
        }
    } else {
        ui->v_sem2->setStyleSheet("background-color: green;");
        if (sem2_4->getTremId() != 0) {
            std::string s = "Semáforo 2: V() dado por " + std::to_string(sem2_4->getTremId());
            ui->sem2->setText(s.c_str());
        }
    }

    if (sem5_6->getContador() == 0) {
        ui->v_sem3->setStyleSheet("background-color: red;");
        if (sem5_6->getTremId() != 0) {
            std::string s = "Semáforo 3: P() dado por " + std::to_string(sem5_6->getTremId());
            ui->sem3->setText(s.c_str());
        }
    } else {
        ui->v_sem3->setStyleSheet("background-color: green;");
        if (sem5_6->getTremId() != 0) {
            std::string s = "Semáforo 3: V() dado por " + std::to_string(sem5_6->getTremId());
            ui->sem3->setText(s.c_str());
        }
    }

    if (sem5_3->getContador() == 0) {
        ui->v_sem4->setStyleSheet("background-color: red;");
        if (sem5_3->getTremId() != 0) {
            std::string s = "Semáforo 4: P() dado por " + std::to_string(sem5_3->getTremId());
            ui->sem4->setText(s.c_str());
        }
    } else {
        ui->v_sem4->setStyleSheet("background-color: green;");
        if (sem5_3->getTremId() != 0) {
            std::string s = "Semáforo 4: V() dado por " + std::to_string(sem5_3->getTremId());
            ui->sem4->setText(s.c_str());
        }
    }

    if (sem1_3->getContador() == 0) {
        ui->v_sem5->setStyleSheet("background-color: red;");
        if (sem1_3->getTremId() != 0) {
            std::string s = "Semáforo 5: P() dado por " + std::to_string(sem1_3->getTremId());
            ui->sem5->setText(s.c_str());
        }
    } else {
        ui->v_sem5->setStyleSheet("background-color: green;");
        if (sem1_3->getTremId() != 0) {
            std::string s = "Semáforo 5: V() dado por " + std::to_string(sem1_3->getTremId());
            ui->sem5->setText(s.c_str());
        }
    }

    if (sem4_3->getContador() == 0) {
        ui->v_sem6->setStyleSheet("background-color: red;");
        if (sem4_3->getTremId() != 0) {
            std::string s = "Semáforo 6: P() dado por " + std::to_string(sem4_3->getTremId());
            ui->sem6->setText(s.c_str());
        }
    } else {
        ui->v_sem6->setStyleSheet("background-color: green;");
        if (sem4_3->getTremId() != 0) {
            std::string s = "Semáforo 5: V() dado por " + std::to_string(sem4_3->getTremId());
            ui->sem6->setText(s.c_str());
        }
    }

    if (sem1_4->getContador() == 0) {
        ui->v_sem7->setStyleSheet("background-color: red;");
        if (sem1_4->getTremId() != 0) {
            std::string s = "Semáforo 7: P() dado por " + std::to_string(sem1_4->getTremId());
            ui->sem7->setText(s.c_str());
        }
    } else {
        ui->v_sem7->setStyleSheet("background-color: green;");
        if (sem1_4->getTremId() != 0) {
            std::string s = "Semáforo 7: V() dado por " + std::to_string(sem1_4->getTremId());
            ui->sem7->setText(s.c_str());
        }
    }

    if (sem7_1->getContador() == 0) {
        ui->v_sem8->setStyleSheet("background-color: red;");
        if (sem7_1->getTremId() != 0) {
            std::string s = "Semáforo 7: P() dado por " + std::to_string(sem7_1->getTremId());
            ui->sem8->setText(s.c_str());
        }
    } else {
        ui->v_sem8->setStyleSheet("background-color: green;");
        if (sem7_1->getTremId() != 0) {
            std::string s = "Semáforo 7: V() dado por " + std::to_string(sem7_1->getTremId());
            ui->sem8->setText(s.c_str());
        }
    }

    if (sem1_6->getContador() == 0) {
        ui->v_sem9->setStyleSheet("background-color: red;");
        if (sem1_6->getTremId() != 0) {
            std::string s = "Semáforo 9: P() dado por " + std::to_string(sem1_6->getTremId());
            ui->sem9->setText(s.c_str());
        }
    } else {
        ui->v_sem9->setStyleSheet("background-color: green;");
        if (sem1_6->getTremId() != 0) {
            std::string s = "Semáforo 9: V() dado por " + std::to_string(sem1_6->getTremId());
            ui->sem9->setText(s.c_str());
        }
    }

    if (sem7_6->getContador() == 0) {
        ui->v_sem10->setStyleSheet("background-color: red;");
        if (sem7_6->getTremId() != 0) {
            std::string s = "Semáforo 10: P() dado por " + std::to_string(sem7_6->getTremId());
            ui->sem10->setText(s.c_str());
        }
    } else {
        ui->v_sem10->setStyleSheet("background-color: green;");
        if (sem7_6->getTremId() != 0) {
            std::string s = "Semáforo 10: V() dado por " + std::to_string(sem7_6->getTremId());
            ui->sem10->setText(s.c_str());
        }
    }
}

void MainWindow::updateTime() {
    std::string s = "Trem 1 - Média:  " + std::to_string(trem1->mean()) + " Desvio padrão: " + std::to_string(trem1->desvio()) + "  Ultima volta: " + std::to_string(trem1->getUltima()) ;
    ui->trem1medias->setText(s.c_str());

    std::string s2 = "Trem 2 - Média:  " + std::to_string(trem2->mean()) + " Desvio padrão: " + std::to_string(trem2->desvio()) + "  Ultima volta: " + std::to_string(trem2->getUltima()) ;
    ui->trem2medias->setText(s2.c_str());

    std::string s3 = "Trem 3 - Média:  " + std::to_string(trem3->mean()) + " Desvio padrão: " + std::to_string(trem3->desvio()) + "  Ultima volta: " + std::to_string(trem3->getUltima()) ;
    ui->trem3medias->setText(s3.c_str());

    std::string s4 = "Trem 4 - Média:  " + std::to_string(trem4->mean()) + " Desvio padrão: " + std::to_string(trem4->desvio()) + "  Ultima volta: " + std::to_string(trem4->getUltima()) ;
    ui->trem4medias->setText(s4.c_str());

    std::string s5 = "Trem 5 - Média:  " + std::to_string(trem5->mean()) + " Desvio padrão: " + std::to_string(trem5->desvio()) + "  Ultima volta: " + std::to_string(trem5->getUltima()) ;
    ui->trem5medias->setText(s5.c_str());

    std::string s6 = "Trem 6 - Média:  " + std::to_string(trem6->mean()) + " Desvio padrão: " + std::to_string(trem6->desvio()) + "  Ultima volta: " + std::to_string(trem6->getUltima()) ;
    ui->trem6medias->setText(s6.c_str());

    std::string s7 = "Trem 7 - Média:  " + std::to_string(trem7->mean()) + " Desvio padrão: " + std::to_string(trem7->desvio()) + "  Ultima volta: " + std::to_string(trem7->getUltima()) ;
    ui->trem7medias->setText(s7.c_str());
}
void MainWindow::soc(){


}



