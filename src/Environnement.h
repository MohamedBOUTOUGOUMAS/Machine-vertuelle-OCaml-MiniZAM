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
#include "Ivalue.h"
using namespace std;

namespace minizam{

class Environnement:public IValue {

	vector<IValue *> elements = vector<IValue *>();

public:
	Environnement(){}

	Environnement(vector<IValue *> elements): elements(elements){}

	Environnement(Environnement * e ){
		elements = e->getEnvironnement();
	}
	double getValue(){
		cout<<"From Environnement Class : "<<endl;
		return -1;
	}
	void setValue(double v){}
	int getPointer(){return -1;}
	void setPointer(int p){}
	vector<IValue *> getEnvironnement(){return elements;}
	void setEnv(IValue * e){}
	void extends(IValue * v){elements.push_back(v);}

	IValue* AND(IValue * val){
	}

	IValue* OR(IValue * val){
	}

	IValue* NOT(){
	}
	IValue* INF(IValue * val){
	}
	IValue* INFOUEGAL(IValue * val){
	}
	IValue* SUPP(IValue * val){
	}
	IValue* SUPPOUEGAL(IValue * val){
	}
	IValue* EGAL(IValue * val){
	}
	IValue* DIFF(IValue * val){
	}

//	~Environnement(){
//		elements.~vector();
//	}
};

}


#endif /* SRC_ENVIRONNEMENT_H_ */
