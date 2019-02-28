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
		mutable mutex m;
		condition_variable cv_consom;
		condition_variable cv_prod;
		T ** tab;
		size_t allocz;
		size_t begin;
		size_t sz;
		bool isBlocking;

		bool empty()const{
			return sz==0;
		}
		bool full()const{
			return sz==allocz;
		}
	public:
		Queue (size_t maxsize) :allocz(maxsize),begin(0),sz(0) {
			tab = new T * [maxsize];
			isBlocking = false;
			memset(tab, 0, maxsize * sizeof(T*));
		}
		Queue(const Queue &q){
			tab = q.tab;
			allocz = q.allocz;
			sz = q.sz;
			begin = q.begin;
			isBlocking = q.isBlocking;
		}
		size_t size() const {
			return sz;
		}

		void setBlockingPop(bool b){
			//unique_lock<mutex> l(m);
			cout<<"isBlocking function"<<endl;
			isBlocking = b;
		}

		T * pop(){
			unique_lock<mutex> l(m);
			cout<<getBool()<<" : isBlocking"<<endl;
			while(empty() && !isBlocking){
				cout<<"thread_consom_attente"<<endl;
				cv_consom.wait(l);
			}
			if(empty()){
				cout<<"nullptr issu de pop"<<endl;
				return nullptr;
			}
			if(full()){
				cout<<"thread_consom_Réveille"<<endl;
				cv_prod.notify_all();
			}
			cout<<"pop"<<endl;
			auto ret = tab[begin];
			tab[begin] = nullptr;
			sz--;
			begin = (begin+1) % allocz;
			return ret;
		}

		bool getBool()const{
			return isBlocking;
		}
		void push (T * elt) {
			unique_lock<mutex> l(m);
			while(full() && !isBlocking){
				cout<<"thread_prod"<<endl;
				cv_prod.wait(l);
			}
			if(empty()){
				cout<<"thread_prod_Réveille"<<endl;
				cv_consom.notify_all();
			}
			cout<<"push"<<endl;
			tab[(begin + sz)%allocz] = elt;
			sz++;
			return ;
		}

		~Queue() {
			for (size_t i = 0; i < sz ; i++) {
			auto ind = (begin + i) % allocz;
			delete tab[ind];
			}
			delete[] tab;
		}

	};
}


#endif /* QUEUE_H_ */
