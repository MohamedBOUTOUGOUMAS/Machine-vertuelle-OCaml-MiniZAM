/*
 * MlValue.h
 *
 *  Created on: 28 févr. 2019
 *      Author: moumouh
 */

#ifndef SRC_MLVALUE_H_
#define SRC_MLVALUE_H_


namespace minizam{

class MlValue{
	int value;
public:
	MlValue(int v):value(v){}
	int getValue(){return value;}
	void setValue(int v){value = v;}
	MlValue & operator + (MlValue val) {
			return MlValue(this->value + val.getValue());
	}
	MlValue & operator - (MlValue val) {
			return MlValue(this->value - val.getValue());
	}
	MlValue & operator * (MlValue val) {
			return MlValue(this->value * val.getValue());
	}
	MlValue & operator / (MlValue val) {
			return MlValue(this->value / val.getValue());
	}

	MlValue AND(MlValue val){
		return MlValue(this->value && val.getValue());
	}

	MlValue OR(MlValue val){
		return MlValue(this->value || val.getValue());
	}

	MlValue NOT(){
		return MlValue(!this->value);
	}
	MlValue INF(MlValue val){
		return MlValue(this->value < val.getValue());
	}
	MlValue INFOUEGAL(MlValue val){
		return MlValue(this->value <= val.getValue());
	}
	MlValue SUPP(MlValue val){
		return MlValue(this->value > val.getValue());
	}
	MlValue SUPPOUEGAL(MlValue val){
		return MlValue(this->value >= val.getValue());
	}
	MlValue EGAL(MlValue val){
		return MlValue(this->value == val.getValue());
	}
	MlValue DIFF(MlValue val){
		return MlValue(this->value != val.getValue());
	}

	~MlValue(){}
};


}


#endif /* SRC_MLVALUE_H_ */
