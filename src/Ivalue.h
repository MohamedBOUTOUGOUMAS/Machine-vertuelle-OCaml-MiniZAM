/*
 * Ivalue.h
 *
 *  Created on: 1 mars 2019
 *      Author: moumouh
 */

#ifndef IVALUE_H_
#define IVALUE_H_
namespace minizam{

	class IValue{
	public:
		virtual double getValue() = 0;
		virtual void setValue(double v) = 0;
		virtual int getPointer() = 0;
		virtual void setPointer(int p) = 0;
		virtual vector<IValue *> getEnvironnement() = 0;
		virtual void setEnv(IValue * e) = 0;
		virtual void extends(IValue * e) = 0;

		virtual IValue * AND(IValue * val) = 0;
		virtual IValue * OR(IValue * val) = 0;
		virtual IValue * NOT() = 0;
		virtual IValue * INF(IValue * val) = 0;
		virtual IValue * INFOUEGAL(IValue * val) = 0;
		virtual IValue * SUPP(IValue * val) = 0;
		virtual IValue * SUPPOUEGAL(IValue * val) = 0;
		virtual IValue * EGAL(IValue * val) = 0;
		virtual IValue * DIFF(IValue * val) = 0;


		virtual ~IValue(){};
	};
}



#endif /* IVALUE_H_ */
