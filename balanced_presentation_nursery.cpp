//
//  balanced_presentation_nursery.cpp
//  Andrews-Curtis Conjecture
//
//  Created by Kelly Davis on 8/23/11.
//
//


#include "globals.h"
#include "relator.h"
#include "balanced_presentation.h"
#include "balanced_presentation_nursery.h"


namespace andrews_curtis
{
    // Utility function that added Relators to the passed presentation
    static void populate_child(Balanced_presentation *balanced_presentation);
    
    // Utility function that creates children resulting form Type I moves: [r => r^-1]
    static void create_type_one_children(const Balanced_presentation *bp,std::list<Balanced_presentation*> &children);
    
    // Utility function that creates children resulting form Type II moves: [r => g*r*g^-1]
    static void create_type_two_children(const Balanced_presentation *bp,std::list<Balanced_presentation*> &children);
    
    // Utility function that creates children resulting form Type III moves: [r => r*s]
    static void create_type_three_children(const Balanced_presentation *bp,std::list<Balanced_presentation*> &children);
    
    
    std::list<Balanced_presentation*> Balanced_presentation_nursery::get_children(const Balanced_presentation *bp)
    {
        // Create list to return
        std::list<Balanced_presentation*> children;
        
        // Create children resulting from Type I moves: [r => r^-1]
        create_type_one_children(bp,children);
        
        // Create children resulting from Type II moves: [r => g*r*g^-1]
        create_type_two_children(bp,children);
        
        // Create children resulting from Type III moves: [r => r*s]
        create_type_three_children(bp,children);
        
        // Return children
        return children;
    }
    
    void populate_child(Balanced_presentation *balanced_presentation)
    {
        // Loop over relators
        for(unsigned int r_index = 0; r_index < g_relators_count; ++r_index)
        {
            // Put a new Relator in the Balanced_presentation
            balanced_presentation->set_relator(new Relator(), r_index);
        }
    }
    
    void create_type_one_children(const Balanced_presentation *bp,std::list<Balanced_presentation*> &children)
    {
        // Loop over Relator's
        for(unsigned int index = 0; index < g_relators_count; ++index)
        {
            // New up a Balanced_presentation
            Balanced_presentation *balanced_presentation = new Balanced_presentation();
            
            // Populate balanced_presentation with Relators
            populate_child(balanced_presentation);
            
            // Copy bp to balanced_presentation
            *balanced_presentation = *bp;
            
            // Invert Relator at index
            balanced_presentation->get_relator(index)->invert();
            
            // Put balanced_presentation into children
            children.push_back(balanced_presentation);
        }
    }
    
    void create_type_two_children(const Balanced_presentation *bp,std::list<Balanced_presentation*> &children)
    {
        // Loop over relators
        for(unsigned int r_index = 0; r_index < g_relators_count; ++r_index)
        {
            // Loop over all generators (Note: They're 1 based, n and -n are inverses)
            for(int g_index = -g_generators_count; g_index <= g_generators_count; ++g_index)
            {
                // There is no generator 0; so, skip it
                if(0 == g_index)
                    continue;
                
                // New up a Balanced_presentation
                Balanced_presentation *balanced_presentation = new Balanced_presentation();
                
                // Populate balanced_presentation with Relators
                populate_child(balanced_presentation);
                
                // Copy bp to balanced_presentation
                *balanced_presentation = *bp;
                
                // Conjugate Relator at r_index with generator g_index
                balanced_presentation->get_relator(r_index)->conjugate(g_index);
                
                // Put balanced_presentation into children
                children.push_back(balanced_presentation);
            }
        }
    }
    
    void create_type_three_children(const Balanced_presentation *bp,std::list<Balanced_presentation*> &children)
    {
        // Loop over relators acted on
        for(unsigned int index1 = 0; index1 < g_relators_count; ++index1)
        {
            // Loop over relators acting on
            for(unsigned int index2 = 0; index2 < g_relators_count; ++index2)
            {
                // The move r_index1 => r_index1*r_index2 only occurs for index1 != index2
                if(index1 == index2)
                    continue;
                
                // New up a Balanced_presentation
                Balanced_presentation *balanced_presentation = new Balanced_presentation();
                
                // Populate balanced_presentation with Relators
                populate_child(balanced_presentation);
                
                // Copy bp to balanced_presentation
                *balanced_presentation = *bp;
                
                // Multiply Relator at index1 on the right by Relator at index2
                balanced_presentation->get_relator(index1)->multiply(balanced_presentation->get_relator(index2));
                
                // Put balanced_presentation into children
                children.push_back(balanced_presentation);
            }
        }
    }
}
