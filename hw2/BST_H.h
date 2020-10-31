#ifndef BST_h
#define BST_h


#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;


template <class Key,class Value>
class BstTree;

template <class Key,class Value>
class BstNode
{
	Key 	word;
	Value  val ;
	BstNode   		*left;
	BstNode   		*right;
	int        		height;

	BstNode( const Key & key, const Value & word_item,
		BstNode *lt, BstNode *rt, int h = 0 )
		: word( key ),val(word_item) ,left( lt ), right( rt ), height( h ) { }

	friend class BstTree<Key,Value>;
};
//USTU DUZENLE


//template <class Comparable>
template <class Key, class Value>
class BstTree
{
public:
	explicit BstTree( const Key & notFound ,const Value &value); //yaptım galiba ???
	//AvlTree( const AvlTree & rhs );
	//~AvlTree( );

	const Key & findMin( ) const; //done
	const Key & findMax( ) const; //done
	const Key & find( const Key & x ) const; //done
	bool isEmpty( ) const; //ben yazdım 
	void printTree( ) const; //done

	void makeEmpty( ); //done
	void insert( const Key & x ,const Value &theval); //done
	void remove( const Key & x ); //SEN YAZ!!!!!!
	
	
	

	Value * getNode(Key & element); 
	//const AvlTree & operator=( const AvlTree & rhs ); // bu yok!!

private:
	BstNode<Key,Value> *root;
	const Key ITEM_NOT_FOUND;

	const Key & elementAt( BstNode<Key,Value> *t ) const;

	void insert( const Key & x, const Value &theval ,BstNode<Key,Value> * & t ) const; //UGRAS BRACES BOZUK-- done
	void remove(const Key & x, BstNode<Key,Value> * & t ) const; // SEN YAZ!!!!!!!!!!!!!!!!

	BstNode<Key,Value> * findMin( BstNode<Key,Value> *t ) const; //done
	BstNode<Key,Value> * findMax( BstNode<Key,Value> *t ) const; //done
	BstNode<Key,Value> * find( const Key & x, BstNode<Key,Value> *t ) const;  //done recursion hali

	void makeEmpty( BstNode<Key,Value> * & t ) const; //done
	void printTree( BstNode<Key,Value> *t ) const; //done
	BstNode<Key,Value> * clone( BstNode<Key,Value> *t ) const;

	// Avl manipulations
	int height( BstNode<Key,Value> *t ) const; //done
	int max( int lhs, int rhs ) const; //done
//	void rotateWithLeftChild( BstNode<Key,Value> * & k2 ) const;  //done
//	void rotateWithRightChild( BstNode<Key,Value> * & k1 ) const;// done
//	void doubleWithLeftChild( BstNode<Key,Value> * & k3 ) const;//done
//	void doubleWithRightChild( BstNode<Key,Value> * & k1 ) const;//done
};

//#include "headercpp.cpp"
//#endif


//#include <iostream>
//#include <vector>
//#include <string>

//using namespace std;


//template <class Key,class Value>
//void BstTree<Key,Value>::insert ( const Key & x,const Value  &theval,BstNode<Key,Value> * & t ) const // private insert
//{
//    if ( t == NULL )
//        t = new BstNode<Key,Value>( x, theval,NULL, NULL );
//
//    else if ( x < t->word ) {
//        // X should be inserted to the left tree!
//        insert( x, theval,t->left );
//        // Check if the left tree is out of balance (left subtree grew in height!)
//        if ( height( t->left ) - height( t->right ) == 2 )
//        {
//            if ( x < t->left->word )  // X was inserted to the left-left subtree!
//                rotateWithLeftChild( t );
//            else                 // X was inserted to the left-right subtree!
//                doubleWithLeftChild( t );
//        }
//    }
//
//    else if( t->word < x )
//    {    // Otherwise X is inserted to the right subtree
//        insert( x, theval,t->right );
//        if ( height( t->right ) - height( t->left ) == 2 )
//        {
//            // height of the right subtree increased
//            if ( t->right->word < x )
//            {
//                // X was inserted to right-right subtree
//                rotateWithRightChild( t );
//            }
//            else // X was inserted to right-left subtree
//            {
//                doubleWithRightChild( t );
//            }
//        }
//        else
//        {;}  // Duplicate; do nothing
//
//
//        t->height = max( height( t->left ), height( t->right ) ) + 1;
//    }
//}
//
//
//template <class Key,class Value>void AvlTree<Key,Value>::insert( const Key & x,const Value &theval ) //insert public
//{
//
//    insert( x,theval,root );
//
//}


template <class Key,class Value>void BstTree<Key,Value> :: insert (const Key &x, const Value &theval) //insert public
{
    
    insert (x,theval,root) ;
}






template <class Key,class Value>void BstTree<Key,Value> :: insert (const Key &x, const Value  &theval, BstNode<Key,Value> *&t)const //insert priv
{
    if (t==NULL)
        t=new BstNode<Key,Value>(x,theval,NULL,NULL) ;
    else if (x<t->word)
        insert (x,theval,t->left);
    else if (t->word<x)
        insert (x,theval,t->right) ;
    else
        ;
    
    
}




template <class Key,class Value>BstNode<Key,Value> *BstTree<Key,Value>::find( const Key & x, BstNode<Key,Value> * t ) const //find priv
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


template <class Key,class Value>const Key & BstTree<Key,Value>::find( const Key & x ) const //find public

{
    return elementAt( find( x, root ) );

}


template <class Key,class Value>
int BstTree<Key,Value>::max( int lhs, int rhs ) const
{
    if (lhs > rhs)
        return lhs;

    return rhs;
}



template <class Key,class Value>
int BstTree<Key,Value>::height( BstNode<Key,Value> *t ) const
{
    if (t == NULL)
        return -1;

    return t->height;
}



//template <class Key,class Value>
//void BstTree<Key,Value>::doubleWithRightChild
//    ( AvlNode<Key,Value> * & k1 ) const
//{
//    rotateWithLeftChild( k1->right );
//    rotateWithRightChild( k1 );
//}

//
//template <class Key,class Value>
//void AvlTree<Key,Value>::doubleWithLeftChild
//    ( AvlNode<Key,Value> * & k3 ) const
//{
//    rotateWithRightChild( k3->left );
//    rotateWithLeftChild( k3 );
//}
//
//template <class Key,class Value>
//void AvlTree<Key,Value>::rotateWithRightChild
//    ( AvlNode<Key,Value> * & k1 ) const
//{
//    AvlNode<Key,Value> *k2 = k1->right;
//    k1->right = k2->left;
//    k2->left = k1;
//    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
//    k2->height = max( height( k2->right ), k1->height ) + 1;
//    k1 = k2;
//}
//
//template <class Key,class Value>
//void AvlTree<Key,Value>::rotateWithLeftChild(
//    AvlNode<Key,Value> * & k2 ) const
//{
//    AvlNode<Key,Value> *k1 = k2->left;
//    k2->left = k1->right;
//    k1->right = k2;
//    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
//    k1->height = max( height( k1->left ), k2->height ) + 1;
//    k2 = k1;
//}


template <class Key,class Value>
BstNode<Key,Value> *BstTree<Key,Value>::findMin( BstNode<Key,Value> *t )const //find min priv
{

    if( t == NULL )

        return NULL;

    if( t->left == NULL )

        return t;

    return findMin( t->left );
}


template <class Key,class Value>const Key & BstTree<Key,Value>::findMin( ) const //find min public
{
    return elementAt( findMin( root ) );
}







template<class Key,class Value> BstNode<Key,Value>*BstTree<Key,Value>::findMax( BstNode<Key,Value> *t )const // find max priv
{
    if( t != NULL )

        while( t->right != NULL )

            t = t->right;

    return t;

}



template <class Key,class Value>const Key & BstTree<Key,Value>::findMax( ) const //find max public

{
    return elementAt( findMax( root ) );

}






template <class Key,class Value >void BstTree<Key,Value>::printTree( ) const //public print tree
{

    if( isEmpty( ) )

        cout << "Empty tree" << endl;

    else

        printTree( root );
}


template<class Key,class Value>void BstTree<Key,Value>::printTree( BstNode<Key,Value> * t ) const // private print tree
{
    if ( t != NULL )
    {
        printTree( t->left );
        cout << t->word << endl;
        printTree( t->right );
    }
}




template <class Key,class Value> void BstTree<Key,Value>::makeEmpty( ) //make empty public
{
    makeEmpty( root );

}



template <class Key,class Value> void BstTree<Key,Value>::makeEmpty( BstNode<Key,Value> * & t ) const //make empty priv

{
    if( t != NULL )
    {

        makeEmpty( t->left );

        makeEmpty( t->right );

        delete t;

    }

    t = NULL;
}




template<class Key,class Value> bool BstTree<Key,Value>::isEmpty()const  //ben yazdım isempty
{

    if (root==NULL)
        return true;
    else
        return false;
}


template <class Key,class Value> BstNode<Key,Value> *BstTree<Key,Value>::clone( BstNode<Key,Value> * t ) const
{
    if ( t == NULL )
        return NULL;
    else
        return new BstNode<Key,Value>
        ( t->word,
        clone( t->left ),
        clone( t->right ) );
}




template <class Key,class Value> BstTree<Key,Value>::BstTree(const Key & notFound, const Value &value ) :
ITEM_NOT_FOUND( notFound ), root( NULL )
{

}




template <class Key,class Value> const Key & BstTree<Key,Value>::elementAt( BstNode<Key,Value> *t ) const
{
    return t == NULL ? ITEM_NOT_FOUND  : t->word;
}




template<class Key,class Value>
Value * BstTree<Key,Value>::getNode(Key & element)
{

    return &find(element,root)->val;
}










#endif

