
#ifndef CSP_VAR_H
#define CSP_VAR_H

#include <map>

template <class DataType>
class CspVariable
{
public:
    CspVariable()
        : m_isAssigned(false),
          m_value()
    {}

    bool isAssigned() { return this->m_isAssigned; }
    
    void setValue(const DataType& value)
    {
        this->m_isAssigned = true;
        this->m_value = value;
    }

    DataType getValue() const { return this->m_value; }

private:
    bool m_isAssigned;
    DataType m_value;
};

template <class DataType>
using CspVar = CspVariable<DataType>;

template <class IdType, class DataType>
using CspVarMap = std::map<IdType, CspVar<DataType>>;

#endif /* CSP_VARIABLE_H */

