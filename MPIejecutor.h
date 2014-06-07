
#ifndef MPIEJECUTOR_H
#define MPIEJECUTOR_H
#include "ejecutor.h"
#include <mpi.h>
#include <iostream>
#include <string>
#include <math.h>
using namespace std;


class MPIejecutor : public ejecutor {
public:

	virtual void ejecutar (procedimiento* xejecutar){//void (*funcion)(int, int, int, int*, int, int), int IA, int KK, int DT, int *TMX1 ){
            setProcedimiento(xejecutar);
            
            int idnode = MPI::COMM_WORLD.Get_rank();
            
            //Esta informacion deberia obtenerla/verificarla del json
            int numtask = MPI::COMM_WORLD.Get_size();    

            //Variables auxiliares
            int div=ceil((float)xejecutar->getsize()/numtask);
            int TMX[div];
            int mod=xejecutar->getsize()%numtask;
            bool flag=false;
            
            if(mod==0) flag=true;
            cout << xejecutar->getsize() << ":" << div << endl;
            if (flag ||  (!flag && idnode!=numtask-1) ){     
                for (int i=0;i<div;i++){
                    xejecutar->runit(i,idnode); //El 1 al final debe cambiar
                }    
            } /*else {  //Necesito recalcular que hacer con la parte que queda pendiente por calcular
                for(int i=0;i<IA-idn*div;i++){ 
                    TMX1[i]=sqrt(KK)*DT*(i+idn*div);
                }  
            } */           
                     
            return;
        }

};

#endif // MPIEJECUTOR_H
