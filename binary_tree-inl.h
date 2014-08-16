//
//  binary_tree-inl.h
//  Andrews-Curtis Conjecture
//
//  Created by Kelly Davis on 9/17/11.
//
//

#ifndef Andrews_Curtis_Conjecture_binary_tree_inl_h
#define Andrews_Curtis_Conjecture_binary_tree_inl_h


namespace andrews_curtis
{	
	// Define Binary_tree<T>::s_root
    template <class T>
    T *Binary_tree<T>::s_root = 0; 
	
    // Define Binary_tree<T>::m_mutex
    template <class T>
    boost::mutex Binary_tree<T>::m_mutex;
    
    // Define Binary_tree<T>::m_size
    template <class T>
    unsigned long Binary_tree<T>::m_size = 0;
    
    // Define Binary_tree<T>::m_length
    template <class T>
    unsigned long Binary_tree<T>::m_length = 0;
    
    
    template <class T>
    inline T *Binary_tree<T>::insert(T *element)
    {
    		// Lock m_mutex
    		boost::lock_guard<boost::mutex> lock_guard(m_mutex);
    		
    		// If the tree is empty, add element
        if(!s_root)
        {
            // Set s_root
            s_root = element;
            
            // Increment m_size
            ++m_size;
            
            // Increment m_length
            m_length += element->get_length();
            
            // Return
            return 0;
        }
        
        // Set the current element to s_root
        T *current_element = s_root;
        
        // Loop forever
        while(true)
        {
            // If element == current_element, element is already there
            if(*element == *current_element)
                return current_element;
			
    			  // If element < current_element
            if(*element < *current_element)
            {
                // If current_element has no left child
                if(!current_element->m_left)
                {
                    // Insert element as the left child of current_element
                    current_element->m_left = element;
                    
                    // Increment m_size
                    ++m_size;
					
        					  // Increment m_length
        					  m_length += element->get_length();
        					
        					  // Return 0 indicating the element was inserted
                    return 0;
                }
                else
                {
                    // If current_element has a left child, use it as current_element
                    current_element = current_element->m_left;
					
					          // Continue to while
                    continue;
                }
            }
            else
            {
                // If current_element has no right child
                if(!current_element->m_right)
                {
                    // Insert element as the right child of current_element
                    current_element->m_right = element;
                    
                    // Increment m_size
                    ++m_size;
					
        					  // Increment m_length
        					  m_length += element->get_length();
        					
        					  // Return 0 indicating the element was inserted
                    return 0;
                }
                else
                {
                    // If current_element has a right child, use it as current_element
                    current_element = current_element->m_right;
					
					          // Continue to while
                    continue;
                }
            }
        }
    }
    
	template <class T>
	inline unsigned long Binary_tree<T>::size()
	{
		// Lock m_mutex
		boost::lock_guard<boost::mutex> lock_guard(m_mutex);
		
		// Return the size
		return m_size;
	}
    
	template <class T>
	inline unsigned long Binary_tree<T>::length()
	{
		// Lock m_mutex
		boost::lock_guard<boost::mutex> lock_guard(m_mutex);
		
		// Return the size
		return m_length;
	}
	
    template <class T>
    inline void Binary_tree<T>::clear()
    {
		// Lock m_mutex
		boost::lock_guard<boost::mutex> lock_guard(m_mutex);
		
        // Clear s_root
        clear(s_root);
        
        // Set s_root to 0
        s_root = 0;
        
        // Reset m_size
        m_size = 0;
        
        // Reset m_length
        m_length = 0;
    }
    
    template <class T>
    void Binary_tree<T>::clear(T *element)
    {
        // If !element return to caller
        if(!element)
            return;
        
        // Obtain the root of element's left subtree
        T *left = element->m_left;
        
        // Obtain the root of element's right subtree
        T *right = element->m_right;
        
        // Delete element
        delete element;
        
        // Clear the left and right subtrees
        clear(left);
        clear(right);
    }
}

#endif
