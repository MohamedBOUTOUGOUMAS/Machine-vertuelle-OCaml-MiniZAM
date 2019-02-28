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
using namespace std;

namespace minizam{


class Environnement{
	vector<MlValue> elements = vector<MlValue>();
public:
	Environnement(){}
	vector<MlValue> getEnv(){return elements;}
	void extends(MlValue v){elements.push_back(v);}
	~Environnement(){}
};

}


#endif /* SRC_ENVIRONNEMENT_H_ */
