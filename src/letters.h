//
//  letters.h
//  Andrews-Curtis Conjecture
//
//  Created by Kelly Davis on 8/20/11.
//
//

#ifndef Andrews_Curtis_Conjecture_letters_h
#define Andrews_Curtis_Conjecture_letters_h


namespace andrews_curtis
{
    //
    // This class enpaculates various functionaly required to express
    // the letters in a relator as a set of bits.
    //
    class Letters
    {
    public:
        //
        // Returns an array of bools that represents the passed letter. The passed
        // number identifies a letter as follows: ...B=-2,A=-1,a=1,b=1... each one
        // of these numbers can be expressed in one's compliment in hexidecimal as
        // follows ...B=0xFD,A=0xFE,a=0x01,b=0x02... and in binary...B=0b11111101,
        // A=0b11111110,a=0b00000001,b=...  These binary numbers can be viewed as
        // arrays of bools with length g_bits_per_letter. This method returns such
        // an arrary.
        //
        // \param index The index of the letter to return
        // \return An array of bool's representing the selected letter
        static const bool *get_bools(int index);
        
        //
        // Returns the char corresponding to the passed bits
        //
        // \param bits The bits to convert to a char
        // \return The corresponsing char
        static char get_letter(unsigned int bits);
        
        //
        // Returns a (const unsigned int&) that has its g_bits_per_letter least
        // significant bits set to the bits representing the passed letter.
        //
        // \param letter The letter to convert to bits
        // \return The passed letter represented as bits
        static const unsigned int &get_bits(const char &letter);
    };
}

#include "letters-inl.h"

#endif
