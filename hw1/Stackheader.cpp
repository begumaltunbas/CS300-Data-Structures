

#ifndef STACK_H
#define STACK_H
#include "Stack.h"
#include <iostream>
#include <sstream>
#include <fstream>




template <class Object>Stack<Object>::Stack() //Constructor
{
    topOfStack = NULL;
    
}

//template <class Object> bool Stack <Object> :: isFull()const
//{
//   return topOfStack!=NULL // false;
//}

template <class Object> bool Stack <Object> :: isEmpty()const
{
   return topOfStack==NULL;
}

template <class Object>const Object & Stack<Object>::top( ) const
{
    /*if ( isEmpty( ) )
        throw Underflow( );*/
    return topOfStack->element;
    
}

template <class Object>void Stack <Object> ::pop()
{
   /* if ( isEmpty( ) )
        throw Underflow( );*/
    ListNode *oldTop = topOfStack;
    topOfStack = topOfStack->next;
    delete oldTop;

}
template <class Object> void Stack <Object>:: push(const  Object & x )
{
    topOfStack = new ListNode( x, topOfStack );
}

template <class Object>void Stack<Object>::makeEmpty( )
{ //delete stack
    while ( ! isEmpty( ) )
        pop( );
}

template <class Object>const Stack<Object> & Stack<Object>::operator=( const Stack<Object> & rhs )
{ //operator overloading of = to use later for deep copy
    if ( this != &rhs )
    {
        makeEmpty( );
        if ( rhs.isEmpty( ) )
            return *this;
        ListNode *rptr = rhs.topOfStack;
        ListNode *ptr  = new ListNode( rptr->element );
        topOfStack = ptr;
        for ( rptr = rptr->next; rptr != NULL; rptr = rptr->next )
            ptr = ptr->next = new ListNode( rptr->element );
        
    }
    return *this;
    
}


template <class Object>Stack<Object>::Stack( const Stack<Object> & rhs )
{ //copy constructor deep copy
    topOfStack = NULL;
    *this = rhs; // deep copy
    
}


template <class Object>Stack<Object>::~Stack( )
{ //destructor
    makeEmpty( );
    
}



#endif