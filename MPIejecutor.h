
#ifndef MPIEJECUTOR_H
#define MPIEJECUTOR_H
#include "ejecutor.h"
#include <iostream>
using namespace std;

#include <string>

class MPIejecutor : public ejecutor {
public:

	virtual int ejecutar ( int (*funcion)(int, int) ){
            int x=funcion(3,2);
            cout << "Opcion MPI (" << x << ")" << endl;
            return x;
        }

};

#endif // MPIEJECUTOR_H
