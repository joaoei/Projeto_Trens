#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "semaforo.h"
#include "trem.h"
#include <thread>
#include <string>

#include <cstdio>       //printf
#include <cstring>      //memset
#include <cstdlib>      //exit
#include <netinet/in.h> //htons
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h> //socket
#include <unistd.h>     //close
#define MAXMSG 1024
#define PORTNUM 4325

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
    //faz conexão e recebe uma msg
    int play = 0;//true, false
    int speed = 0;//0~9
    int down = 0;
    int up = 1; //train number 1~7
    //variáveis do servidor
    struct sockaddr_in endereco;
       int socketId;
       struct sockaddr_in enderecoCliente;
       socklen_t tamanhoEnderecoCliente = sizeof(struct sockaddr);
       int conexaoClienteId;
       char *msg = new char[MAXMSG+1];
       int byteslidos;

       memset(&endereco, 0, sizeof(endereco));
       endereco.sin_family = AF_INET;
                   endereco.sin_port = htons(PORTNUM);
                   endereco.sin_addr.s_addr = inet_addr("127.0.0.1");

                   socketId = socket(AF_INET, SOCK_STREAM, 0);
                   if (socketId == -1)
                   {
                       printf("Falha ao executar socket()\n");
                       exit(EXIT_FAILURE);
                   }
                   int e = 1;
                   if (setsockopt(socketId, SOL_SOCKET, SO_REUSEADDR, &e, sizeof(int)) < 0)
                       printf("setsockopt(SO_REUSEADDR) failed");
                   if ( bind (socketId, (struct sockaddr *)&endereco, sizeof(struct sockaddr)) == -1 )
                   {
                       printf("Falha ao executar bind()\n");
                       exit(EXIT_FAILURE);
                   }
                   if ( listen( socketId, 10 ) == -1)
                   {
                       printf("Falha ao executar listen()\n");
                       exit(EXIT_FAILURE);
                   }
                   //servidor ficar em um loop infinito



                       printf("Servidor: esperando conexões clientes\n");

                       //Servidor fica bloqueado esperando uma conexão do cliente
                       conexaoClienteId = accept( socketId,(struct sockaddr *) &enderecoCliente,&tamanhoEnderecoCliente );

                       printf("Servidor: recebeu conexão de %s\n", inet_ntoa(enderecoCliente.sin_addr));

                       //Verificando erros
                       if ( conexaoClienteId == -1)
                       {
                           printf("Falha ao executar accept()");
                           exit(EXIT_FAILURE);
                       }

                       //receber uma msg do cliente
                       printf("Servidor vai ficar esperando uma mensagem\n");
                       byteslidos = recv(conexaoClienteId,msg,MAXMSG,0);

                       if (byteslidos == -1)
                       {
                           printf("Falha ao executar recv()");
                           exit(EXIT_FAILURE);
                       }
                       else if (byteslidos == 0)
                       {
                           printf("Cliente finalizou a conexão\n");
                           exit(EXIT_SUCCESS);
                       }

                       //Inserir o caracter de fim de mensagem
                       msg[byteslidos] = '\0';

                       printf("Servidor recebeu a seguinte msg do cliente: %s \n",msg);

                       play = ctoi(msg[0]);
                       up = ctoi(msg[1]);
                       down = ctoi(msg[2]);
                       speed = ctoi(msg[3]);



    if (up) {
        int v = ui->spinBox->value() + 1;
        ui->spinBox->setValue(v);
    } else if (down) {
        int v = ui->spinBox->value() - 1;
        ui->spinBox->setValue(v);
    } else if (play) {
        switch(ui->spinBox->value()){
            case 1:

                break;
            case 2:

                break;
            case 3:
                trem1->setEnable(false);
                trem2->setEnable(false);
                trem3->setEnable(false);
                trem4->setEnable(false);
                trem5->setEnable(false);
                trem6->setEnable(false);
                trem7->setEnable(false);
                break;
            case 4:
                trem1->setEnable(true);
                trem2->setEnable(true);
                trem3->setEnable(true);
                trem4->setEnable(true);
                trem5->setEnable(true);
                trem6->setEnable(true);
                trem7->setEnable(true);
                break;
            case 5:
                ////faz conexão e recebe uma msg
                printf("Servidor: esperando conexões clientes\n");

                //Servidor fica bloqueado esperando uma conexão do cliente
                conexaoClienteId = accept( socketId,(struct sockaddr *) &enderecoCliente,&tamanhoEnderecoCliente );

                printf("Servidor: recebeu conexão de %s\n", inet_ntoa(enderecoCliente.sin_addr));

                //Verificando erros
                if ( conexaoClienteId == -1)
                {
                    printf("Falha ao executar accept()");
                    exit(EXIT_FAILURE);
                }

                //receber uma msg do cliente
                printf("Servidor vai ficar esperando uma mensagem\n");
                byteslidos = recv(conexaoClienteId,msg,MAXMSG,0);

                if (byteslidos == -1)
                {
                    printf("Falha ao executar recv()");
                    exit(EXIT_FAILURE);
                }
                else if (byteslidos == 0)
                {
                    printf("Cliente finalizou a conexão\n");
                    exit(EXIT_SUCCESS);
                }

                //Inserir o caracter de fim de mensagem
                msg[byteslidos] = '\0';

                printf("Servidor recebeu a seguinte msg do cliente: %s \n",msg);

                play = ctoi(msg[0]);
                up = ctoi(msg[1]);
                down = ctoi(msg[2]);
                speed = ctoi(msg[3]);

                if (up) {
                    int v = ui->spinBox_2->value() + 1;
                    ui->spinBox_2->setValue(v);
                } else if (down) {
                    int v = ui->spinBox_2->value() - 1;
                    ui->spinBox_2->setValue(v);
                } else if (play) {
                    switch(ui->spinBox_2->value()){
                        case 1:
                            trem1->setEnable(false);
                            break;
                        case 2:
                            trem2->setEnable(false);
                            break;
                        case 3:
                            trem3->setEnable(false);
                            break;
                        case 4:
                            trem4->setEnable(false);
                            break;
                        case 5:
                            trem5->setEnable(false);
                            break;
                        case 6:
                            trem6->setEnable(false);
                            break;
                        case 7:
                            trem7->setEnable(false);
                            break;
                        default:
                            break;
                    }
                }
                break;
            case 6:
                ////faz conexão e recebe uma msg
                printf("Servidor: esperando conexões clientes\n");

                //Servidor fica bloqueado esperando uma conexão do cliente
                conexaoClienteId = accept( socketId,(struct sockaddr *) &enderecoCliente,&tamanhoEnderecoCliente );

                printf("Servidor: recebeu conexão de %s\n", inet_ntoa(enderecoCliente.sin_addr));

                //Verificando erros
                if ( conexaoClienteId == -1)
                {
                    printf("Falha ao executar accept()");
                    exit(EXIT_FAILURE);
                }

                //receber uma msg do cliente
                printf("Servidor vai ficar esperando uma mensagem\n");
                byteslidos = recv(conexaoClienteId,msg,MAXMSG,0);

                if (byteslidos == -1)
                {
                    printf("Falha ao executar recv()");
                    exit(EXIT_FAILURE);
                }
                else if (byteslidos == 0)
                {
                    printf("Cliente finalizou a conexão\n");
                    exit(EXIT_SUCCESS);
                }

                //Inserir o caracter de fim de mensagem
                msg[byteslidos] = '\0';

                printf("Servidor recebeu a seguinte msg do cliente: %s \n",msg);

                play = ctoi(msg[0]);
                up = ctoi(msg[1]);
                down = ctoi(msg[2]);
                speed = ctoi(msg[3]);
                if (up) {
                    int v = ui->spinBox_2->value() + 1;
                    ui->spinBox_2->setValue(v);
                } else if (down) {
                    int v = ui->spinBox_2->value() - 1;
                    ui->spinBox_2->setValue(v);
                } else if (play) {
                    switch(ui->spinBox_2->value()){
                        case 1:
                            trem1->setEnable(true);
                            break;
                        case 2:
                            trem2->setEnable(true);
                            break;
                        case 3:
                            trem3->setEnable(true);
                            break;
                        case 4:
                            trem4->setEnable(true);
                            break;
                        case 5:
                            trem5->setEnable(true);
                            break;
                        case 6:
                            trem6->setEnable(true);
                            break;
                        case 7:
                            trem7->setEnable(true);
                            break;
                        default:
                            break;
                    }
                }
                break;
            case 7:

                break;
            default:
                break;
        }
    }

}

int MainWindow::ctoi(char c){
    switch(c){

        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        default: return 9;
    }

}



