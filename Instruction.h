/*
 * Instruction.h
 *
 *  Created on: 27 févr. 2019
 *      Author: moumouh
 */

#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_
#include <iostream>
#include <vector>
using namespace std;

namespace minizam{

	class Instruction{

		string label;
		string inst;
		vector<string> attributes = vector<string>();
	public :
		Instruction(string l, string i):label(l),inst(i){
			regex e("\\s");
			regex_token_iterator<string::iterator> it(i.begin(), i.end(), e, -1);
			regex_token_iterator<string::iterator> end;
			it++;
			while (it != end){
				string attr = *it++;
				regex e2(",");
				regex_token_iterator<string::iterator> it2(attr.begin(), attr.end(), e2, -1);
				regex_token_iterator<string::iterator> end2;
				while( it2 != end2){
					attributes.push_back(*it2++);
				}
			}



		}

		string getLabel(){return label;}

		string getInst(){return inst;}

		vector<string> getAttributes(){return attributes;}

		bool isLabel(){
			if(label == " "){
				return true;
			}
			return false;
		}

		ostream & operator << (std::ostream & os) {
			os << label<< " "<< inst<< endl;
			return os;
		}
		~Instruction(){
			label.~basic_string();
			inst.~basic_string();
		}

	};

}



#endif /* INSTRUCTION_H_ */
