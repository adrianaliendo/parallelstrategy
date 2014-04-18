
#ifndef EJECUTOR_H
#define EJECUTOR_H

#include <string>
#include <iostream>
using namespace std;


class ejecutor{
public:

	virtual void ejecutar ( void (*funcion)(int, int, int, int*, int), int, int, int, int* ) = 0;

};

#endif // EJECUTOR_H
