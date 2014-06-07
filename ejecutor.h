
#ifndef EJECUTOR_H
#define EJECUTOR_H

#include <string>
#include <iostream>
#include "procedimiento.h"

using namespace std;


class ejecutor{
private:
    procedimiento *_xejecutar;
       
public:

	virtual void ejecutar (procedimiento* xejecutar)=0;

        void setProcedimiento(procedimiento *xejecutar){
            _xejecutar=xejecutar;
            return;
        }
    //virtual void ejecutar ( void (*funcion)(int, int, int, int*, int, int), int, int, int, int* ) = 0;

};

#endif // EJECUTOR_H
