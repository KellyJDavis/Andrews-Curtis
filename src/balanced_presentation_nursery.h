//
//  balanced_presentation_nursery.h
//  Andrews-Curtis Conjecture
//
//  Created by Kelly Davis on 8/23/11.
//
//

#ifndef Andrews_Curtis_Conjecture_balanced_presentation_nursery_h
#define Andrews_Curtis_Conjecture_balanced_presentation_nursery_h


#include <list>


namespace andrews_curtis
{
    /// Forward declarations
    class Balanced_presentation;
    
    ///
    /// An instance of this class creates children of a given Balanced_presentation
    /// using Andrews Curtis moves.
    ///
    class Balanced_presentation_nursery
    {
    public:
        ///
        /// Returns a list of Balanced_presentation's each one of which is a child of
        /// the passed Balanced_presentation with respect to Andrews Curtis moves.
        ///
        /// The lifetime of the returned Balanced_presentation's and Relator's should be
        /// controlled by the caller, ie the caller should call delete on each when they
        /// are no longer needed.
        ///
        /// \param bp The Balanced_presentation to find the children of
        /// \return The children of the passed Balanced_presentation
        ///
        static std::list<Balanced_presentation*> get_children(const Balanced_presentation *bp);
    };
}

#endif
