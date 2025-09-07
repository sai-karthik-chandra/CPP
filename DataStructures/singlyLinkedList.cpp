#include<iostream>
using namespace std;

/*
-> What is a Linked List?

	A linear data structure where elements (nodes) are dynamically allocated on the heap.

-> Each node contains:

	Data field (the value)

	Pointer/reference to next node

-> Unlike arrays:

	Memory is not contiguous.

	Insertions/deletions are faster (no shifting).

	Random access (arr[i]) is not possible (O(n)).

-> Address of the head node should be stored in a variable and shouldn't be changed since this variable is used to access the whole linked list if changed we loose the starting point of the linked list.
*/

//In Linked list data is stored as a node which consists of data and address to next node
struct Node{
	int data;	//data
	Node* next;	//address to next node
	Node(int val) : data(val),next(nullptr) {}
};

/*-------------Utility-------------------*/
void printList(Node* head){
	while(head != nullptr){
		cout<<head->data<<"->";
		head = head->next;
	}
	cout<<"NULL"<<endl;
}

int length(Node* head){
	int count = 0;
	while(head != nullptr){
		count++;
		head = head->next;
	}
	return count;
}
/*-------------Utility-------------------*/

/*-------------Insertion-----------------*/
void insertAtHead(Node*& head,int data){
	Node* newNode = new Node(data);
	newNode->next = head;
	head = newNode;
}

void insertAtTail(Node*& head,int data){
	Node* newNode = new Node(data);
	if(head == nullptr){
		head = newNode;
	}
	else{
		Node* temp = head;
		while(temp->next != nullptr){
			temp = temp->next;
		}
		temp->next = newNode;
	}
}

void insertAtPosition(Node*& head,int pos,int data){
	if(pos == 1){
		insertAtHead(head,data);
	}
	else{
		Node* temp = head;
		for(int i=1;temp && i<pos-1;i++){ //i<pos-1 since we need to point to the node which is prev of the node at pos
			temp = temp->next;
		}
		if(temp == nullptr){cout<<"Position out of range"<<endl;}
		Node* newNode = new Node(data);
		newNode->next = temp->next;
		temp->next = newNode;
	}
}
/*-------------Insertion-----------------*/

/*-------------Deletion-----------------*/
void deleteHead(Node*& head){
	if(head != nullptr){
		Node* temp = head->next;
		delete head;
		head = temp;
	}
}

void deleteTail(Node*& head){
	if(head == nullptr) return;
	if(head->next == nullptr){
		delete head;
		head = nullptr;
		return;
	}
	Node* temp = head;
	while(temp->next->next!=nullptr){
		temp = temp->next;
	}
	delete temp->next;
	temp->next = nullptr;
}

void deleteAtPosition(Node*& head,int pos){
	if(head == nullptr) return;
	if(pos == 1){
		deleteHead(head);
		return;
	}
	Node* temp = head;
	for(int i=1;temp && i<pos-1;i++){	//i<pos-1 since we need to point to the node which is prev of node at pos
		temp = temp->next;
	}
	if(temp == nullptr || temp->next == nullptr) return;
	Node* nodeToDelete = temp->next;
	temp->next = temp->next->next;
	delete nodeToDelete;
}

void deleteByValue(Node*& head,int key){
	if(head == nullptr) return;
	if(head->data == key){
		deleteHead(head);
		return;
	}
	Node* temp = head;
	while(temp->next && temp->next->data != key){
		temp = temp->next;
	}
	if(temp->next == nullptr) return;
	Node* nodeToDelete = temp->next;
	temp->next = temp->next->next;
	delete nodeToDelete;
}
/*-------------Deletion-----------------*/

/*-------------Search-----------------*/
bool search(Node*& head,int key){
	if(head == nullptr) return false;
	Node* temp = head;
	while(temp){
		if(temp->data == key) return true;
		temp = temp->next;
	}
	return false;
}
/*-------------Search-----------------*/

/*-------------Reverse-----------------*/
Node* reverse(Node*& head){
	Node* prev = nullptr;
	Node* curr = head;
	while(curr){
		Node* next = curr->next;	//(1) store the next
		curr->next = prev;		//(2) reverse the link
		prev = curr;			//(3) forward prev
		curr = next;			//(4) forward curr
	}
	return prev;
}

Node* recursiveReverse(Node*& head){
	if(head == nullptr || head->next == nullptr) return head;

	Node* newHead = recursiveReverse(head->next);
	head->next->next = head;
	head->next = nullptr;

	return newHead;
}
/*-------------Reverse-----------------*/

/*-------------Memory Cleanup-----------------*/
void freeList(Node*& head){
	while(head){
		Node* temp = head;
		head = head->next;
		delete temp;
	}
}
/*-------------Memory Cleanup-----------------*/

/*-------------Special-----------------*/
Node* findMiddle(Node*& head){	//Tortoise and Hare algorithm
	Node* slow = head;	//slow moves one step at a time
	Node* fast = head;	//fast moves two steps at a time
	while(fast && fast->next){	//when fast reaches the end slow is at the middle
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

//A loop exists in a linked list if the next pointer of the last node points to any other node in the list(including itself).
bool detectCycle(Node*& head){	//Floyd's Cycle Detection Algorithm
	Node* slow = head;
	Node* fast = head;
	while(fast && fast->next){
		slow = slow->next;
		fast = fast->next->next;
		if(slow==fast) return true;	//if there is a cycle eventually slow and fast will meet at a node and if there is no cycle then fast will reach NULL
	}
	return false;
}

//extension of above algorithm to find the starting node of the cycle
//start of the cycle is the node that the last node of the loop points back to
Node* startingNodeofCycle(Node*& head){
	Node* slow = head;
	Node* fast = head;

	while(fast && fast->next){
		slow = slow->next;
		fast = fast->next->next;
		if(slow==fast) break;	//if slow and fast meets then a cycle exsist, call this meeting point
	}

	slow = head;	//reset one pointer to head and keep the other at meeting point
	while(slow!=fast){	//move both pointers one step at a time they will meet again at start of the cycle
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}

Node* mergeSorted(Node* l1,Node* l2){
	Node dummy(0);
	Node* tail = &dummy;	//here we use a dummy node we always append to tail and at last the real head is dummy.next
	
	while(l1 && l2){
		if(l1->data<l2->data){
			tail->next = l1;	//link the smaller node to the tail
			l1 = l1->next;		//advance the list
		}else{
			tail->next = l2;
			l2 = l2->next;
		}
		tail = tail->next;	//advance the tail to the newly attached node
	}
	
	tail->next = (l1 ? l1 : l2);	//attach remaining
	return dummy.next;	//head of the merged list is after the dummy node
}
/*-------------Special-----------------*/

int main(){
	Node* head = nullptr; //head has the memory address of first node of the linked list and this is the only variable which is available to access our linked list so it should not be modified, if modified we loose the starting point to the linked list.

	return 0;
}
