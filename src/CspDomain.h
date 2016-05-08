
#ifndef CSP_DOMAIN_H
#define CSP_DOMAIN_H

#include <vector>

template <class DataType>
class CspDomain
{
public:
    CspDomain()
        : m_domainValues()
    {}

    std::vector<DataType> getValues() const { return this->m_domainValues; }
    void addValue(const DataType& value) { this->m_domainValues.push_back(value); }
    void addValues(const std::vector<DataType>& values) { this->m_domainValues = values; }

private:
    std::vector<DataType> m_domainValues;
};

#endif /* CSP_DOMAIN_H */

