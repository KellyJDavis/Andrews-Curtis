//
//  arguments.cpp
//  Andrews-Curtis Conjecture
//
//  Created by Kelly Davis on 8/19/11.
//  Copyright 2011 Kelly Davis. All rights reserved.
//


#include <cmath>
#include <cstring>

#include "globals.h"
#include "arguments.h"


namespace andrews_curtis
{
    // Define globals
	long g_children_count = 0;
	long g_relators_count = 0;
	long g_bits_per_letter = 0;
	long g_generators_count = 0;
    
    Arguments::Arguments(int argc,char *argv[])
    :   m_message(),
        m_is_valid(true),
        m_relators(0),
        m_generators(0)
    {
        // Check if there are to few arguments
        if(argc < 3)
        {
            // Set message
            m_message = "To few arguments.";
            
            // Flag validity
            m_is_valid = false;
            
            // Return
            return;
        }
        
        // Check that the presentation is balanced
        if(std::strlen(argv[1]) != (argc - 2))
        {
            // Set message
            m_message = "The presentation is not balanced.";
            
            // Flag validity
            m_is_valid = false;
            
            // Return
            return;
        }
        
        // Define current relator
        const char *relator = 0;
        
        // Define generators
        const char *generators = 0;
        
        // Define a bool indicating *relator validity
        bool is_valid = false;
        
        // Check that relators contain only generators and inverses
        for(int count = 2; count <  argc; ++count) 
        {
            // Obtain current relator
            relator = argv[count];
            
            // Loop over elements in relator
            do
            {
                // Set bool indicating *relator validity
                is_valid = false;
                
                // Obtain generators
                generators = argv[1];
                
                // Loop over generators
                do 
                {
                    // Is *relator a generator or the inverse of a generator
                    if( (*relator == *generators) || (*relator == (*generators - 32)) ) 
                    {
                        // Flag *relator as valid
                        is_valid = true;
                    }
                } while( !is_valid && *(++generators) );
                
                // Check validity of *relator
                if(!is_valid) 
                {
                    // Set message
                    m_message = "A relator does not consist of generators and their inverses.";
                    
                    // Flag validity
                    m_is_valid = false;
                    
                    // Return
                    return;
                }
            } while( *(++relator) );
        }
        
        // Set m_generators
        m_generators = argv[1];
        
        // Set m_relators
        m_relators = &argv[2];
        
        // Set g_generators_count
        g_generators_count = std::strlen(m_generators);
        
        // Set g_relators_count (The presentation is balanced)
        g_relators_count = std::strlen(m_generators);
        
        // Set g_children_count (The presentation is balanced)
        g_children_count = 3*g_generators_count*g_generators_count;
        
        // Set g_bits_per_letter (The min bit count needed to represent 2 * g_generators_count)
        g_bits_per_letter = (std::log(2 * g_generators_count) / std::log(2)) + 1;
    }
}
