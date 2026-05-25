//-----------------------------------------------------------------------------
// Dictionary.cpp
// Implementation file for Dictionary ADT based on a Binary Search Tree.
//-----------------------------------------------------------------------------
#include "Dictionary.h"
#include <stdexcept>

// Node Constructor
Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

// Dictionary Constructor
Dictionary::Dictionary() {
    nil = new Node("\0", 0);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// Copy Constructor
Dictionary::Dictionary(const Dictionary& D) {
    nil = new Node("\0", 0);
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary() {
    postOrderDelete(root);
    delete nil;
}

// Helper Functions -----------------------------------------------------------

void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        s += R->key + "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R != N) {
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

void Dictionary::postOrderDelete(Node* R) {
    if (R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R == nil || k == R->key) {
        return R;
    } else if (k < R->key) {
        return search(R->left, k);
    } else {
        return search(R->right, k);
    }
}

Dictionary::Node* Dictionary::findMin(Node* R) {
    if (R != nil) {
        while (R->left != nil) {
            R = R->left;
        }
    }
    return R;
}

Dictionary::Node* Dictionary::findMax(Node* R) {
    if (R != nil) {
        while (R->right != nil) {
            R = R->right;
        }
    }
    return R;
}

Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N->right != nil) {
        return findMin(N->right);
    }
    Node* y = N->parent;
    while (y != nil && N == y->right) {
        N = y;
        y = y->parent;
    }
    return y;
}

Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N->left != nil) {
        return findMax(N->left);
    }
    Node* y = N->parent;
    while (y != nil && N == y->left) {
        N = y;
        y = y->parent;
    }
    return y;
}

// Access functions -----------------------------------------------------------

int Dictionary::size() const {
    return num_pairs;
}

bool Dictionary::contains(keyType k) const {
    return search(root, k) != nil;
}

valType& Dictionary::getValue(keyType k) const {
    Node* N = search(root, k);
    if (N == nil) {
        throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
    }
    return N->val;
}

bool Dictionary::hasCurrent() const {
    return current != nil;
}

keyType Dictionary::currentKey() const {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: currentKey(): current undefined");
    }
    return current->key;
}

valType& Dictionary::currentVal() const {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: currentVal(): current undefined");
    }
    return current->val;
}

// Manipulation procedures ----------------------------------------------------

void Dictionary::clear() {
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v) {
    Node* y = nil;
    Node* x = root;
    
    while (x != nil) {
        y = x;
        if (k == x->key) {
            x->val = v; 
            return;
        } else if (k < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    
    Node* z = new Node(k, v);
    z->left = nil;
    z->right = nil;
    z->parent = y;
    
    if (y == nil) {
        root = z;
    } else if (k < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
    num_pairs++;
}

void Dictionary::remove(keyType k) {
    Node* z = search(root, k);
    if (z == nil) {
        throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
    }
    
    if (current == z) {
        current = nil; 
    }
    
    if (z->left == nil) {
        if (z->parent == nil) root = z->right;
        else if (z == z->parent->left) z->parent->left = z->right;
        else z->parent->right = z->right;
        if (z->right != nil) z->right->parent = z->parent;
    } else if (z->right == nil) {
        if (z->parent == nil) root = z->left;
        else if (z == z->parent->left) z->parent->left = z->left;
        else z->parent->right = z->left;
        if (z->left != nil) z->left->parent = z->parent;
    } else {
        Node* y = findMin(z->right);
        if (y->parent != z) {
            if (y->parent == nil) root = y->right;
            else if (y == y->parent->left) y->parent->left = y->right;
            else y->parent->right = y->right;
            if (y->right != nil) y->right->parent = y->parent;
            
            y->right = z->right;
            y->right->parent = y;
        }
        if (z->parent == nil) root = y;
        else if (z == z->parent->left) z->parent->left = y;
        else z->parent->right = y;
        y->parent = z->parent;
        
        y->left = z->left;
        y->left->parent = y;
    }
    delete z;
    num_pairs--;
}

void Dictionary::begin() {
    if (num_pairs > 0) {
        current = findMin(root);
    }
}

void Dictionary::end() {
    if (num_pairs > 0) {
        current = findMax(root);
    }
}

void Dictionary::next() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: next(): current undefined");
    }
    current = findNext(current);
}

void Dictionary::prev() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: prev(): current undefined");
    }
    current = findPrev(current);
}

// Other Functions ------------------------------------------------------------

std::string Dictionary::to_string() const {
    std::string s = "";
    inOrderString(s, root);
    return s;
}

std::string Dictionary::pre_string() const {
    std::string s = "";
    preOrderString(s, root);
    return s;
}

bool Dictionary::equals(const Dictionary& D) const {
    if (num_pairs != D.size()) {
        return false;
    }
    std::string s1 = this->to_string();
    std::string s2 = D.to_string();
    return s1 == s2;
}

// Overloaded Operators -------------------------------------------------------

std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
    return stream << D.to_string();
}

bool operator==(const Dictionary& A, const Dictionary& B) {
    return A.equals(B);
}

Dictionary& Dictionary::operator=(const Dictionary& D) {
    if (this != &D) {
        Dictionary temp = D;
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }
    return *this;
}

