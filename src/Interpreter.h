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
	IValue * accu;

public :

	Interpreter(Programme p):prog(p){}

	Programme getProgramme(){return prog;}

	void afficher(){
		for(auto i : getProgramme().getProg()){
			cout<<i.getAttributes().size()<<endl;
		}
	}


	IValue * evaluer(){

		//for(auto inst : prog.getProg()){
		for(int i=0; i<prog.getProg().size(); i++){
			cout<<"i : "<<i<<endl;
			Instruction inst = prog.getProg().at(i);
			if(i != pc){
				inst = prog.getProg().at(pc);
				i = pc;
			}
			string c = "CONST";
			if( inst.getInst().find(c) != -1){
				accu = new MlValue(0.0);
				cout<<stoi(inst.getAttributes().at(0))<<endl;
				accu->setValue(stoi(inst.getAttributes().at(0)));
				cout<<accu->getValue()<<endl;
				pc += 1;
				continue;
			}

			string op = "PRIM";
			if(inst.getInst().find(op) != -1){

				string op = inst.getAttributes().at(0);
				cout<<op<<" : op"<<endl;
				cout<<accu->getValue()<<" : value de accu operator"<<endl;
				if(op == "+"){

					accu = new MlValue(accu->getValue() + (pile.pop())->getValue());
					pc += 1;
					continue;
				}
				if(op == "-"){
					accu = new MlValue(accu->getValue() - pile.pop()->getValue());
					cout<<accu->getValue()<<" : accu"<<endl;
					pc += 1;
					continue;
				}
				if(op == "*"){

					accu = new MlValue(accu->getValue() * pile.pop()->getValue());
					pc += 1;
					continue;
				}
				if(op == "/"){

					accu = new MlValue(accu->getValue() / pile.pop()->getValue());
					pc += 1;
					continue;
				}
				if(op == "and"){

					accu = accu->AND(pile.pop());
					pc += 1;
					continue;
				}
				if(op == "or"){
					accu = accu->OR(pile.pop());
					pc += 1;
					continue;
				}
				if(op == "not"){
					accu = accu->NOT();
					pc += 1;
					continue;
				}
				if(op == "<"){
					accu = accu->INF(pile.pop());
					pc += 1;
					continue;
				}
				if(op == "<="){
					accu = accu->INFOUEGAL(pile.pop());
					pc += 1;
					continue;
				}
				if(op == ">"){
					accu = accu->SUPP(pile.pop());
					pc += 1;
					continue;
				}
				if(op == ">="){
					accu = accu->SUPPOUEGAL(pile.pop());
					pc += 1;
					continue;
				}
				if(op == "="){
					accu = accu->EGAL(pile.pop());
					pc += 1;
					continue;
				}
				if(op == "<>"){
					accu = accu->DIFF(pile.pop());
					pc += 1;
					continue;
				}
				if(op == "print"){
					cout<<"Contenu de l'accu :  "<<accu->getValue()<<endl;
					pc += 1;
					continue;
				}

			}


			string branch = "BRANCH ";
			if(inst.getInst().find(branch) != -1){
				cout<<prog.position(inst.getAttributes().at(0)+":")<<endl;
				pc = prog.position(inst.getAttributes().at(0)+":");
				cout<<"pc : "<<pc<<endl;
				continue;
			}


			string bnot = "BRANCHIFNOT";
			if(inst.getInst().find(bnot) != -1){
				if(accu->getValue() == 0){
					pc = prog.position(inst.getAttributes().at(0)+":");
				}else{
					pc += 1;
				}
				continue;
			}


			string push = "PUSH";
			if(inst.getInst().find(push) != -1){
				cout<<"value : "<<accu->getPointer()<<endl;
				pile.push(accu);
				pc += 1;
				continue;
			}



			string pop = "POP";
			if(inst.getInst().find(pop) != -1){
				if(pile.size()>0){
					pile.pop();
				}
				pc += 1;
				continue;
			}


			string acc = "ACC";
			if(inst.getInst().find(acc) != -1){
				cout<<"value : befor : "<<accu->getValue()<<endl;
				cout<<"index dans la pile : "<<stoi(inst.getAttributes().at(0))<<endl;
				accu = pile.getElementByIndex(stoi(inst.getAttributes().at(0)));
				cout<<"value : after : "<<accu->getValue()<<endl;
				pc += 1;
				continue;
			}


			string envacc = "ENVACC";
			if(inst.getInst().find(envacc) != -1){
				cout<<"value : befor : "<<accu->getPointer()<<endl;
				accu = env->getEnvironnement().at(stoi(inst.getAttributes().at(0)));
				pc += 1;
				cout<<"value : after : "<<accu->getPointer()<<endl;
				continue;
			}

			string closure = "CLOSURE ";
			if(inst.getInst().find(closure) == 0){

				int n = stoi(inst.getAttributes().at(1));

				if(n>0) {pile.push(accu);}
				cout<<"n : "<<n<<endl;
				int l = prog.position(inst.getAttributes().at(0)+":");
				cout<<"label : "<<l<<endl;
				for(int i=0 ; i<n; i++){
					env->extends(pile.pop());
				}
				accu = new Fermeture(l,env);
				cout<<"env size : "<<accu->getEnvironnement().size()<<endl;
				pc += 1;
				cout<<"value : after : "<<accu->getPointer()<<endl;
				continue;
			}


			string closureRec = "CLOSUREREC";
			if(inst.getInst().find( closureRec) != -1){

				int n = stoi(inst.getAttributes().at(1));

				if(n>0) {
					pile.push(accu);
				}
				cout<<"n : "<<n<<endl;

				int l = prog.position(inst.getAttributes().at(0)+":");

				cout<<"label : "<<l<<endl;

				env->extends(new MlValue(l));

				for(int i=0 ; i<n; i++){
					env->extends(pile.pop());
				}

				accu = new Fermeture(l,env);
				cout<<"env size : "<<accu->getEnvironnement().size()<<endl;
				pc += 1;
				cout<<"value : after : "<<accu->getPointer()<<endl;

				pile.push(accu);
				continue;
			}


			string offsetClosure = "OFFSETCLOSURE";
			if(inst.getInst().find(offsetClosure) != -1){
				IValue * v = env->getEnvironnement().at(0);
				accu = new Fermeture(v->getValue(), env);
				pc += 1;
				continue;
			}

			string apply = "APPLY ";
			if(inst.getInst().find(apply) != -1){
				cout<<"value : befor : "<<accu->getPointer()<<endl;
				vector<IValue *> tmp = vector<IValue *>();

				int n = stoi(inst.getAttributes().at(0));
				cout<<"n : "<<n<<endl;
				for(int i=0 ; i<n; i++){
					tmp.push_back(pile.pop());
				}

				pile.push(env);
				IValue * e = pile.pop();
				pile.push(e);
				MlValue * v = new MlValue(pc+1);
				pile.push(v);

				for(int i=0; i<n ;i++){
					pile.push(tmp.at(n-i-1));
				}
				//Fermeture f = *accu;
				pc = accu->getPointer();
				cout<<accu->getPointer()<<endl;

				cout<<"pc : "<<pc<<endl;
				cout<<"env size : "<<accu->getEnvironnement().size()<<endl;
				env = new Environnement(accu->getEnvironnement());
				continue;
			}



			string retur = "RETURN";
			if(inst.getInst().find( retur) != -1){

				int n = stoi(inst.getAttributes().at(0));

				for(int i=0 ; i<n; i++){
					pile.pop();
				}

				IValue * ret = pile.pop();
				pc = ret->getValue();

				env = pile.pop();
				continue;
			}

			string stop = "STOP";
			if(inst.getInst().find( stop) != -1){}





		}
		return accu;
	}


//	~Interpreter(){
//		accu->~IValue();
//		env->~IValue();
//		pile.~Queue();
//		prog.~Programme();
//
//	}

};

}//end namespace





#endif /* SRC_EVALUATEUR_H_ */
