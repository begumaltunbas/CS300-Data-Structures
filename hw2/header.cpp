//#ifndef HEADER_H
//#define HEADER_H
#include "Header1233.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;


template <class Key,class Value>
void AvlTree<Key,Value>::insert ( const Key & x,const Value  &theval,AvlNode<Key,Value> * & t ) const // private insert
{
	if ( t == NULL )
		t = new AvlNode<Key,Value>( x, theval,NULL, NULL );

	else if ( x < t->word ) {
		// X should be inserted to the left tree!
		insert( x, theval,t->left );
		// Check if the left tree is out of balance (left subtree grew in height!)
		if ( height( t->left ) - height( t->right ) == 2 )
		{
			if ( x < t->left->word )  // X was inserted to the left-left subtree!
				rotateWithLeftChild( t );
			else			     // X was inserted to the left-right subtree!
				doubleWithLeftChild( t );
		}
	}

	else if( t->word < x )
	{    // Otherwise X is inserted to the right subtree
		insert( x, theval,t->right );
		if ( height( t->right ) - height( t->left ) == 2 )
		{
			// height of the right subtree increased
			if ( t->right->word < x )
			{
				// X was inserted to right-right subtree
				rotateWithRightChild( t );
			}
			else // X was inserted to right-left subtree
			{
				doubleWithRightChild( t );
			}
		}
		else
		{;}  // Duplicate; do nothing


		t->height = max( height( t->left ), height( t->right ) ) + 1;
	}
}


template <class Key,class Value>void AvlTree<Key,Value>::insert( const Key & x,const Value &theval ) //insert public
{

	insert( x,theval,root );

}



template <class Key,class Value>AvlNode<Key,Value> *AvlTree<Key,Value>::find( const Key & x, AvlNode<Key,Value> * t ) const //find priv
{

	if ( t == NULL )
		return NULL;

	else if( x < t->word )
		return find( x, t->left );

	else if( t->word < x )
		return find( x, t->right );

	else
		return t; // Match 
	//
}


template <class Key,class Value>const Key & AvlTree<Key,Value>::find( const Key & x ) const //find public

{
	return elementAt( find( x, root ) );

}


template <class Key,class Value>
int AvlTree<Key,Value>::max( int lhs, int rhs ) const
{
	if (lhs > rhs)
		return lhs;

	return rhs;            
}



template <class Key,class Value>
int AvlTree<Key,Value>::height( AvlNode<Key,Value> *t ) const
{
	if (t == NULL)
		return -1;

	return t->height;
}



template <class Key,class Value>
void AvlTree<Key,Value>::doubleWithRightChild
	( AvlNode<Key,Value> * & k1 ) const
{
	rotateWithLeftChild( k1->right );
	rotateWithRightChild( k1 );
}


template <class Key,class Value>
void AvlTree<Key,Value>::doubleWithLeftChild
	( AvlNode<Key,Value> * & k3 ) const
{
	rotateWithRightChild( k3->left );
	rotateWithLeftChild( k3 );
}

template <class Key,class Value>
void AvlTree<Key,Value>::rotateWithRightChild
	( AvlNode<Key,Value> * & k1 ) const
{
	AvlNode<Key,Value> *k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
	k2->height = max( height( k2->right ), k1->height ) + 1;
	k1 = k2;
}

template <class Key,class Value>
void AvlTree<Key,Value>::rotateWithLeftChild( 
	AvlNode<Key,Value> * & k2 ) const
{
	AvlNode<Key,Value> *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
	k1->height = max( height( k1->left ), k2->height ) + 1;
	k2 = k1;
}


template <class Key,class Value>
AvlNode<Key,Value> *AvlTree<Key,Value>::findMin( AvlNode<Key,Value> *t )const //find min priv
{

	if( t == NULL )

		return NULL;

	if( t->left == NULL )

		return t;

	return findMin( t->left );
}


template <class Key,class Value>const Key & AvlTree<Key,Value>::findMin( ) const //find min public
{
	return elementAt( findMin( root ) );
}







template<class Key,class Value> AvlNode<Key,Value>*AvlTree<Key,Value>::findMax( AvlNode<Key,Value> *t )const // find max priv
{
	if( t != NULL )

		while( t->right != NULL )

			t = t->right;

	return t;

}



template <class Key,class Value>const Key & AvlTree<Key,Value>::findMax( ) const //find max public

{
	return elementAt( findMax( root ) );

}






template <class Key,class Value >void AvlTree<Key,Value>::printTree( ) const //public print tree
{

	if( isEmpty( ) )

		cout << "Empty tree" << endl;

	else

		printTree( root );
}


template<class Key,class Value>void AvlTree<Key,Value>::printTree( AvlNode<Key,Value> * t ) const // private print tree
{
	if ( t != NULL )
	{
		printTree( t->left );
		cout << t->word << endl;
		printTree( t->right );
	}
}




template <class Key,class Value> void AvlTree<Key,Value>::makeEmpty( ) //make empty public
{
	makeEmpty( root );

}



template <class Key,class Value> void AvlTree<Key,Value>::makeEmpty( AvlNode<Key,Value> * & t ) const //make empty priv

{
	if( t != NULL )
	{

		makeEmpty( t->left );

		makeEmpty( t->right );

		delete t;

	}

	t = NULL;
}




template<class Key,class Value> bool AvlTree<Key,Value>::isEmpty()const  //ben yazdım isempty 
{

	if (root==NULL)
		return true;
	else 
		return false;
}


template <class Key,class Value> AvlNode<Key,Value> *AvlTree<Key,Value>::clone( AvlNode<Key,Value> * t ) const
{
	if ( t == NULL )
		return NULL;
	else
		return new AvlNode<Key,Value> 
		( t->word, 
		clone( t->left ), 
		clone( t->right ) );
}




template <class Key,class Value> AvlTree<Key,Value>::AvlTree(const Key & notFound, const Value &value ) :
ITEM_NOT_FOUND( notFound ), root( NULL )
{

}




template <class Key,class Value> const Key & AvlTree<Key,Value>::elementAt( AvlNode<Key,Value> *t ) const
{
    return t == NULL ? ITEM_NOT_FOUND  : t->word;
}




template<class Key,class Value>
Value * AvlTree<Key,Value>::getNode(Key & element)
{

    return &find(element,root)->val;
}



