
#ifndef OPENMPEJECUTOR_H
#define OPENMPEJECUTOR_H
#include "ejecutor.h"
#include <iostream>
using namespace std;

#include <string>

class OpenMPejecutor : public ejecutor {
public:
    
	virtual int ejecutar ( int (*funcion)(int, int) ){
            int x=funcion(3,2);
            cout << "Opcion OpenMP (" << x << ")" << endl;
            return x;
        }

};

#endif // OPENMPEJECUTOR_H
