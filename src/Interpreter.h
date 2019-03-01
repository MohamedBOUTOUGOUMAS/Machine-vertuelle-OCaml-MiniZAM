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
#include "Fermeture.h"
#include "Ivalue.h"
using namespace std;

namespace minizam{

class Interpreter{

	Programme prog;
	int pc = 0;
	Queue<IValue * > pile = Queue<IValue *>();
	IValue * env = new Environnement();
	IValue * accu = new MlValue(0);

public :

	Interpreter(Programme p):prog(p){}

	Programme getProgramme(){return prog;}

	void afficher(){
		for(auto i : getProgramme().getProg()){
			cout<<i.getAttributes().size()<<endl;
		}
	}


	void evaluer(){

		for(auto inst : prog.getProg()){

			string c = "CONST";
			if( inst.getInst().find(c) != -1){
				MlValue accu = static_cast<MlValue>(accu);
				cout<<stoi(inst.getAttributes().at(0))<<endl;
				accu.setValue(stoi(inst.getAttributes().at(0)));
				pc += 1;
				continue;
			}

			string op = "PRIM";
			if(inst.getInst().find(op) != -1){
				MlValue accu = static_cast<MlValue>(accu);
				string op = inst.getAttributes().at(0);
				cout<<op<<" : op"<<endl;

				if(op == "+"){

					accu.setValue(accu.getValue() + (pile.pop())->getValue());
					pc += 1;
					continue;
				}
				if(op == "-"){
					accu.setValue(accu.getValue() - pile.pop()->getValue());
					cout<<accu.getValue()<<" : accu"<<endl;
					pc += 1;
					continue;
				}
				if(op == "*"){

					accu.setValue(accu.getValue() * pile.pop()->getValue());
					pc += 1;
					continue;
				}
				if(op == "/"){

					accu.setValue(accu.getValue() / pile.pop()->getValue());
					pc += 1;
					continue;
				}
				if(op == "and"){

					accu = accu.AND(pile.pop());
					pc += 1;
					continue;
				}
				if(op == "or"){
					accu = accu.OR(pile.pop());
					pc += 1;
					continue;
				}
				if(op == "not"){
					accu = accu.NOT();
					pc += 1;
					continue;
				}
				if(op == "<"){
					accu = accu.INF(pile.pop());
					pc += 1;
					continue;
				}
				if(op == "<="){
					accu = accu.INFOUEGAL(pile.pop());
					pc += 1;
					continue;
				}
				if(op == ">"){
					accu = accu.SUPP(pile.pop());
					pc += 1;
					continue;
				}
				if(op == ">="){
					accu = accu.SUPPOUEGAL(pile.pop());
					pc += 1;
					continue;
				}
				if(op == "="){
					accu = accu.EGAL(pile.pop());
					pc += 1;
					continue;
				}
				if(op == "<>"){
					accu = accu.DIFF(pile.pop());
					pc += 1;
					continue;
				}

			}


			string branch = "BRANCH";
			if(inst.getInst().find(branch) != -1){
				cout<<prog.position(inst.getAttributes().at(0)+":")<<endl;
				pc = prog.position(inst.getAttributes().at(0));
				continue;
			}


			string bnot = "BRANCHIFNOT";
			if(inst.getInst().find(bnot) != -1){
				MlValue accu = static_cast<MlValue>(accu);
				if(accu.getValue() == 0){
					pc = prog.position(inst.getAttributes().at(0));
				}else{
					pc += 1;
				}
				continue;
			}


			string push = "PUSH";
			if(inst.getInst().find(push) != -1){
				pile.push(accu);
				pc += 1;
				continue;
			}



			string pop = "POP";
			if(inst.getInst().find(pop) != -1){
				pile.pop();
				pc += 1;
				continue;
			}


			string acc = "ACC";
			if(inst.getInst().find(acc) != -1){
				cout<<stoi(inst.getAttributes().at(0))<<endl;
				accu = pile.getElementByIndex(stoi(inst.getAttributes().at(0)) - 1);
				pc += 1;
				continue;
			}


			string envacc = "ENVACC";
			if(inst.getInst().find(envacc) != -1){
				Environnement env = static_cast<Environnement>(env);
				accu = env.getEnv().at(stoi(inst.getAttributes().at(0)));
				pc += 1;
				continue;
			}

			string closure = "CLOSURE";
			if(inst.getInst().find(closure) != -1){
				Environnement env = static_cast<Environnement>(env);

				int n = stoi(inst.getAttributes().at(1));

				if(n>0) {pile.push(accu);}

				int l = prog.position(inst.getAttributes().at(0));

				for(int i=0 ; i<n; i++){
					env.extends(pile.pop());
				}
				Fermeture f = Fermeture(l,env);
				accu = &f;
				pc += 1;
				continue;
			}


			string apply = "APPLY";
			if(inst.getInst().find(apply) != -1){

				vector<IValue *> tmp = vector<IValue *>();

				int n = stoi(inst.getAttributes().at(0));

				for(int i=0 ; i<n; i++){
					tmp.push_back(pile.pop());
				}

				pile.push(env);
				MlValue v = MlValue(pc+1);
				pile.push(&v);

				for(int i=n-1 ; i>0; i--){
					pile.push(tmp.at(i));
				}

				Fermeture accu = static_cast<Fermeture>(accu);

				pc = accu.getPointer();
				*env = accu.getEnv();
				continue;
			}



			string retur = "RETURN";
			if(inst.getInst().find( retur) != -1){

				int n = stoi(inst.getAttributes().at(0));

				for(int i=0 ; i<n; i++){
					pile.pop();
				}
				pc = pile.pop()->getValue();

				env = pile.pop();
				continue;
			}

			string stop = "STOP";
			if(inst.getInst().find( stop) != -1){
				prog.~Programme();
				pile.~Queue();
				env->~IValue();
				accu->~IValue();
				pc += 1;
				continue;
			}
		}
	}
};

}//end namespace





#endif /* SRC_EVALUATEUR_H_ */
