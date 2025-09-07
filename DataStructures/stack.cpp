#include<iostream>
#include<string>
#include<stack>
#include<vector>
using namespace std;

//Stack is LIFO (Last In, First Out) data structure.

/* ----------------Stack using Array--------------*/
int topIndex = -1;
int n = 0;
int* arr = nullptr;

void push(int x){
	if(topIndex < n){
		arr[++topIndex] = x;
		return;
	}else{
		cout<<"Stack overflow"<<endl;
	}
}

void pop(){
	topIndex--;
}

int top(){
	return arr[topIndex];
}

bool isEmpty(){
	return topIndex == -1;
}
/* ----------------Stack using Array--------------*/

/*------------------Stack using Linked List--------------*/
struct Node{
	int data;
	Node* next;
	Node(int val) : data(val),next(nullptr) {}
};

class Stack{
	Node* topNode;
	public:
		Stack() : topNode(nullptr) {}

		void push(int x){
			Node* newNode = new Node(x);
			newNode->next = topNode;
			topNode = newNode;
		}

		void pop(){
			if(topNode == nullptr){
				cout<<"Stack is Empty"<<endl;
				return;
			}
			Node* temp = topNode;
			topNode = topNode->next;
			delete temp;
		}

		int top(){
			if(topNode == nullptr){
				cout<<"Stack is Empty"<<endl;
				return -1;
			}
			return topNode->data;
		}

		bool isEmpty(){
			return topNode == nullptr;
		}
};
/*------------------Stack using Linked List--------------*/

Node* reverseLinkedList(Node* head){
	if(head == nullptr) return head;
	stack<Node*> st;
	while(head){
		st.push(head);
		head = head->next;
	}
	head = st.top();
	Node* temp = st.top();
	st.pop();
	while(!st.empty()){
		temp->next = st.top();
		st.pop();
		temp = temp->next;
	}
	temp->next = nullptr;
	return head;
}

bool helper(char left,char right){
	if(left == '(' && right == ')') return true;
	else if(left == '{' && right == '}') return true;
	else if(left == '[' && right == ']') return true;
	else return false;
}

bool balancedParentheses(string s){
	stack<char> st;
        int len = s.length();
        for(int i=0;i<len;i++){
            if(s[i] == '(' || s[i] == '{' || s[i] == '['){
                st.push(s[i]);
            }else{
                if(!st.empty()){
                    if(helper(st.top(),s[i])){
                        st.pop();
                        continue;
                    }else{
                        return false;
                    }
                }else{
                    return false;
                }
            }
        }
        if(!st.empty()) return false;
        return true;
}

int eval(int a,int b,char op){
	switch(op){
		case '+' : return a+b;
		case '-' : return a-b;
		case '*' : return a*b;
		case '/' : return a/b;
		default : return 0;
	}
}

int postfixEvaluation(vector<string>& tokens) {
	stack<int> st;
	int len = tokens.size();
	for(int i=0;i<len;i++){
		if(tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/"){
			int right = st.top();
			st.pop();
			int left = st.top();
			st.pop();
			st.push(eval(left,right,tokens[i][0]));
		}else{
			st.push(stoi(tokens[i]));
		}
	}
	return st.top();
}

int prefixEvaluation(vector<string>& tokens){
	stack<int> st;
	int len = tokens.size();
	for(int i=len-1;i>=0;i--){
		if(tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/"){
			int left = st.top();
			st.pop();
			int right = st.top();
			st.pop();
			st.push(eval(left,right,tokens[i][0]));
		}else{
			st.push(stoi(tokens[i]));
		}
	}
	return st.top();
}

bool check(char left,char right){
	if(left == '^') return true;
	else if((left == '*' || left == '/') && (right != '^')) return true;
	else if((left == '+' || left == '-') && (right == '+' || right == '-')) return true;
	else return false;
}

string infixToPostfix(string& s) {
	string ans = "";
	int len = s.size();
	stack<char> st;
	for(int i=0;i<len;i++){
		if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^'){
			while(st.empty() != true && check(st.top(),s[i])){
				ans += st.top();
				st.pop();
			}
			st.push(s[i]);
		}else if(s[i] != '(' && s[i] != ')'){
			ans += s[i];
		}
	}
	while(!st.empty()){
		ans += st.top();
		st.pop();
	}
	return ans;
}

int main(){
	/* ----------------Stack using Array--------------
	cout<<"Enter the size of stack: "<<endl;
	cin>>n;
	arr = new int[n];
	push(2);
	push(3);
	push(4);
	push(5);
	cout<<top()<<endl;
	pop();
	pop();
	cout<<top()<<endl;
	delete[] arr;
	*/
	
	/*------------------Stack using Linked List--------------
	Stack st;
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);
	cout<<st.top()<<endl;
	st.pop();
	st.pop();
	cout<<st.top()<<endl;
	*/
	vector<string> ex = {"-","+","*","2","3","*","5","4","9"};
	cout<<prefixEvaluation(ex)<<endl;
	return 0;
}
