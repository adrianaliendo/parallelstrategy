
#ifndef CUDAEJECUTOR_H
#define CUDAEJECUTOR_H
#include "ejecutor.h"
#include <iostream>
using namespace std;

#include <string>

class CUDAejecutor : public ejecutor{
public:

	virtual void ejecutar ( void (*funcion)(int, int, int, int*, int), int IA, int KK, int DT, int *TMX1 ){
            cout << "Opcion CUDA" << endl;
            funcion(IA,KK,DT,TMX1,0);//Considerando que la ejecucion solo lo hace el nodo principal
            return;
        }

};

#endif // CUDAEJECUTOR_H
