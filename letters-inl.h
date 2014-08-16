//
//  letters-inl.h
//  Andrews-Curtis Conjecture
//
//  Created by Kelly Davis on 8/20/11.
//  Copyright 2011 Kelly Davis. All rights reserved.
//

#ifndef Andrews_Curtis_Conjecture_letters_inl_h
#define Andrews_Curtis_Conjecture_letters_inl_h


#include <map>

#include "globals.h"


namespace andrews_curtis
{
    static const bool bools[52][5] =
    {
        {true , false, false, false, false},  // 'a' 1
        {false, true , false, false, false},  // 'b' 2
        {true , true , false, false, false},  // 'c' 3
        {false, false, true , false, false},  // 'd' 4
        {true , false, true , false, false},  // 'e' 5
        {false, true , true , false, false},  // 'f' 6
        {true , true , true , false, false},  // 'g' 7
        {false, false, false, true , false},  // 'h' 8
        {true , false, false, true , false},  // 'i' 9
        {false, true , false, true , false},  // 'j' 10
        {true , true , false, true , false},  // 'k' 11
        {false, false, true , true , false},  // 'l' 12
        {true , false, true , true , false},  // 'm' 13
        {false, true , true , true , false},  // 'n' 14
        {true , true , true , true , false},  // 'o' 15
        {false, false, false, false, true },  // 'p' 16
        {true , false, false, false, true },  // 'q' 17
        {false, true , false, false, true },  // 'r' 18
        {true , true , false, false, true },  // 's' 19
        {false, false, true , false, true },  // 't' 20
        {true , false, true , false, true },  // 'u' 21
        {false, true , true , false, true },  // 'v' 22
        {true , true , true , false, true },  // 'w' 23
        {false, false, false, true , true },  // 'x' 24
        {true , false, false, true , true },  // 'y' 25
        {false, true , false, true , true },  // 'z' 26
        {false, true , true , true , true },  // 'A' ~1
        {true , false, true , true , true },  // 'B' ~2
        {false, false, true , true , true },  // 'C' ~3
        {true , true , false, true , true },  // 'D' ~4
        {false, true , false, true , true },  // 'E' ~5
        {true , false, false, true , true },  // 'F' ~6
        {false, false, false, true , true },  // 'g' ~7
        {true , true , true , false, true },  // 'H' ~8
        {false, true , true , false, true },  // 'I' ~9
        {true , false, true , false, true },  // 'J' ~10
        {false, false, true , false, true },  // 'K' ~11
        {true , true , false, false, true },  // 'L' ~12
        {false, true , false, false, true },  // 'M' ~13
        {true , false, false, false, true },  // 'N' ~14
        {false, false, false, false, true },  // 'O' ~15
        {true , true , true , true , false},  // 'P' ~16
        {false, true , true , true , false},  // 'Q' ~17
        {true , false, true , true , false},  // 'R' ~18
        {false, false, true , true , false},  // 'S' ~19
        {true , true , false, true , false},  // 'T' ~20
        {false, true , false, true , false},  // 'U' ~21
        {true , false, false, true , false},  // 'V' ~22
        {false, false, false, true , false},  // 'W' ~23
        {true , true , true , false, false},  // 'X' ~24
        {false, true , true , false, false},  // 'Y' ~25
        {true , false, true , false, false},  // 'Z' ~26
    };
    
    inline const bool *Letters::get_bools(int index)
    {
        // Offset index properly
        if(index < 0)
            index = 25 - index;
        else
            index -= 1;
        
        // Return the array of bools
        return bools[index];
    }
    
    
    // Utility class to map a char to its corresponding bits. Each
    // char has a number ...C=-3,B=-2,A=-1,a=1,b=2,c=3,... the bits
    // is this number in one's compliment.
    class Char_to_bits
    {
    public:
        Char_to_bits()
        {
            m_map['a'] =  0x01;
            m_map['b'] =  0x02;
            m_map['c'] =  0x03;
            m_map['d'] =  0x04;
            m_map['e'] =  0x05;
            m_map['f'] =  0x06;
            m_map['g'] =  0x07;
            m_map['h'] =  0x08;
            m_map['i'] =  0x09;
            m_map['j'] =  0x0A;
            m_map['k'] =  0x0B;
            m_map['l'] =  0x0C;
            m_map['m'] =  0x0D;
            m_map['n'] =  0x0E;
            m_map['o'] =  0x0F;
            m_map['p'] =  0x10;
            m_map['q'] =  0x11;
            m_map['r'] =  0x12;
            m_map['s'] =  0x13;
            m_map['t'] =  0x14;
            m_map['u'] =  0x15;
            m_map['v'] =  0x16;
            m_map['w'] =  0x17;
            m_map['x'] =  0x18;
            m_map['y'] =  0x19;
            m_map['z'] =  0x1A;
            m_map['A'] =  0xFE;
            m_map['B'] =  0xFD;
            m_map['C'] =  0xFC;
            m_map['D'] =  0xFB;
            m_map['E'] =  0xFA;
            m_map['F'] =  0xF9;
            m_map['G'] =  0xF8;
            m_map['H'] =  0xF7;
            m_map['I'] =  0xF6;
            m_map['J'] =  0xF5;
            m_map['K'] =  0xF4;
            m_map['L'] =  0xF3;
            m_map['M'] =  0xF2;
            m_map['N'] =  0xF1;
            m_map['O'] =  0xF0;
            m_map['P'] =  0xEF;
            m_map['Q'] =  0xEE;
            m_map['R'] =  0xED;
            m_map['S'] =  0xEC;
            m_map['T'] =  0xEB;
            m_map['U'] =  0xEA;
            m_map['V'] =  0xE9;
            m_map['W'] =  0xE8;
            m_map['X'] =  0xE7;
            m_map['Y'] =  0xE6;
            m_map['Z'] =  0xE5;
        }
        
        const unsigned int &get_bits(const char &letter)
        {
            return m_map[letter];
        }
        
    private:
        std::map<char,unsigned int> m_map;
    };
    
    inline char Letters::get_letter(unsigned int bits)
    {   
        // Determine if bits is negative (One's compliment)
        if(bits & (0x1 << (g_bits_per_letter - 1)))
        {
            // Flip the bits of bits
            bits = ~bits;
            
            // Return a upper case letter
            return bits + 72;
        }
        
        // Return a lower case letter
        return bits + 96;
    }
    
    
    inline const unsigned int &Letters::get_bits(const char &letter)
    {
        // Construct Char_to_bits statically
        static Char_to_bits map;
        
        // Return the apropos bits
        return map.get_bits(letter);
    }
}

#endif
