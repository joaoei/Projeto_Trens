#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

class Semaforo{

public:
  //chave, valor inicial, flags
  Semaforo(key_t,int,int);
  ~Semaforo();
  void P(int);
  void V(int);
  int getSemaforoId();
  int getTremId();
  int getContador();

private:
  union semun{int val;} arg;
  int semaforoId;
  int tremId;
  struct sembuf estruturaOperacao;

};

#endif // SEMAFORO_H
