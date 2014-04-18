
#ifndef OPENMPEJECUTOR_H
#define OPENMPEJECUTOR_H
#include "ejecutor.h"
#include "omp.h"
#include <iostream>
using namespace std;

#include <string>

class OpenMPejecutor : public ejecutor {
public:
    
	virtual void ejecutar ( void (*funcion)(int, int, int, int*, int), int IA, int KK, int DT, int *TMX1 ){
            cout << "Opcion OpenMP" << endl;
            #pragma omp parallel //for
            funcion(IA,KK,DT,TMX1,0);//Considerando que la ejecucion solo lo hace el nodo principal
            return;
        }

};

#endif // OPENMPEJECUTOR_H
