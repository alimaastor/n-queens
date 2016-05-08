
#include <algorithm>

template <class IdType, class DataType>
unsigned int Csp<IdType, DataType>::getNumberOfUnassignedVar() const
{
    return std::count_if(this->m_varMap.begin(), this->m_varMap.end(),
            [&](std::pair<IdType, CspVar<DataType>> mapEntry)->bool{
                return !mapEntry.second.isUnassigned();
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
                return mapEntry.second.isUnassigned();
            }).first;
}

template <class IdType, class DataType>
void Csp<IdType, DataType>::setVar(IdType varId, DataType value)
{
    this->m_varMap[varId].setValue(value);
}

template <class IdType, class DataType>
bool Csp<IdType, DataType>::isConsistent() const
{
    return std::all_of(this->m_constrains.begin(), this->m_constrains.end(),
            [&](const CspBinaryConstrain<IdType, DataType>& constrain)->bool{
                return constrain.isValid(this->m_varMap);
            });
}

template <class IdType, class DataType>
void Csp<IdType, DataType>::addBinaryConstrain(const CspBinaryConstrain<IdType, DataType>& constrain)
{
    this->m_binaryConstrains.push_back(constrain);
}

template <class IdType, class DataType>
void Csp<IdType, DataType>::addVar(IdType varId)
{
    CspVar<DataType> newVar;
    this->m_varMap[varId] = newVar;
}

