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

   // inOrderString ()
   // Appends a string representation of the tree rooted at R to string s. The
   // string appended consists of: "key : value \n" for each key-value pair
   // in tree R, arranged in order by keys.
   void inOrderString(std::string& s, Node* R) const;

   // preOrderString ()
   // Appends a string representation of the tree rooted at R to s. The appended
   // string consists of keys only, separated by "\n", with the order
   // determined by pre-order tree walk.
   void preOrderString(std::string& s, Node* R) const;

   // preOrderCopy ()
   // Recursively inserts a deep copy of the subtree rooted at R 
   // into this BST. Recursion terminates at Node N.
   void preOrderCopy(Node* R, Node* N);

   // postOrderDelete ()
   // Deletes all Nodes in the subtree rooted at the Node R.
   void postOrderDelete(Node* R);

   // search ()
   // Searches the subtree rooted at R for a Node with key==k.
   // Returns the address of the Node if it exists, nil otherwise.
   Node* search(Node* R, keyType k) const;

   // findMin ()
   // If the subtree rooted at R is not empty, returns a pointer to the
   // leftmost Node in that subtree, otherwise returns nil.
   Node* findMin(Node* R);

   // findMax ()
   // If the subtree rooted at R is not empty, returns a pointer to the
   // rightmost Node in that subtree, otherwise returns nil.
   Node* findMax(Node* R);

   // findNext ()
   // If N does not point to the rightmost Node, returns a pointer to the
   // Node after N in an in-order tree walk. If N points to the rightmost
   // Node, or nil, returns nil.
   Node* findNext(Node* N);

   // findPrev ()
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

   // If the current iterator is not at the last pair, advances current
   // to the next pair (as defined by the order operator < on keys). If 
   // the current iterator is at the last pair, makes current undefined.
   // Pre: hasCurrent()
   void next();

   // prev()
   // If the current iterator is not at the first pair, moves current to  
   // the previous pair (as defined by the order operator < on keys). If 
   // the current iterator is at the first pair, makes current undefined.
   // Pre: hasCurrent()
   void prev();


   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this Dictionary. Consecutive (key, value)
   // pairs are separated by a newline "\n" character, and the items key and value 
   // are separated by the sequence space-colon-space " : ". The pairs are arranged 
   // in order, as defined by the order operator <.
   std::string to_string() const;

   // pre_string()
   // Returns a string consisting of all keys in this Dictionary. Consecutive
   // keys are separated by newline "\n" characters. The key order is given
   // by a pre-order tree walk.
   std::string pre_string() const;

   // equals()
   // Returns true if and only if this Dictionary contains the same (key, value)
   // pairs as Dictionary D.
   bool equals(const Dictionary& D) const;


   // Overloaded Operators ----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of Dictionary D into stream, as defined by
   // member function to_string().
   friend std::ostream& operator<<( std::ostream& stream, Dictionary& D );

   // operator==()
   // Returns true if and only if Dictionary A equals Dictionary B, as defined
   // by member function equals(). 
   friend bool operator==( const Dictionary& A, const Dictionary& B );

   // operator=()
   // Overwrites the state of this Dictionary with state of D, and returns a
   // reference to this Dictionary.
   Dictionary& operator=( const Dictionary& D );

};


#endif
