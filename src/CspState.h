
#ifndef CSP_STATE_H
#define CSP_STATE_H

#include <map>
#include <algorithm>
#include <stdexcept>
#include <iostream>

#include "CspVar.h"

template <class IdType, class DataType>
class CspState
{
public:
    CspState()
        : m_varMap()
    {}

    CspState& operator=(const CspState<IdType, DataType>& other)
    {
        auto it = other.m_varMap.begin();
        while(it != other.m_varMap.end())
        {
            this->m_varMap[it->first] = it->second;
            ++it;
        }

        return *this;
    }

    size_t getNumberOfUnassignedVar() const
    {
        return std::count_if(this->m_varMap.begin(), this->m_varMap.end(),
            [](const std::pair<IdType, CspVar<DataType>>& mapEntry)->bool{
                return !mapEntry.second.isAssigned();
            });
    }

    IdType getIdUnassignedVar() const
    {
        return std::find_if(this->m_varMap.begin(), this->m_varMap.end(),
                [](const std::pair<IdType, CspVar<DataType>>& mapEntry)->bool{
                    return !mapEntry.second.isAssigned();
                 })->first;
    }

    IdType getIdVarMaxRemainingValues() const
    {
        return std::max_element(this->m_varMap.begin(), this->m_varMap.end(),
                [](const std::pair<IdType, CspVar<DataType>>& mapEntry1, const std::pair<IdType, CspVar<DataType>>& mapEntry2)->bool{
                    return (mapEntry1.second.domainLen() < mapEntry2.second.domainLen());
                })->first;
    }

    IdType getIdVarMinRemainingValues() const
    {
        auto list = std::remove_copy_if(this->m_varMap.begin(), this->m_varMap.end(),
                [](const std::pair<IdType, CspVar<DataType>>& mapEntry)->bool{
                    return mapEntry.second.isAssigned();
                });
        return std::min_element(list,
                [](const std::pair<IdType, CspVar<DataType>>& mapEntry1, const std::pair<IdType, CspVar<DataType>>& mapEntry2)->bool{
                    return (mapEntry1.second.domainLen() < mapEntry2.second.domainLen());
                })->first;
    }

    bool isVarAssigned(IdType varId) const
    {
        auto mapEntry = this->m_varMap.find(varId);
        if (mapEntry == this->m_varMap.end())
        {
            throw std::runtime_error("Cannot check: Variable does not exist");
        }
        return mapEntry->second.isAssigned();
    }

    CspDomain<DataType> getVarDomain(const IdType& varId) const
    {
        auto mapEntry = this->m_varMap.find(varId);
        if (mapEntry == this->m_varMap.end())
        {
            throw std::runtime_error("Cannot get domain: Variable does not exist");
        }
        return mapEntry->second.getDomain();
    }

    bool isDomainEmpty(const IdType& varId) const
    {
        auto mapEntry = this->m_varMap.find(varId);
        if (mapEntry == this->m_varMap.end())
        {
            throw std::runtime_error("Cannot get value: Variable does not exist");
        }
        return mapEntry->second.isDomainEmpty();
    }

    DataType getValue(const IdType& varId) const
    {
        auto mapEntry = this->m_varMap.find(varId);
        if (mapEntry == this->m_varMap.end())
        {
            throw std::runtime_error("Cannot get value: Variable does not exist");
        }
        return mapEntry->second.getValue();
    }

    void setVar(const IdType& varId, const DataType& value)
    {
        auto mapEntry = this->m_varMap.find(varId);
        if (mapEntry == this->m_varMap.end())
        {
            throw std::runtime_error("Cannot set value: Variable does not exist");
        }
        mapEntry->second.setValue(value);
    }

    void addVar(const IdType& varId, const CspDomain<DataType>& cspDomain)
    {
        CspVar<DataType> newVar(cspDomain);
        this->m_varMap[varId] = newVar;
    }

    void removeValueFromDomain(const IdType& varId, const DataType& tailValue)
    {
        auto mapEntry = this->m_varMap.find(varId);
        if (mapEntry == this->m_varMap.end())
        {
            throw std::runtime_error("Cannot set value: Variable does not exist");
        }
        mapEntry->second.removeFromDomain(tailValue);
    }

    std::vector<std::pair<IdType, DataType>> getRaw() const
    {
        std::vector<std::pair<IdType, DataType>> solution;
        for (const auto& var : this->m_varMap)
        {
            if (var.second.isAssigned())
            {
                solution.push_back(std::make_pair(var.first, var.second.getValue()));
            }
        }
        return solution;
    }

private:
    std::map<IdType, CspVar<DataType>> m_varMap;
};

#endif /* CSP_STATE_H */

