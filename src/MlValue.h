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
	int getValue(){return value;}
	void setValue(int v){value = v;}
	MlValue operator + (IValue * val) {
		return MlValue(this->value + val->getValue());
	}
	MlValue operator - (IValue * val) {
			return MlValue(this->value - val->getValue());
	}
	MlValue operator * (IValue * val) {
			return MlValue(this->value * val->getValue());
	}
	MlValue operator / (IValue * val) {
			return MlValue(this->value / val->getValue());
	}

	MlValue AND(IValue * val){
		return MlValue(this->value && val->getValue());
	}

	MlValue OR(IValue * val){
		return MlValue(this->value || val->getValue());
	}

	MlValue NOT(){
		return MlValue(!this->value);
	}
	MlValue INF(IValue * val){
		return MlValue(this->value < val->getValue());
	}
	MlValue INFOUEGAL(IValue * val){
		return MlValue(this->value <= val->getValue());
	}
	MlValue SUPP(IValue * val){
		return MlValue(this->value > val->getValue());
	}
	MlValue SUPPOUEGAL(IValue * val){
		return MlValue(this->value >= val->getValue());
	}
	MlValue EGAL(IValue * val){
		return MlValue(this->value == val->getValue());
	}
	MlValue DIFF(IValue * val){
		return MlValue(this->value != val->getValue());
	}

	~MlValue(){}
};


}


#endif /* SRC_MLVALUE_H_ */
