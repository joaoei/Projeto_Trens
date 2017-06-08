#include "trem.h"
#include "semaforo.h"

#include <iostream>

Trem::Trem(int id, int x, int y)
{
    this->id = id;
    this->x = x;
    this->y = y;
    velocidade = 50;
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


void Trem::run(Semaforo *sem1, Semaforo *sem2, Semaforo *sem3, Semaforo *sem4, Semaforo *sem5, Semaforo *sem6, Semaforo *sem7, Semaforo *sem8, Semaforo *sem9, Semaforo *sem10)
{
    while(true){
        switch(id){
        case 1:
            if (enable)
            {
                emit updateGUI(id,x,y);
                if (y == 150 && x <460) {
                    x+=10;
                } else if (x == 460 && y < 250) {
                    if (y == 230) {
                        sem7->P();
                        sem5->P();
                    } else if (y == 170) {
                        sem8->V();
                        sem9->V();
                    }
                    y+=10;
                } else if (x > 230 && y == 250) {
                    x-=10;
                } else {
                    if (y == 230) {
                        sem5->V();
                        sem7->V();
                    } else if (y == 170) {
                        sem9->P();
                        sem8->P();
                    }
                    y-=10;
                }
            }
            break;
        case 2:
            if (enable)
            {
                emit updateGUI(id,x,y);
                //Vai para a direita no eixo x
                if (y == 50 && x <120) {
                    if (x == 100) {
                        sem1->P();
                    }
                    x+=10;
                } else if (x == 120 && y < 350) {
                        //desce o eixo y
                        if (y == 160) {
                            sem1->V();
                        } else if (y == 230) {
                            sem2->P();
                        }
                        y+=10;
                } else if (x > 10 && y == 350) {
                    if (x == 100) {
                        sem2->V();
                    }
                    x-=10;
                } else {
                    //sobe o eixo y
                    y-=10;
                }
            }
            break;
        case 3:
            if (enable)
            {
                emit updateGUI(id,x,y);
                if (y == 250 && x <580) {
                    if (x == 560) {
                        sem4->P();
                    } else if (x == 480) {
                        sem6->V();
                        sem5->V();
                    }
                    x+=10;
                } else if (x == 580 && y < 350) {
                    y+=10;
                } else if (x > 350 && y == 350) {
                    if (x == 560) {
                        sem4->V();
                    } else if (x == 370) {
                        sem5->P();
                        sem6->P();
                    }
                    x-=10;
                } else {
                    y-=10;
                }
            }
            break;
        case 4:
            if (enable)
            {
                emit updateGUI(id,x,y);
                if (y == 250 && x <350) {
                    if (x == 140) {
                        sem2->V();
                    } else if (x == 210) {
                        sem6->P();
                        sem7->P();
                    }
                    x+=10;
                } else if (x == 350 && y < 350) {
                    y+=10;
                } else if (x > 120 && y == 350) {
                    if (x == 140) {
                        sem2->P();
                    } else if (x == 330) {
                        sem7->V();
                        sem6->V();
                    }
                    x-=10;
                } else {
                    y-=10;
                }
            }
            break;
        case 5:
            if (enable)
            {
                emit updateGUI(id,x,y);
                if (y == 50 && x <690) {
                    if (x == 600) {
                        sem3->V();
                    }
                    x+=10;
                } else if (x == 690 && y < 350) {
                    y+=10;
                } else if (x > 580 && y == 350) {
                    if (x == 600) {
                        sem4->P();
                    }
                    x-=10;
                } else {
                    if (y == 170) {
                        sem3->P();
                    } else if (y == 230) {
                        sem4->V();
                    }
                    y-=10;
                }
            }
            break;
        case 6:
            if (enable)
            {
                emit updateGUI(id,x,y);
                if (y == 50 && x <580) {
                    if (x == 560) {
                        sem3->P();
                    } else if (x == 370) {
                        sem9->V();
                        sem10->V();
                    }
                    x+=10;
                } else if (x == 580 && y < 150) {
                    y+=10;
                } else if (x > 350 && y == 150) {
                    if (x == 560) {
                       sem3->V();
                    } else if (x == 480) {
                        sem10->P();
                        sem9->P();
                    }
                    x-=10;
                } else {
                    y-=10;
                }
            }
            break;
        case 7:
            if (enable)
            {
                emit updateGUI(id,x,y);
                if (y == 50 && x <350) {
                    if (x == 140) {
                        sem1->V();
                    } else if (x == 330) {
                        sem8->P();
                        sem10->P();
                    } else if (x == 170) {
                        sem10->V();
                        sem8->V();
                    }
                    x+=10;
                } else if (x == 350 && y < 150) {
                    y+=10;
                } else if (x > 120 && y == 150) {
                    if (x == 140) {
                        sem1->P();
                    }
                    x-=10;
                } else {
                    y-=10;
                }
            }
            break;
        default:
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(velocidade));
    }
}

