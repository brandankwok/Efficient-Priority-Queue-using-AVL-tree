#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include "PQ.h"
#include <algorithm>
#include <iostream> 
using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// ID findMin( )  --> Return smallest item
// ID findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename ID>
class AvlTree
{
    template <class AVLTree>friend class PQ;
    
  public:

    

    AvlTree( ) : root{ nullptr }
      { }
    
    AvlTree( const AvlTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    AvlTree( AvlTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    ~AvlTree( )
    {
        makeEmpty( );
    }

    /**
     * Deep copy.
     */
    AvlTree & operator=( const AvlTree & rhs )
    {
        AvlTree copy = rhs;
        swap( *this, copy );
        return *this;
    }
        
    /**
     * Move.
     */
    AvlTree & operator=( AvlTree && rhs )
    {
        swap( root, rhs.root );
        
        return *this;
    }
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const ID & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->id_num;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const ID & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->id_num;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const ID & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }

    void displayTree(ostream & out = cout) const {
        if(isEmpty())
            out << "Empty tree" << endl;
        else
            displayTree(root, 0, out);
    }

    void displayLinks(ostream & out = cout) const
    {
        if(isEmpty())
            out << "Empty tree" << endl;
        else
            displayLinks(root, 0, out);
    }

    int height() const 
    {
        return height(root);
    }

    int depth(const ID & x) const
    {
        return depth(x, root);
    }


    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void* insert( const ID & x, int index )
    {
        void* ptr = insert( x, index, root );
        return ptr;
    }
     
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const ID & x )
    {
        remove( x, root );
    }

    int findIndex(const ID & x) {
        return findIndex(x, root);
    }

  private:

    struct AvlNode
    {
        ID id_num;
        int index;
        AvlNode   *left;
        AvlNode   *right;
        int       height;

        AvlNode( const ID & ele, int i, AvlNode *lt, AvlNode *rt, int h = 0 )
          : id_num{ ele }, index{ i }, left{ lt }, right{ rt }, height{ h } { }
        
        // AvlNode( ID && ele, int i, AvlNode *lt, AvlNode *rt, int h = 0 )
        //   : id_num{ move( ele ) }, index{ i }, left{ lt }, right{ rt }, height{ h } { }
    };

    AvlNode *root;

    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void* insert( const ID & x, int index, AvlNode * & t )
    {
        void* r;
        if( t == nullptr ) {
            t = new AvlNode{ x, index, nullptr, nullptr };
            r = t;
            // cout << t->id_num << " " << t->index << endl;
        }
        else if( x < t->id_num )
            r = insert( x, index, t->left );
        else if( t->id_num < x )
            r = insert( x, index, t->right );
        
        balance( t );
        return r;
    }

    int findIndex( const ID & x, AvlNode * & t ) {

        if( t == nullptr )
            return -1;
        else if( x < t->id_num )
            return findIndex( x, t->left );
        else if( t->id_num < x )
            return findIndex( x, t->right );
        else
            return t->index;    
    }
     
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const ID & x, AvlNode * & t )
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
        
        if( x < t->id_num )
            remove( x, t->left );
        else if( t->id_num < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->id_num = findMin( t->right )->id_num;
            remove( t->id_num, t->right );
        }
        else
        {
            AvlNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
        
        balance( t );
    }
    
    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t )
    {
        if( t == nullptr )
            return;
        
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        else
        if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
                
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }
    

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode* findMin( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const ID & x, AvlNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->id_num )
            return contains( x, t->left );
        else if( t->id_num < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const ID & x, AvlNode *t ) const
    {
        while( t != nullptr )
            if( x < t->index )
                t = t->left;
            else if( t->index < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( AvlNode *t ) const
    {
        if( t != nullptr )
        {
            printTree( t->left );
            cout << "ID: " << t->id_num << " PQ Index: " << t->index << endl;
            printTree( t->right );
        }
    }

    void displayTree (AvlNode *t, int depth, ostream & out) const {
        const int SHIFT = 4;
        if (t!= nullptr) {
            for (int i = 0; i < SHIFT*depth; i++) {out << " ";}
            out << t->id_num << endl;
            displayTree (t->left, depth+1, out);
            displayTree (t->right, depth+1, out);
        }
    }

    void displayLinks( AvlNode *t, int depth, ostream & out ) const
    {
        const int SHIFT = 4 ;
        if( t != nullptr )
        {
            for( int i = 0 ; i < SHIFT*depth ; i++ ){ out << " " ; }
            out << t->index << ") @:" << &t->index;
            if (t->left == nullptr)
                out << "  L:" << 0 << " R:" << t->right << endl;
            else if (t->right == nullptr)
                out << "  L:" << t->left << " R:" << 0 << endl;
            else 
                out << "  L:" << t->left << " R:" << t->right << endl;
            displayLinks( t->left, depth+1, out );
            displayLinks( t->right, depth+1, out );
        }
    }

    int depth (const ID & x, AvlNode *t) const
    {
        if (t == nullptr)
            return 0;

        else if (x > t->id_num)
            return 1+depth(x, t->right);
        
        else if (x < t->id_num)
            return 1+depth(x, t->left);

        else 
            return 0;
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->id_num, clone( t->left ), clone( t->right ), t->height };
    }
        // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height( AvlNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }
};

#endif
