//
//  searcher.cpp
//  Andrews-Curtis Conjecture
//
//  Created by Kelly Davis on 8/19/11.
//
//

#include <list>
#include <queue>
#include <memory>
#include <vector>
#include <utility>
#include <iostream>
#include <functional>

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/scoped_array.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/mpi/nonblocking.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <boost/mpi/collectives.hpp>
#include <boost/mpi/communicator.hpp>

#include "relator.h"
#include "globals.h"
#include "searcher.h"
#include "arguments.h"
#include "binary_tree.h"
#include "boost/threadpool.hpp"
#include "balanced_presentation.h"
#include "balanced_presentation_nursery.h"




// Mutex for in_values
static boost::mutex s_in_values_mutex;

// Mutex for queue
static boost::mutex s_queue_mutex;

// Queue to hold elements in the next level
static std::queue<andrews_curtis::Balanced_presentation*> s_balanced_presentation_queue;

namespace andrews_curtis
{
  // Typedefs
  typedef std::list<Balanced_presentation*>::iterator Itr;
	typedef std::queue<andrews_curtis::Balanced_presentation*>::size_type queue_size_type;
	
	// Utility function to obtain children
	void obtain_children(std::vector< std::list<Balanced_presentation*> > *in_values);
	
	// Utility function to clear lists
	void clear_list(std::list<Balanced_presentation*> *list);
	
	// Utility function to delete a Balanced_presentation
	void delete_balanced_presentation(Balanced_presentation *balanced_presentation);
	
	// Utility function to insert Balanced presentations
	void insert_balanced_presentation(Balanced_presentation *balanced_presentation,bool *is_trivial,Balanced_presentation **trivial_presentation);
    
    
    Searcher::Searcher(const Arguments &arguments)
    :   m_is_trivial(false),
        m_counterexample(),
        m_arguments(arguments),
        m_trivial_presentation(0)
    {
        // New up a Balanced_presentation
        std::auto_ptr<Balanced_presentation> balanced_presentation(new Balanced_presentation());
        
        // Define array of Relator's
        boost::scoped_array< std::auto_ptr<Relator> > relators(new std::auto_ptr<Relator>[g_relators_count]);
        
        // Loop over user relators
        for(unsigned int index = 0; index < g_relators_count; ++index)
        {
            // New up a Relator with 'index' relator from m_arguments
            relators[index] = std::auto_ptr<Relator>(new Relator(m_arguments.get_relators()[index]));
            
            // Insert relator into balanced_presentation
            balanced_presentation->set_relator(relators[index].get(), index);
        }
        
        // Set m_counterexample
        m_counterexample = "Counterexample:\n";
        m_counterexample += balanced_presentation->to_string();
        
        // Define the world communicator in which we reside
        boost::mpi::communicator communicator;
        
        // Is this process the home of balanced_presentation?
        if(communicator.rank() == balanced_presentation->get_process())
        {
            // Insert Relators into scapegoat tree and give up ownership
            for(unsigned int index = 0; index < g_relators_count; ++index)
                Binary_tree<Relator>::insert(relators[index].release());
            
            // Push the Balanced_presentation onto the queue
            s_balanced_presentation_queue.push(balanced_presentation.get());
                
            // Insert Balanced_presentation into scapegoat tree and give up ownership
            Binary_tree<Balanced_presentation>::insert(balanced_presentation.release());
        }
    }
    
    void Searcher::search()
    {
		// Define a thread pool with hardware_concurrency threads
		boost::threadpool::thread_pool<> thread_pool(boost::thread::hardware_concurrency());
		
		// Define variable to hold the current level
		unsigned long level = 0;
		
        // Define the world communicator in which we reside
        boost::mpi::communicator communicator;
		
		// Log the number of threads in the thread pool
		std::cout << "Process: " << communicator.rank() << " Thread pool size: " << thread_pool.size() << std::endl;
        
        // Define vector to hold values to send
        std::vector< std::list<Balanced_presentation*> > in_values(communicator.size());
        
        // Define vector to hold values to receive
        std::vector< std::list<Balanced_presentation*> > out_values(communicator.size());
        
        // Loop forever
        while(true)
        {
			// Obtain length of local Relator Binary_tree
			unsigned long local_relator_length = Binary_tree<Relator>::length();
			
			// Define a variable to hold the length of the global Relator Binary_tree
			unsigned long global_relator_length;
			
			// Obtain global Relator length
			boost::mpi::reduce(communicator,local_relator_length,global_relator_length, std::plus<unsigned long>(),0);
			
			// Obtain size of local Relator Binary_tree
			unsigned long local_relator_size = Binary_tree<Relator>::size();
			
			// Define a variable to hold the size of the global Relator Binary_tree
			unsigned long global_relator_size;
			
			// Obtain global Relator size
			boost::mpi::reduce(communicator,local_relator_size,global_relator_size, std::plus<unsigned long>(),0);
			
			// Obtain size of local Balanced_presentation Binary_tree
			unsigned long local_balanced_presentation_size = Binary_tree<Balanced_presentation>::size();
			
			// Define a variable to hold the size of the global Balanced_presentation Binary_tree
			unsigned long global_balanced_presentation_size;
			
			// Obtain global Balanced_presentation size
			boost::mpi::reduce(communicator,local_balanced_presentation_size,global_balanced_presentation_size, std::plus<unsigned long>(),0);
			
			// If we are process 0
			if(!communicator.rank())
			{
				// Print current level
				std::cout << std::endl << "Completed level: " << level++ << std::endl;
				
				// Obtain start time
				static boost::posix_time::ptime start_time(boost::posix_time::microsec_clock::local_time());
				
				// Obtain stop time
				boost::posix_time::ptime stop_time(boost::posix_time::microsec_clock::local_time());
				
				// Obtain difference between start_time and stop_time
				boost::posix_time::time_duration time_difference = stop_time - start_time;
				
				// Print runtime
				std::cout << "\tUptime: " << time_difference.total_milliseconds() << "ms" << std::endl;
				
				// Print Relator count
				std::cout << "\tRelators: " << global_relator_size << std::endl;
				
				// Print Balanced_presentation count
				std::cout << "\tBalanced_presentations: " << global_balanced_presentation_size << std::endl;  
				
				// Print Average Relator length
				std::cout << "\tAverage Relator Length: " << (static_cast<double>(global_relator_length)/global_relator_size) << std::endl; 
				
				// Print Average Relator length
				std::cout << "\tAverage Balanced_presentation Length: " << g_relators_count*(static_cast<double>(global_relator_length)/global_relator_size) << std::endl; 
			}
			
			// Obtain size of s_balanced_presentation_queue
			queue_size_type queue_size = s_balanced_presentation_queue.size();
			
			// Schedule tasks on thread_pool
			for(queue_size_type index = 0; index < queue_size; ++index)
				thread_pool.schedule(boost::bind(obtain_children,&in_values));
			
			// Wait until all children have been obtained
			thread_pool.wait();
			
			// Loop over processes and do our hand rolled all to all to save on memory
			for(unsigned int process = 0; process < communicator.size(); ++process)
			{
				// Determine destinaion of send
                int destinaion = (communicator.rank() + process) % communicator.size();
				
				// Determine source of recieve
				int source = (communicator.rank() - process + communicator.size()) % communicator.size();
				
				// Define requests
				boost::mpi::request requests[2];
				
				// Start recieve from source
				requests[0] = communicator.irecv(source,0,out_values[source]);
				
				// Start send to destinaion
				requests[1] = communicator.isend(destinaion,0,in_values[destinaion]);
				
				// Wait on requests
				boost::mpi::wait_all(requests, requests + 2);
				
				// Delete all Balanced_presentation's in in_values[destinaion]
				for(Itr itr = in_values[destinaion].begin(); itr != in_values[destinaion].end(); ++itr)
					thread_pool.schedule(boost::bind(delete_balanced_presentation,(*itr)));
				
                // Clear in_values[destinaion] to prevent invalid pointers hanging around
				thread_pool.schedule(boost::bind(clear_list,&in_values[destinaion]));
			}
            
            // Loop over out_values
            for(int process = 0; process < communicator.size(); ++process)
            {
                // Loop over elements at index
                for(Itr itr = out_values[process].begin(); itr != out_values[process].end(); ++itr)
                {
					// Schedule a thread to insert the current element
					thread_pool.schedule(boost::bind(insert_balanced_presentation,*itr,&m_is_trivial,&m_trivial_presentation));
                }
            }
			
			// Wait until all elements have been inserted
			thread_pool.wait();
            
            // Define bool indicating if there exists a trivial presentation globally
            bool global_is_trivial = boost::mpi::all_reduce(communicator,m_is_trivial,std::logical_or<bool>());
            
            // If there is globally a trivial presentation
            if(global_is_trivial)
            {
                // Flag the search as trivial
                m_is_trivial = true;
                
                // Break while(true)
                break;
            }
            
            // Define bool indicating if there exist new local presentation's
            bool new_local_presentations = !s_balanced_presentation_queue.empty();

            // Define bool indicating if there exist new global presentation's
            bool new_global_presentations = boost::mpi::all_reduce(communicator,new_local_presentations,std::logical_or<bool>());
            
            // If there are globally no new presentations, the original presentation contradicts the AC conjecture
            if(!new_global_presentations)
                break;
            
            // Clear out_values to prevent invalid pointers hanging around
            for(unsigned int index = 0; index < out_values.size(); ++index)
				thread_pool.schedule(boost::bind(clear_list,&out_values[index]));
			
			// Wait until all lists have been cleared
			thread_pool.wait();
        }
    }
    
    
    void Searcher::print_derivation() const
    {
        // If the presentation is not AC trivial, do nothing
        if(!m_is_trivial)
            return;
		
		// Define string to hold derivation
		std::string derivation;
        
        // Define the world communicator in which we reside
        boost::mpi::communicator communicator;
        
        // Set current Balanced_presentation
        const Balanced_presentation *bp = m_trivial_presentation;
        
        // Loop forever
        while(true)
        {
            // Define bool to indicate if we are done
            bool done = false;
            
            // Define vector to hold values to send
            std::vector< std::pair<const Balanced_presentation*,std::string> > in_values(communicator.size());
            
            // Define vector to hold values to receive
            std::vector< std::pair<const Balanced_presentation*,std::string> > out_values(communicator.size());
            
            // If bp is not null
            if(bp)
            {
                // Add bp to the derivation
				derivation = bp->to_string() + derivation;
             
                // If there is a parent to bp 
                if(bp->get_parent())
                {
                    // Add bp to in_values
                    in_values[bp->get_parent_process()] = std::pair<const Balanced_presentation*,std::string>(bp,derivation);
                }
                else
                {
                    // Indicate we are done
                    done = true;
					
					// Print out the derivation
					std::cout << std::endl << "Derivation:" << std::endl;
					
					// Print out the derivation
					std::cout << derivation;
                }
            }
            
            // If we are done, break the while(true)
            if(boost::mpi::all_reduce(communicator,done,std::logical_or<bool>()))
                break;
            
            // Send in_values to apropos host and receive out_values
            boost::mpi::all_to_all(communicator,in_values,out_values);
            
            // Null out bp
            bp = 0;
            
            // Loop over out_values
            for(unsigned int process = 0; process < out_values.size(); ++process)
            {
                // If out_values[process] is not null
                if(out_values[process].first)
                {
                    // Set bp to the parent of the last printed bp
                    bp = out_values[process].first->get_parent();
					
                    // Set derivation to the current derivation
                    derivation = out_values[process].second;
                    
                    // Delete out_values[process].first, newed up in all_to_all
                    if(communicator.rank() != out_values[process].first->get_process())
                        delete out_values[process].first;
                    
                    // Break out of for, a child has only one parent
                    break;
                }
            }
        }
    }
	
	void obtain_children(std::vector< std::list<Balanced_presentation*> > *in_values)
	{
		// Define Balanced_presentation
		Balanced_presentation *parent = 0;
		
		// Define scope for queue lock
		{
			// Lock s_queue_mutex
			boost::lock_guard<boost::mutex> lock_guard(s_queue_mutex);
			
			// Obtain the next Balanced_presentation
			parent = s_balanced_presentation_queue.front();
			
			// Pop balanced_presentation
			s_balanced_presentation_queue.pop();
		}
		
		// Obtain children of parent
		std::list<Balanced_presentation*> children = Balanced_presentation_nursery::get_children(parent);
		
		// Loop over children
		for(Itr itr = children.begin(); itr != children.end(); ++itr)
		{
			// Lock s_in_values_mutex
			boost::lock_guard<boost::mutex> lock_guard(s_in_values_mutex);
			
			// Place children in apropos place in in_values
			(*in_values)[(*itr)->get_process()].push_back((*itr));
		}
	}
	
	void clear_list(std::list<Balanced_presentation*> *list)
	{
		list->clear();
	}
	
	void delete_balanced_presentation(Balanced_presentation *balanced_presentation)
	{
		// Delete Relators
		for(unsigned int relator = 0; relator < g_relators_count; ++relator)
			delete balanced_presentation->get_relator(relator);
		
		// Delete Balanced_presentation
		delete balanced_presentation;
	}
	
	void insert_balanced_presentation(Balanced_presentation *balanced_presentation,bool *is_trivial,Balanced_presentation **trivial_presentation)
	{
		// Attempt to insert balanced_presentation into the tree
		Balanced_presentation *bp = Binary_tree<Balanced_presentation>::insert(balanced_presentation);
		
		// If insertion worked, i.e. if balanced_presentation was not previously in the tree
		if(!bp)
		{
			// Loop over Relators
			for(unsigned int relator = 0; relator < g_relators_count; ++relator)
			{
				// Attempt to insert relator into the tree
				Relator *rel = Binary_tree<Relator>::insert(balanced_presentation->get_relator(relator));
				
				// If insertion did not work, i.e. if the rel was previously in the tree
				if(rel)
				{
					// Lock m_mutex as we are modifying balanced_presentation which is in the tree
					boost::lock_guard<boost::mutex> lock_guard(Binary_tree<Balanced_presentation>::m_mutex);
					
					// Delete the current relator
					delete balanced_presentation->get_relator(relator);
					
					// Replace it with rel, saving memory
					balanced_presentation->set_relator(rel,relator);
				}
			}
			
			// Define scope for queue lock
			{
				// Lock s_queue_mutex
				boost::lock_guard<boost::mutex> lock_guard(s_queue_mutex);
				
				// Push the balanced_presentation onto the queue
				s_balanced_presentation_queue.push(balanced_presentation);
			}
			
			// Save pointer to first trivial presentation found
			if(!(*is_trivial) && balanced_presentation->is_trivial())
				(*trivial_presentation) = balanced_presentation;
			
			// Flip m_is_trivial (TODO: Remove this CPU sink)
			(*is_trivial) = (*is_trivial) || balanced_presentation->is_trivial();
		}
		// If insertion did not work, i.e. if balanced_presentation was previously in the tree
		else
		{
			// Delete Relators
			for(unsigned int relator = 0; relator < g_relators_count; ++relator)
				delete balanced_presentation->get_relator(relator);
			
			// Delete the Balanced_presentation balanced_presentation
			delete balanced_presentation;
		}
	}
}
