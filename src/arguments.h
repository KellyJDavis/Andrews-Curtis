//
//  arguments.h
//  Andrews-Curtis Conjecture
//
//  Created by Kelly Davis on 8/19/11.
//
//

#ifndef Andrews_Curtis_Conjecture_arguments_h
#define Andrews_Curtis_Conjecture_arguments_h


#include <string>


namespace andrews_curtis
{
    
    ///
    /// This class encapsulates the command line arguments and
    /// provides an interface to these arguments for the rest
    /// of system.
    ///
    class Arguments
    {
    public:
        ///
        /// Constructs an Arguments from the user supplied
        /// command line arguments.
        ///
        /// \param argc The number of command line arguments
        /// \param argv The command line arguments
        ///
        Arguments(int argc,char *argv[]);
        
        ///
        /// Returns a bool indicating if the command line
        /// arguments are valid.
        ///
        /// \return A bool indicating argument validity
        ///
        bool is_valid() const;
        
        ///
        /// Returns a human readable string describing a
        /// reason the command line arguments are invalid.
        /// If the command line arguments are valid, the
        /// empty string is returned.
        ///
        /// \return A string describing a problem with the
        ///         command line arguments
        ///
        const std::string &get_message() const;
        
        ///
        /// Returns a return code apropos for any problems
        /// that arose as a result of the command line 
        /// arguments
        ///
        /// \return A return code apropos for command line
        ///         argument problems.
        ///
        int get_return_code() const;
        
        ///
        /// Obtain the user supplied relators
        ///
        /// \return The user supplied relators
        char **get_relators() const;
        
        ///
        /// Obtain the user supplied generators
        ///
        /// \return The user supplied generators
        ///
        char *get_generators() const;
        
    private:    
        /// A string describing the problem with the args
        std::string m_message;
        
        /// A bool indicating validity
        bool m_is_valid;  
        
        /// User supplied relators
        char **m_relators;
        
        /// User supplied generators
        char *m_generators;
    };
    
}

#include "arguments-inl.h"

#endif
