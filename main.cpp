//
//  main.cpp
//  Andrews-Curtis Conjecture
//
//  Created by Kelly Davis on 8/19/11.
//  Copyright 2011 Kelly Davis. All rights reserved.
//

#include <iostream>
#include <boost/mpi/environment.hpp>

#include "relator.h"
#include "searcher.h"
#include "arguments.h"
#include "binary_tree.h"
#include "balanced_presentation.h"

using namespace andrews_curtis;

int main (int argc,char * argv[])
{
    // Initialize the MPI environment
    boost::mpi::environment environment(argc,argv);
    
    // Initialize the user arguments
    Arguments arguments(argc,argv);
    
    // Determine if arguments is not valid
    if(!arguments.is_valid()) 
    {
        // Print error message for invalid arguments
        std::cout << arguments.get_message() << std::endl;
        
        // Return error
        return arguments.get_return_code();
    }
    
    // Create searcher
    Searcher searcher(arguments);
    
    // Search
    searcher.search();
    
    // Is Andrews-Curtis trivial
    if(searcher.is_trivial())
    {
        // Print derivation
        searcher.print_derivation();
    }
    else 
    {
        // Print Andrews-Curtis counterexample
        searcher.print_counterexample();
    }
    
    // Clean up Relators
    Binary_tree<Relator>::clear();
    
    // Clean up Balanced_presentation's
    Binary_tree<Balanced_presentation>::clear();
    
    // Return success
    return 0;
}

