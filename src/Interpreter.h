/*
 * Evaluateur.h
 *
 *  Created on: 28 févr. 2019
 *      Author: moumouh
 */

#ifndef SRC_EVALUATEUR_H_
#define SRC_EVALUATEUR_H_
#include <iostream>
#include <vector>
#include <regex>

#include "Instruction.h"
#include "Queue.h"
#include "MlValue.h"
#include "Programme.h"
#include "Environnement.h"
using namespace std;

namespace minizam{

class Interpreter{

	Programme p;
	int pc = 0;
	Queue<MlValue> pile = Queue<MlValue>();
	Environnement env = Environnement();
	MlValue accu = MlValue();
	regex pattern;
public :

	Interpreter(Programme p):p(p){}



	void evaluer(){

		for(auto inst : p.getProg()){

			if(inst.isLabel() == 0){
				pattern = {"CONST"};
				if(regex_search(inst.getInst(), pattern)){
					accu.setValue(stoi(inst.getAttributes().at(0)));
				}
				pattern = {"PRIM"};
				if(regex_search(inst.getInst(), pattern)){
					string op = inst.getAttributes().at(0);
					cout<<op<<" : op"<<endl;
					if(op == "+"){
						MlValue val = pile.pop();
						accu += val;
					}
					if(op == "-"){
						MlValue val = pile.pop();
						accu -= val;
					}
					if(op == "*"){
						MlValue val = pile.pop();
						accu = accu * val;
					}
					if(op == "/"){
						MlValue val = pile.pop();
						accu = accu / val;
					}
					if(op == "and"){
						MlValue val = pile.pop();
						accu = accu.AND(val);
					}
					if(op == "or"){
						MlValue val = pile.pop();
						accu = accu.OR(val);
					}
					if(op == "not"){
						accu = accu.NOT();
					}
					if(op == "<"){
						MlValue val = pile.pop();
						accu = accu.INF(val);
					}
					if(op == "<="){
						MlValue val = pile.pop();
						accu = accu.INFOUEGAL(val);
					}
					if(op == ">"){
						MlValue val = pile.pop();
						accu = accu.SUPP(val);
					}
					if(op == ">="){
						MlValue val = pile.pop();
						accu = accu.SUPPOUEGAL(val);
					}
					if(op == "="){
						MlValue val = pile.pop();
						accu = accu.EGAL(val);
					}
					if(op == "<>"){
						MlValue val = pile.pop();
						accu = accu.DIFF(val);
					}

				}
			}



			pc += 1;
		}
	}
};

}//end namespace





#endif /* SRC_EVALUATEUR_H_ */
