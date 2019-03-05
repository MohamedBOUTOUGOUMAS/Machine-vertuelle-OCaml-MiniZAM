/*
 * Queue.h
 *
 *  Created on: 19 oct. 2018
 *      Author: 3703039
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream>
#include <mutex>
#include <string>
#include <condition_variable>
#include <cstring>
using namespace std;
namespace minizam{


template<typename T>
	class Queue{
		vector<T> tab;
	public:
		Queue (){
			tab = vector<T>();
		}
		Queue(const Queue &q){
			tab = q.tab;
		}
		size_t size() const {
			return tab.size();
		}

		T pop(){
			T tete = tab.at(tab.size()-1);
			cout<<"pop pile size : "<<tab.size()<<endl;
			tab.pop_back();
			cout<<"pop pile size : "<<tab.size()<<endl;
			return tete;
		}

		void push (T elt) {
			tab.push_back(elt);
			cout<<"push pile size : "<<tab.size()<<endl;
		}

		T getElementByIndex(int i){
			if(i >= tab.size()){
				cout<< "out of bound" <<endl;
			}
			i = tab.size() - i - 1;
			cout<< "getElementByIndex index : "<<i <<endl;
			T res = tab.at(i);
			return res;
		}


		~Queue() {
			tab.clear();
		}

	};
}


#endif /* QUEUE_H_ */
