# include <new>
# include <stdexcept>
# include <sstream>
# include "binarysearchtree.h"

using namespace std;

BST::Node::Node(keyType k, valType v) {
	this->key = k;
	this->val = v;
	this->parent = nullptr;
	this->left = nullptr;
	this->right = nullptr;
}

BST::BST(){
	this->nil = new Node("nil", 0);
	this->root = this->nil;
	this->current = this->root;
	this->num_pairs = 0;
}

BST::BST(const BST& A){
	this->nil = new Node("nil", 0);
	this->num_pairs = 0;
	this->root = this->nil;
	this->preOrderCopy (A.root, A.nil);
	this->current = this->root;
}

BST::~BST(){
	this->clear();
	delete(this->nil);
}

void BST::inOrderString(string& s, Node* R) const{
	if (R->left == nullptr || R->right == nullptr) {
		return;
	} else if (R->left != this->nil){
		this->inOrderString (s, R->left);
	}
	s += R->key + " : " + ::to_string(R->val) + "\n" ;
	if (R->right != this->nil) {
		this->inOrderString (s, R->right);
	}
}

void BST::preOrderString(string& s, Node* R) const{
	if (R->left == nullptr || R->right == nullptr) {
		return;
	}
	s += R->key + "\n";
	if (R->left != this->nil) {
		this->preOrderString (s, R->left);
	}
	if (R->right != this->nil) {
		this->preOrderString (s, R->right);
	}
}

void BST::preOrderCopy(Node* R, Node* N) {
	if (R == N) {
		return;
	}
	this->setValue (R->key, R->val);
	if (R->left->key != "nil") {
		this->preOrderCopy (R->left, N);
	}
	if (R->right->key != "nil") {
		this->preOrderCopy (R->right, N);
	}
}

void BST::postOrderDelete(Node* R){
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

Node* BST::search(Node* R, keyType k) const{
	if (R == this->nil || R->key == k) {
		return(R);
	} else if (k > R->key){
		return(this->search (R->right, k));
	} else {
		return(this->search (R->left, k));
	}
}

Node* BST::findMin(Node* R){
	if (R->left == this->nil || R->left == nullptr) {
		return(R);
	}
	return(this->findMin(R->left));
}

Node* BST::findMax(Node* R){
	if (R->right == this->nil || R->right == nullptr) {
		return(R);
	}
	return(this->findMax(R->right));
}

Node* BST::findNext(Node* N){
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

Node* BST::findPrev(Node* N){
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

int BST::size() const{
	return(this->num_pairs);
}

bool BST::contains(keyType k) const {
	if (this->search(this->root, k) == this->nil) {
		return(false);
	} else {
		return(true);
	}
}

valType& BST::getValue(keyType k) const {
	if (!(this->contains(k))) {
		throw out_of_range("Binary Search Tree: getValue(): key "+ k +" does not exist");
	}
	return(const_cast<valType&>((this->search (this->root, k))->val));
}

bool BST::hasCurrent() const{
	if (this->current == this->nil) {
		return(false);
	} else {
		return(true);
	}
}

keyType BST::currentKey() const{
	if (!(this->hasCurrent())) {
		throw out_of_range("Binary Search Tree: currentKey(): current key is undefined");
	}
	return((this->current)->key);
}

valType& BST::currentVal() const{
	if (!(this->hasCurrent())) {
		throw out_of_range("Binary Search Tree: currentVal(): current key is undefined");
	}
	return(const_cast<valType&>((this->current)->val));
}

void BST::clear() {
	this->postOrderDelete(this->root);
	this->root = this->nil;
}

void BST::setValue(keyType k, valType v) {
	if (this->contains(k)) {
		(this->search (this->root, k))->val = v;
	} else {
		if (this->root == this->nil) {
			this->root = new Node(k, v);
			this->num_pairs++;
			this->root->parent = this->nil;
			this->root->left = this->nil;
			this->root->right = this->nil;
		} else {
			Node* N = this -> root;
			while (true) {
				if (k < N->key && N->left != this->nil) {
					N = N->left;
				} else if(k > N->key && N->right != this->nil){
					N = N->right;
				} else {
					break;
				}
			}
			Node* newNode = new Node(k, v);
			this->num_pairs++;
			if (k < N->key) {
				N->left = newNode;
			} else {
				N->right = newNode;
			}
			newNode->parent = N;
			newNode->left = this->nil;
			newNode->right = this->nil;
		}
	}
}

void BST::remove(keyType k){
	if (!(this->contains(k))) {
		throw out_of_range("Binary Search Tree: remove(): key "+ k +" does not exist");
	}
	Node* N = this->search(this->root, k);
	if (N->left == this->nil && N->right == this->nil) {
		if ((N->parent)->left == N) {
			(N->parent)->left = this->nil;
		}
		if ((N->parent)->right == N) {
			(N->parent)->right = this->nil;
		}
		if (N == this->root) {
			this->root = this->nil;
		}
	} else if (N->left == this->nil){
		if ((N->parent)->left == N) {
			(N->parent)->left = N->right;
		}
		if ((N->parent)->right == N) {
			(N->parent)->right = N->right;
		}
		(N->right)->parent = N->parent;
		if (N == this->root) {
			this->root = N->right;
		}
	} else if (N->right == this->nil){
		if ((N->parent)->left == N) {
			(N->parent)->left = N->left;
		}
		if ((N->parent)->right == N) {
			(N->parent)->right = N->left;
		}
		(N->left)->parent = N->parent;
		if (N == this->root) {
			this->root = N->left;
		}
	} else {
		Node* next = this -> findNext(N);
		if ((N->parent)->left == N) {
			(N->parent)->left = next;
		}
		if ((N->parent)->right == N) {
			(N->parent)->right = next;
		}
		if (next->parent != N) {
			(next->parent)->left = next->right;
			if (next->right != this->nil) {
				(next->right)->parent = next->parent;
			}
			next->right = N->right;
			(next->right)->parent = next;
		}
		next->parent = N->parent;
		next->left = N->left;
		(next->left)->parent = next;
		if (N == this->root) {
			this->root = next;
		}
	}
	if (this->current == N) {
		this->current = this->nil;
	}
	delete(N);
	this->num_pairs--;
}

void BST::begin() {
	if (this->num_pairs > 0) {
		this->current = this->findMin(this->root);
	}
}

void BST::end() {
	if (this->num_pairs > 0) {
		this->current = this->findMax(this->root);
	}
}

void BST::next() {
	if (!(this->hasCurrent())) {
		throw out_of_range("Binary Search Tree: next(): current key is undefined");
	}
	this->current = this->findNext(this->current);
}

void BST::prev() {
	if (!(this->hasCurrent())) {
		throw out_of_range("Binary Search Tree: prev(): current key is undefined");
	}
	this->current = this->findPrev(this->current);
}

string BST::to_string() const{
	string s ;
	this->inOrderString (s, this->root);
	return(s);
}

string BST::pre_string() const{
	string s ;
	this->preOrderString (s, this->root);
	return(s);
}

bool BST::equals(const BST& A) const {
	return(this->to_string() == A.to_string());
}

ostream& operator<<( ostream& stream, BST& A){
	return(stream << A.to_string());
}

bool operator==( const BST& A, const BST& B) {
	return(A.equals(B));
}

BST& BST::operator=( const BST& A) {
	if (this != &A) {
		BST temp = A ;
		swap (this->nil, temp.nil);
		swap (this->num_pairs, temp.num_pairs);
		swap (this->root, temp.root);
		swap (this->current, temp.current);
	}
	return(*this);
}
