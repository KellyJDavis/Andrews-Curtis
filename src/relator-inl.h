//
//  relator-inl.h
//  Andrews-Curtis Conjecture
//
//  Created by Kelly Davis on 8/20/11.
//
//

#ifndef Andrews_Curtis_Conjecture_relator_inl_h
#define Andrews_Curtis_Conjecture_relator_inl_h


#include <vector>
#include <limits>
#include <cstring>

#include <boost/functional/hash.hpp>
#include <boost/serialization/vector.hpp>

#include "globals.h"
#include "letters.h"


namespace andrews_curtis
{
    inline Relator::Relator()
    :   m_relator(),
        m_left(0),
        m_right(0)
    {
    }
    
    inline Relator::Relator(const char *relator)
    :   m_relator(std::strlen(relator) * g_bits_per_letter),
        m_left(0),
        m_right(0)
    {
        // Loop over letters in relator
        for(size_t index = 0; index < std::strlen(relator); ++index)
        {
            // Obtain bits in letter at index
            const unsigned int &bits_in_letter =  Letters::get_bits(relator[index]);
            
            // Loop over bits in letter
            for(unsigned int bit = 0; bit < g_bits_per_letter; ++bit)
            {
                // Set apropos m_relator bit to bit of next_letter (Note: does not allocate)
                m_relator[index*g_bits_per_letter + bit] = (bits_in_letter >> bit) & 0x1;
            }
        }
    }
    
    inline size_t Relator::get_length() const
    {
        return (m_relator.size() / g_bits_per_letter);
    }
    
    inline Relator::operator std::size_t() const
	{
		// Define hash
		boost::hash<std::string> hash;
		
		// Obtain string
		std::string string = to_string();
		
		// Return result
		return hash(string);
	}
    
    inline std::string Relator::to_string() const
    {        
        // Define the string
        std::string relator;
        
        // Loop over letters in m_relator
        for(unsigned int letter = 0; letter < (m_relator.size() / g_bits_per_letter); ++letter)
        {
            // Define int to hold bits in letter
            unsigned int bits_in_letter = 0;
            
            // Loop over bits in letter
            for(unsigned int bit = 0; bit < g_bits_per_letter; ++bit)
            {
                // Flip apropos bit in bits_in_letter
                if(m_relator[letter*g_bits_per_letter + bit])
                    bits_in_letter |= (0x1 << bit);
            }
            
            // Append letter 
            relator += Letters::get_letter(bits_in_letter);
        }
        
        // Return relator
        return relator;
    }
    
    inline Relator &Relator::operator=(const Relator &rhs)
    {
        // Check for self assignment
        if(this == &rhs)
            return *this;
        
        // Copy dynamic_bitset
        m_relator = rhs.m_relator;
        
        // Do not copy position in tree
        m_left = 0;
        m_right = 0;
        
        // Return self
        return *this;
    }
    
    inline bool Relator::operator==(const Relator &rhs) const
    {
        if(m_relator.size() != rhs.m_relator.size())
           return false;
        return m_relator == rhs.m_relator;
    }
    
    inline bool Relator::operator!=(const Relator &rhs) const
    {
        return !operator==(rhs);
    }
    
    inline bool Relator::operator<(const Relator &rhs) const
    {
        if(m_relator.size() < rhs.m_relator.size())
            return true;
        if(m_relator.size() > rhs.m_relator.size())
            return false;
        return m_relator < rhs.m_relator;
    }
    
    inline bool Relator::operator<=(const Relator &rhs) const
    {
        return !operator>(rhs);
    }
    
    inline bool Relator::operator>(const Relator &rhs) const
    {
        return (rhs < *this);
    }
    
    inline bool Relator::operator>=(const Relator &rhs) const
    {
        return !operator<(rhs);
    }
    
    template<class Archive>
    inline void Relator::save(Archive &archive,unsigned int version) const
    {
        // Obtain size
        boost::dynamic_bitset<>::size_type size = m_relator.size();;
        
        // Write size of m_relator to archive
        archive & size;
        
        // Define a vetor to hold the blocks of m_relator
        std::vector< boost::dynamic_bitset<>::block_type > blocks(m_relator.num_blocks());
        
        // Write blocks to blocks
        boost::to_block_range(m_relator,blocks.begin());
        
        // Write blocks to archive
        archive & blocks;
    }
    
    template<class Archive>
    inline void Relator::load(Archive &archive,unsigned int version)
    {
        // Define size
        boost::dynamic_bitset<>::size_type size;
        
        // Read size from archive
        archive & size;

        // Resize m_relator (Note: may allocate)
        m_relator.resize(size);
        
        // Define vector to hold blocks
        std::vector< boost::dynamic_bitset<>::block_type > blocks(m_relator.num_blocks());
        
        // Read blocks from archive
        archive & blocks;
        
        // Copy blocks from blocks to m_relator
        boost::from_block_range(blocks.begin(),blocks.end(),m_relator);
    }
}

#endif
