
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

	virtual void ejecutar ( void (*funcion)(int, int, int, int*, int), int IA, int KK, int DT, int *TMX1 ){
            cout << "Opcion MPI" << endl;

            int idnode = MPI::COMM_WORLD.Get_rank();
            //cout << idnode << endl;
            int numtask = MPI::COMM_WORLD.Get_size();    
            //cout << numtask << endl;
            
            int div=ceil((float)IA/numtask);
            int TMX[div];
            int mod=IA%numtask;
            bool flag;
            
            if(mod==0) flag=true;
            else flag=false;
            
            
            
            if (flag ||  (!flag && idnode!=numtask-1) ){
                funcion(div,KK,DT,TMX,idnode); 
            } else {
                funcion(div,KK,DT,TMX,idnode);//cambiar
            }
            MPI::COMM_WORLD.Gather(TMX,div,MPI::INT,TMX1,div, MPI::INT,0); 
            
            return;
        }

};

#endif // MPIEJECUTOR_H
