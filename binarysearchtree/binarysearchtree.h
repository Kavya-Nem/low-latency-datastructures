#include<iostream>
#include<string>

# ifndef BINARYSEARCHTREE_H_INCLUDE
# define BINARYSEARCHTREE_H_INCLUDE

typedef std::string keyType;
typedef int valType;

class BST {

private:

   struct Node {
      keyType key ;
      valType val ;
      Node* parent ;
      Node* left ;
      Node* right ;
      Node (keyType k, valType v);
   };

   Node* nil ;
   Node* root ;
   Node* current ;
   int num_pairs ;

   // Appends a string representation of the tree rooted at R to string s. The
   // string appended consists of: "key : value \n" for each key-value pair
   // in tree R, arranged in order by keys.
   void inOrderString(std::string& s, Node* R) const;

   // Appends a string representation of the tree rooted at R to s. The appended
   // string consists of keys only, separated by "\n", with the order
   // determined by pre-order tree walk.
   void preOrderString(std::string& s, Node* R) const;

   // Recursively inserts a deep copy of the subtree rooted at R 
   // into this BST. Recursion terminates at Node N.
   void preOrderCopy(Node* R, Node* N);

   // Deletes all Nodes in the subtree rooted at the Node R.
   void postOrderDelete(Node* R);

   // Searches the subtree rooted at R for a Node with key==k.
   // Returns the address of the Node if it exists, nil otherwise.
   Node* search(Node* R, keyType k) const;

   // If the subtree rooted at R is not empty, returns a pointer to the
   // leftmost Node in that subtree, otherwise returns nil.
   Node* findMin(Node* R);

   // If the subtree rooted at R is not empty, returns a pointer to the
   // rightmost Node in that subtree, otherwise returns nil.
   Node* findMax(Node* R);

   // If N does not point to the rightmost Node, returns a pointer to the
   // Node after N in an in-order tree walk. If N points to the rightmost
   // Node, or nil, returns nil.
   Node* findNext(Node* N);

   // If N does not point to the leftmost Node, returns a pointer to the
   // Node before N in an in-order tree walk. If N points to the leftmost
   // Node, or nil, returns nil.
   Node* findPrev(Node* N);

public:

   BST();

   BST(const BST& A);

   ~BST();

   int size() const;

   bool contains (keyType k) const;

   // Returns a reference to the value corresponding to key k .
   // Pre: contains(k)
   valType& getValue (keyType k) const;

   // Returns true if the current iterator is defined, and false otherwise.
   bool hasCurrent() const;

   // Pre: hasCurrent()
   keyType currentKey() const;

   // Returns a reference to the current iterator's value.
   // Pre: hasCurrent()
   valType& currentVal() const;

   void clear();

   // If a pair with key==k exists, overwrites the corresponding value with
   // v, otherwise inserts the new pair (k, v).
   void setValue(keyType k, valType v);

   // Pre: contains(k).
   void remove(keyType k);

   // If non-empty, places current iterator at the first (key, value) pair
   // (as defined by the order operator < on keys), otherwise nothing.
   void begin ();

   // If non-empty, places current iterator at the last (key, value) pair
   // (as defined by the order operator < on keys), otherwise nothing.
   void end ();

   // If the current iterator is at last pair, makes current undefined.
   // Pre: hasCurrent()
   void next() ;

   // If the current iterator is at first pair, makes current undefined.
   // Pre: hasCurrent()
   void prev();

   // Consecutive (key, value) pairs are separated by a newline "\n" character.
   std::string to_string() const;

   // Returns a string consisting of all keys in this BST. Consecutive
   // keys are separated by "\n".
   std::string pre_string() const;

   // Returns true if and only if this BST contains the same
   // (key, value) pairs as BST A contains too.
   bool equals(const BST& A) const;
   
   friend std::ostream& operator<<(std::ostream& stream, BST& A);
 
   friend bool operator==( const BST& A, const BST& B);

   // Returns reference to this BST.
   BST& operator=( const BST& A );

};

#endif
