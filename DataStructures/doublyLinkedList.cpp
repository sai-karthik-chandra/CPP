#include<iostream>
using namespace std;

struct Node{
	int data;
	Node* next;
	Node* prev;
	Node(int x):data(x),next(nullptr),prev(nullptr) {}
};

void printListForward(Node* head){
	while(head){
		cout<<head->data<<"->";
		head = head->next;
	}
	cout<<"NULL"<<endl;
}

void printListReverse(Node* head){
	if(head == nullptr) return;
	while(head->next){
		head = head->next;
	}
	while(head){
		cout<<head->data<<"->";
		head = head->prev;
	}
	cout<<"NULL"<<endl;
}

void insertAtHead(Node*& head,int val){
	Node* newNode = new Node(val);
	if(head == nullptr){
		head = newNode;
		return;
	}
	newNode->next = head;
	head->prev = newNode;
	head = newNode;
}

void insertAtTail(Node*& head,int val){
	Node* newNode = new Node(val);
	if(head == nullptr){
		head = newNode;
		return;
	}
	Node* temp = head;
	while(temp->next){
		temp = temp->next;
	}
	temp->next = newNode;
	newNode->prev = temp;
}

void insertAtPosition(Node*& head,int pos,int val){
	Node* newNode = new Node(val);
	if(pos == 1){
		insertAtHead(head,val);
		return;
	}
	Node* temp = head;
	for(int i=1;temp && i<pos-1;i++){
		temp = temp->next;
	}
	if(temp == nullptr){
		cout<<"Position out of range"<<endl;
		return;
	}
	newNode->prev = temp;
	newNode->next = temp->next;
	if(temp->next != nullptr) temp->next->prev = newNode;
	temp->next = newNode;
}

void deleteHead(Node*& head){
	if(head == nullptr)  return;
	if(head->next == nullptr){
		delete head;
		head = nullptr;
	}
	Node* temp = head->next;
	head->next->prev = nullptr;
	delete head;
	head = temp;
}

void deleteTail(Node*& head){
	if(head == nullptr) return;
	if(head->next == nullptr){
		delete head;
		head = nullptr;
	}
	Node* temp = head;
	while(temp->next){
		temp = temp->next;
	}
	temp->prev->next = nullptr;
	delete temp;
}

void deleteAtPosition(Node*& head,int pos){
	if(head == nullptr) return;
	if(pos == 1){
		deleteHead(head);
		return;
	}
	Node* temp = head;
	for(int i=1;temp && i<pos-1;i++){
		temp = temp->next;
	}
	Node* deleteNode = temp->next;
	temp->next = temp->next->next;
	temp->next->prev = temp;
	delete deleteNode;
}

Node* reverse(Node* head){
	Node* temp = nullptr;
	Node* curr = head;
	while(curr){
		//swap prev and next
		temp = curr->prev;
		curr->prev = curr->next;
		curr->next = temp;
		//move forward since next is swapped go to prev
		curr = curr->prev;
	}

	if(temp!=nullptr){
		head = temp->prev; //temp ends at second last node and temp->prev will always be the new head
	}
	return head;
}

int main(){
	Node* head = nullptr;
	insertAtHead(head,5);
	insertAtTail(head,6);
	insertAtHead(head,4);
	insertAtTail(head,7);
	insertAtHead(head,3);
	insertAtPosition(head,3,9);
	deleteAtPosition(head,3);
	printListForward(head);
	head = reverse(head);
	printListForward(head);
	return 0;
}
