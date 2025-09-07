#include<iostream>
#include<queue>
#include<thread>
#include<mutex>
#include<condition_variable>
using namespace std;

mutex m;
condition_variable cv;
queue<int> buffer;
const unsigned int maxBufferSize = 10;

void producer(int val){
	while(val){
		unique_lock<mutex> ul(m);
		cv.wait(ul, [](){return buffer.size()<maxBufferSize;});
		buffer.push(val);
		cout<<"Produced: "<<val<<endl;
		val--;
		ul.unlock();
		cv.notify_one();
	}
}

void consumer(){
	while(true){
		unique_lock<mutex> ul(m);
		cv.wait(ul, [](){return buffer.size()>0;});
		int val = buffer.front();
		buffer.pop();
		cout<<"Consumed: "<<val<<endl;
		ul.unlock();
		cv.notify_one();
	}
}

int main(){
	thread t1(consumer);
	thread t2(producer,100);

	t1.join();
	t2.join();

	return 0;
}
