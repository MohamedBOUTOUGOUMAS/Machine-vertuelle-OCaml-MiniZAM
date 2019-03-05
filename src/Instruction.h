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
//			for(auto at : attributes){
//				cout<<at<<endl;
//			}

		}

		string getLabel(){return label;}

		string getInst(){return inst;}

		vector<string> getAttributes(){return attributes;}


		bool isLabel(){
			regex t{"\\s*"};
			if(!regex_match(label,t)){
				return true;
			}
			return false;
		}

		ostream & operator << (std::ostream & os) {
			os << label<< " "<< inst<< endl;
			return os;
		}

//		~Instruction(){
//			attributes.clear();
//		}

	};

}



#endif /* INSTRUCTION_H_ */
