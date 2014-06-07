
#ifndef PROC1_H
#define PROC1_H
#include "procedimiento.h"
#include <string>
#include <iostream>
using namespace std;
class proc1 : public procedimiento {
public:
    	int size;
	int input2;
	int input3;
	int *output;
	void (*funcion)(int,int,int,int,int,int*); 
        virtual void runit(int iteracion,int nnodos){
            funcion(size,input2,input3,iteracion,nnodos,output);           
        }
        proc1(void (*f)(int,int,int,int,int,int*), int a,int b,int c,int* g){
            size=a;
            input2=b;
            input3=c;
            output=g;
            funcion=f;
        }        
        int getsize(){
            return size;
        }
};

#endif // PROC1_H
