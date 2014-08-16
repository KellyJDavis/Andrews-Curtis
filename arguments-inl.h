//
//  arguments-inl.h
//  Andrews-Curtis Conjecture
//
//  Created by Kelly Davis on 8/19/11.
//
//

#ifndef Andrews_Curtis_Conjecture_arguments_inl_h
#define Andrews_Curtis_Conjecture_arguments_inl_h


namespace andrews_curtis
{
    inline bool Arguments::is_valid() const
    {
        return m_is_valid;
    }
    
    inline const std::string &Arguments::get_message() const
    {
        return m_message;
    }
    
    inline int Arguments::get_return_code() const
    {
        return m_is_valid ? 0 : 1;
    }
    
    inline char **Arguments::get_relators() const
    {
        return m_relators;
    }
    
    inline char *Arguments::get_generators() const
    {
        return m_generators;
    }
}

#endif
