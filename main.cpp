/* 
 * File:   main.cpp
 * Author: aliendo
 *
 * Created on 9 de abril de 2014, 06:31 PM
 */

#include <cstdlib>
#include <iostream>
#include <mpi.h>
#include "omp.h"
#include "ejecucion.h"
#include "ejecutor.h"
#include "CUDAejecutor.h"
#include "MPIejecutor.h"
#include "OpenMPejecutor.h"

using namespace std;

void suma(int IA, int KK, int DT, int *TMX1, int idn){
    for (int i=0;i<IA;i++){
         TMX1[i]=KK*DT*(i+idn*IA); 
    }    
    return;
}

void sumagpu(int IA, int KK, int DT, int *TMX1, int idn){
//#if CUDA
    //Aqui deberia agregar la version de CUDA

//#else
    for (int i=0;i<IA;i++){
         TMX1[i]=KK*DT*i; 
    }    
//#endif
    return;
}


/*En este punto es donde se debe tomar la decision sobre que estrategia se debe 
 * usar dependiendo de la arquitectura disponible, ya que es en este nivel donde
 * se debe setear la estrategia
*/
int main(int argc, char** argv) {
    MPI::Init(argc,argv);
    MPI::COMM_WORLD.Set_errhandler(MPI::ERRORS_THROW_EXCEPTIONS);
    
    try{
        int idnode = MPI::COMM_WORLD.Get_rank();
        cout << idnode << endl;

        void (*para_determinar_estrategia)(int IA, int KK, int DT, int *TMX1, int idn);
        int IA=1024;//*1024; //Pendiente con el tamanio 1024*1024 que es muy grande
        int TMX1[IA];
        int KK=5;
        int DT=1;
        double inicio;
        double final;
            
        //Defino un conjunto de objetos que me serviran de base para definir la estrategia]
        MPIejecutor muestraMPI;
        CUDAejecutor muestraCUDA;
        OpenMPejecutor muestraOpenMP;


        //Defino el objeto que hara uso de la estrategia seleccionada
        inicio=MPI::Wtime();
        para_determinar_estrategia=suma;
        ejecucion auxiliar(&muestraMPI); //Lo inicializo con la version para MPI
        auxiliar.Ejecuta(para_determinar_estrategia,IA,KK,DT,TMX1);
        final=MPI::Wtime();
        if(idnode==0){
            cout << "Ejecutado (MPI) en:" << (final - inicio)*1000 << ": ms" << endl;
        }
        
        inicio=MPI::Wtime();
        para_determinar_estrategia=suma;
        auxiliar.setEjecutor(&muestraOpenMP);
        auxiliar.Ejecuta(para_determinar_estrategia,IA,KK,DT,TMX1);
        final=MPI::Wtime();
        if(idnode==0){
            cout << "Ejecutado (OpenMP) en:" << (final - inicio)*1000 << ": ms" << endl;
        }

        inicio=MPI::Wtime();
        para_determinar_estrategia=sumagpu;
        auxiliar.setEjecutor(&muestraCUDA); //Si ahora lo quiero ejecutar con otra estrategia, cambio el objeto ejecutor
        auxiliar.Ejecuta(para_determinar_estrategia,IA,KK,DT,TMX1);
        final=MPI::Wtime();
        if(idnode==0){
            cout << "Ejecutado (CUDA) en:" << (final - inicio)*1000 << ": ms" << endl;
        }

    } catch(MPI::Exception e) {
        cout << "MPI ERROR: " << e.Get_error_code() << " - " << e.Get_error_string() << std::endl;
    }

    try {
        MPI::Finalize();
    } catch (MPI::Exception e) {
        cout << "MPI ERROR(F): " << e.Get_error_code() << " - " << e.Get_error_string() << std::endl;
    }
    
 
    return 0;   
    
}

