#include "trem.h"
#include "semaforo.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

QTime timer_1, timer_2, timer_3, timer_4, timer_5, timer_6, timer_7;

Trem::Trem(int id, int x, int y, Ui::MainWindow *ui)
{
    this->id = id;
    this->x = x;
    this->y = y;
    this->ui = ui;
    this->apontador = 0;
    velocidade = 150;
    enable = true;
}

Trem::~Trem()
{
    threadTrem.join();
}

void Trem::setVelocidade(int velocidade)
{
    this->velocidade = velocidade;
}

void Trem::setEnable(bool enable)
{
    this->enable = enable;
}

void Trem::start(Semaforo *sem1, Semaforo *sem2, Semaforo *sem3, Semaforo *sem4, Semaforo *sem5, Semaforo *sem6, Semaforo *sem7, Semaforo *sem8, Semaforo *sem9, Semaforo *sem10)
{
    threadTrem = std::thread(&Trem::run,this, sem1, sem2, sem3, sem4, sem5, sem6, sem7, sem8, sem9, sem10);
}
int Trem::getX()
{
    return this->x;
}

int Trem::getY()
{
    return this->y;
}

float Trem::mean()
{   if ((media[0]==0)) return 0.0;
    int i = 0;
    float m = 0.0;
    while((media[i]!=0) && (i<11)){
        m +=media[i];
        i++;
    }
    return (float)m/(float)i;
}
float Trem::desvio()
{   int i = 0;
    float m = mean();
    if (m==0.0) return 0;
    float dp = 0.0;
    while((media[i]!=0) && (i<11)){
        dp += pow(media[i]-m,2);
        i++;
    }
    return (float)sqrt(dp/(float) i);
}//desvio padrão
void Trem::apontar()
{
    apontador++;
    apontador = apontador%11;
}
int Trem::getUltima(){
   if(apontador==0) return media[10];
   return media[apontador-1];

}

void Trem::run(Semaforo *sem1, Semaforo *sem2, Semaforo *sem3, Semaforo *sem4, Semaforo *sem5, Semaforo *sem6, Semaforo *sem7, Semaforo *sem8, Semaforo *sem9, Semaforo *sem10)
{
    while(true){
        switch(id){
        case 1:
            if (enable)
            {
                if((x==230)&&(y==200)) {
                    timer_1.start();
                }

                emit updateGUI(id,x,y);
                if (y == 150 && x <460) {
                    x+=10;
                } else if (x == 460 && y < 250) {
                    if (y == 230) {
                        sem7->P(1);
                        sem5->P(1);
                    } else if (y == 170) {
                        sem8->V(1);
                        sem9->V(1);
                    }
                    y+=10;
                } else if (x > 230 && y == 250) {
                    x-=10;
                } else {
                    if (y == 230) {
                        sem5->V(1);
                        sem7->V(1);
                    } else if (y == 170) {
                        sem9->P(1);
                        sem8->P(1);
                    }
                    y-=10;
                }
                if((x==230)&&(y==200)){
                    int nMilliseconds = timer_1.elapsed();
                    if(nMilliseconds!=0){
                        media[apontador] = nMilliseconds;
                        apontar();
                    }
                 }
            }
            break;
        case 2:
            if (enable)
            {
                if((x==10)&&(y==280)) {
                    timer_2.start();
                }

                emit updateGUI(id,x,y);
                //Vai para a direita no eixo x
                if (y == 50 && x <120) {
                    if (x == 100) {
                        sem1->P(2);
                    }
                    x+=10;
                } else if (x == 120 && y < 350) {
                        //desce o eixo y
                        if (y == 160) {
                            sem1->V(2);
                        } else if (y == 230) {
                            sem2->P(2);
                        }
                        y+=10;
                } else if (x > 10 && y == 350) {
                    if (x == 100) {
                        sem2->V(2);
                    }
                    x-=10;
                } else {
                    //sobe o eixo y
                    y-=10;
                }
                if((x==10)&&(y==280)){
                    int nMilliseconds = timer_2.elapsed();
                    if(nMilliseconds!=0){
                        media[apontador] = nMilliseconds;
                        apontar();
                    }
                 }
            }
            break;
        case 3:
            if (enable)
            {
                if((x==520)&&(y==350)) {
                    timer_3.start();
                }
                emit updateGUI(id,x,y);
                if (y == 250 && x <580) {
                    if (x == 560) {
                        sem4->P(3);
                    } else if (x == 480) {
                        sem6->V(3);
                        sem5->V(3);
                    }
                    x+=10;
                } else if (x == 580 && y < 350) {
                    y+=10;
                } else if (x > 350 && y == 350) {
                    if (x == 560) {
                        sem4->V(3);
                    } else if (x == 370) {
                        sem5->P(3);
                        sem6->P(3);
                    }
                    x-=10;
                } else {
                    y-=10;
                }
                if((x==520)&&(y==350)){
                    int nMilliseconds = timer_3.elapsed();
                    if(nMilliseconds!=0){
                        media[apontador] = nMilliseconds;
                        apontar();
                    }
                 }
            }
            break;
        case 4:
            if (enable)
            {
                if((x==150)&&(y==250)) {
                    timer_4.start();
                }
                emit updateGUI(id,x,y);
                if (y == 250 && x <350) {
                    if (x == 140) {
                        sem2->V(4);
                    } else if (x == 210) {
                        sem6->P(4);
                        sem7->P(4);
                    }
                    x+=10;
                } else if (x == 350 && y < 350) {
                    y+=10;
                } else if (x > 120 && y == 350) {
                    if (x == 140) {
                        sem2->P(4);
                    } else if (x == 330) {
                        sem7->V(4);
                        sem6->V(4);
                    }
                    x-=10;
                } else {
                    y-=10;
                }
                if((x==150)&&(y==250)){
                    int nMilliseconds = timer_4.elapsed();
                    if(nMilliseconds!=0){
                        media[apontador] = nMilliseconds;
                        apontar();
                    }
                 }
            }
            break;
        case 5:
            if (enable)
            {
                if((x==690)&&(y==150)) {
                    timer_5.start();
                }
                emit updateGUI(id,x,y);
                if (y == 50 && x <690) {
                    if (x == 600) {
                        sem3->V(5);
                    }
                    x+=10;
                } else if (x == 690 && y < 350) {
                    y+=10;
                } else if (x > 580 && y == 350) {
                    if (x == 600) {
                        sem4->P(5);
                    }
                    x-=10;
                } else {
                    if (y == 170) {
                        sem3->P(5);
                    } else if (y == 230) {
                        sem4->V(5);
                    }
                    y-=10;
                }
                if((x==690)&&(y==150)){
                    int nMilliseconds = timer_5.elapsed();
                    if(nMilliseconds!=0){
                        media[apontador] = nMilliseconds;
                        apontar();
                    }
                 }
            }
            break;
        case 6:
            if (enable)
            {
                if((x==480)&&(y==50)) {
                    timer_6.start();
                }
                emit updateGUI(id,x,y);
                if (y == 50 && x <580) {
                    if (x == 560) {
                        sem3->P(6);
                    } else if (x == 370) {
                        sem9->V(6);
                        sem10->V(6);
                    }
                    x+=10;
                } else if (x == 580 && y < 150) {
                    y+=10;
                } else if (x > 350 && y == 150) {
                    if (x == 560) {
                       sem3->V(6);
                    } else if (x == 480) {
                        sem10->P(6);
                        sem9->P(6);
                    }
                    x-=10;
                } else {
                    y-=10;
                }
                if((x==480)&&(y==50)){
                    int nMilliseconds = timer_6.elapsed();
                    if(nMilliseconds!=0){
                        media[apontador] = nMilliseconds;
                        apontar();
                    }
                 }
            }
            break;
        case 7:
            if (enable)
            {
                if((x==230)&&(y==50)) {
                    timer_7.start();
                }

                emit updateGUI(id,x,y);
                if (y == 50 && x <350) {
                    if (x == 140) {
                        sem1->V(7);
                    } else if (x == 330) {
                        sem8->P(7);
                        sem10->P(7);
                    }
                    x+=10;
                } else if (x == 350 && y < 150) {
                    y+=10;
                } else if (x > 120 && y == 150) {
                    if (x == 140) {
                        sem1->P(7);
                    } else if (x == 170) {
                        sem10->V(7);
                        sem8->V(7);
                    }
                    x-=10;
                } else {
                    y-=10;
                }
                if((x==230)&&(y==50)){
                    int nMilliseconds = timer_7.elapsed();
                    if(nMilliseconds!=0){
                        media[apontador] = nMilliseconds;
                        apontar();
                    }
                 }
            }
            break;
        default:
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(velocidade));
    }
}

