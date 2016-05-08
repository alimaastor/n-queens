
#ifndef CSP_H
#define CSP_H

#include "CspVar.h"
#include "CspConstrain.h"

#include <vector>

template <class IdType, class DataType>
class Csp
{
public:
    Csp()
        : m_varMap()
    {}

    bool isComplete() const;

    void addBinaryConstrain(const CspBinaryConstrain<IdType, DataType>& constrain);

    bool isConsistent() const;

    IdType getUnassignedVar() const;

    void addVar(IdType varId);
    void setVar(IdType varId, DataType value);

private:
    unsigned int getNumberOfUnassignedVar() const;

    CspVarMap<IdType, DataType> m_varMap;
    std::vector<CspBinaryConstrain<IdType, DataType>> m_binaryConstrains;
};

#include "Csp.hpp"

#endif /* CSP_H */

