
#ifndef EJECUCION_H
#define EJECUCION_H

#include <string>
#include "ejecutor.h"
#include <iostream>
using namespace std;


class ejecucion{
private:
	ejecutor *m_estrategia;

public:

	// Constructors/Destructors
	ejecucion ( ejecutor *estrategia ) : m_estrategia(estrategia){
        
        }

	void setEjecutor ( ejecutor *estrategia ) {//string jsonfilename
            m_estrategia=estrategia;
        }

	/*void Ejecuta ( void (*funcion)(int, int, int, int*, int, int), int IA, int KK, int DT, int *TMX1 ){
            m_estrategia->ejecutar(funcion, IA, KK, DT, TMX1);
        }*/
	void Ejecuta (procedimiento* xejecutar) {
            m_estrategia->ejecutar(xejecutar);
	}        

};

#endif // EJECUCION_H
