//
//  searcher.h
//  Andrews-Curtis Conjecture
//
//  Created by Kelly Davis on 8/19/11.
//
//

#ifndef Andrews_Curtis_Conjecture_searcher_h
#define Andrews_Curtis_Conjecture_searcher_h


#include <string>


namespace andrews_curtis
{
    /// Forward declaration
    class Arguments;
    class Balanced_presentation;
    
    
    ///
    /// An instance of this class, using Andrews-Curtis moves, searches
    /// through the balanced presentations derived from the Argument's
    /// balanced presentation. 
    ///
    /// This search halts for one of two reasons:
    /// -If a trivial balanced presentation is found.
    /// -The the full tree of balanced presentations derivable from the
    ///  Argument's balanced presentation is exhausted without finding
    ///  a trivial balanced presentation.
    ///
    /// Upon the search halting one can determine why the search halted
    /// by calling the is_trivial() method. If this method returns true,
    /// then a trivial balanced presentation was found. It returns false
    /// if the full tree was exhausted without finding a trivial balanced
    /// presentation.
    ///
    class Searcher
    {
    public:
        ///
        /// Constructs a Searcher that searches for counterexamples to the
        /// Andrews-Curtis conjecture for the Argument's balanced presentation.
        ///
        /// \param arguments The arguments to examine
        ///
        Searcher(const Arguments &arguments);
        
        ///
        /// Searches for counterexamples to the Andrews-Curtis conjecture
        /// for the balanced presentation represented by the contained
        /// Arguments. Halts only if a counterexample is found or if the
        /// balanced presentation is Andrews-Curtis trivial.
        ///
        void search();
        
        ///
        /// Returns a bool indicating if the balanced presentation
        /// represented by the contained Arguments is Andrews-Curtis 
        /// trivial. This method only returns a valid bool after the
        /// search() completes.
        ///
        /// \return A bool indicating Andrews-Curtis triviality
        ///
        bool is_trivial() const;
        
        ///
        /// If is_trivial() returns true after search() completes, this
        /// method prints the derivation of triviality, otherwise this
        /// method does nothing. The derivation is in a human readable
        /// form.
        ///
        void print_derivation() const;
        
        ///
        /// If is_trivial() returns false after search() completes, this
        /// method prints the counterexample to Andrews-Curtis triviality
        /// otherwise this method does nothing. The counterexample is in
        /// a human readable form.
        ///
        void print_counterexample() const;
        
    private:
        /// A bool indicating triviality
		bool m_is_trivial;
        
        /// The original balanced presentation
        std::string m_counterexample;
        
        /// The command line user defined arguments
        const Arguments &m_arguments;
        
        /// Pointer to m_trivial_presentation
		Balanced_presentation *m_trivial_presentation;
    };
}

#include "searcher-inl.h"

#endif
