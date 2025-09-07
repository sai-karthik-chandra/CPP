#include<iostream>
#include<queue>
#include<thread>
#include<mutex>
#include<condition_variable>
using namespace std;

mutex m;
condition_variable cv_producer,cv_consumer;
queue<int> buffer;
const unsigned int maxBufferSize = 10;

void producer(int val){
	while(val){
		unique_lock<mutex> ul(m);
		cv_producer.wait(ul, [](){return buffer.size()<maxBufferSize;});
		buffer.push(val);
		cout<<"Produced: "<<val<<endl;
		val--;
		ul.unlock();
		cv_consumer.notify_one();
	}
}

void consumer(){
	while(true){
		unique_lock<mutex> ul(m);
		cv_consumer.wait(ul, [](){return buffer.size()>0;});
		int val = buffer.front();
		buffer.pop();
		cout<<"Consumed: "<<val<<endl;
		ul.unlock();
		cv_producer.notify_one();
	}
}

/*-------------------Binary Semaphore---------------------*/
class binarySemaphore{
	mutex m;
	condition_variable cv;
	bool flag;

	public:
		binarySemaphore(int val) : flag(val) {}

		void acquire(){
			unique_lock<mutex> ul(m);
			cv.wait(ul, [this](){return flag;});
			flag = false;
		}

		void release(){
			{
				lock_guard<mutex> lg(m);
				flag = true;
			}
			cv.notify_one();
		}
};
/*-------------------Binary Semaphore---------------------*/

/*-------------------Counting Semaphore---------------------*/
class countingSemaphore{
	mutex m;
	condition_variable cv;
	int count;

	public:
		countingSemaphore(int val) : count(val) {}

		void acquire(){
			unique_lock<mutex> ul(m);
			cv.wait(ul, [this](){return count>0;});
			--count;
		}

		void release(){
			{
				lock_guard<mutex> lg(m);
				++count;
			}
			cv.notify_one();
		}
};

countingSemaphore Empty(10),Full(0);
mutex m1;

void producerSemaphore(int val){
	while(val){
		Empty.acquire();
		{
			lock_guard<mutex> lg(m1);
			buffer.push(val);
			cout<<"Produced: "<<val<<endl;
			val--;
		}
		Full.release();
	}
}

void consumerSemaphore(){
	while(true){
		Full.acquire();
		{
			lock_guard<mutex> lg(m1);
			int val = buffer.front();
			buffer.pop();
			cout<<"Consumed: "<<val<<endl;
		}
		Empty.release();
	}
}
/*-------------------Counting Semaphore---------------------*/

int main(){
	thread t1(consumerSemaphore);
	thread t2(producerSemaphore,100);

	t1.join();
	t2.join();

	return 0;
}
