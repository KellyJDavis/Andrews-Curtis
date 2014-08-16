//
//  balanced_presentation-inl.h
//  Andrews-Curtis Conjecture
//
//  Created by Kelly Davis on 8/20/11.
//
//

#ifndef Andrews_Curtis_Conjecture_balanced_presentation_inl_h
#define Andrews_Curtis_Conjecture_balanced_presentation_inl_h


#include <boost/mpi/communicator.hpp>

#include "globals.h"
#include "relator.h"


namespace andrews_curtis
{
    inline Balanced_presentation::Balanced_presentation()
    :   m_relators(new Relator*[g_relators_count]),
        m_parent(0),
        m_parent_process(0),
        m_left(0),
        m_right(0)
    {
    }
    
    inline Balanced_presentation::~Balanced_presentation()
    {
        delete[] m_relators;
    }
    
    inline const Balanced_presentation*  const &Balanced_presentation::get_parent() const
    {
        return m_parent;
    }
    
    inline unsigned int Balanced_presentation::get_parent_process() const
    {
        return m_parent_process;
    }
    
    inline Relator *Balanced_presentation::get_relator(int unsigned &index) const
    {
        return m_relators[index];
    }
    
    inline void Balanced_presentation::set_relator(Relator *relator, int unsigned &index)
    {
        m_relators[index] = relator;
    }
    
    inline unsigned int Balanced_presentation::get_process() const
    {
        // Define variable to hold the sum of the relators
        std::size_t relator_sum = 0;
        
        // Sum the relators
        for(unsigned int index = 0; index < g_relators_count; ++index)
            relator_sum += static_cast<std::size_t>(*m_relators[index]);

        // Access the world communicator
        boost::mpi::communicator communicator;
        
        // Return the process on which we should reside
        return relator_sum % communicator.size();
    }
    
    inline bool Balanced_presentation::is_trivial() const
    {
        // Populate relator_set
        for(unsigned int index = 0; index < g_relators_count; ++index) 
        {
            // Check if m_relators[count] has length 1
            if(1 != m_relators[index]->get_length())
                return false;
        }
        
        // Return result
        return true;
    }
    
    inline std::string Balanced_presentation::to_string() const
    {
        // Start the string with "("
        std::string to_string = "(";
        
        // Append "[relator]," for all but the last relator
        for(unsigned int index = 0; index < (g_relators_count - 1); ++index)
            to_string += m_relators[index]->to_string() + ", ";
        
        // Append "[relator])\n" for the last relator 
        to_string += m_relators[g_relators_count - 1]->to_string() + ")\n";
        
        // Return result
        return to_string;
    }
	
	inline size_t Balanced_presentation::get_length() const
	{
		// Define variable to hold length
		size_t length = 0;
		
		// Loop over relators and summ their lengths
		for(int index = 0; index < g_relators_count; ++index)
			length += m_relators[index]->get_length();
		
		// Return length
		return length;
	}
    
    inline Balanced_presentation &Balanced_presentation::operator=(const Balanced_presentation &rhs)
    {
        // Check for self assignment
        if(this == &rhs)
            return *this;
        
        // Assign Relators's
        for(int index = 0; index < g_relators_count; ++index)
            *m_relators[index] = *rhs.m_relators[index];
        
        // Note: operator= is used as the first step in creating a child of a
        //       Balanced_presentation. Hence, the next few assignments, that
        //       seem odd at first, are odd in that they are used in that con-
        //       ext and that context only.
        
        // Assign m_parent
        m_parent = &rhs;
        
        // Assign m_parent_process
        m_parent_process = rhs.get_process();
        
        // Assign m_left and m_right, we are not in the BST yet
        m_left = 0;
        m_right = 0;
        
        // Return *this
        return *this;
    }
    
    inline bool Balanced_presentation::operator==(const Balanced_presentation &rhs) const
    {
        // Loop over relators
        for(int unsigned index = 0; index < g_relators_count; ++index)
        {
            // Check for inequality
            if(*m_relators[index] != *rhs.m_relators[index])
                return false;
        }
        
        // Indicate equality
        return true;
    }
    
    inline bool Balanced_presentation::operator!=(const Balanced_presentation &rhs) const
    {
        return !operator==(rhs);
    }
    
    inline bool Balanced_presentation::operator<(const Balanced_presentation &rhs) const
    {
        // Loop over relators
        for(int unsigned index = 0; index < g_relators_count; ++index)
        {
            // Check for greater-than-or-equal
            if(*m_relators[index] >= *rhs.m_relators[index])
                return false;
        }
        
        // Indicate less than
        return true;
    }
    
    inline bool Balanced_presentation::operator<=(const Balanced_presentation &rhs) const
    {
        return !operator>(rhs);
    }
    
    inline bool Balanced_presentation::operator>(const Balanced_presentation &rhs) const
    {
        return (rhs < *this);
    }
    
    inline bool Balanced_presentation::operator>=(const Balanced_presentation &rhs) const
    {
        return !operator<(rhs);
    }
    
    // Union allowing serialization of a pointer to a Balanced_presentation,
    // while not serializing the Balanced_presentation itself. The apropos
    // member is used to obtain the pointer as a number or number as a pointer.
    union Intpoint {
        // The number
        unsigned long number;
        
        // The pointer to 
        const Balanced_presentation *pointer;
    };
    
    template<class Archive>
    inline void Balanced_presentation::save(Archive &archive,unsigned int version) const
    {
        // Serialize all Relators
        for(unsigned int index = 0; index < g_relators_count; ++index)
            archive & m_relators[index];
        
        // Define the Intpoint
        Intpoint intpoint;
        
        // Set pointer of intpoint
        intpoint.pointer = m_parent;
        
        // Serialize the parent
        archive & intpoint.number;
        
        // Serialize the parent's process
        archive & m_parent_process;
    }
    
    template<class Archive>
    inline void Balanced_presentation::load(Archive &archive,unsigned int version)
    {
        // De-serialize all Relators
        for(unsigned int index = 0; index < g_relators_count; ++index)
            archive & m_relators[index];
        
        // Define the Intpoint
        Intpoint intpoint;
        
        // De-serialize the parent
        archive & intpoint.number;
        
        // Set the parent pointer
        m_parent = intpoint.pointer;
        
        // De-serialize the parent's process
        archive & m_parent_process;
    }
}

#endif
