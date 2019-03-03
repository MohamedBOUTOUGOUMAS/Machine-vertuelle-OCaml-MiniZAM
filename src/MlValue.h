/*
 * MlValue.h
 *
 *  Created on: 28 févr. 2019
 *      Author: moumouh
 */

#ifndef SRC_MLVALUE_H_
#define SRC_MLVALUE_H_

#include "Ivalue.h"
namespace minizam{

class MlValue : public IValue{
	double value = 0;
public:

	MlValue(double v):value(v){}
	MlValue(MlValue * v){
		value = v->getValue();
	}
	double getValue(){return value;}
	void setValue(double v){value = v;}

	int getPointer(){return -1;}
	void setPointer(int p){}
	vector<IValue *> getEnvironnement(){return vector<IValue *>();}
	void setEnv(IValue * e){}


	MlValue operator + (MlValue * val) {
		return MlValue(this->value + val->getValue());
	}
	MlValue operator - (MlValue * val) {
			return MlValue(this->value - val->getValue());
	}
	MlValue operator * (MlValue * val) {
			return MlValue(this->value * val->getValue());
	}
	MlValue operator / (MlValue * val) {
			return MlValue(this->value / val->getValue());
	}

	IValue * AND(IValue * val){
		return new MlValue(this->value && val->getValue());
	}

	IValue * OR(IValue * val){
		return new MlValue(this->value || val->getValue());
	}

	IValue * NOT(){
		return new MlValue(!this->value);
	}
	IValue * INF(IValue * val){
		return new MlValue(this->value < val->getValue());
	}
	IValue * INFOUEGAL(IValue * val){
		return new MlValue(this->value <= val->getValue());
	}
	IValue * SUPP(IValue * val){
		return new MlValue(this->value > val->getValue());
	}
	IValue * SUPPOUEGAL(IValue * val){
		return new MlValue(this->value >= val->getValue());
	}
	IValue * EGAL(IValue * val){
		return new MlValue(this->value == val->getValue());
	}
	IValue * DIFF(IValue * val){
		return new MlValue(this->value != val->getValue());
	}

	void extends(IValue * e){}

	~MlValue(){}
};


}


#endif /* SRC_MLVALUE_H_ */
