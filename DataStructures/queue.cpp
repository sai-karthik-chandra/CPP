#include<iostream>
using namespace std;

class QueueArray{
	int* arr;
	int capacity;
	int size;
	int front;
	int rear;

	public:
		QueueArray(int cap){
			capacity = cap;
			arr = new int[capacity];
			size = 0;
			front = 0;
			rear = cap-1; //important initialization for a circular array So that the very first enqueue puts the element at index 0 (after increment).
		}

		bool isEmpty() { return size==0;}
		bool isFull() {return size==capacity;}

		void enqueue(int x){
			if(isFull()){
				cout<<"Queue is Full"<<endl;
				return;
			}
			rear = (rear+1)%capacity;
			arr[rear] = x;
			size++;
		}

		void dequeue(){
			if(isEmpty()){
				cout<<"Queue is Empty"<<endl;
				return;
			}
			front = (front+1)%capacity;
			size--;
		}

		int getFront(){
			if(isEmpty()) return -1;
			return arr[front];
		}

		int getRear(){
			if(isEmpty()) return -1;
			return arr[rear];
		}
};

struct Node{
	int data;
	Node*  next;
	Node(int val) : data(val),next(nullptr){}
};

class queueLinkedList{
	Node *front,*rear;
	public:
		queueLinkedList():front(nullptr),rear(nullptr){}

		bool isEmpty(){ return front==nullptr;}

		void enqueue(int x){
			Node* newNode = new Node(x);
			if(rear == nullptr){ 
				front=rear=newNode;
				return;
			}
			rear->next = newNode;
			rear = newNode;
		}

		void dequeue(){
			if(isEmpty()){
			       cout<<"Queue is empty"<<endl;
		       		return;
			}
			Node* temp = front;
			front = front->next;
			if(front == nullptr){
				rear = nullptr; //queue is empty
				return;
			}
			delete temp;
		}
		
		int getFront(){
			if(isEmpty()) return -1;
			return front->data;
		}

		int getRear(){
			if(isEmpty()) return -1;
			return rear->data;
		}
};

int main(){

	return 0;
}
