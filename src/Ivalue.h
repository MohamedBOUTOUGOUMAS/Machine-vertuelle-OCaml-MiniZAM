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
		virtual int getValue() = 0;
		~IValue(){}
	};
}



#endif /* IVALUE_H_ */
