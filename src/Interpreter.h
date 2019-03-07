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
	IValue * extra_args;
	IValue * trap_sp = new MlValue(-1);
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
			if( inst.getInst().find(c) == 0){
				accu = new MlValue(0.0);
				cout<<stoi(inst.getAttributes().at(0))<<endl;
				accu->setValue(stoi(inst.getAttributes().at(0)));
				cout<<accu->getValue()<<endl;
				pc += 1;
				continue;
			}

			string op = "PRIM";
			if(inst.getInst().find(op) == 0){

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
			if(inst.getInst().find(branch) == 0){
				cout<<prog.position(inst.getAttributes().at(0)+":")<<endl;
				pc = prog.position(inst.getAttributes().at(0)+":");
				cout<<"pc : "<<pc<<endl;
				continue;
			}


			string bnot = "BRANCHIFNOT";
			if(inst.getInst().find(bnot) == 0){
				if(accu->getValue() == 0){
					pc = prog.position(inst.getAttributes().at(0)+":");
				}else{
					pc += 1;
				}
				continue;
			}

			regex pushtrap{"PUSHTRAP"};
			if(regex_search(inst.getInst(), pushtrap)){

				int l = prog.position(inst.getAttributes().at(0)+":");
				cout<<"label : "<<l<<endl;


				pile.push(extra_args);
				pile.push(env);
				pile.push(trap_sp);
				pile.push(new MlValue(l));

				trap_sp = pile.getElementByIndex(0);

				pc += 1;
				continue;
			}

			regex poptrap {"POPTRAP"};
			if(regex_search(inst.getInst(), poptrap)){
				pile.pop();
				IValue * ret = pile.pop();
				trap_sp = ret;
				pile.pop();
				pile.pop();

				pc += 1;
				continue;
			}


			string raise = "RAISE";
			if(inst.getInst().find(raise) == 0){
				if(trap_sp->getValue() == -1){
					cout<<"error : "<<accu->getValue()<<endl;
					break;
				}else{
					for(int i = 0; i<pile.size(); i++){
						IValue * ret = pile.pop();
						if(trap_sp->getValue() == ret->getValue()){
							break;
						}
					}

					if(pile.size() > 0){
						pc = trap_sp->getValue();
						trap_sp = pile.pop();
						env = pile.pop();
						extra_args = pile.pop();
					}

				}
				continue;
			}

			regex push{"PUSH"};
			if(regex_search(inst.getInst(), push)){
				cout<<"value : "<<accu->getPointer()<<endl;
				pile.push(accu);
				pc += 1;
				continue;
			}



			regex pop{"POP"};
			if(regex_search(inst.getInst(), pop)){
				if(pile.size()>0){
					pile.pop();
				}
				pc += 1;
				continue;
			}


			string acc = "ACC";
			if(inst.getInst().find(acc, 0) == 0){
				cout<<"value : befor : "<<accu->getValue()<<endl;
				cout<<"index dans la pile : "<<stoi(inst.getAttributes().at(0))<<endl;
				accu = pile.getElementByIndex(stoi(inst.getAttributes().at(0)));
				cout<<"value : after : "<<accu->getValue()<<endl;
				pc += 1;
				continue;
			}


			string envacc = "ENVACC";
			if(inst.getInst().find(envacc) == 0){
				cout<<"value : befor : "<<accu->getPointer()<<endl;
				int index = stoi(inst.getAttributes().at(0));
				accu = env->getEnvironnement().at(index);
				pc += 1;
				cout<<"value : after : "<<accu->getPointer()<<endl;
				continue;
			}

			string closure = "CLOSURE ";
			if(inst.getInst().find(closure) == 0){

				int n = stoi(inst.getAttributes().at(1));

				if(n>0) {
					pile.push(accu);
				}
				cout<<"n : "<<n<<endl;
				int l = prog.position(inst.getAttributes().at(0)+":");
				cout<<"label : "<<l<<endl;

				Environnement * e = new Environnement();
				for(int i=0 ; i<n; i++){
					e->extends(pile.pop());
				}

				accu = new Fermeture(l,e);
				cout<<"env size : "<<accu->getEnvironnement().size()<<endl;
				pc += 1;
				cout<<"value : after : "<<accu->getPointer()<<endl;
				continue;
			}


			string closureRec = "CLOSUREREC";
			if(inst.getInst().find( closureRec) == 0){

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
			if(inst.getInst().find(offsetClosure) == 0){
				IValue * v = env->getEnvironnement().at(0);
				accu = new Fermeture(v->getValue(), env);
				pc += 1;
				continue;
			}

			string apply = "APPLY ";
			if(inst.getInst().find(apply) == 0){

				cout<<"value : befor : "<<accu->getPointer()<<endl;
				vector<IValue *> tmp = vector<IValue *>();

				int n = stoi(inst.getAttributes().at(0));
				cout<<"n : "<<n<<endl;


				for(int i=0 ; i<n; i++){
					tmp.push_back(pile.pop());
				}


				pile.push(new Environnement(env->getEnvironnement()));
				MlValue * v = new MlValue(pc+1);
				pile.push(v);


				pile.push(extra_args);
				extra_args = new MlValue(n - 1);

				for(int i=0; i<n ;i++){
					pile.push(tmp.at(n-i-1));
				}

				pc = accu->getPointer();
				cout<<accu->getPointer()<<endl;

				cout<<"pc : "<<pc<<endl;
				cout<<"env size : "<<accu->getEnvironnement().size()<<endl;
				env = new Environnement(accu->getEnvironnement());
				continue;
			}


			string grab = "GRAB";
			if(inst.getInst().find( grab) == 0){
				int n = stoi(inst.getAttributes().at(0));
				cout<<"n : "<<n<<endl;
				if(extra_args->getValue() >= n){
					extra_args = new MlValue(extra_args->getValue() - n);
					pc += 1;
				}else{
					vector<IValue *> tmp = vector<IValue *>();
					for(int i=0 ; i<extra_args->getValue() + 1; i++){
						tmp.push_back(pile.pop());
					}
					int c = pc - 1;

					Environnement * e = new Environnement();
					e->extends(new Environnement(env->getEnvironnement()));

					for(int i=0; i < tmp.size() ;i++){
						e->extends(tmp.at(tmp.size()-i-1));
					}

					accu = new Fermeture(c, e);

					extra_args = pile.pop();
					IValue * ret = pile.pop();
					pc = ret->getValue();
					env = pile.pop();
				}

				continue;
			}

			string restart = "RESTART";
			if(inst.getInst().find(restart) == 0){
				int n = env->getEnvironnement().size();
				for(int i = 1 ; i<n; i++){
					pile.push(env->getEnvironnement().at(n-i));
				}


				env = env->getEnvironnement().at(0);

				extra_args = new MlValue(extra_args->getValue() + n-1);
				pc += 1;
				continue;
			}

			string retur = "RETURN";
			if(inst.getInst().find( retur) == 0){

				int n = stoi(inst.getAttributes().at(0));

				for(int i=0 ; i<n; i++){
					pile.pop();
				}

				if(extra_args->getValue() == 0){

					extra_args = pile.pop();
					IValue * ret = pile.pop();
					pc = ret->getValue();

					env = pile.pop();

				}else{
					extra_args = new MlValue(extra_args->getValue() - 1);
					pc = accu->getPointer();
					env = new Environnement(accu->getEnvironnement());
				}


				continue;
			}



			string stop = "STOP";
			if(inst.getInst().find( stop) == 0){}





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
