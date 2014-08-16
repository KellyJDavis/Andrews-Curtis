//
//  globals.h
//  Andrews-Curtis Conjecture
//
//  Created by Kelly Davis on 8/19/11.
//  Copyright 2011 Kelly Davis. All rights reserved.
//

#ifndef Andrews_Curtis_Conjecture_globals_h
#define Andrews_Curtis_Conjecture_globals_h


namespace andrews_curtis
{
    
    // As the presentation is balanced, there need be only
    // one place where we store the number of relators, as
    // this number is the same for all presentations. Hence,
    // instead of keeping a copy of this number around for
    // each balanced presentation we keep it in a global.
    // As there can be billions of presentations, this will
    // save lots of space.
    extern long g_relators_count;
    
    // As the program only works on a single Andrews-Curtis
    // reduction problem at a time there is only one set of
    // generators being used at any given time. The number
    // of generators in this set it therefore global info
    // that does not vary from instance to instance. So,
    // we store that info here, once and for all, to stop
    // memory wasting copies of the data.
    extern long g_generators_count;
    
    // As the program only works on a single Andrews-Curtis
    // reduction problem at a time there is only one set of
    // generators being used at any given time. As the number
    // of children of a given presentation depends only upon
    // the number of genertors, the presentation is balanced,
    // we store the number of children here, once and for all,
    // to stop memory wasting copies of the data.
    extern long g_children_count;
    
    // As the program only works on a single Andrews-Curtis
    // reduction problem at a time there is only one set of
    // generators being used at any given time. This one set
    // of generators has g_generators_count elements, if we
    // include inverses it has 2*g_generators_count elements.
    // This number holds the smallest number of bits required
    // to represent the number 2*g_generators_count.
    extern long g_bits_per_letter;
    
}

#endif
