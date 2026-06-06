/***
* Kavya Nemavat
* knemavat
* 2026 Spring CSE101 PA8
* Dictionary.cpp
* Implementation of Dictionary ADT using a red black tree with cursor.
***/

#include <new>
#include <stdexcept>
#include <sstream>
#include "Dictionary.h"

using namespace std;

Dictionary::Node::Node(keyType k, valType v) {
	this->key = k;
	this->val = v;
	this->parent = nullptr;
	this->left = nullptr;
	this->right = nullptr;
	this->color = 0;
}

Dictionary::Dictionary(){
	this->nil = new Node("nil", 0);
	(this->nil)->color = 1;
	this->root = this->nil;
	this->current = this->root;
	this->num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D){
	this->nil = new Node("nil", 0);
	(this->nil)->color = 1;
	this->num_pairs = 0;
	this->root = this->nil;
	this->preOrderCopy(D.root, D.nil);
	this->current = this->root;
}

Dictionary::~Dictionary(){
	this->clear();
	delete(this->nil);
}

void Dictionary::inOrderString(string& s, Node* R) const{
	if (R->left == nullptr || R->right == nullptr) {
		return;
	} else if (R->left != this->nil) {
		this->inOrderString(s, R->left);
	}
	s += R->key + " : " + std::to_string(R->val) + "\n";
	if (R->right != this->nil) {
		this->inOrderString(s, R->right);
	}
}

void Dictionary::preOrderString(string& s, Node* R) const{
	if (R->left == nullptr || R->right == nullptr) {
		return;
	}
	s += R->key;
	if (R->color == 0) {
		s += " (RED)";
	}
	s += "\n";
	if (R->left != this->nil) {
		this->preOrderString(s, R->left);
	}
	if (R->right != this->nil) {
		this->preOrderString(s, R->right);
	}
}

void Dictionary::BST_insert(Node* M){
	if (this->root == this->nil) {
		this->root = new Node(M->key, M->val);
		(this->root)->parent = this->nil;
		(this->root)->left = this->nil;
		(this->root)->right = this->nil;
		(this->root)->color = 1;
	} else {
		Node* N = this->root;
		while (true) {
			if (M->key < N->key && N->left != this->nil) {
				N = N->left;
			} else if(M->key > N->key && N->right != this->nil){
				N = N->right;
			} else {
				break;
			}
		}
		Node* newNode = new Node(M->key, M->val);
		if (M->key < N->key) {
			N->left = newNode;
		} else {
			N->right = newNode;
		}
		newNode->parent = N;
		newNode->left = this->nil;
		newNode->right = this->nil;
		this->RB_InsertFixUp(newNode);
	}
	this->num_pairs++;
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
	if (R == N) {
		return;
	}
	if (this->root == this->nil) {
		this->root = new Node(R->key, R->val);
		(this->root)->parent = this->nil;
		(this->root)->left = this->nil;
		(this->root)->right = this->nil;
		(this->root)->color = 1;
	} else {
		Node* A = this->root;
		while (true) {
			if (R->key < A->key && A->left != this->nil) {
				A = A->left;
			} else if(R->key > A->key && A->right != this->nil){
				A = A->right;
			} else {
				break;
			}
		}
		Node* newNode = new Node(R->key, R->val);
		if (R->key < A->key) {
			A->left = newNode;
		} else {
			A->right = newNode;
		}
		newNode->parent = A;
		newNode->left = this->nil;
		newNode->right = this->nil;
	}
	this->num_pairs++;
	if (R->left->key != "nil") {
		this->preOrderCopy(R->left, N);
	}
	if (R->right->key != "nil") {
		this->preOrderCopy(R->right, N);
	}
}

void Dictionary::postOrderDelete(Node* R){
	if (R == this->nil) {
		return;
	}
	if (R->left != this->nil) {
		this->postOrderDelete(R->left);
	}
	if (R->right != this->nil) {
		this->postOrderDelete(R->right);
	}
	if (this->current == R) {
		this->current = this->nil;
	}
	delete(R);
	this->num_pairs--;
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
	if (R == this->nil || R->key == k) {
		return(R);
	} else if (k > R->key) {
		return(this->search(R->right, k));
	} else {
		return(this->search(R->left, k));
	}
}

Dictionary::Node* Dictionary::findMin(Node* R){
	if (R->left == this->nil || R->left == nullptr) {
		return(R);
	}
	return(this->findMin(R->left));
}

Dictionary::Node* Dictionary::findMax(Node* R){
	if (R->right == this->nil || R->right == nullptr) {
		return(R);
	}
	return(this->findMax(R->right));
}

Dictionary::Node* Dictionary::findNext(Node* N){
	if (N == this->nil || N == this->findMax(this->root)) {
		return(this->nil);
	}
	if (N->right != this->nil) {
		return(this->findMin(N->right));
	} else {
		while (N->key > (N->parent)->key) {
			N = N->parent;
		}
		return(N->parent);
	}
}

Dictionary::Node* Dictionary::findPrev(Node* N){
	if (N == this->nil || N == this->findMin(this->root)) {
		return(this->nil);
	}
	if (N->left != this->nil) {
		return(this->findMax(N->left));
	} else {
		while (N->key < (N->parent)->key) {
			N = N->parent;
		}
		return(N->parent);
	}
}

void Dictionary::LeftRotate(Node* N){
	Node* A = N->right;
	N->right = A->left;
	if (A->left != this->nil) {
		(A->left)->parent = N;
	}
	A->parent = N->parent;
	if (N->parent == this->nil) {
		this->root = A;
	} else if (N == (N->parent)->left){
		(N->parent)->left = A;
	} else {
		(N->parent)->right = A;
	}
	A->left = N;
	N->parent = A;
}

void Dictionary::RightRotate(Node* N){
	Node* A = N->left;
	N->left = A->right;
	if (A->right != this->nil) {
		(A->right)->parent = N;
	}
	A->parent = N->parent;
	if (N->parent == this->nil) {
		this->root = A;
	} else if (N == (N->parent)->right){
		(N->parent)->right = A;
	} else {
		(N->parent)->left = A;
	}
	A->right = N;
	N->parent = A;
}

void Dictionary::RB_InsertFixUp(Node* N){
	while ((N->parent)->color == 0) {
		if (N->parent == ((N->parent)->parent)->left) {
			Node* A = ((N->parent)->parent)->right;
			if (A->color == 0) {
				(N->parent)->color = 1;
				A->color = 1;
				((N->parent)->parent)->color = 0;
				N = (N->parent)->parent;
			} else {
				if (N == (N->parent)->right) {
					N = N->parent;
					this->LeftRotate(N);
				}
				(N->parent)->color = 1;
				((N->parent)->parent)->color = 0;
				this->RightRotate((N->parent)->parent);
			}
		} else {
			Node* A = ((N->parent)->parent)->left;
			if (A->color == 0) {
				(N->parent)->color = 1;
				A->color = 1;
				((N->parent)->parent)->color = 0;
				N = (N->parent)->parent;
			} else {
				if (N == (N->parent)->left) {
					N = N->parent;
					this->RightRotate(N);
				}
				(N->parent)->color = 1;
				((N->parent)->parent)->color = 0;
				this->LeftRotate((N->parent)->parent);
			}
		}
	}
	(this->root)->color = 1;
}

void Dictionary::RB_Transplant(Node* u, Node* v) {
	if (u->parent == this->nil) {
		this->root = v;
	} else if (u == (u->parent)->left){
		(u->parent)->left = v;
	} else {
		(u->parent)->right = v;
	}
	v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node* N){
	while (N != this->root && N->color == 1) {
		if (N == (N->parent)->left) {
			Node* A = (N->parent)->right;
			if (A->color == 0) {
				A->color = 1;
				(N->parent)->color = 0;
				this->LeftRotate(N->parent);
				A = (N->parent)->right;
			}
			if ((A->left)->color == 1 && (A->right)->color == 1) {
				A->color = 0;
				N = N->parent;
			} else {
				if ((A->right)->color == 1) {
					(A->left)->color = 1;
					A->color = 0;
					this->RightRotate(A);
					A = (N->parent)->right;
				}
				A->color = (N->parent)->color;
				(N->parent)->color = 1;
				(A->right)->color = 1;
				this->LeftRotate(N->parent);
				N = this->root;
			}
		} else {
			Node* A = (N->parent)->left;
			if (A->color == 0) {
				A->color = 1;
				(N->parent)->color = 0;
				this->RightRotate(N->parent);
				A = (N->parent)->left;
			}
			if ((A->right)->color == 1 && (A->left)->color == 1) {
				A->color = 0;
				N = N->parent;
			} else {
				if ((A->left)->color == 1) {
					(A->right)->color = 1;
					A->color = 0;
					this->LeftRotate(A);
					A = (N->parent)->left;
				}
				A->color = (N->parent)->color;
				(N->parent)->color = 1;
				(A->left)->color = 1;
				this->RightRotate(N->parent);
				N = this->root;
			}
		}
	}
	N->color = 1;
}

void Dictionary::RB_Delete(Node* N){
	int color = N->color;
	Node* B;
	if (N->left == this->nil) {
		B = N->right;
		this->RB_Transplant(N, N->right);
	} else if (N->right == this->nil) {
		B = N->left;
		this->RB_Transplant(N, N->left);
	} else {
		Node* A = this->findNext(N);
		color = A->color;
		B = A->right;
		if (A->parent == N) {
			B->parent = A;
		} else {
			this->RB_Transplant(A, A->right);
			A->right = N->right;
			(A->right)->parent = A;
		}
		this->RB_Transplant(N, A);
		A->left = N->left;
		(A->left)->parent = A;
		A->color = N->color;
	}
	if (this->current == N) {
		this->current = this->nil;
	}
	delete(N);
	this->num_pairs--;
	if (color == 1) {
		this->RB_DeleteFixUp(B);
	}
}

int Dictionary::size() const{
	return(this->num_pairs);
}

bool Dictionary::contains(keyType k) const {
	return(!(this->search(this->root, k) == this->nil));
}

valType& Dictionary::getValue(keyType k) const {
	if (!(this->contains(k))) {
		throw out_of_range("Dictionary: getValue(): key \"blah\" does not exist");
	}
	return(const_cast<valType&>((this->search(this->root, k))->val));
}

bool Dictionary::hasCurrent() const{
	return(!(this->current == this->nil));
}

keyType Dictionary::currentKey() const{
	if (!(this->hasCurrent())) {
		throw out_of_range("Dictionary: currentKey(): current undefined");
	}
	return((this->current)->key);
}

valType& Dictionary::currentVal() const{
	if (!(this->hasCurrent())) {
		throw out_of_range("Dictionary: currentVal(): current undefined");
	}
	return(const_cast<valType&>((this->current)->val));
}

void Dictionary::clear() {
	this->postOrderDelete(this->root);
	this->root = this->nil;
}

void Dictionary::setValue(keyType k, valType v) {
	if (this->contains(k)) {
		(this->search(this->root, k))->val = v;
	} else {
		Node* N = new Node(k, v);
		this->BST_insert(N);
		delete(N);
	}
}

void Dictionary::remove(keyType k){
	if (!(this->contains(k))) {
		throw out_of_range("Dictionary: remove(): key \"blah\" does not exist");
	}
	Node* N = this->search(this->root, k);
	this->RB_Delete(N);
}

void Dictionary::begin() {
	if (this->num_pairs > 0) {
		this->current = this->findMin(this->root);
	}
}

void Dictionary::end() {
	if (this->num_pairs > 0) {
		this->current = this->findMax(this->root);
	}
}

void Dictionary::next() {
	if (!(this->hasCurrent())) {
		throw out_of_range("Dictionary: next(): current undefined");
	}
	this->current = this->findNext(this->current);
}

void Dictionary::prev() {
	if (!(this->hasCurrent())) {
		throw out_of_range("Dictionary: prev(): current undefined");
	}
	this->current = this->findPrev(this->current);
}

string Dictionary::to_string() const{
	string s;
	this->inOrderString(s, this->root);
	if (!s.empty()) {
		s.pop_back();
	}
	return(s);
}

string Dictionary::pre_string() const{
	string s;
	this->preOrderString(s, this->root);
	return(s);
}

bool Dictionary::equals(const Dictionary& D) const {
	return(this->to_string() == D.to_string());
}

ostream& operator<<( ostream& stream, Dictionary& D){
	return(stream << D.to_string());
}

bool operator==( const Dictionary& A, const Dictionary& B ) {
	return(A.equals(B));
}

Dictionary& Dictionary::operator=( const Dictionary& D) {
	if (this != &D) {
		Dictionary temp = D;
		swap(this->nil, temp.nil);
		swap(this->num_pairs, temp.num_pairs);
		swap(this->root, temp.root);
		swap(this->current, temp.current);
	}
	return(*this);
}
