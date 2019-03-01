/*
 * Fermeture.h
 *
 *  Created on: 28 févr. 2019
 *      Author: moumouh
 */

#ifndef SRC_FERMETURE_H_
#define SRC_FERMETURE_H_

#include "Environnement.h"
#include "Ivalue.h"

namespace minizam{

class Fermeture : public IValue{
	int pointeurCode;
	Environnement env;
public:
	Fermeture(int p, Environnement e):pointeurCode(p),env(e){}
	int getPointer(){return pointeurCode;}
	int getValue(){}
	Environnement getEnv(){return env;}
};

}




#endif /* SRC_FERMETURE_H_ */
