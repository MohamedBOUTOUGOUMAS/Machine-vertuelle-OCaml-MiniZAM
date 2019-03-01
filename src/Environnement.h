/*
 * Environnement.h
 *
 *  Created on: 28 févr. 2019
 *      Author: moumouh
 */

#ifndef SRC_ENVIRONNEMENT_H_
#define SRC_ENVIRONNEMENT_H_

#include <iostream>
#include <vector>
#include "MlValue.h"
#include "Ivalue.h"
using namespace std;

namespace minizam{


class Environnement : public IValue{

	vector<IValue *> elements = vector<IValue *>();

public:
	Environnement(){}
	Environnement(vector<IValue *> elements): elements(elements){}
	vector<IValue *> getEnv(){return elements;}

	int getValue(){}

	void extends(IValue * v){elements.push_back(v);}

	~Environnement(){ elements.~vector();}
};

}


#endif /* SRC_ENVIRONNEMENT_H_ */
