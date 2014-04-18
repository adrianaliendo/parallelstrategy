
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

	void Ejecuta ( int (*funcion)(int , int) ){
            m_estrategia->ejecutar(funcion);
        }

};

#endif // EJECUCION_H
