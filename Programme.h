/*
 * Programme.h
 *
 *  Created on: 28 févr. 2019
 *      Author: moumouh
 */

#ifndef SRC_PROGRAMME_H_
#define SRC_PROGRAMME_H_

#include <iostream>
#include <vector>
#include "MlValue.h"
#include "Instruction.h"
using namespace std;

namespace minizam{

class Programme{

	vector<Instruction> prog = vector<Instruction>();
public:
	Programme(vector<Instruction> prog):prog(prog){}
	vector<Instruction> getProg(){return prog;}

	ostream & operator << (std::ostream & os) {
		for(auto i:prog){
			os<<i<<" ";
		}
		os<<endl;
		return os;
	}
};


}



#endif /* SRC_PROGRAMME_H_ */
