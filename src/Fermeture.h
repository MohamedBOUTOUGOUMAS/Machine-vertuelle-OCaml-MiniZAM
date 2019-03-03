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
	IValue * env;
public:
	Fermeture(int p, IValue * e):pointeurCode(p),env(e){}

	Fermeture(Fermeture * f){
		pointeurCode = f->getPointer();
		env = new Environnement(f->getEnvironnement());
	}
	int getPointer(){
		return pointeurCode;
	}
	void setPointer(int p){
		pointeurCode = p;
	}
	void setEnv(IValue * e){

	}
	vector<IValue *> getEnvironnement(){return env->getEnvironnement();}

	double getValue(){
		cout<<"From Fermeture Class : "<<endl;
		return -1;
	}

	void setValue(double v){}

	void extends(IValue * e){}

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


//	~Fermeture(){
//		env->~IValue();
//	}

};

}




#endif /* SRC_FERMETURE_H_ */
