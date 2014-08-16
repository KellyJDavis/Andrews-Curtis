//
//  relator.cpp
//  Andrews-Curtis Conjecture
//
//  Created by Kelly Davis on 8/23/11.
//
//


#include "globals.h"
#include "relator.h"


namespace andrews_curtis
{    
    void Relator::invert()
    {
        // TODO: Optimize this method to not require the copy below
        
        // Make a copy of m_relator
        boost::dynamic_bitset<> source = m_relator;
        
        // Obtain size of source
        boost::dynamic_bitset<>::size_type size = source.size();
        
        // Obain count of letters in source
        unsigned long letter_count = size / g_bits_per_letter;
        
        // Loop over "half" the leters in source
        for(unsigned int letter = 0; letter < (letter_count/2); ++letter)
        {
            // Loop over the bits in letter
            for(unsigned int bit = 0; bit < g_bits_per_letter; ++bit)
            {
                // Write the inversion of the apropos bits (Note: Letters as in one's compliment)
                m_relator[size - letter*g_bits_per_letter - g_bits_per_letter + bit] = 
                    !source[letter*g_bits_per_letter + bit];
                m_relator[letter*g_bits_per_letter + bit] = 
                    !source[size - letter*g_bits_per_letter - g_bits_per_letter + bit];
            }
        }
        
        // If there is a middle element in m_relator
        if(1 == (letter_count % 2))
        {
            // Loop over the bits in middle letter
            for(unsigned int bit = 0; bit < g_bits_per_letter; ++bit)
            {
                // Invert the middle element in source
                m_relator[(letter_count/2)*g_bits_per_letter + bit] =  
                    !source[(letter_count/2)*g_bits_per_letter + bit];
            }
        }
    }
    
    void Relator::conjugate(int generator)
    {
        // TODO: Optimize this method to not require the copy below
        
        // Make a copy of m_relator
        boost::dynamic_bitset<> source = m_relator;
        
        // Obtain source length
        boost::dynamic_bitset<>::size_type relator_length = source.size();
        
        // Obtain new relator length, assuming no cancellations
        boost::dynamic_bitset<>::size_type length = relator_length + (2*g_bits_per_letter);
        
        // Define where to start copying bits from source to this m_relator
        boost::dynamic_bitset<>::size_type loop_start = 0;
        
        // Define where to stop copying bits from source to this m_relator
        boost::dynamic_bitset<>::size_type loop_stop = relator_length;
        
        // Obtain bool array representing the letter 'generator'
        const bool *letter = Letters::get_bools(generator);
        
        // Define a bool to indicate if an initial cancellation occurs
        bool initial_cancellation = !relator_length ? false : true;
        
        // Loop over initial bits to look for a cancellation
        for(unsigned int bit = 0; initial_cancellation && (bit < g_bits_per_letter); ++bit)
        {
            // Check for cancellation (Remember, one's compliment and -N is the inverse of N)
            if(letter[bit] == source[bit])
                initial_cancellation = false;
        }
        
        // If there is an initial cancellation, adjust length and loop_start
        if(initial_cancellation)
        {
            // Modify length
            length -= (2*g_bits_per_letter);
            
            // Set loop_start
            loop_start += g_bits_per_letter;
        }
        
        // Define a bool to indicate if a final cancellation occurs
        bool final_cancellation = !relator_length ? false : true;
        
        // Loop over final bits to look for a cancellation
        for(unsigned int bit = 0; final_cancellation && (bit < g_bits_per_letter); ++bit)
        {
            // Check for cancellation
            if(letter[bit] != source[relator_length - g_bits_per_letter + bit])
                final_cancellation = false;
        }
        
        // If there is an final cancellation, adjust length and loop_stop
        if(final_cancellation)
        {
            // Modify length
            length -= (2*g_bits_per_letter);
            
            // Set loop_stop
            loop_stop -= g_bits_per_letter;
        }
        
        // Resize m_relator to hold length bits. (Note: may allocate)
        m_relator.resize(length);
        
        // Define number of bits to skip when copying source to m_relator
        int bits_to_skip = -g_bits_per_letter;
        
        // If there's no starting cancelation
        if(0 == loop_start)
        {
            // Add the first letter
            for(unsigned int bit = 0; bit < g_bits_per_letter; ++bit)
                m_relator[bit] = letter[bit];
            
            // Set bits_to_skip to skip this data
            bits_to_skip = g_bits_per_letter;
        }
        
        // Loop over non-canceled characters of source
        for(boost::dynamic_bitset<>::size_type index = loop_start; index < loop_stop; ++index)
        {
            // Add the index bit to m_relator
            m_relator[index + bits_to_skip] = source[index];
        }
        
        // If there's no stoping cancelation
        if(relator_length == loop_stop)
        {
            // Add the final letter
            for(unsigned int bit = 0; bit < g_bits_per_letter; ++bit)
                m_relator[length - g_bits_per_letter + bit] = !letter[bit];
        }
    }
    
    void Relator::multiply(const Relator *relator2)
    {
        // TODO: Optimize this method to not require the copy below
        
        // Make a copy of m_relator
        boost::dynamic_bitset<> source = m_relator;
        
        // Obtain relator1 length
        boost::dynamic_bitset<>::size_type relator1_length = source.size();
        
        // Obtain relator2 length
        boost::dynamic_bitset<>::size_type relator2_length = relator2->m_relator.size();
        
        // Obtain navie length assuming no cancelations
        boost::dynamic_bitset<>::size_type naive_length = relator1_length + relator2_length;
        
        // Determine min of relator1_length and relator2_length
        boost::dynamic_bitset<>::size_type min_length = 
        (relator1_length < relator2_length) ? relator1_length : relator2_length;
        
        // Define cancelation_count to count the cancelations in relator1*relator2
        unsigned int cancelation_count = 0;
        
        // Declare bool used to indicate if a cancelations occurs
        bool is_cancelation;
        
        // Declare bool's used to hold relator1 and relator2 bits
        bool relator1_bit;
        bool relator2_bit;
        
        // Determine actual new length based on calcelations
        for(unsigned int letter = 0; letter < (min_length / g_bits_per_letter); ++letter)
        {
            // Re-set is_cancelation
            is_cancelation = true;
            
            // Loop over bits
            for(unsigned int bit = 0; is_cancelation && (bit < g_bits_per_letter); ++bit)
            {
                // Obtain current relator1 bit
                relator1_bit = source[relator1_length - g_bits_per_letter - letter*g_bits_per_letter + bit];
                
                // Obtain current relator2 bit
                relator2_bit = relator2->m_relator[letter*g_bits_per_letter + bit];
                
                // Check current bit for lack of cancelation
                if(relator1_bit == relator2_bit)
                    is_cancelation = false;
            }
            
            // Check is_cancelation
            if(is_cancelation)
            {
                // Increment cancelation_count
                cancelation_count += 1;
            }
            else
            {
                // Break out of the loop, non-concident cancelations can't occur
                break;
            }
        }
        
        // Resize m_relator to hold the actual number of bits. (Note: may allocate)
        m_relator.resize(naive_length - (2*cancelation_count*g_bits_per_letter));
        
        // Copy the non-canceled elements from relator1
        for(boost::dynamic_bitset<>::size_type index = 0; index < (relator1_length - cancelation_count*g_bits_per_letter); ++index)
        {
            // Copy the element at index
            m_relator[index] = source[index];
        }
        
        // Copy the non-canceled elements from relator2
        for(boost::dynamic_bitset<>::size_type index = cancelation_count*g_bits_per_letter; index < relator2_length; ++index)
        {
            // Copy the element at index
            m_relator[(relator1_length - cancelation_count*g_bits_per_letter) + (index - cancelation_count*g_bits_per_letter)] =
            relator2->m_relator[index];
        }
    }
}
