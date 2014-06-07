/* 
 * File:   main.cpp
 * Author: aliendo
 *
 * Created on 9 de abril de 2014, 06:31 PM
 */

#include <cstdlib>
#include <iostream>
#include <string.h>
#include <mpi.h>
#include <math.h>
#include "omp.h"
#include "ejecucion.h"
#include "ejecutor.h"
#include "CUDAejecutor.h"
#include "MPIejecutor.h"
#include "OpenMPejecutor.h"
#include "procedimiento.h"
#include "proc0.h"
#include "proc1.h"

using namespace std;

void suma(int IA, int KK, int DT, int idn, int numt, int *TMX1){
    int div=ceil((float)IA/numt);
    int mod=IA%numt;
    bool flag;

    if(mod==0) flag=true;
    else flag=false;

    if (flag ||  (!flag && idn!=numt-1) ){     
        for (int i=0;i<div;i++){
             TMX1[i]=sqrt(KK)*DT*(i+idn*IA); 
        }    
    } else {
        for(int i=0;i<IA-idn*div;i++){ 
            TMX1[i]=sqrt(KK)*DT*(i+idn*div);
        }  
    }
    return;
}

void sumaf(int IA, int KK, int DT, int i, int numt, int *TMX1){
    TMX1[i]=sqrt(KK)*DT*(i+numt*IA); 
    return;
}

void sumagpu(int IA, int KK, int DT, int idn, int numt, int *TMX1){
//#if CUDA
    //Aqui deberia agregar la version de CUDA

//#else
    for (int i=0;i<IA;i++){
         TMX1[i]=sqrt(KK)*DT*i; 
    }    
//#endif
    return;
}


/*En este punto es donde se debe tomar la decision sobre que estrategia se debe 
 * usar dependiendo de la arquitectura disponible, ya que es en este nivel donde
 * se debe setear la estrategia
*/
int main(int argc, char** argv) {
    //Se leen los argumentos de entrada
    
    //Para seleccionar/indicar la estrategia a usar 
    char op='n';//Se usa esta opcion en caso de que no se indique ninguna opcion
    if (argc>1 && strcmp(argv[1],"-op")==0)
        op=argv[2][0]; 

    
    MPI::Init(argc,argv);
    MPI::COMM_WORLD.Set_errhandler(MPI::ERRORS_THROW_EXCEPTIONS);
    
    try{
        int idnode = MPI::COMM_WORLD.Get_rank();
        //cout << "idnode:" << idnode << endl;

        //Datos asociados al problema        
        int IA=10000;//*1024; //Pendiente con el tamanio 1024*1024 que es muy grande
        int TMX1[IA];
        int KK=5;
        int DT=1;
        double inicio;
        double final;
        int idn=1;//Debo cambiar por el id del nodo que ejecuta
        int numt=1;//Debo cambiar por el numero de nodos que se estan usando
            
        //Defino un conjunto de objetos que me serviran de base para definir la estrategia
        MPIejecutor muestraMPI;
        CUDAejecutor muestraCUDA;
        OpenMPejecutor muestraOpenMP;
        
        //Defino otro conjunto de objetos que me serviran de base para definir las funciones a ser ejecutadas
        proc1 muestraF1(sumaf,IA,KK,DT,TMX1);
        proc1 muestraF3(sumagpu,IA,KK,DT,TMX1);
        proc1 muestraF2(sumaf,IA,KK,DT,TMX1);
                
        inicio=MPI::Wtime();
        ejecucion auxiliar(&muestraOpenMP); //Como por defecto
        switch (op){
            case 'o':   //Esta opcion ejecutara la suma  usando la opcion de OpenMP,
                        //Esta opcion usara la version simple de la suma
                        auxiliar.setEjecutor(&muestraOpenMP); //Lo inicializo con la version para OpenMP
                        auxiliar.Ejecuta(&muestraF2);
                        break;
                        
            case 'c':   //Esta opcion ejecutara la suma  usando la opcion de CUDA,
                        //Esta opcion usara la segunda version de la suma
                        auxiliar.setEjecutor(&muestraCUDA); //Lo inicializo con la version para CUDA
                        auxiliar.Ejecuta(&muestraF3);
                        break;
                        
            case 'n':
            case 'm':
            default:    //Esta opcion ejecutara la suma  usando la opcion de MPI,
                        //Esta opcion usara la primera version de la suma
                        auxiliar.setEjecutor(&muestraMPI); //Lo inicializo con la version para MPI
                        auxiliar.Ejecuta(&muestraF1);
                        break;        
        }
        cout << "TMX1:" << TMX1[IA-1] << ":" << endl;                        
        final=MPI::Wtime();
        if(idnode==0){
            cout << "Ejecutado (" << op << ") en:" << (final - inicio)*1000 << ": ms" << endl;
        }
                
       
    } catch(MPI::Exception e) {//Corresponde al MPI::Init
        cout << "MPI ERROR (Init): " << e.Get_error_code() << " - " << e.Get_error_string() << std::endl;
    }

    try {
        MPI::Finalize();
    } catch (MPI::Exception e) { //Corresponde al MPI::Finalize
        cout << "MPI ERROR (Finalize): " << e.Get_error_code() << " - " << e.Get_error_string() << std::endl;
    }
    
 
    return 0;   
    
}

