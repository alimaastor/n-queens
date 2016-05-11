
#ifndef CSP_DOMAIN_H
#define CSP_DOMAIN_H

#include <vector>
#include <algorithm>

template <class DataType>
class CspDomain
{
public:
    CspDomain(const std::vector<DataType>& domainValues)
        : m_domainValues(domainValues)
    {}

    CspDomain()
        : m_domainValues()
    {}

    std::vector<DataType> getValues() const
    {
        return this->m_domainValues;
    }

    void addValue(const DataType& value)
    {
        this->m_domainValues.push_back(value);
    }

    void addValues(const std::vector<DataType>& values)
    {
        this->m_domainValues = values;
    }

    void removeValue(const DataType& value)
    {
        this->m_domainValues.erase(std::remove(this->m_domainValues.begin(), this->m_domainValues.end(), value), this->m_domainValues.end());
    }

    bool isEmpty()
    {
        return this->m_domainValues.empty();
    }

private:
    std::vector<DataType> m_domainValues;
};

#endif /* CSP_DOMAIN_H */

