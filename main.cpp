/* 
 * File:   main.cpp
 * Author: aliendo
 *
 * Created on 9 de abril de 2014, 06:31 PM
 */

#include <cstdlib>
#include <iostream>
#include "ejecucion.h"
#include "ejecutor.h"
#include "CUDAejecutor.h"
#include "MPIejecutor.h"
#include "OpenMPejecutor.h"

using namespace std;

int suma(int x, int y){
    cout << x << "+" << y << "=" << x+y << endl;
    return x+y;
}

int resta(int x, int y){
    cout << x << "-" << y << "=" << x-y << endl;
    return x-y;
}

int mult(int x, int y){
    cout << x << "*" << y << "=" << x*y << endl;
    return x*y;
}

/*En este punto es donde se debe tomar la decision sobre que estrategia se debe 
 * usar dependiendo de la arquitectura disponible, ya que es en este nivel donde
 * se debe setear la estrategia
*/
int main(int argc, char** argv) {
    int (*para_determinar_estrategia)(int x, int y);
    
    //Defino un conjunto de objetos que me serviran de base para definir la estrategia]
    MPIejecutor muestraMPI;
    CUDAejecutor muestraCUDA;
    OpenMPejecutor muestraOpenMP;
 
    //Defino el objeto que hara uso de la estrategia seleccionada
    para_determinar_estrategia=suma;
    ejecucion prueba(&muestraMPI); //Lo inicializo con la version para MPI
    prueba.Ejecuta(para_determinar_estrategia);//Y se ejecuta
    
    para_determinar_estrategia=resta;
    //prueba.setEjecutor(&muestraCUDA); //Si ahora lo quiero ejecutar con otra estrategia, cambio el objeto ejecutor
    prueba.Ejecuta(para_determinar_estrategia);
    
    para_determinar_estrategia=mult;
    //prueba.setEjecutor(&muestraOpenMP);
    prueba.Ejecuta(para_determinar_estrategia);
 
    return 0;   
    
}

