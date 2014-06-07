
#ifndef OPENMPEJECUTOR_H
#define OPENMPEJECUTOR_H
#include "ejecutor.h"
#include "omp.h"
#include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <string>
using namespace std;

class OpenMPejecutor : public ejecutor {
public:
	virtual void ejecutar (procedimiento* xejecutar){//void (*funcion)(int, int, int, int*, int, int), int IA, int KK, int DT, int *TMX1 ){
            setProcedimiento(xejecutar);
            cout <<xejecutar->getsize() << endl;
            #pragma omp parallel for
            for (int i=0;i<xejecutar->getsize();i++){
                xejecutar->runit(i,1); //El 1 al final debe cambiar
            }    
            return;
        }

};

#endif // OPENMPEJECUTOR_H
