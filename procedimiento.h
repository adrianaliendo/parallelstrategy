
#ifndef PROCEDIMIENTO_H
#define PROCEDIMIENTO_H

#include <string>

/**
  * class procedimiento
  * Abstract Class ****************************
  * procedimiento does not have any pure virtual methods, but its author
  * defined it as an abstract class, so you should not use it directly.
  * Inherit from it instead and create only objects from the derived classes
  */

class procedimiento{
public:

	// Public attributes
	//  

	int size;
	//int output;
        virtual void runit(int iteracion,int nnodos)=0;
        virtual int getsize()=0;

};

#endif // PROCEDIMIENTO_H
