
#ifndef CUDAEJECUTOR_H
#define CUDAEJECUTOR_H
#include "ejecutor.h"
#include <iostream>
using namespace std;

#include <string>

class CUDAejecutor : public ejecutor{
public:

	virtual void ejecutar (procedimiento* xejecutar){//void (*funcion)(int, int, int, int*, int, int), int IA, int KK, int DT, int *TMX1 ){
            //La forma en que se ejecuta xejecutar->runit(); deberia estar ajustado a como se quiere que se haga en CUDA
            setProcedimiento(xejecutar);
            
#if CUDA
                //Aqui deberia agregar la version de CUDA

#else
            cout << xejecutar->getsize() << endl;
            for (int i=0;i<xejecutar->getsize();i++){
                xejecutar->runit(i,1); //El 1 al final debe cambiar
            }     
#endif                     
             return;
        }

};

#endif // CUDAEJECUTOR_H
