//
//  balanced_presentation.h
//  Andrews-Curtis Conjecture
//
//  Created by Kelly Davis on 8/20/11.
//
//

#ifndef Andrews_Curtis_Conjecture_balanced_presentation_h
#define Andrews_Curtis_Conjecture_balanced_presentation_h


#include <string>

#include <boost/serialization/access.hpp>
#include <boost/serialization/split_member.hpp>


namespace andrews_curtis
{
    // Forward declarations
    class Relator;
    template <class T> class Binary_tree;
    
    ///
    /// An instance of this class represents a balanced presentation. A balanced
    /// presentation is an array of relators such that the number of relators is
    /// equal to the number of generators that were used to create the relators.
    ///
    class Balanced_presentation
    {
    public:
        ///
        /// Default constructor
        ///
        Balanced_presentation();
        
        ///
        /// Destructor
        ///
        ~Balanced_presentation();
        
        ///
        /// Gets the parent of this Balanced_presentation
        ///
        /// \return The parent of this Balanced_presentation
        ///
        const Balanced_presentation*  const &get_parent() const;
        
        ///
        /// Obtains the process on which the parent of this instance should live
        ///
        /// \return The process on which the parent of this instance should live
        ///
        unsigned int get_parent_process() const;
        
        
        ///
        /// Gets the indicated relator of this Balanced_presentation
        ///
        /// \param index The index of the relator to get
        /// \return The indicated relator
        ///
        Relator *get_relator(int unsigned &index) const;
        
        ///
        /// Sets the indicated relator of this Balanced_presentation
        ///
        /// \param relator The new relator
        /// \param index The index of the new Relator
        void set_relator(Relator *relator, int unsigned &index);
        
        ///
        /// Obtains the process on which this instance should live
        ///
        /// \return The process on which this instance should live
        ///
        unsigned int get_process() const;
        
        ///
        /// Returns a bool indicating if this presentation is trivial
        ///
        /// \return A bool indicating if this presentation is trivial
        ///
        bool is_trivial() const;
        
        ///
        /// Produces human readable string representation of this presentation
        ///
        /// \return A human readable string representation of this presentation
        ///
        std::string to_string() const;
        
        ///
        /// Returns the length of this presentation
        ///
        /// \return The length of this presentation
        ///
        size_t get_length() const;
        
        ///
        /// Operator assignment
        ///
        /// \param rhs The right hand side of the assignement
        /// \return *this
        ///
        Balanced_presentation &operator=(const Balanced_presentation &rhs);
        
        ///
        /// Implementation of ==
        ///
        /// \param rhs The Balanced_presentation to compare to
        /// \return The bool indicating the result of ==
        ///
        bool operator==(const Balanced_presentation &rhs) const;
        
        ///
        /// Implementation of !=
        ///
        /// \param rhs The Balanced_presentation to compare to
        /// \return The bool indicating the result of !=
        ///
        bool operator!=(const Balanced_presentation &rhs) const;
        
        ///
        /// Implementation of <
        ///
        /// \param rhs The Balanced_presentation to compare to
        /// \return The bool indicating the result of <
        ///
        bool operator<(const Balanced_presentation &rhs) const;
        
        ///
        /// Implementation of <=
        ///
        /// \param rhs The Balanced_presentation to compare to
        /// \return The bool indicating the result of <=
        ///
        bool operator<=(const Balanced_presentation &rhs) const;
        
        ///
        /// Implementation of >
        ///
        /// \param rhs The Balanced_presentation to compare to
        /// \return The bool indicating the result of >
        ///
        bool operator>(const Balanced_presentation &rhs) const;
        
        ///
        /// Implementation of >=
        ///
        /// \param rhs The Balanced_presentation to compare to
        /// \return The bool indicating the result of >=
        ///
        bool operator>=(const Balanced_presentation &rhs) const;
        
        
    private:
        /// The relators of this Balanced_presentation
        Relator **m_relators;
        
        /// The parent of this Balanced_presentation
        const Balanced_presentation *m_parent;
        
        /// The process of the parent of this Balanced_presentation
        unsigned int m_parent_process;
        
        
        /// Indicate Binary_tree<Balanced_presentation> is a friend
        friend class Binary_tree<Balanced_presentation>;
        
        /// Note: Having the Balanced_presentation be a Balanced_presentation and
        /// a node in a BST allows for saving of one pointer per instance. If all
        /// Balanced_presentations were stored in an external BST class, then for
        /// any Balanced_presentation there would be a Node which would contain 2
        /// pointers, one for the left and right Node,as well as a pointer to the
        /// contained Balanced_presentation. The pointer to the contained element
        /// is not needed in our case, the Node is the Balanced_presentation.  If 
        /// we have 10-100 million Balanced_presentations, this will save us from
        /// 80-800 MB or more! (One 64 bit pointer per Balanced_presentation.)
        
        /// Left subtree of this Balanced_presentation's binary search tree
        Balanced_presentation *m_left;
        
        /// Right subtree of this Balanced_presentation's binary search tree
        Balanced_presentation *m_right;
        
        
        // Indicate boost::serialization::access is a friend for serialization
        friend class boost::serialization::access;
        
        //
        // This method serializes this instance to the passed Archive using the
        // specified verison of serialization
        //
        // \param archive The archive to serialize to
        // \param version The version of serialization to use
        //
        template<class Archive> void save(Archive &archive,unsigned int version) const;
        
        //
        // This method deserializes this instance to the passed Archive using the
        // specified verison of deserialization
        //
        // \param archive The archive to deserialize from
        // \param version The version of deserialization to use
        //
        template<class Archive> void load(Archive &archive,unsigned int version);
        
        // Generates code which invokes the save or load in the aropos situation
        BOOST_SERIALIZATION_SPLIT_MEMBER()
    };
}

#include "balanced_presentation-inl.h"

#endif
