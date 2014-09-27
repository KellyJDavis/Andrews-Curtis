//
//  binary_tree.h
//  Andrews-Curtis Conjecture
//
//  Created by Kelly Davis on 9/17/11.
//
//

#ifndef Andrews_Curtis_Conjecture_binary_tree_h
#define Andrews_Curtis_Conjecture_binary_tree_h


#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>

namespace andrews_curtis
{
    ///
    /// This class encapsulates the functionality of a global binary tree.
    ///
    /// The passed type T must have operator==, operator<, a member m_left of
    /// type T*, and a member m_right of typer T*.
    ///
    template <class T>
    class Binary_tree
    {
    public:
        ///
        /// Inserts an element into the binary tree. This method returns 0
        /// if the inserted element was not previously in the binary tree. 
        /// If the element was already in the binary tree, then a pointer
        /// to the element already in the tree is returned.
        ///
        /// \param element The element to insert into the Binary_tree
        /// \return The equivalent instance already in the tree or 0
        ///
        static T *insert(T *element);
        
        ///
        /// Obtains the size of this binary tree
        ///
        /// \return The size of this binary tree
        ///
        static unsigned long size();
            
        ///
        /// Obtains the length of this binary tree
        ///
        /// \return The length of this binary tree
        ///
        static unsigned long length();
        
        ///
        /// Clear the binary tree of all elements and calls the destructor
        /// of each contained element.
        ///
        static void clear();
        
        /// Mutex for the tree
        static boost::mutex m_mutex;
        
        
    private:
        /// The root of the binary tree
        static T *s_root;
        
        /// The size of the binary tree
        static unsigned long m_size;
        
        /// The length of the binary tree's elements
        static unsigned long m_length;
        
        
    private:
        /// Utility function used by clear
        static void clear(T *element);
    };
}

#include "binary_tree-inl.h"

#endif
