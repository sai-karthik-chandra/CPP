#include<iostream>
#include<queue>
using namespace std;

struct Node{
	int data;
	Node* left;
	Node* right;
	Node(int val) : data(val),left(nullptr),right(nullptr) {}
};

Node* insert(Node* root,int val){
	if(root == nullptr){
		Node* newNode = new Node(val);
		return newNode;
	}
	else if(val < root->data){
		root->left = insert(root->left,val);
	}else{
		root->right = insert(root->right,val);
	}
	return root;
}

bool search(Node* root,int val){
	if(root == nullptr) return false;
	if(root->data == val) return true;
	else if(val < root->data) return search(root->left,val);
	else return search(root->right,val);
}

Node* findMinNode(Node* root){
	if(root == nullptr) return root;
	Node* temp = root;
	while(temp->left){
		temp = temp->left;
	}
	return temp;
}

Node* findMaxNode(Node* root){
	if(root == nullptr) return root;
	Node* temp = root;
	while(temp->right){
		temp = temp->right;
	}
	return temp;
}

int findHeight(Node* root){
	if(root == nullptr) return -1; //since the height of empty tree is -1 because height of leaf node is 0
	return max(findHeight(root->left),findHeight(root->right)) + 1;
}

void levelOrderTraversal(Node* root){
	if(root == nullptr) return;
	queue<Node*> q;
	q.push(root);
	while(!q.empty()){
		Node* curr = q.front();
		cout<<curr->data<<" ";
		if(curr->left != nullptr) q.push(curr->left);
		if(curr->right != nullptr) q.push(curr->right);
		q.pop();
	}
}

void preorderTraversal(Node* root){
	if(root == nullptr) return;
	cout<<root->data<<" ";
	preorderTraversal(root->left);
	preorderTraversal(root->right);
}

void inorderTraversal(Node* root){
	if(root == nullptr) return;
	inorderTraversal(root->left);
	cout<<root->data<<" ";
	inorderTraversal(root->right);
}

void postorderTraversal(Node* root){
	if(root == nullptr) return;
	postorderTraversal(root->left);
	postorderTraversal(root->right);
	cout<<root->data<<" ";
}

bool checkBST(Node* root,int min_val,int max_val){
	if(root == nullptr) return true;

	if(root->data > min_val && root->data<max_val &&
			checkBST(root->left,min_val,root->data) &&
			checkBST(root->right,root->data,max_val))
		return true;
	else
		return false;
}

Node* deleteNode(Node* root,int val){
	if(root == nullptr) return root;
	else if(val < root->data) root->left = deleteNode(root->left,val);
	else if(val > root->data) root->right = deleteNode(root->right,val);
	else{
		//case 1: No child
		if(root->left == nullptr && root->right == nullptr){
			delete root;
			root = nullptr;
		}else if(root->left == nullptr){ //case 2: One right child
			Node* temp = root;
			root = root->right;
			delete temp;
		}else if(root->right == nullptr){ //case 2: One left child
			Node* temp = root;
			root = root->left;
			delete temp;
		}else{
			//case 3: two child
			Node* temp = findMinNode(root->right);
			root->data = temp->data;
			root->right = deleteNode(root->right,temp->data);
		}
	}
	return root;
}

Node* findNode(Node* root,int val){
	if(root == nullptr) return root;
	else if(root->data == val) return root;
	else if(val < root->data) return findNode(root->left,val);
	else return findNode(root->right,val);
}

Node* inorderSuccessor(Node* root,int val){
	if(root == nullptr) return root;
	Node* curr = findNode(root,val);
	if(curr == nullptr) return curr;
	if(curr->right){
		return findMinNode(curr->right);
	}

	Node* successor = nullptr;
	Node* ancestor = root;
	while(ancestor != curr){
		if(curr->data < ancestor->data){
			successor = ancestor;
			ancestor = ancestor->left;
		}else{
			ancestor = ancestor->right;
		}
	}
	return successor;
}

int main(){
	Node* root = nullptr;
	root = insert(root,10);
	root = insert(root,13);
	root = insert(root,9);
	root = insert(root,35);
	root = insert(root,3);
	cout<<search(root,19)<<endl;
	return 0;
}

