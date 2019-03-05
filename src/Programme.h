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

	Programme(vector<Instruction> prog):prog(prog){

	}

	vector<Instruction> getProg(){return prog;}

	int position(string label){
		for(int i=0; i<prog.size(); i++){
			if(prog.at(i).isLabel()==1 && prog.at(i).getLabel() == label){
				return i;
			}
		}
		return -1;
	}

//	~Programme(){
//		prog.~vector();
//	}

};


}



#endif /* SRC_PROGRAMME_H_ */
