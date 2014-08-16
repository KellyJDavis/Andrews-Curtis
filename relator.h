//
//  relator.h
//  Andrews-Curtis Conjecture
//
//  Created by Kelly Davis on 8/20/11.
//
//

#ifndef Andrews_Curtis_Conjecture_relator_h
#define Andrews_Curtis_Conjecture_relator_h


#include <string>

#include <boost/dynamic_bitset.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/split_member.hpp>


namespace andrews_curtis
{
    /// Forward declaration
    template <class T> class Binary_tree;
    
    /// 
    /// An instance of this class representes a relator.  A relator is a word
    /// in the generators and their inverses.
    ///
    class Relator
    {
    public:
        //
        // Default construct this Relator, with an empy word.
        //
        Relator();
        
        //
        // Construct this Relator from a const char* this is used to initialize
        // a Relator from the arguments suppied by the user via the commandline.
        //
        // \param relator The const char* used to init this Relator
        //
        Relator(const char *relator);
        
        ///
        /// Inverts the Relator in place
        ///
        void invert();
        
        ///
        /// Conjugtes the Relator by the passed generator. The passed generator
        /// is identified by an int. The int's 1,2,3,... correspond to a,b,c...
        /// while the int's -1,-2,-3... correspond to the inverses of a,b,c...
        ///
        /// \param generator The generator to conjugate by
        ///
        void conjugate(int generator);
        
        ///
        /// Multiplies the Relator on the right by the passed Relator
        ///
        /// \param relator The Relator to multiply on the right with
        ///
        void multiply(const Relator *relator);
        
        ///
        /// Returns the length of the relator
        ///
        /// \return The length of the relator
        ///
        size_t get_length() const;
        
        //
        // Casts this Relator to an std::size_t
        //
        operator std::size_t() const;
        
        ///
        /// Produces human readable string representation of this Relator
        ///
        /// \return A human readable string representation of this Relator
        ///
        std::string to_string() const;
        
        ///
        /// Operator assignment
        ///
        /// \param rhs The right hand side of the assignement
        /// \return *this
        ///
        Relator &operator=(const Relator &rhs);
        
        ///
        /// Implementation of ==
        ///
        /// \param rhs The Relator to compare to
        /// \return The bool indicating the result of ==
        ///
        bool operator==(const Relator &rhs) const;
        
        ///
        /// Implementation of !=
        ///
        /// \param rhs The Relator to compare to
        /// \return The bool indicating the result of !=
        ///
        bool operator!=(const Relator &rhs) const;
        
        ///
        /// Implementation of <
        ///
        /// \param rhs The Relator to compare to
        /// \return The bool indicating the result of <
        ///
        bool operator<(const Relator &rhs) const;
        
        ///
        /// Implementation of <=
        ///
        /// \param rhs The Relator to compare to
        /// \return The bool indicating the result of <=
        ///
        bool operator<=(const Relator &rhs) const;
        
        ///
        /// Implementation of >
        ///
        /// \param rhs The Relator to compare to
        /// \return The bool indicating the result of >
        ///
        bool operator>(const Relator &rhs) const;
        
        ///
        /// Implementation of >=
        ///
        /// \param rhs The Relator to compare to
        /// \return The bool indicating the result of >=
        ///
        bool operator>=(const Relator &rhs) const;
        
    private:
        /// Note: The relator payload m_relator is represented as a dynamic_bitset
        /// A more conventional means of representing the relator would have been
        /// through a size, capacity, and a int* where the int* points to an array
        /// of ints each of which represents a letter in the relator. However, as
        /// the set of allowed letters is usually very small, 4 for example is the
        /// most common number, using an int to hold four values is wasting 61bits
        /// on a 64bit machine. So, for 10's to 100's of millions of Relators with
        /// an average length of 40 this wastes 3.05 to 30.50GB! Yes, GB!!!
        
        /// The relator
        boost::dynamic_bitset<> m_relator;
        
        
        /// Note: In addition, an instance of this class representes a node in a
        /// binary search tree. Normally this would be an odd situation, but, as
        /// all Relators are eventually stored in a binary search tree, this ac-
        /// tually saves memory, dispite being odd from an OO perspective.
        
        /// Indicate Binary_tree<Relator> is a friend
        friend class Binary_tree<Relator>;
        
        /// Note: Having the Relator be a Relator and a node in a ST allows for 
        /// saving of one pointer per Relator. If all relators were stored in an
        /// external ST class, then for any Relator there would be a Node which
        /// would contain two pointers, one for the let and right Node,  as well
        /// as a pointer to the contained Relator. This pointer to the contained
        /// Relator is not needed in our case as the Node is the Relator itself. 
        /// With 10's to 100's of millions of Relators this will save us from 80
        /// to 800 MB or more! (One 64 bit pointer per Relator.)
        
        /// Left subtree of this Relator's scapegoat tree
        Relator *m_left;
        
        /// Right subtree of this Relator's scapegoat tree
        Relator *m_right;
        
        
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

#include "relator-inl.h"

#endif
