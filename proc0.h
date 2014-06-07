
#ifndef PROC0_H
#define PROC0_H
#include "procedimiento.h"

#include <string>
#include <iostream>
using namespace std;
class proc0 : public procedimiento{
public:

	int size;
	int output;
	void (*funcion)(int,int);
        virtual void runit(int iteracion,int nnodos){
            funcion(size,output);
        }
        proc0(void (*f)(int,int), int x,int y){
            size=x;
            output=y;
            funcion=f;
        }
        int getsize(){
            return size;
        }
        

};

#endif // PROC0_H
