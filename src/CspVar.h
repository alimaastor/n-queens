
#ifndef CSP_VAR_H
#define CSP_VAR_H

#include <map>

#include "CspDomain.h"

template <class DataType>
class CspVar
{
public:
    CspVar(const CspDomain<DataType>& cspDomain)
        : m_isAssigned(false),
          m_domain(cspDomain),
          m_value()
    {}

    CspVar()
        : m_isAssigned(false),
          m_domain(),
          m_value()
    {}

    void setDomain(const CspDomain<DataType>& cspDomain)
    {
        this->m_domain = cspDomain;
    }

    bool isAssigned() const
    {
        return this->m_isAssigned;
    }
 
    bool isDomainEmpty() const
    {
        return this->m_domain.isEmpty();
    }
    
    void setValue(const DataType& value)
    {
        this->m_isAssigned = true;
        this->m_value = value;
    }

    DataType getValue() const
    {
        return this->m_value;
    }

    CspDomain<DataType> getDomain() const
    {
        return this->m_domain;
    }

    void removeFromDomain(const DataType& value)
    {
        this->m_domain.removeValue(value);
    }
private:
    bool m_isAssigned;
    CspDomain<DataType> m_domain;
    DataType m_value;
};

#endif /* CSP_VARIABLE_H */

