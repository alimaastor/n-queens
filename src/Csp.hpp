
#include <algorithm>
#include <iostream>


template <class IdType, class DataType>
unsigned int Csp<IdType, DataType>::getNumberOfUnassignedVar() const
{
    return std::count_if(this->m_varMap.begin(), this->m_varMap.end(),
            [&](std::pair<IdType, CspVar<DataType>> mapEntry)->bool{
                return !mapEntry.second.isAssigned();
            });
}

template <class IdType, class DataType>
bool Csp<IdType, DataType>::isComplete() const
{
    return (this->getNumberOfUnassignedVar() == 0) && (this->isConsistent());
}

template <class IdType, class DataType>
IdType Csp<IdType, DataType>::getUnassignedVar() const
{
    return std::find_if(this->m_varMap.begin(), this->m_varMap.end(),
            [&](std::pair<IdType, CspVar<DataType>> mapEntry)->bool{
                return !mapEntry.second.isAssigned();
            })->first;
}

template <class IdType, class DataType>
void Csp<IdType, DataType>::setVar(IdType varId, DataType value)
{
    this->m_varMap[varId].setValue(value);
}

template <class IdType, class DataType>
bool Csp<IdType, DataType>::isConsistent() const
{
    return std::all_of(this->m_binaryConstrains.cbegin(), this->m_binaryConstrains.cend(),
            [&](const CspBinaryConstrain<IdType, DataType>& constrain)->bool{
                return constrain.isValid(this->m_varMap);
            });
}

template <class IdType, class DataType>
void Csp<IdType, DataType>::addBinaryConstrain(const CspBinaryConstrain<IdType, DataType>& constrain)
{
    auto it1 = this->m_varMap.find(constrain.m_idFirst);
    auto it2 = this->m_varMap.find(constrain.m_idSecond);
    if ((it1 == this->m_varMap.end()) || (it2 == this->m_varMap.end()))
    {
        throw std::runtime_error("Variable(s) of binary constrain has not been defined.");
    }

    this->m_binaryConstrains.push_back(constrain);
}

template <class IdType, class DataType>
void Csp<IdType, DataType>::addVar(IdType varId)
{
    CspVar<DataType> newVar;
    this->m_varMap[varId] = newVar;
}

