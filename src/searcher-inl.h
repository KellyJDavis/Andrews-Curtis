//
//  searcher-inl.h
//  Andrews-Curtis Conjecture
//
//  Created by Kelly Davis on 8/19/11.
//
//

#ifndef Andrews_Curtis_Conjecture_searcher_inl_h
#define Andrews_Curtis_Conjecture_searcher_inl_h


#include <iostream>

#include <boost/mpi/communicator.hpp>


namespace andrews_curtis
{
    inline bool Searcher::is_trivial() const
    {
        return m_is_trivial;
    }
    
    inline void Searcher::print_counterexample() const
    {
        // Define the world communicator in which we reside
        boost::mpi::communicator communicator;
        
        // If we are on process 0, print the counter example
        if(!communicator.rank())
            std::cout << m_counterexample;
    }
}

#endif
