#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

//What is a thread ?
//-> A thread is the smallest unit of execution a CPU can run.
//-> A thread lives inside a process.

//-> Process : compiled program (.exe)
//-> Thread : main is one thread

//Ways to create threads:
//1. Function pointers
//2. Lambda functions
//3. Functors
//4. Non-static member functions
//5. Static member functions

void func1(int x){
	cout<<"X: "<<x<<endl;
	return;
}

class Class{
	public:
		void operator() (int x){
			cout<<"X: "<<x<<endl;
			return;
		}

		void func2(int x){
			cout<<"X: "<<x<<endl;
			return;
		}

		static void func3(int x){
			cout<<"X: "<<x<<endl;
			return;
		}
};

int cnt = 0;
mutex m;

void increment_lock(){
	for(int i=0;i<1000000;i++){
		m.lock();
		cnt++;
		m.unlock();
	}
	return;
}

void increment_try_lock(){
	for(int i=0;i<1000000;i++){
		if(m.try_lock()){
			cnt++;
			m.unlock();
		}
	}
}

int main(){
	//thread t1(func1,10); //creation of a thread through function pointer
	//thread t2([](int x) {cout<<"X: "<<x<<endl;},11); //creation of a thread through lambda function
	//thread t3((Class()),12); //creation of a thread using functor
	//Class c;
	//thread t4(&Class::func2,&c,13); //creation of a thread using non-static member function
	//thread t5(&Class::func3,14); //creation of a thread using static member function
	
	//thread t6(increment_lock);
	//thread t7(increment_lock);

	thread t8(increment_try_lock);
	thread t9(increment_try_lock);

	t8.join();
	t9.join();	
	cout<<cnt<<endl;
	return 0;
}
