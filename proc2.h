
#ifndef PROC2_H
#define PROC2_H
#include "procedimiento.h"

#include <string>
#include <iostream>
using namespace std;
class proc2 : public procedimiento {
public:
//suma(int IA, int KK, int DT, int *TMX1, int idn, int numt)
	int input1;
	int input2;
	int input3;
	int *output;
	void (*funcion)(int,int,int,int,int,int*); 
        virtual void runit(int iteracion,int nnodos){
            funcion(input1,input2,input3,iteracion,nnodos,output);
        }
        proc2(void (*f)(int,int,int,int,int,int*), int a,int b,int c,int e,int g,int* d){
            input1=a;
            input2=b;
            input3=c;
            output=d;        
            funcion=f;
        }        
};

#endif // PROC1_H
