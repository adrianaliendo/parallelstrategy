
#ifndef EJECUTOR_H
#define EJECUTOR_H

#include <string>
#include <iostream>
using namespace std;


class ejecutor{
public:

	virtual int ejecutar ( int (*funcion)(int, int) ) = 0;

};

#endif // EJECUTOR_H
